/**
 * Author: sascha_lammers@gmx.de
 */

// 4 Channel Dimmer with I2C interface

#include <Arduino.h>
#include "i2c_slave.h"
#include "helpers.h"
#if USE_EEPROM
#include <EEPROM.h>
#endif

config_t config;
uint16_t eeprom_position = sizeof(uint64_t);
unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;
bool eeprom_write_scheduled = false;

void fade(int8_t channel, int16_t from, int16_t to, float time);

void reset_config() {
    memset(&config, 0, sizeof(config));
    memset(&register_mem.data.cfg, 0, sizeof(register_mem.data.cfg));
    register_mem.data.cfg.max_temp = 75;
    register_mem.data.cfg.bits.restore_level = true;
    register_mem.data.cfg.bits.report_temp = true;
    register_mem.data.cfg.fade_in_time = 7.5;
    register_mem.data.cfg.temp_check_interval = 30;
#if DIMMER_USE_LINEAR_CORRECTION
    register_mem.data.cfg.linear_correction_factor = 1.0;
#endif
}

// initialize EEPROM and wear leveling
void init_eeprom() {
    uint64_t config_id = CONFIG_ID;

    EEPROM.begin();
    config.eeprom_cycle = 1;
    eeprom_position = sizeof(uint64_t);
    _D(5, SerialEx.printf_P(PSTR("init eeprom cycle=%ld, position %d\n"), (long)config.eeprom_cycle, (int)eeprom_position));

    for(uint16_t i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
    }
    EEPROM.put(0, config_id);
    EEPROM.put(eeprom_position, config);
    EEPROM.end();
}

void read_config() {
    uint64_t config_id;

    EEPROM.begin();
    EEPROM.get(0, config_id);
    if (config_id != CONFIG_ID) {
        EEPROM.end();
        reset_config();
        init_eeprom();
    } else {
        uint16_t pos = sizeof(uint64_t);
        uint32_t cycle, max_cycle = 0;

        // find last configuration
        while(pos < EEPROM.length()) {
            EEPROM.get(pos, cycle);
            _D(5, SerialEx.printf_P(PSTR("eeprom cycle %ld position %d\n"), cycle, pos));
            if (cycle >= max_cycle) {
                eeprom_position = pos;
                max_cycle = cycle;
            }
            pos += sizeof(config_t);
        }
        EEPROM.get(eeprom_position, config);
        EEPROM.end();
        _D(5, SerialEx.printf_P(PSTR("read_config, eeprom cycle %ld, position %d\n"), (long)max_cycle, (int)eeprom_position));
    }

    memcpy(&register_mem.data.cfg, &config.cfg, sizeof(config.cfg));

    _D(5, SerialEx.printf_P(PSTR("---Read config---\n")));
    _D(5, SerialEx.printf_P(PSTR("Report temp. and VCC %d\n"), register_mem.data.cfg.bits.report_temp));
    _D(5, SerialEx.printf_P(PSTR("Restore level %d\n"), register_mem.data.cfg.bits.restore_level));
    _D(5, SerialEx.printf_P(PSTR("Temperature alert triggered %d\n"), register_mem.data.cfg.bits.temperature_alert));
    _D(5, SerialEx.printf_P(PSTR("Fade in time %s\n"), float_to_str(register_mem.data.cfg.fade_in_time)));
    _D(5, SerialEx.printf_P(PSTR("Max. temp %u\n"), register_mem.data.cfg.max_temp));
    _D(5, SerialEx.printf_P(PSTR("Temp. check interval %u\n"), register_mem.data.cfg.temp_check_interval));
    _D(5, SerialEx.printf_P(PSTR("Linear correction factor %s\n"), float_to_str(register_mem.data.cfg.linear_correction_factor)));
    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
        _D(5, SerialEx.printf_P(PSTR("Channel %u: %d\n"), i, config.level[i]));
    }
#if DIMMER_USE_LINEAR_CORRECTION
    dimmer_set_lcf(register_mem.data.cfg.linear_correction_factor);
#endif
}

