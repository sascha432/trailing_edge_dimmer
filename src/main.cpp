/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include <util/atomic.h>
#include "i2c_slave.h"
#include "helpers.h"
#include "cubic_interpolation.h"
#include <EEPROM.h>
#include "crc16.h"

config_t config;
uint16_t eeprom_position = 0;
unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;

void fade(int8_t channel, int16_t from, int16_t to, float time);

void reset_config()
{
    config.clear();
    register_mem.data.errors = {};
    register_mem.data.cfg = {};
    register_mem.data.version = DIMMER_VERSION_WORD;
    register_mem.data.cfg.max_temp = DIMMER_MAX_TEMP;
    register_mem.data.cfg.bits.restore_level = true;
    register_mem.data.cfg.bits.report_metrics = true;
    register_mem.data.cfg.fade_in_time = 7.5;
    register_mem.data.cfg.temp_check_interval = 2;
    register_mem.data.cfg.zero_crossing_delay_ticks = DIMMER_US_TO_TICKS(DIMMER_ZC_DELAY_US, DIMMER_TMR1_TICKS_PER_US);
    register_mem.data.cfg.min_on_ticks = DIMMER_US_TO_TICKS(DIMMER_MIN_ON_TIME_US, DIMMER_TMR1_TICKS_PER_US);
    register_mem.data.cfg.max_on_ticks = DIMMER_US_TO_TICKS(DIMMER_MAX_ON_TIME_US, DIMMER_TMR1_TICKS_PER_US);
    register_mem.data.cfg.internal_1_1v_ref = INTERNAL_VREF_1_1V;
    register_mem.data.cfg.report_metrics_max_interval = 10;
#ifdef INTERNAL_TEMP_OFS
    register_mem.data.cfg.int_temp_offset = INTERNAL_TEMP_OFS;
#endif
// #if DIMMER_CUBIC_INTERPOLATION
//     register_mem.data.cfg.bits.cubic_interpolation = 1;
// #endif
    config.crc16 = UINT16_MAX - 1;
//    memcpy(&config.cfg, &register_mem.data.cfg, sizeof(config.cfg));
}

void bzero(void *ptr, size_t size)
{
    memset(ptr, 0, size);
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
    config.crc16 = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg));
    EEPROM.put(eeprom_position, config);
    EEPROM.end();
}

bool eeprom_crc_error = false;

void read_config()
{
    uint16_t pos = 0;
    uint32_t cycle;
    unsigned long eeprom_max_cycle = 0;

    eeprom_position = 0;

    // find last configuration
    // the first byte is the cycle, which increases by one once the last position has been written
    while((pos + sizeof(config_t)) < EEPROM.length()) {
        EEPROM.get(pos, cycle);
        _D(5, debug_printf_P(PSTR("eeprom cycle %ld position %d id\n"), cycle, pos));
        if (cycle >= eeprom_max_cycle) {
            eeprom_position = pos; // last position with highest cycle number is the config written last
            eeprom_max_cycle = cycle;
        }
        pos += config.size();
    }
    config.read(eeprom_position);
    EEPROM.end();

    auto crc = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg));

    Serial_printf_P(PSTR("+REM=EEPROMR,c=%lu,p=%u,n=%lu,crc=%04x=%04x\n"), eeprom_max_cycle, eeprom_position, get_eeprom_num_writes(eeprom_max_cycle, eeprom_position), config.crc16, crc);

    if (config.crc16 != crc) {
        Serial.println(F("+REM=EEPROM CRC error"));
        _D(5, debug_printf_P(PSTR("read_config, CRC mismatch %04x<>%04x, eeprom cycle %lu, position %u\n"), config.crc16, crc, eeprom_max_cycle, eeprom_position));
        reset_config();
        init_eeprom();
        eeprom_crc_error = true;
    }
    else {
        _D(5, debug_printf_P(PSTR("read_config, eeprom cycle %lu, position %u\n"), config.crc16, eeprom_max_cycle, eeprom_position));
    }

    register_mem.data.version = DIMMER_VERSION_WORD;
}

