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
    register_mem.data.cfg.max_temp = 65;
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

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
float get_interal_temperature(void) {
  unsigned int wADC;
  float t;

  // The internal temperature has to be used
  // with the internal reference of 1.1V.
  // Channel 8 can not be selected with
  // the analogRead function yet.

  // Set the internal reference and mux.
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA, ADSC)) ;

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;

  // The returned temperature is in degrees Celsius.
  return (t);
}

// read VCC in mV
uint16_t read_vcc() {
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(20);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return ((uint32_t)(5000 * (INTERNAL_VREF_1_1V / 5) * 1024)) / ADCW;
}

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
    steinhart *= 2200;                          // serial resistance
    steinhart /= 10000;                         // nominal resistance
    steinhart = log(steinhart);
    steinhart /= 3950;                          // beta coeff.
    steinhart += 1.0 / (25 + 273.15);           // nominal temperature
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    return steinhart;
}

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
        int current_temp = get_interal_temperature();
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
                Wire.write(current_temp);
                Wire.write(register_mem.data.cfg.max_temp);
                Wire.endTransmission();
            }
        }
        if (register_mem.data.cfg.bits.report_temp) {
            uint16_t vcc = read_vcc();
            Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
            Wire.write(DIMMER_TEMPERATURE_REPORT);
            Wire.write(current_temp);
            Wire.write(reinterpret_cast<const uint8_t *>(&vcc), sizeof(vcc));
            Wire.endTransmission();
        }
    }
#endif
}

#endif
