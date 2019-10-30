/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "dimmer.h"
#include "i2c_slave.h"

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

#ifndef HAVE_NTC
#define HAVE_NTC                                1
#endif

#ifndef HAVE_READ_VCC
#define HAVE_READ_VCC                           1
#endif

#ifndef INTERNAL_VREF_1_1V
// after calibration VCC readings are pretty accurate, +-2-3mV
// default for cfg.internal_1_1v_ref
#define INTERNAL_VREF_1_1V                      1.1
#endif

#ifndef HAVE_READ_INT_TEMP
#define HAVE_READ_INT_TEMP                      1
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
#define NTC_SERIES_RESISTANCE                   3300
#endif
// ntc resistance @ 25°C
#ifndef NTC_NOMINAL_RESISTANCE
#define NTC_NOMINAL_RESISTANCE                  10000
#endif

#ifndef NTC_NOMINAL_TEMP
#define NTC_NOMINAL_TEMP                        25
#endif

#define SERIAL_INPUT_BUFFER_MAX_LENGTH          64
#define SERIAL_MAX_ARGUMENTS                    10

#ifndef HAVE_PRINT_METRICS
#define HAVE_PRINT_METRICS                      1
#endif
#ifndef PRINT_METRICS_REPEAT
#define PRINT_METRICS_REPEAT                    5000
#endif

#if USE_EEPROM

#define EEPROM_WRITE_DELAY                      500
#define EEPROM_REPEATED_WRITE_DELAY             5000

void read_config();
void write_config();
void init_eeprom();
void _write_config(bool force = false);
void reset_config();

 // bitset
 typedef enum : uint8_t {
    TYPE_NONE =             0,
    READ_VCC =              0x01,
    READ_INT_TEMP =         0x02,
    READ_NTC_TEMP =         0x04,
    PRINT_DIMMER_INFO =     0x08,
    EEPROM_WRITE =          0x10,
    PRINT_METRICS =         0x20,
    FREQUENCY_LOW =         0x40,       // frequency 75% or less
    FREQUENCY_HIGH =        0x80,       // frequency 120% or more
    FREQUENCY_ERROR =       FREQUENCY_LOW|FREQUENCY_HIGH,
} dimmer_scheduled_calls_enum_t;

typedef struct {
    unsigned long next_event;
    uint16_t vcc;
    float frequency;
    float int_temp;
    float ntc_temp;
} dimmer_metrics_event_t;

#if USE_TEMPERATURE_CHECK
extern unsigned long next_temp_check;
#endif

#if HAVE_PRINT_METRICS
extern unsigned long print_metrics_timeout;
#endif

extern uint8_t dimmer_scheduled_calls;

inline void dimmer_schedule_call(dimmer_scheduled_calls_enum_t type) {
    dimmer_scheduled_calls |= (uint8_t)type;
}

inline bool dimmer_is_call_scheduled(dimmer_scheduled_calls_enum_t type) {
    return (dimmer_scheduled_calls & (uint8_t)type);
}

inline void dimmer_remove_scheduled_call(dimmer_scheduled_calls_enum_t type) {
    dimmer_scheduled_calls &= ~((uint8_t)type);
}

#if HAVE_READ_INT_TEMP
float get_internal_temperature();
#endif

#if HIDE_DIMMER_INFO == 0
void display_dimmer_info();
#endif

#if HAVE_READ_VCC
uint16_t read_vcc();
#endif

#if HAVE_NTC
float get_ntc_temperature();
#endif

#endif