void _write_config(bool force)
{
    DIMMER_RESPONSE_EEPROM_WRITTEN_t event;

    //memcpy(&config.cfg, &register_mem.data.cfg, sizeof(config.cfg));
    memcpy(&config.level, &register_mem.data.level, sizeof(config.level));
    config.crc16 = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg));

    EEPROM.begin();

    if (force || config.compare(eeprom_position)) {
        _D(5, debug_printf_P(PSTR("old eeprom write cycle %lu, position %u, "), (unsigned long)config.eeprom_cycle, eeprom_position));
        eeprom_position += config.size();
        if (eeprom_position + config.size() >= EEPROM.length()) { // end reached, start from beginning and increase cycle counter
            eeprom_position = 0;
            config.eeprom_cycle++;
            config.crc16 = crc16_calc(reinterpret_cast<const uint8_t *>(&config.cfg), sizeof(config.cfg)); // recalculate CRC
        }
        _D(5, debug_printf_P(PSTR("new cycle %lu, position %u\n"), (unsigned long)config.eeprom_cycle, eeprom_position));
        event.bytes_written += config.write(eeprom_position);
        eeprom_write_timer = millis();
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
    Wire.write(DIMMER_RESPONSE_EEPROM_WRITTEN);
    Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
    Wire.endTransmission();

    Serial_printf_P(PSTR("+REM=EEPROMW,c=%lu,p=%u,n=%lu,w=%u,crc=%04x\n"), (unsigned long)event.write_cycle, eeprom_position, get_eeprom_num_writes(event.write_cycle, eeprom_position), event.bytes_written, config.crc16);
}

