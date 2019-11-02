/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include "i2c_slave.h"
#include "helpers.h"
#if USE_EEPROM
#include <EEPROM.h>
#include "crc16.h"
#endif

config_t config;
uint16_t eeprom_position = 0;
unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;

void fade(int8_t channel, int16_t from, int16_t to, float time);

void reset_config() {
    memset(&config, 0, sizeof(config));
    memset(&register_mem.data.cfg, 0, sizeof(register_mem.data.cfg));
    register_mem.data.version = DIMMER_VERSION_WORD;
    register_mem.data.cfg.max_temp = 90;
    register_mem.data.cfg.bits.restore_level = true;
    register_mem.data.cfg.bits.report_metrics = true;
    register_mem.data.cfg.fade_in_time = 7.5;
    register_mem.data.cfg.temp_check_interval = 2;
    register_mem.data.cfg.zero_crossing_delay_ticks = DIMMER_US_TO_TICKS(DIMMER_ZC_DELAY_US, DIMMER_TMR2_TICKS_PER_US);
    register_mem.data.cfg.minimum_on_time_ticks = DIMMER_US_TO_TICKS(DIMMER_MIN_ON_TIME_US, DIMMER_TMR1_TICKS_PER_US);
    register_mem.data.cfg.adjust_halfwave_time_ticks = DIMMER_US_TO_TICKS(DIMMER_ADJUST_HALFWAVE_US, DIMMER_TMR1_TICKS_PER_US);
    register_mem.data.cfg.internal_1_1v_ref = INTERNAL_VREF_1_1V;
    register_mem.data.cfg.report_metrics_max_interval = 30;
#ifdef INTERNAL_TEMP_OFS
    register_mem.data.cfg.int_temp_offset = INTERNAL_TEMP_OFS;
#endif
#if DIMMER_USE_LINEAR_CORRECTION
    register_mem.data.cfg.linear_correction_factor = 1.0;
#endif
    config.crc16 = UINT16_MAX - 1;
    memcpy(&config.cfg, &register_mem.data.cfg, sizeof(config.cfg));
}

unsigned long get_eeprom_num_writes(unsigned long cycle, uint16_t position) {
    return ((EEPROM.length() / sizeof(config_t)) * (cycle - 1)) + (position / sizeof(config_t));
}

// initialize EEPROM and wear leveling
void init_eeprom() {
    EEPROM.begin();
    config.eeprom_cycle = 1;
    eeprom_position = 0;
    _D(5, debug_printf_P(PSTR("init eeprom cycle=%ld, position %d\n"), (long)config.eeprom_cycle, (int)eeprom_position));

    for(uint16_t i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
    }
    config.crc16 = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg));
    EEPROM.put(eeprom_position, config);
    EEPROM.end();
}

#if DEBUG
void debug_dump_config() {
    _D(5, debug_printf_P(PSTR("CRC %04x\n"), crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg))));
    _D(5, debug_printf_P(PSTR("Report temp. and VCC %d\n"), register_mem.data.cfg.bits.report_metrics));
    _D(5, debug_printf_P(PSTR("Restore level %d\n"), register_mem.data.cfg.bits.restore_level));
    _D(5, debug_printf_P(PSTR("Temperature alert triggered %d\n"), register_mem.data.cfg.bits.temperature_alert));
    _D(5, debug_printf_P(PSTR("Fade in time %.3f\n"), register_mem.data.cfg.fade_in_time));
    _D(5, debug_printf_P(PSTR("Max. temp %u\n"), register_mem.data.cfg.max_temp));
    _D(5, debug_printf_P(PSTR("Temp. check interval %u\n"), register_mem.data.cfg.temp_check_interval));
    _D(5, debug_printf_P(PSTR("Linear correction factor %.6f\n"), register_mem.data.cfg.linear_correction_factor));
    _D(5, debug_printf_P(PSTR("ZC delay %u\n"), register_mem.data.cfg.zero_crossing_delay_ticks));
    _D(5, debug_printf_P(PSTR("Min. on time ticks %u\n"), register_mem.data.cfg.minimum_on_time_ticks));
    _D(5, debug_printf_P(PSTR("Adj. halfwave time ticks %u\n"), register_mem.data.cfg.adjust_halfwave_time_ticks));
    _D(5, debug_printf_P(PSTR("Internal 1.1V ref %.6f\n"), register_mem.data.cfg.internal_1_1v_ref));
    _D(5, debug_printf_P(PSTR("Internal temp. sensor offset %.1f\n"), register_mem.data.cfg.int_temp_offset / 10.0f));
}
#endif

