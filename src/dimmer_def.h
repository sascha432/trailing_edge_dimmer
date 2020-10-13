/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#ifndef ZC_SIGNAL_PIN
#define ZC_SIGNAL_PIN                                           3
#endif

// **********************************
//  NOTE:
//  for timing see docs/timings.svg
// **********************************

// the exact delay depends on the zero crossing detection, the prescaler and the CPU speed, the propagation delay and all
// capacitiy of the circuit. I strongly recommend to check with an oscilloscope to get the exact timings. It can be tuned very
// well by software to be accurate in the 200-300 nano second range.

// 60 Hz example, time in milliseconds

//  0.000 zero crossing
//  6.658 zero crossing interrupt
//  1.675 zero crossing delay (DIMMER_ZC_DELAY_US=1675)
//        NOTE: there is an additional delay of 22.8us (atmega328p, 16mhz) between the interrupt and the MOSFETs being turned on
//        depending on the circuit, there will be a propagation delay of 100-500ns, or even more. The delay needs to be adjusted accordingly
//  8.333 next zero crossing, turn on mosfets - dimmer level 0%
//  8.533 keep mosfets on (DIMMER_MIN_ON_TIME_US=200) until level 2.49%
// 14.991 zero crossing interrupt
// 16.366 dimming level reached 100%, turn mosfets off if still on
//        depending on the level set, the MOSFETs can be turned off between 2.49% and 100% (between 0.200-8.033ms of the 8333ms half wave)
// 16.666 next zero crossing

// delay after receiving the zero crossing signal and the mosfet being turned on
#ifndef DIMMER_ZC_DELAY_US
#define DIMMER_ZC_DELAY_US                                      1104  // in µs
#endif

// zero crossing interrupt trigger mode
// if CHANGE is used, the zero crossing signal is the average time between rising and falling
// measured over 2 or more halfwaves
#ifndef DIMMER_ZC_INTERRUPT_MODE
#define DIMMER_ZC_INTERRUPT_MODE                                RISING
//#define DIMMER_ZC_INTERRUPT_MODE                                FALLING
//#define DIMMER_ZC_INTERRUPT_MODE                                CHANGE
#endif

// DIMMER_MIN_ON_TIME_US and DIMMER_MIN_OFF_TIME_US remove the unusable part of the halfwave
// to maximize the level range. the level range can be configured dynamically to match the
// requirements of the device being dimmed
//
// in combination with DIMMER_ZC_DELAY_US it can be used to turn the MOSFETs on after the half wave
// starts and off, before it ends

// minimum on time after the zero crossing interrupt
// this is level Level::min_on
#ifndef DIMMER_MIN_ON_TIME_US
#define DIMMER_MIN_ON_TIME_US                                   200 // minimum on-time in µs
#endif

// default for DIMMER_REGISTER_MIN_OFF_TIME_TICKS
// minimum time to turn MOSFETs off before the halfwave ends
// this is level Level::max - 1
// level Level::max turns the mosfet on permanently
#ifndef DIMMER_MIN_OFF_TIME_US
#define DIMMER_MIN_OFF_TIME_US                                  300 // minimum off-time before the halfwave ends
#endif

// this can be used to configure trailing or leading edge by default. the mode can be configured dynamically
#ifndef DIMMER_INVERT_MOSFET_SIGNAL
#define DIMMER_INVERT_MOSFET_SIGNAL                             0
#endif

// state of the PIN that controls the MOSFETs to turn them off
// this is not affected by DIMMER_INVERT_MOSFET_SIGNAL while the dimmer is turned off
#ifndef DIMMER_MOSFET_OFF_STATE
#define DIMMER_MOSFET_OFF_STATE                                 LOW
#endif

// used to calculate the length of the half wave
#ifndef DIMMER_AC_FREQUENCY
    #define DIMMER_AC_FREQUENCY                                 60      // Hz
#endif

#ifndef DIMMER_LOW_FREQUENCY
#define DIMMER_LOW_FREQUENCY                                    0.75    // 75%
#endif

#ifndef DIMMER_HIGH_FREQUENCY
#define DIMMER_HIGH_FREQUENCY                                   1.2     // 120%
#endif

// output pins as comma separated list
#ifndef DIMMER_MOSFET_PINS
    #define DIMMER_MOSFET_PINS                                  6, 8, 9, 10
#endif

// maximum number of different dimming levels
// some non dimmable LEDs can be dimmed inside a narrow window of 10-20% of the halfwave
// this reduces the number of effective levels and should be taken in account when
// choosing this number. the limit is the number of ticks the timer
#ifndef DIMMER_MAX_LEVEL
#define DIMMER_MAX_LEVEL                                        8192
#endif

