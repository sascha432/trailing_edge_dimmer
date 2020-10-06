/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include "i2c_slave.h"
#include "helpers.h"
#if USE_EEPROM
#include <EEPROM.h>
#include <crc16.h>
#endif

// size reduction
//23704 - 2.1.3
//23492 - helpers.cpp / get_signature

config_t config;
uint16_t eeprom_position = 0;
unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;

void fade(int8_t channel, int16_t from, int16_t to, float time);

void reset_config() {
    config = {};
    register_mem.data.cfg = {};
    register_mem.data.version = DIMMER_VERSION_WORD;
    register_mem.data.cfg.max_temp = 75;
    register_mem.data.cfg.bits.restore_level = true;
    register_mem.data.cfg.bits.report_metrics = true;
    register_mem.data.cfg.fade_in_time = 7.5;
    register_mem.data.cfg.temp_check_interval = 2;
    register_mem.data.cfg.zero_crossing_delay_ticks = DIMMER_US_TO_TICKS(DIMMER_ZC_DELAY_US, DIMMER_TMR2_TICKS_PER_US);
    register_mem.data.cfg.minimum_on_time_ticks = DIMMER_US_TO_TICKS(DIMMER_MIN_ON_TIME_US, DIMMER_TMR1_TICKS_PER_US);
    register_mem.data.cfg.adjust_halfwave_time_ticks = DIMMER_US_TO_TICKS(DIMMER_ADJUST_HALFWAVE_US, DIMMER_TMR1_TICKS_PER_US);
    register_mem.data.cfg.internal_1_1v_ref = INTERNAL_VREF_1_1V;
    register_mem.data.cfg.report_metrics_max_interval = 5;
#ifdef INTERNAL_TEMP_OFS
    register_mem.data.cfg.int_temp_offset = INTERNAL_TEMP_OFS;
#endif
#if DIMMER_USE_LINEAR_CORRECTION
    register_mem.data.cfg.linear_correction_factor = 1.0;
#endif
    config.crc16 = UINT16_MAX - 1;
    memcpy(&config.cfg, &register_mem.data.cfg, sizeof(config.cfg));
}

unsigned long get_eeprom_num_writes(unsigned long cycle, uint16_t position)
{
    return ((EEPROM.length() / sizeof(config_t)) * (cycle - 1)) + (position / sizeof(config_t));
}