void read_config() {

    uint16_t pos = 0;
    uint32_t cycle, max_cycle = 0;

    eeprom_position = 0;

    // find last configuration
    // the first byte is the cycle, which increases by one once the last position has been written
    while((pos + sizeof(config_t)) < EEPROM.length()) {
        EEPROM.get(pos, cycle);
        _D(5, debug_printf_P(PSTR("eeprom cycle %ld position %d id\n"), cycle, pos));
        if (cycle >= max_cycle) {
            eeprom_position = pos; // last position with highest cycle number is the config written last
            max_cycle = cycle;
        }
        pos += sizeof(config_t);
    }
    EEPROM.get(eeprom_position, config);
    EEPROM.end();

    auto crc = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg));

    Serial_printf_P(PSTR("+REM=EEPROMR,c=%lu,p=%u,n=%lu,crc=%04x=%04x\n"), (unsigned long)max_cycle, eeprom_position, get_eeprom_num_writes(max_cycle, eeprom_position), config.crc16, crc);

    if (config.crc16 != crc) {
        Serial.println(F("+REM=EEPROM CRC error"));
        _D(5, debug_printf_P(PSTR("read_config, CRC mismatch %04x<>%04x, eeprom cycle %lu, position %u\n"), config.crc16, crc, (unsigned long)max_cycle, eeprom_position));
        reset_config();
        init_eeprom();
    }
    else {
        _D(5, debug_printf_P(PSTR("read_config, eeprom cycle %lu, position %u\n"), config.crc16, (unsigned long)max_cycle, eeprom_position));
    }

    memcpy(&register_mem.data.cfg, &config.cfg, sizeof(config.cfg));
    register_mem.data.version = DIMMER_VERSION_WORD;

#if DEBUG
    _D(5, debug_printf_P(PSTR("---Read config---\n")));
    debug_dump_config();
    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
        _D(5, debug_printf_P(PSTR("Channel %u: %d\n"), i, config.level[i]));
    }
#endif

#if DIMMER_USE_LINEAR_CORRECTION
    dimmer_set_lcf(register_mem.data.cfg.linear_correction_factor);
#endif
}

void _write_config(bool force) {
    config_t temp_config;
    dimmer_eeprom_written_t event;

#if DEBUG
    _D(5, debug_printf_P(PSTR("---Read config---\n")));
    debug_dump_config();
    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
        _D(5, debug_printf_P(PSTR("Channel %u: %d\n"), i, register_mem.data.level[i]));
    }