// timer1, 16 bit, used for turning MOSFETs on and off
#ifndef DIMMER_TIMER1_PRESCALER
#define DIMMER_TIMER1_PRESCALER                                 8
#endif


// timer2, 8bit, used to delay the turn on after receiving the ZC signal
#ifndef DIMMER_TIMER2_PRESCALER
#define DIMMER_TIMER2_PRESCALER                                 64
#endif

//
// the prescaler should be chosen to have maximum precision while having enough range for fine tuning

#ifndef HAVE_FADE_COMPLETION_EVENT
#define HAVE_FADE_COMPLETION_EVENT                              1
#endif

#ifndef HIDE_DIMMER_INFO
#define HIDE_DIMMER_INFO                                        0
#endif

// the frequency is updated twice per second
// 0 disables frequency messuring
#ifndef FREQUENCY_TEST_DURATION
#define FREQUENCY_TEST_DURATION                                 600
#endif

#ifndef HAVE_EXT_VCC
#define HAVE_EXT_VCC                                            0
#endif

#ifndef VCC_PIN
#define VCC_PIN                                                 A0
#endif

#ifndef ZC_MAX_TIMINGS
// 4 byte RAM required for each timing
#define ZC_MAX_TIMINGS                                          0
#endif

#if ZC_MAX_TIMINGS > 255
#error ZC_MAX_TIMINGS is limited to 255, decrease ZC_MAX_TIMINGS_INTERVAL to collect more data
#endif

#ifndef ZC_MAX_TIMINGS_INTERVAL
#define ZC_MAX_TIMINGS_INTERVAL                                 500
#endif

#if ZC_MAX_TIMINGS
extern volatile unsigned long *zc_timings;
extern volatile uint8_t zc_timings_counter;
extern bool zc_timings_output;
#endif

#ifndef SERIAL_I2C_BRDIGE
#define SERIAL_I2C_BRDIGE                                       0
#endif

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE                                       57600
#endif

#ifndef HAVE_NTC
#define HAVE_NTC                                                1
#endif

#ifndef HAVE_READ_VCC
#define HAVE_READ_VCC                                           1
#endif

#ifndef INTERNAL_VREF_1_1V
// after calibration VCC readings are pretty accurate, +-2-3mV
// default for cfg.internal_1_1v_ref
#define INTERNAL_VREF_1_1V                                      1.1
#endif

#ifndef HAVE_READ_INT_TEMP
#define HAVE_READ_INT_TEMP                                      1
#endif

#ifndef USE_TEMPERATURE_CHECK
#if HAVE_NTC || HAVE_READ_INT_TEMP
#define USE_TEMPERATURE_CHECK                                   1
#else
#define USE_TEMPERATURE_CHECK                                   0
#endif
#endif

// NTC pin
#ifndef NTC_PIN
#define NTC_PIN                                                 A1
#endif
// beta coefficient
#ifndef NTC_BETA_COEFF
#define NTC_BETA_COEFF                                          3950
#endif
// resistor in series with the NTC
#ifndef NTC_SERIES_RESISTANCE
#define NTC_SERIES_RESISTANCE                                   3300
#endif
// ntc resistance @ 25°C
#ifndef NTC_NOMINAL_RESISTANCE
#define NTC_NOMINAL_RESISTANCE                                  10000
#endif

#ifndef NTC_NOMINAL_TEMP
#define NTC_NOMINAL_TEMP                                        25
#endif

#define SERIAL_INPUT_BUFFER_MAX_LENGTH                          64
#define SERIAL_MAX_ARGUMENTS                                    10

#ifndef HAVE_PRINT_METRICS
#define HAVE_PRINT_METRICS                                      1
#endif
#ifndef PRINT_METRICS_REPEAT
#define PRINT_METRICS_REPEAT                                    5000
#endif

#ifndef EEPROM_WRITE_DELAY
#define EEPROM_WRITE_DELAY                                      500
#endif

#ifndef EEPROM_REPEATED_WRITE_DELAY
#define EEPROM_REPEATED_WRITE_DELAY                             5000
#endif

#ifndef DIMMER_VERSION_MAJOR
#define DIMMER_VERSION_MAJOR                                    2
#define DIMMER_VERSION_MINOR                                    2
#define DIMMER_VERSION_REVISION                                 0
#endif

#define DIMMER_VERSION                                          _STRINGIFY(DIMMER_VERSION_MAJOR) "." _STRINGIFY(DIMMER_VERSION_MINOR) "." _STRINGIFY(DIMMER_VERSION_REVISION)
#define DIMMER_INFO                                             "Author sascha_lammers@gmx.de"