void write_config()
{
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
float get_internal_temperature()
{
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    delay(40); // 20 was not enough. It takes quite a while when switching from reading VCC to temp.
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return ((ADCW - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (float)(register_mem.data.cfg.int_temp_offset / DIMMER_TEMP_OFFSET_DIVIDER);
}

#endif

#if HAVE_READ_VCC

// read VCC in mV
uint16_t read_vcc()
{
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(40);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return (1000.0f * 1024.0f) * register_mem.data.cfg.internal_1_1v_ref / (float)ADCW;
}

#endif

#if HAVE_NTC

uint16_t read_ntc_value(uint8_t num)
{
    uint32_t value = analogRead(NTC_PIN);
    for(uint8_t i = 1; i < num; i++) {
        delay(1);
        value += analogRead(NTC_PIN);
    }
    return value / num;
}

float convert_to_celsius(uint16_t value)
{
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

float get_ntc_temperature()
{
#ifdef FAKE_NTC_VALUE
    return FAKE_NTC_VALUE;
#else
    return convert_to_celsius(read_ntc_value(5)) + (float)(register_mem.data.cfg.ntc_temp_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
}

#endif

void restore_level()
{
    if (register_mem.data.cfg.bits.restore_level) {
        FOR_CHANNELS(i) {
            fade(i, DIMMER_FADE_FROM_CURRENT_LEVEL, config.level[i], register_mem.data.cfg.fade_in_time);
        }
    }
}

#if DIMMER_I2C_SLAVE

void rem()
{
#if SERIAL_I2C_BRDIGE
    Serial.print(F("+REM="));
#endif
}

void display_dimmer_info()
{
    rem();
    Serial.println(F("MOSFET Dimmer " DIMMER_VERSION " " __DATE__ " " __TIME__ " " DIMMER_INFO));
    Serial.flush();

    rem();
    char *mcu;
    uint8_t *sig, *fuses;
    auto buffer = get_mcu_type(mcu, sig, fuses);
    Serial_printf_P(PSTR("sig=%02x-%02x-%02x,fuses=l:%02x,h:%02x,e:%02x"), *sig, *(sig + 1), *(sig + 2), *fuses, *(fuses + 1), *(fuses + 2));
    if (*mcu) {
        Serial_printf_P(PSTR(",MCU=%s"), mcu);
    }
    Serial_printf_P(PSTR("@%uMhz\n"), (unsigned)(F_CPU / 1000000UL));
    Serial.flush();

    rem();
    Serial.print(F("options="));
    Serial_printf_P(PSTR("EEPROMwr=%lu,"), get_eeprom_num_writes(config.eeprom_cycle, eeprom_position));
#if HAVE_NTC
    // Serial_printf_P(PSTR("NTC=A%u,"), NTC_PIN - A0);
    Serial.print(F("NTC=" _STRINGIFY(NTC_PIN) ","));
#endif
#if HAVE_READ_INT_TEMP && HAVE_READ_VCC
    Serial.print(F("IntTemp,VCC,"));
#else
#if HAVE_READ_INT_TEMP
    Serial.print(F("IntTemp,"));
#endif
#if HAVE_READ_VCC
    Serial.print(F("VCC,"));
#endif
#endif
#if DIMMER_CUBIC_INTERPOLATION
    Serial.print(F("CubicInt,"));
#endif
#if SERIAL_I2C_BRDIGE
    Serial.print(F("Pr=UART,"));
#else
    Serial.print(F("Pr=I2C,"));
#endif
#if HAVE_FADE_COMPLETION_EVENT
    Serial.print(F("CE=1,"));
#endif
    Serial_printf_P(PSTR("Addr=%02x"), DIMMER_I2C_ADDRESS);
    Serial.print(F(",Pre=" _STRINGIFY(DIMMER_TIMER1_PRESCALER) ",Ticks="));
    Serial_print_float(1 / DIMMER_TMR1_TICKS_PER_US);
    Serial.print(F("us,MaxLvls=" _STRINGIFY(DIMMER_MAX_LEVELS) ",GPIO/lvl="));
    FOR_CHANNELS(i) {
        Serial.print((int)dimmer_pins[i]);
        Serial.print('/');
        Serial.print(dimmer_level(i));
        if (i < DIMMER_CHANNELS - 1) {
            Serial.print(',');
        }
    }
    Serial.println();
    Serial.flush();

    rem();
    Serial.print(F("values="));
    Serial_printf_P(PSTR("Restore=%u,Frq=%.3f,Ref11="), register_mem.data.cfg.bits.restore_level, dimmer.getFrequency());
    Serial_print_float(register_mem.data.cfg.internal_1_1v_ref, 4, 4);
    Serial.print(',');
#if HAVE_NTC
    Serial_printf_P(PSTR("NTC=%.2f/%+.1fC,"), get_ntc_temperature(), register_mem.data.cfg.ntc_temp_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
#if HAVE_READ_INT_TEMP
    Serial_printf_P(PSTR("IntTemp=%.2f/%+.1fC,"), get_internal_temperature(), register_mem.data.cfg.int_temp_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
    Serial_printf_P(PSTR("MaxTmp=%u/%us,Metrics=%us,"), register_mem.data.cfg.max_temp, register_mem.data.cfg.temp_check_interval, register_mem.data.cfg.report_metrics_max_interval);
#if HAVE_READ_VCC
    Serial_printf_P(PSTR("VCC=%.3f,"), read_vcc() / 1000.0);
#endif
#if DIMMER_CUBIC_INTERPOLATION
    Serial.print(F("CubInt="));
    cubicInterpolation.printState();
#endif
    Serial_printf_P(PSTR("Min/MaxOn=%u/%.2fus,%u/%.2fus,"),
        register_mem.data.cfg.min_on_ticks,
        DIMMER_MIN_ON_TICKS_TO_US(register_mem.data.cfg.min_on_ticks),
        register_mem.data.cfg.max_on_ticks,
        DIMMER_ADJ_HW_TICKS_TO_US(register_mem.data.cfg.max_on_ticks)
    );
    Serial_printf_P(PSTR("ZC=%d/%.2fus\n"),
        register_mem.data.cfg.zero_crossing_delay_ticks,
        DIMMER_ZC_TICKS_TO_US(register_mem.data.cfg.zero_crossing_delay_ticks)
    );
    rem();
    Serial_printf_P(PSTR("errors=ZCmisfire=%u,EEPROMCrcErr=%u\n"),
        register_mem.data.errors.zc_misfire,
        eeprom_crc_error
    );
    Serial.flush();
}

void setup()
{
    uint8_t buf[3];
    is_Atmega328PB = memcmp_P(get_signature(buf), PSTR("\x1e\x95\x16"), 3) == 0;

    Serial.begin(DEFAULT_BAUD_RATE);
    #if SERIAL_I2C_BRDIGE && DEBUG
    _debug_level = 9;
    #endif

    Serial.println(F("+REM=BOOT"));
    Serial.flush();

// extern void test();
// test();

#if HAVE_NTC
    pinMode(NTC_PIN, INPUT);
#endif

    dimmer_i2c_slave_setup();

    read_config();
    dimmer.begin();

    delay(100);
    Serial.println(F("+REM=Measuring frequency"));
    Serial.flush();
    if (dimmer.measure(10000)) {
        dimmer.enable();
    }
    else {
        Serial.println(F("+REM=timeout"));
        Serial.flush();
    }

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        dimmer_set_level(0, 2048);
        dimmer_set_level(1, 2300);
        dimmer_set_level(2, 2301);
        dimmer_set_level(3, 2301);
    }

    // restore_level(); //TODO remove comment

    display_dimmer_info();
}

uint16_t dimmer_scheduled_calls = TYPE_NONE;

unsigned long next_temp_check = 0;
unsigned long next_event_metrics_event = 0;

#if HAVE_PRINT_METRICS

unsigned long print_metrics_timeout;

#endif

#if HAVE_FADE_COMPLETION_EVENT

unsigned long next_fading_event_check = 0;

void send_fading_completion_events()
{
    FadingCompletionEvent_t buffer[DIMMER_CHANNELS];
    FadingCompletionEvent_t *ptr = buffer;

    FOR_CHANNELS(i) {
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
        Wire.write(DIMMER_RESPONSE_FADING_COMPLETE);
        Wire.write(reinterpret_cast<const uint8_t *>(buffer), (reinterpret_cast<const uint8_t *>(ptr) - reinterpret_cast<const uint8_t *>(buffer)));
        Wire.endTransmission();
    }
}

#endif

void loop()
{
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
        Serial_printf_P(PSTR("frq=%.3f(%u),"), dimmer.getFrequency(), dimmer.getHalfWaveTicks());
        Serial.print(F("lvl="));
        FOR_CHANNELS(i) {
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

    if (dimmer_is_call_scheduled(EEPROM_WRITE) && millis() > eeprom_write_timer) {
        _write_config();
    }

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
                Wire.write(DIMMER_RESPONSE_TEMPERATURE_ALERT);
                Wire.write((uint8_t)current_temp);
                Wire.write(register_mem.data.cfg.max_temp);
                Wire.endTransmission();
            }
        }

        if (register_mem.data.cfg.bits.report_metrics) {
            if (millis() > next_event_metrics_event) {
                dimmer_metrics_t metrics = {
                    (uint8_t)current_temp,
                #if HAVE_READ_VCC
                    metrics.vcc = read_vcc(),
                #else
                    0,
                #endif
                    dimmer.getFrequency(),
                #if HAVE_NTC
                    ntc_temp,
                #else
                    NAN,
                #endif
                #if HAVE_READ_INT_TEMP
                    int_temp
                #else
                    NAN
                #endif
                };
                next_event_metrics_event = millis() + (register_mem.data.cfg.report_metrics_max_interval * 1000UL);

                Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
                Wire.write(DIMMER_RESPONSE_METRICS_REPORT);
                Wire.write(reinterpret_cast<const uint8_t *>(&metrics), sizeof(metrics));
                Wire.endTransmission();
            }
        }
    }
#endif
}