#endif

    memcpy(&config.cfg, &register_mem.data.cfg, sizeof(config.cfg));
    memcpy(&config.level, &register_mem.data.level, sizeof(config.level));
    config.crc16 = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg));

    EEPROM.begin();
    EEPROM.get(eeprom_position, temp_config);
    if (memcmp(&config, &temp_config, sizeof(config)) != 0 || force) {
        _D(5, debug_printf_P(PSTR("old eeprom write cycle %lu, position %u, "), (unsigned long)config.eeprom_cycle, eeprom_position));
        eeprom_position += sizeof(config);
        if (eeprom_position + sizeof(config) >= EEPROM.length()) { // end reached, start from beginning and increase cycle counter
            eeprom_position = 0;
            config.eeprom_cycle++;
            config.crc16 = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg)); // recalculate CRC
        }
        _D(5, debug_printf_P(PSTR("new cycle %lu, position %u\n"), (unsigned long)config.eeprom_cycle, eeprom_position));
        EEPROM.put(eeprom_position, config);
        eeprom_write_timer = millis();
        event.bytes_written = sizeof(config);
    } else {
        _D(5, debug_printf_P(PSTR("configuration didn't change, skipping write cycle\n")));
        eeprom_write_timer = millis();
        event.bytes_written = 0;
    }
    EEPROM.end();
    dimmer_remove_scheduled_call(EEPROM_WRITE);

    event.write_cycle = config.eeprom_cycle;
    event.write_position = eeprom_position;

    _D(5, debug_printf_P(PSTR("eeprom written event: cycle %lu, pos %u, written %u\n"), (unsigned long)event.write_cycle, event.write_position, event.bytes_written));
    Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
    Wire.write(DIMMER_EEPROM_WRITTEN);
    Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
    Wire.endTransmission();

    Serial_printf_P(PSTR("+REM=EEPROMW,c=%lu,p=%u,n=%lu,w=%u,crc=%04x\n"), (unsigned long)event.write_cycle, eeprom_position, get_eeprom_num_writes(event.write_cycle, eeprom_position), event.bytes_written, config.crc16);
}