void _write_config() {
    config_t temp_config;

    _D(5, SerialEx.printf_P(PSTR("---Write config---\n")));
    _D(5, SerialEx.printf_P(PSTR("Report temp. and VCC %d\n"), register_mem.data.cfg.bits.report_temp));
    _D(5, SerialEx.printf_P(PSTR("Restore level %d\n"), register_mem.data.cfg.bits.restore_level));
    _D(5, SerialEx.printf_P(PSTR("Temperature alert triggered %d\n"), register_mem.data.cfg.bits.temperature_alert));
    _D(5, SerialEx.printf_P(PSTR("Fade in time %s\n"), float_to_str(register_mem.data.cfg.fade_in_time)));
    _D(5, SerialEx.printf_P(PSTR("Max. temp %u\n"), register_mem.data.cfg.max_temp));
    _D(5, SerialEx.printf_P(PSTR("Temp. check interval %u\n"), register_mem.data.cfg.temp_check_interval));
    _D(5, SerialEx.printf_P(PSTR("Linear correction factor %s\n"), float_to_str(register_mem.data.cfg.linear_correction_factor)));
    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
        _D(5, SerialEx.printf_P(PSTR("Channel %u: %d\n"), i, register_mem.data.level[i]));
    }

    memcpy(&config.cfg, &register_mem.data.cfg, sizeof(config.cfg));
    memcpy(&config.level, &register_mem.data.level, sizeof(config.level));

    EEPROM.begin();
    EEPROM.get(eeprom_position, temp_config);
    if (memcmp(&config, &temp_config, sizeof(config)) != 0) {
        _D(5, SerialEx.printf_P(PSTR("old eeprom write cycle %ld, position %d, "), (long)config.eeprom_cycle, (int)eeprom_position));
        eeprom_position += sizeof(config_t);
        if (eeprom_position + sizeof(config_t) >= EEPROM.length()) { // end reached, start from beginning
            eeprom_position = sizeof(uint64_t);
            config.eeprom_cycle++;
        }
        _D(5, SerialEx.printf_P(PSTR("new cycle %ld, position %d\n"), (long)config.eeprom_cycle, (int)eeprom_position));
        EEPROM.put(eeprom_position, config);
        eeprom_write_timer = millis();
    } else {
        _D(5, SerialEx.printf_P(PSTR("configuration didn't change, skipping write cycle\n")));
        eeprom_write_timer = millis();
    }
    EEPROM.end();
    eeprom_write_scheduled = false;
}

void write_config() {
    long lastWrite = millis() - eeprom_write_timer;
    if (!eeprom_write_scheduled) { // no write scheduled
        _D(5, SerialEx.printf_P(PSTR("scheduling eeprom write cycle, last write %d seconds ago\n"), (int)(lastWrite / 1000UL)));
        eeprom_write_timer = millis() + ((lastWrite > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
        eeprom_write_scheduled = true;
    } else {
        _D(5, SerialEx.printf_P(PSTR("eeprom write cycle already scheduled in %d seconds\n"), (int)(lastWrite / -1000L)));
    }
}

#if HAVE_READ_INT_TEMP

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
float get_internal_temperature() {
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    delay(40); // 20 was not enough. It takes quite a while when switching from reading VCC to temp.
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return (ADCW - 324.31) / 1.22;
}

#endif

#if HAVE_READ_VCC

// read VCC in mV
uint16_t read_vcc() {
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(40);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return ((uint32_t)(5000 * (INTERNAL_VREF_1_1V / 5) * 1024)) / ADCW;
}

#endif

#if HAVE_NTC

uint16_t read_ntc_value(uint8_t num) {
    uint32_t value = 0;
    for(uint8_t i = 0; i < num; i++) {
        value += analogRead(NTC_PIN);
        delay(1);
    }
    return value / num;
}

float convert_to_celsius(uint16_t value) {
    float steinhart;
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

void setup() {

#if DEBUG || SERIAL_I2C_BRDIGE
    Serial.begin(DEFAULT_BAUD_RATE);
    #if SERIAL_I2C_BRDIGE && DEBUG
    _debug_level = 9;
    #endif
#endif

    dimmer_i2c_slave_setup();
    
    read_config();
    dimmer_zc_setup();
    dimmer_timer_setup();

#if USE_NTC
    pinMode(NTC_PIN, INPUT);
#endif
  
#if USE_EEPROM
    restore_level();
#endif
}

#if USE_TEMPERATURE_CHECK
unsigned long next_temp_check;
#endif

void loop() {
#if USE_EEPROM
    if (eeprom_write_scheduled && millis() > eeprom_write_timer) {
        _write_config();
    }
#endif
#if USE_TEMPERATURE_CHECK
    if (millis() > next_temp_check) {
#if USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN
        int current_temp = get_internal_temperature();
#else
        int current_temp = convert_to_celsius(read_ntc_value());
#endif
        next_temp_check = millis() + register_mem.data.cfg.temp_check_interval * 1000;
        if (register_mem.data.cfg.max_temp && current_temp > register_mem.data.cfg.max_temp) {
            fade(-1, DIMMER_FADE_FROM_CURRENT_LEVEL, 0, 10);
            register_mem.data.cfg.bits.temperature_alert = 1;
            write_config();
            if (register_mem.data.cfg.bits.report_temp) {
                Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
                Wire.write(DIMMER_TEMPERATURE_ALERT);
                Wire.write((uint8_t)current_temp);
                Wire.write(register_mem.data.cfg.max_temp);
                Wire.endTransmission();
            }
        }
        if (register_mem.data.cfg.bits.report_temp) {
            Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
            Wire.write(DIMMER_TEMPERATURE_REPORT);
            Wire.write((uint8_t)current_temp);
#if HAVE_READ_VCC
            uint16_t vcc = read_vcc();
            Wire.write(reinterpret_cast<const uint8_t *>(&vcc), sizeof(vcc));
#endif
            Wire.endTransmission();
        }
    }
#endif
}

#endif
