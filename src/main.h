/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "dimmer.h"
#include "i2c_slave.h"

#ifndef DIMMER_I2C_SLAVE
#define DIMMER_I2C_SLAVE                        1
#endif

#if DIMMER_I2C_SLAVE && DIMMER_CHANNELS > 8
#error I2C is limited to 8 channels
#endif

#ifndef SERIAL_I2C_BRDIGE
#define SERIAL_I2C_BRDIGE                       0
#endif

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE                       115200
#endif

#ifndef USE_EEPROM
#define USE_EEPROM                              1
#endif

#ifndef INTERNAL_VREF_1_1V
#define INTERNAL_VREF_1_1V                      1.1
#endif

#ifndef HAVE_NTC
#define HAVE_NTC                                1
#endif

#ifndef HAVE_READ_VCC
#define HAVE_READ_VCC                           1
#endif

#ifndef HAVE_READ_INT_TEMP
#define HAVE_READ_INT_TEMP                      1
#endif

#ifndef USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN
#if HAVE_READ_INT_TEMP && !HAVE_NTC
#define USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN    1
#else
#define USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN    0
#endif
#endif

#ifndef USE_TEMPERATURE_CHECK
#if HAVE_NTC || HAVE_READ_INT_TEMP
#define USE_TEMPERATURE_CHECK                   1
#else
#define USE_TEMPERATURE_CHECK                   0
#endif
#endif

// NTC pin
#ifndef NTC_PIN
#define NTC_PIN                                 A1
#endif
// beta coefficient
#ifndef NTC_BETA_COEFF
#define NTC_BETA_COEFF                          3950
#endif
// resistor in series with the NTC
#ifndef NTC_SERIES_RESISTANCE
#define NTC_SERIES_RESISTANCE                   2200
#endif
// ntc resistance @ 25°C
#ifndef NTC_NOMINAL_RESISTANCE
#define NTC_NOMINAL_RESISTANCE                  10000
#define NTC_NOMINAL_TEMP                        25
#endif

#define SERIAL_INPUT_BUFFER_MAX_LENGTH          64
#define SERIAL_MAX_ARGUMENTS                    10

#if USE_EEPROM

#define CONFIG_ID                               0xc33e186c5e2c8574
#define EEPROM_WRITE_DELAY                      1000
#define EEPROM_REPEATED_WRITE_DELAY             30000

void read_config();
void write_config();
void init_eeprom();
void _write_config();
void reset_config();
#if HAVE_READ_INT_TEMP
float get_internal_temperature();
#endif

#if HAVE_READ_VCC
uint16_t read_vcc();
#endif

#if HAVE_NTC
uint16_t read_ntc_value(uint8_t num = 5);
float convert_to_celsius(uint16_t value);
#endif

#endif