void write_config() {
    long lastWrite = millis() - eeprom_write_timer;
    if (!dimmer_is_call_scheduled(EEPROM_WRITE)) { // no write scheduled
        _D(5, debug_printf_P(PSTR("scheduling eeprom write cycle, last write %d seconds ago\n"), (int)(lastWrite / 1000UL)));
        eeprom_write_timer = millis() + ((lastWrite > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
        dimmer_schedule_call(EEPROM_WRITE);
    } else {
        _D(5, debug_printf_P(PSTR("eeprom write cycle already scheduled in %d seconds\n"), (int)(lastWrite / -1000L)));
    }
}

#if HAVE_READ_INT_TEMP

bool is_Atmega328PB;

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
float get_internal_temperature() {
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    delay(40); // 20 was not enough. It takes quite a while when switching from reading VCC to temp.
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return ((ADCW - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (float)(register_mem.data.cfg.int_temp_offset / 4.0f);
}

#endif

#if HAVE_READ_VCC

// read VCC in mV
uint16_t read_vcc() {
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(40);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return (1000.0f * 1024.0f) * register_mem.data.cfg.internal_1_1v_ref / (float)ADCW;
}

#endif

#if HAVE_NTC

uint16_t read_ntc_value(uint8_t num) {
    uint32_t value = analogRead(NTC_PIN);
    for(uint8_t i = 1; i < num; i++) {
        delay(1);
        value += analogRead(NTC_PIN);
    }
    return value / num;
}

float convert_to_celsius(uint16_t value) {
    double steinhart;
    steinhart = 1023 / (float)value - 1;
    steinhart *= NTC_SERIES_RESISTANCE;
    steinhart /= NTC_NOMINAL_RESISTANCE;
    steinhart = log(steinhart);
    steinhart /= NTC_BETA_COEFF;
    steinhart += 1.0 / (NTC_NOMINAL_TEMP + 273.15);
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    return steinhart;
}

float get_ntc_temperature() {
#ifdef FAKE_NTC_VALUE
    return FAKE_NTC_VALUE;
#else
    return convert_to_celsius(read_ntc_value(5)) + (float)(register_mem.data.cfg.ntc_temp_offset / 4.0f);
#endif
}

#endif

#if USE_EEPROM
void restore_level() {
    if (register_mem.data.cfg.bits.restore_level) {
        for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
            fade(i, DIMMER_FADE_FROM_CURRENT_LEVEL, config.level[i], register_mem.data.cfg.fade_in_time);
        }
    }
}
#endif

#if DIMMER_I2C_SLAVE

void rem() {
#if SERIAL_I2C_BRDIGE
    Serial.print(F("+REM="));
#endif
}

#if HIDE_DIMMER_INFO == 0

void display_dimmer_info() {

    rem();
    Serial.println(F("MOSFET Dimmer " DIMMER_VERSION " " __DATE__ " " __TIME__ " " DIMMER_INFO));
    Serial.flush();

    rem();
    char *mcu;
    uint8_t *sig, *fuses;
    auto buffer = get_mcu_type(mcu, sig, fuses);
    Serial_printf_P(PSTR("sig=%02x-%02x-%02x,fuses=l:%02x,h:%02x,e:%02x"), *sig, *(sig + 1), *(sig + 2), *fuses, *(fuses + 1), *(fuses + 2));
    if (*mcu) {
        Serial_printf_P(PSTR(",mcu=%s"), mcu);
    }
    Serial_printf_P(PSTR("@%uMhz\n"), (unsigned)(F_CPU / 1000000UL));
    Serial.flush();

    rem();
    Serial.print(F("options="));
#if USE_EEPROM
    Serial_printf_P(PSTR("EEPROM=%lu,"), get_eeprom_num_writes(config.eeprom_cycle, eeprom_position));
#endif
#if HAVE_NTC
    Serial_printf_P(PSTR("NTC=A%u,"), NTC_PIN - A0);
#endif
#if HAVE_READ_INT_TEMP
    Serial.print(F("Int.Temp,"));
#endif
#if USE_TEMPERATURE_CHECK
    Serial.print(F("Temp.Chk,"));
#endif
#if HAVE_READ_VCC
    Serial.print(F("VCC,"));
#endif
#if DIMMER_USE_FADING
    Serial.print(F("Fade,"));
#endif
#if DIMMER_USE_LINEAR_CORRECTION
    Serial.print(F("LCF,"));
#endif
    Serial_printf_P(PSTR("ACFrq=%u,"), DIMMER_AC_FREQUENCY);
#if SERIAL_I2C_BRDIGE
    Serial.print(F("Pr=UART,"));
#else
    Serial.print(F("Pr=I2C,"));
#endif
#if HAVE_FADE_COMPLETION_EVENT
    Serial.print(F("CE=1,"));
#endif
    Serial_printf_P(PSTR("Addr=%02x,Pre=%u/%u,"),
        DIMMER_I2C_ADDRESS,
        DIMMER_TIMER1_PRESCALER, DIMMER_TIMER2_PRESCALER
    );
    Serial.print(F("Ticks="));
    Serial_print_float(DIMMER_TMR1_TICKS_PER_US);
    Serial.print('/');
    Serial_print_float(DIMMER_TMR2_TICKS_PER_US);
    Serial_printf_P(PSTR(",Lvls=%u,P="),
        DIMMER_MAX_LEVEL
    );
    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        Serial.print((int)dimmer_pins[i]);
        if (i < DIMMER_CHANNELS - 1) {
            Serial.print(',');
        }
    }
    Serial.println();
    Serial.flush();

    rem();
    Serial.print(F("values="));
    Serial_printf_P(PSTR("Restore=%u,ACFrq=%.3f,ref11="), register_mem.data.cfg.bits.restore_level, dimmer_get_frequency());
    Serial_print_float(register_mem.data.cfg.internal_1_1v_ref, 4, 4);
    Serial.print(',');
#if HAVE_NTC
    Serial_printf_P(PSTR("NTC=%.2f"), get_ntc_temperature());
    #if USE_TEMPERATURE_CHECK
        Serial_printf_P(PSTR("/%+u"), register_mem.data.cfg.ntc_temp_offset);
    #endif
    Serial.print(',');
#endif
#if HAVE_READ_INT_TEMP
    Serial_printf_P(PSTR("Int.Temp=%.2f"), get_internal_temperature());
    #if USE_TEMPERATURE_CHECK
        Serial_printf_P(PSTR("/%+u"), register_mem.data.cfg.int_temp_offset);
    #endif
    Serial.print(',');
#endif
#if USE_TEMPERATURE_CHECK
    Serial_printf_P(PSTR("max.tmp=%u/%us,metrics=%u,"), register_mem.data.cfg.max_temp, register_mem.data.cfg.temp_check_interval, register_mem.data.cfg.report_metrics_max_interval);
#endif
#if HAVE_READ_VCC
    Serial_printf_P(PSTR("VCC=%.3f,"), read_vcc() / 1000.0);
#endif
#if DIMMER_USE_LINEAR_CORRECTION
    Serial.print(F("LFC="));
    Serial_print_float(register_mem.data.cfg.linear_correction_factor);
    Serial.print(',');
#endif
    Serial_printf_P(PSTR("Min.on=%u,Adj.hw=%u,ZC.delay=%u\n"),
        register_mem.data.cfg.minimum_on_time_ticks,
        register_mem.data.cfg.adjust_halfwave_time_ticks,
        register_mem.data.cfg.zero_crossing_delay_ticks
    );
    Serial.flush();
}

unsigned long frequency_wait_timeout;

#endif

void setup() {

    uint8_t buf[3];
    is_Atmega328PB = memcmp_P(get_signature(buf), PSTR("\x1e\x95\x16"), 3) == 0;

    Serial.begin(DEFAULT_BAUD_RATE);
    #if SERIAL_I2C_BRDIGE && DEBUG
    _debug_level = 9;
    #endif

#if HIDE_DIMMER_INFO == 0
    rem();
    Serial.println(F("BOOT"));
    Serial.flush();
#endif

    dimmer_i2c_slave_setup();

    read_config();
    dimmer_setup();

#if HAVE_NTC
    pinMode(NTC_PIN, INPUT);
#endif

#if USE_EEPROM
    restore_level();
#endif

#if HIDE_DIMMER_INFO == 0
    // run main loop till the frequency is available
    frequency_wait_timeout = millis() + min(550, FREQUENCY_TEST_DURATION);
    dimmer_schedule_call(PRINT_DIMMER_INFO);
#endif
}

uint16_t dimmer_scheduled_calls = TYPE_NONE;

#if USE_TEMPERATURE_CHECK

unsigned long next_temp_check = 0;
dimmer_metrics_event_t metrics_event = { 0, 0, NAN, NAN, NAN };

#endif

#if HAVE_PRINT_METRICS

unsigned long print_metrics_timeout;

#endif

#if ZC_MAX_TIMINGS

unsigned long print_zc_timings = 0;

#endif


#if HAVE_FADE_COMPLETION_EVENT

unsigned long next_fading_event_check = 0;

void send_fading_completion_events() {

    FadingCompletionEvent_t buffer[DIMMER_CHANNELS];
    FadingCompletionEvent_t *ptr = buffer;

    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        cli(); // dimmer.fadingCompleted is modified inside an interrupt and copying needs to be an atomic operation
        if (dimmer.fadingCompleted[i] != INVALID_LEVEL) {
            auto level = dimmer.fadingCompleted[i];
            dimmer.fadingCompleted[i] = INVALID_LEVEL;
            sei();

            ptr->channel = i;
            ptr->level = level;
            ptr++;
        }
        else {
            sei();
        }
    }

    if (ptr != buffer) {
        _D(5, debug_printf_P(PSTR("sending fading completion event for %u channel(s)\n"), ptr - buffer));

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_FADING_COMPLETE);
        Wire.write(reinterpret_cast<const uint8_t *>(buffer), (reinterpret_cast<const uint8_t *>(ptr) - reinterpret_cast<const uint8_t *>(buffer)));
        Wire.endTransmission();
    }

}

