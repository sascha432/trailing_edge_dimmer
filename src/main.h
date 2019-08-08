/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "dimmer.h"

#ifndef DIMMER_I2C_SLAVE
#define DIMMER_I2C_SLAVE                        1
#endif

#if DIMMER_I2C_SLAVE && DIMMER_CHANNELS > 8
#error I2C is limited to 8 channels
#endif

#ifndef SERIAL_I2C_BRDIGE
#define SERIAL_I2C_BRDIGE                       0
#endif

#ifndef USE_EEPROM
#define USE_EEPROM                              1
#endif

#ifndef INTERNAL_VREF_1_1V
#define INTERNAL_VREF_1_1V                      1.1
#endif


#ifndef USE_TEMPERATURE_CHECK
#define USE_TEMPERATURE_CHECK                   1
#endif

#ifndef USE_NTC
#define USE_NTC                                 1
#endif

#ifndef USE_INTERAL_TEMP_SENSOR
#define USE_INTERAL_TEMP_SENSOR                 1
#endif

#ifndef USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN
#define USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN    0
#endif

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE                       115200
#endif

#define NTC_PIN                                 A1

#define SERIAL_INPUT_BUFFER_MAX_LENGTH          64
#define SERIAL_MAX_ARGUMENTS                    10

#if USE_EEPROM

#define CONFIG_ID                               0xc33e166c5e7c6572
#define EEPROM_WRITE_DELAY                      1000
#define EEPROM_REPEATED_WRITE_DELAY             30000

typedef struct {
    uint8_t restore_level: 1;
    uint8_t report_temp: 1;
    uint8_t temperature_alert: 1;
    uint8_t ___reserved: 5;
} config_options_t;

typedef struct {
    float fadein_time;
    uint8_t max_temp;
    union {
        config_options_t bits;
        uint8_t options;
    };
    uint8_t temp_check_interval;
} config_reg_mem_t;

typedef struct {
    uint32_t eeprom_cycle;
    config_reg_mem_t cfg;
    int16_t level[DIMMER_CHANNELS];
} config_t;

void read_config();
void write_config();
void init_eeprom();
void _write_config();
void reset_config();
float get_interal_temperature(void);
uint16_t read_vcc();
uint16_t read_ntc_value(uint8_t num = 5);
float convert_to_celsius(uint16_t value);

extern config_t config;

#endif