// initialize EEPROM and wear leveling
void init_eeprom()
{
    EEPROM.begin();
    config.eeprom_cycle = 1;
    eeprom_position = 0;
    _D(5, debug_printf_P(PSTR("init eeprom cycle=%ld, position %d\n"), (long)config.eeprom_cycle, (int)eeprom_position));

    for(uint16_t i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
    }
    config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg));
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

    auto crc = crc16_update(&config.cfg, sizeof(config.cfg));

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
    config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg));

    EEPROM.begin();
    EEPROM.get(eeprom_position, temp_config);
    if (memcmp(&config, &temp_config, sizeof(config)) != 0 || force) {
        _D(5, debug_printf_P(PSTR("old eeprom write cycle %lu, position %u, "), (unsigned long)config.eeprom_cycle, eeprom_position));
        eeprom_position += sizeof(config);
        if (eeprom_position + sizeof(config) >= EEPROM.length()) { // end reached, start from beginning and increase cycle counter
            eeprom_position = 0;
            config.eeprom_cycle++;
            config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg)); // recalculate CRC
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
    dimmer_scheduled_calls.write_eeprom = false;

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
    if (!dimmer_scheduled_calls.write_eeprom) { // no write scheduled
        _D(5, debug_printf_P(PSTR("scheduling eeprom write cycle, last write %d seconds ago\n"), (int)(lastWrite / 1000UL)));
        eeprom_write_timer = millis() + ((lastWrite > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
        dimmer_scheduled_calls.write_eeprom = true;
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
    uint16_t sum = 0;
    for (uint8_t i = 0; i < 25; i++) {
        delay(1);
        if (i == 15) { // start after 15ms
            sum = 0;
        }
        ADCSRA |= _BV(ADSC);
        while (bit_is_set(ADCSRA, ADSC)) ;
        sum += ADCW;
    }
    return (((sum / 10.0) - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (float)(register_mem.data.cfg.int_temp_offset / 4.0f);
}

#endif

#if HAVE_READ_VCC

#if HAVE_EXT_VCC

uint16_t read_vcc()
{
    analogReference(INTERNAL);
    analogRead(VCC_PIN);
    uint32_t sum = 0;
    for(uint8_t i = 0; i < 25; i++) {
        delay(1);
        if (i == 15) { // start after 15ms
            sum = 0;
        }
        sum += analogRead(VCC_PIN);
    }

    // Vout = (Vs * R2) / (R1 + R2)
    // ((ADCValue / 1024) * (Vref * 1000)) / N = (Vs * R2) / (R1 + R2)
    // Vs=((125*ADCValue*R2+125*ADCValue*R1)*Vref)/(128*N*R2)

    // R1=12K
    // R2=3K
    // N=10
    // ((ADCValue / 1024) * (Vref * 1000)) / N = (Vs * 3000) / (12000 + 3000)
    // Vs=(625*ADCValue*Vref)/(128*N)

    return (625UL * sum * register_mem.data.cfg.internal_1_1v_ref) / 1280U;
}

#else
#define read_vcc()      read_vcc_int()

#endif

// read VCC in mV
uint16_t read_vcc_int() {
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); // analogReference(DEFAULT) = AVCC with external capacitor at AREF pin
    uint16_t sum = 0;
    for (uint8_t i = 0; i < 20; i++) {
        delay(1);
        if (i == 10) { // start after 10ms
            sum = 0;
        }
        ADCSRA |= _BV(ADSC);
        while (bit_is_set(ADCSRA, ADSC));
        sum += ADCW;
    }
    return (10UL * 1000UL * 1024UL) * register_mem.data.cfg.internal_1_1v_ref / (float)sum;
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
    MCUInfo_t mcu;
    get_mcu_type(mcu);

    Serial_printf_P(PSTR("sig=%02x-%02x-%02x,fuses=l:%02x,h:%02x,e:%02x"), mcu.sig[0], mcu.sig[1], mcu.sig[2], mcu.fuses[0], mcu.fuses[1], mcu.fuses[2]);
    if (mcu.name) {
        Serial_printf_P(PSTR(",MCU=%S"), mcu.name);
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

dimmer_scheduled_calls_t dimmer_scheduled_calls = {};
unsigned long metrics_next_event = 0;

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
    dimmer_scheduled_calls.print_info = true;
#endif
}

#if USE_TEMPERATURE_CHECK

unsigned long next_temp_check = 0;

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
    if (dimmer_scheduled_calls.print_info && millis() >= frequency_wait_timeout) {
        dimmer_scheduled_calls.print_info = false;
        display_dimmer_info();
        register_mem.data.errors = {};
    }
#endif

#if HAVE_READ_VCC
    if (dimmer_scheduled_calls.read_vcc) {
        dimmer_scheduled_calls.read_vcc = false;
        register_mem.data.vcc = read_vcc();
        _D(5, debug_printf_P(PSTR("Scheduled: read vcc=%u\n"), register_mem.data.vcc));
    }
#endif
#if HAVE_READ_INT_TEMP
    if (dimmer_scheduled_calls.read_int_temp) {
        dimmer_scheduled_calls.read_int_temp = false;
        register_mem.data.temp = get_internal_temperature();
        _D(5, debug_printf_P(PSTR("Scheduled: read int. temp=%.3f\n"), register_mem.data.temp));
    }
#endif
#if HAVE_NTC
    if (dimmer_scheduled_calls.read_ntc_temp) {
        dimmer_scheduled_calls.read_ntc_temp = false;
        register_mem.data.temp = get_ntc_temperature();
        _D(5, debug_printf_P(PSTR("Scheduled: read ntc=%.3f\n"), register_mem.data.temp));
    }
#endif

    if (dimmer_scheduled_calls.report_error) {
        dimmer_scheduled_calls.report_error = false;

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_FREQUENCY_WARNING);
        Wire.write(0xff);
        Wire.write(reinterpret_cast<const uint8_t *>(&register_mem.data.errors), sizeof(register_mem.data.errors));
        Wire.endTransmission();
        _D(5, debug_printf_P(PSTR("Report error\n")));
    }

#if HAVE_PRINT_METRICS
    if (dimmer_scheduled_calls.print_metrics && millis() >= print_metrics_timeout) {
        print_metrics_timeout = millis() + PRINT_METRICS_REPEAT;
        Serial.print(F("+REM="));
        #if HAVE_NTC
            Serial_printf_P(PSTR("NTC=%.3f,"), get_ntc_temperature());
        #endif
        #if HAVE_READ_INT_TEMP
            Serial_printf_P(PSTR("int.temp=%.3f,"), get_internal_temperature());
        #endif
        #if HAVE_EXT_VCC
            Serial_printf_P(PSTR("VCC=%u,VCCi=%u,"), read_vcc(), read_vcc_int());
        #elif HAVE_READ_VCC
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
    if (millis() >= next_fading_event_check)  {
        send_fading_completion_events();
        next_fading_event_check = millis() + 100;
    }
#endif

#if USE_EEPROM
    if (dimmer_scheduled_calls.write_eeprom && millis() >= eeprom_write_timer) {
        _write_config();
    }
#endif

#if ZC_MAX_TIMINGS
    if (zc_timings_output && millis() >= print_zc_timings) {
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
    if (millis() >= next_temp_check) {

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

        if (register_mem.data.cfg.bits.report_metrics && millis() >= metrics_next_event) {
            metrics_next_event = millis() + (register_mem.data.cfg.report_metrics_max_interval * 1000UL);
            dimmer_metrics_t event = {
                (uint8_t)current_temp,
#if HAVE_READ_VCC
                read_vcc(),
#else
                0,
#endif
#if FREQUENCY_TEST_DURATION
                dimmer_get_frequency(),
#else
                NAN,
#endif
#if HAVE_READ_INT_TEMP
                int_temp,
#else
                NAN,
#endif
#if HAVE_NTC
                ntc_temp
#else
                NAN
#endif
            };
            Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
            Wire.write(DIMMER_METRICS_REPORT);
            Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
            Wire.endTransmission();
        }
    }
#endif
}

#endif