#endif

void loop() {

#if HIDE_DIMMER_INFO == 0
    if (dimmer_is_call_scheduled(PRINT_DIMMER_INFO) && millis() > frequency_wait_timeout) {
        dimmer_remove_scheduled_call(PRINT_DIMMER_INFO);
        display_dimmer_info();
        memset(&register_mem.data.errors, 0, sizeof(register_mem.data.errors));
    }
#endif

#if HAVE_READ_VCC
    if (dimmer_is_call_scheduled(READ_VCC)) {
        dimmer_remove_scheduled_call(READ_VCC);
        register_mem.data.vcc = read_vcc();
        _D(5, debug_printf_P(PSTR("Scheduled: read vcc=%u\n"), register_mem.data.vcc));
    }
#endif
#if HAVE_READ_INT_TEMP
    if (dimmer_is_call_scheduled(READ_INT_TEMP)) {
        dimmer_remove_scheduled_call(READ_INT_TEMP);
        register_mem.data.temp = get_internal_temperature();
        _D(5, debug_printf_P(PSTR("Scheduled: read int. temp=%.3f\n"), register_mem.data.temp));
    }
#endif
#if HAVE_NTC
    if (dimmer_is_call_scheduled(READ_NTC_TEMP)) {
        dimmer_remove_scheduled_call(READ_NTC_TEMP);
        register_mem.data.temp = get_ntc_temperature();
        _D(5, debug_printf_P(PSTR("Scheduled: read ntc=%.3f\n"), register_mem.data.temp));
    }
#endif

    if (dimmer_is_call_scheduled(FREQUENCY_ERROR)) {

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_FREQUENCY_WARNING);
        Wire.write(dimmer_is_call_scheduled(FREQUENCY_HIGH) ? 1 : 0);
        Wire.write(reinterpret_cast<const uint8_t *>(&register_mem.data.errors), sizeof(register_mem.data.errors));
        Wire.endTransmission();
        dimmer_remove_scheduled_call(FREQUENCY_ERROR);

        if (dimmer_is_call_scheduled(FREQUENCY_HIGH)) {
            if (!register_mem.data.cfg.bits.frequency_high) {
                register_mem.data.cfg.bits.frequency_high = true;
                write_config();
            }
        }
        else {
            if (!register_mem.data.cfg.bits.frequency_low) {
                register_mem.data.cfg.bits.frequency_low = true;
                write_config();
            }
        }

        _D(5, debug_printf_P(PSTR("Frequency warning: %s\n"), dimmer_is_call_scheduled(FREQUENCY_HIGH) ? "HIGH" : "LOW"));
    }

