/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <util/atomic.h>
#include "dimmer.h"
#include "i2c_slave.h"
#if SERIAL_I2C_BRDIGE
#include "SerialTwoWire.h"
#else
#include <Wire.h>
#endif

#if DIMMER_CHANNELS > 8
#error A maximum of 8 channels is supported
#endif

#ifndef SERIAL_I2C_BRDIGE
#define SERIAL_I2C_BRDIGE                       0
#endif

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE                       115200
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

#ifndef HAVE_PRINT_METRICS
#define HAVE_PRINT_METRICS                      1
#endif

#ifndef HAVE_CUBIC_INT_PRINT_TABLE
#define HAVE_CUBIC_INT_PRINT_TABLE              0
#endif

#ifndef HAVE_CUBIC_INT_GET_TABLE
#define HAVE_CUBIC_INT_GET_TABLE                0
#endif

#ifndef HAVE_CUBIC_INT_TEST_PERFORMANCE
#define HAVE_CUBIC_INT_TEST_PERFORMANCE         0
#endif

constexpr uint8_t kRegisterMemInfoOptionsBitValue = 0
#if DIMMER_CUBIC_INTERPOLATION
    |DIMMER_OPTIONS_INFO_HAS_CUBIC_INTERPOLATION
#endif
#if HAVE_NTC
    |DIMMER_OPTIONS_INFO_HAS_TEMPERATURE
#endif
#if HAVE_READ_INT_TEMP
    |DIMMER_OPTIONS_INFO_HAS_TEMPERATURE2
#endif
#if HAVE_READ_VCC
    |DIMMER_OPTIONS_INFO_HAS_VCC
#endif
#if HAVE_FADE_COMPLETION_EVENT
    |DIMMER_OPTIONS_INFO_HAS_FADING_COMPLETED_EVENT
#endif
;

#if HAVE_READ_INT_TEMP
extern bool is_Atmega328PB;
#define setAtmega328PB(value) is_Atmega328PB = value;
#else
#define setAtmega328PB(value) ;
#endif

extern unsigned long update_metrics_timer;

#if HAVE_PRINT_METRICS
extern bool print_metrics_enabled;
#endif

template<class T>
uint8_t Wire_read(T &data) {
    return Wire.readBytes(reinterpret_cast<uint8_t *>(&data), sizeof(data));
}

template<class T>
uint8_t Wire_write(T &data) {
    return Wire.write(reinterpret_cast<const uint8_t *>(&data), sizeof(data));
}

void rem();
void display_dimmer_info();