#if HAVE_PRINT_METRICS
    if (dimmer_is_call_scheduled(PRINT_METRICS) && millis() > print_metrics_timeout) {
        print_metrics_timeout = millis() + PRINT_METRICS_REPEAT;
        Serial.print(F("+REM="));
        #if HAVE_NTC
            Serial_printf_P(PSTR("NTC=%.3f,"), get_ntc_temperature());
        #endif
        #if HAVE_READ_INT_TEMP
            Serial_printf_P(PSTR("int.temp=%.3f,"), get_internal_temperature());
        #endif
        #if HAVE_READ_VCC
            Serial_printf_P(PSTR("VCC=%u,"), read_vcc());
        #endif
        #if FREQUENCY_TEST_DURATION
            Serial_printf_P(PSTR("frq=%.3f,"), dimmer_get_frequency());
        #endif
        Serial.print(F("lvl="));
        for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
            Serial.print(register_mem.data.level[i]);
            if (i < DIMMER_CHANNELS - 1) {
                Serial.print(',');
            }
        }
        Serial.println();
        Serial.flush();
    }
#endif

#if HAVE_FADE_COMPLETION_EVENT
    if (millis() > next_fading_event_check)  {
        send_fading_completion_events();
        next_fading_event_check = millis() + 100;
    }
#endif

#if USE_EEPROM
    if (dimmer_is_call_scheduled(EEPROM_WRITE) && millis() > eeprom_write_timer) {
        _write_config();
    }
#endif

#if ZC_MAX_TIMINGS
    if (zc_timings_output && millis() > print_zc_timings) {
        auto tmp = zc_timings[0]; // copy first timing before resetting counter
        auto counter = zc_timings_counter;
        zc_timings_counter = 0;
        print_zc_timings = millis() + 1000;
        if (counter) {
            Serial_printf_P(PSTR("+REM=ZC,%lx "), tmp);
            for(uint8_t i = 1; i < counter; i++) {
                Serial_printf("%lx ", zc_timings[i] - tmp); // use relative time to reduce output
                tmp = zc_timings[i];
            }
            Serial.println();
        }
    }
#endif

#if USE_TEMPERATURE_CHECK
    if (millis() > next_temp_check) {

        int current_temp;
#if HAVE_NTC
        float ntc_temp = get_ntc_temperature();
        current_temp = ntc_temp;
#endif
#if HAVE_READ_INT_TEMP
        float int_temp = get_internal_temperature();
        current_temp = max(current_temp, (int)int_temp);
#endif
        next_temp_check = millis() + (register_mem.data.cfg.temp_check_interval * 1000UL);
        if (register_mem.data.cfg.max_temp && current_temp > (int)register_mem.data.cfg.max_temp) {
            fade(-1, DIMMER_FADE_FROM_CURRENT_LEVEL, 0, 10);
            register_mem.data.cfg.bits.temperature_alert = 1;
            write_config();
            if (register_mem.data.cfg.bits.report_metrics) {
                Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
                Wire.write(DIMMER_TEMPERATURE_ALERT);
                Wire.write((uint8_t)current_temp);
                Wire.write(register_mem.data.cfg.max_temp);
                Wire.endTransmission();
            }
        }
        if (register_mem.data.cfg.bits.report_metrics) {
            bool has_significant_changes = false;
            dimmer_metrics_t metrics = { (uint8_t)current_temp, 0, NAN, NAN, NAN };
#if HAVE_READ_VCC
            metrics.vcc = read_vcc();
            if (metrics_event.vcc != 0 && (abs(metrics_event.vcc - metrics.vcc) > 300)) {       // 0.3V
                has_significant_changes = true;
            }
#endif
#if FREQUENCY_TEST_DURATION
            metrics.frequency = dimmer_get_frequency();
            if (!isnan(metrics_event.frequency) && (abs(metrics_event.frequency - metrics.frequency) >= 5.0f)) {        // 5Hz
                has_significant_changes = true;
            }
#endif
#if HAVE_NTC
            metrics.ntc_temp = ntc_temp;
            if (!isnan(metrics_event.ntc_temp) && (abs(metrics_event.ntc_temp - metrics.ntc_temp) >= 3.0f)) {        // 3°C
                has_significant_changes = true;
            }
#endif
#if HAVE_READ_INT_TEMP
            metrics.internal_temp = int_temp;
            if (!isnan(metrics_event.int_temp) && (abs(metrics_event.int_temp - metrics.internal_temp) >= 3.0f)) {        // 3°C
                has_significant_changes = true;
            }
#endif
            if (millis() > metrics_event.next_event || has_significant_changes) {
                metrics_event.next_event = millis() + (register_mem.data.cfg.report_metrics_max_interval * 1000UL);
                metrics_event.vcc = metrics.vcc;
                metrics_event.frequency = metrics.frequency;
                metrics_event.int_temp = metrics.internal_temp;
                metrics_event.ntc_temp = metrics.ntc_temp;

                Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
                Wire.write(DIMMER_METRICS_REPORT);
                Wire.write(reinterpret_cast<const uint8_t *>(&metrics), sizeof(metrics));
                Wire.endTransmission();
            }
        }
    }
#endif
}

#endif
