/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

// enable debug code
#ifndef DEBUG
#define DEBUG                                                   0
#endif

// enable debug commands
#ifndef DEBUG_COMMANDS
#define DEBUG_COMMANDS                                          1
#endif

// pin for the zero crossing signal
#ifndef ZC_SIGNAL_PIN
#define ZC_SIGNAL_PIN                                           3
#endif

// delay after receiving the zero crossing signal and the mosfets being turned on
// if RISING is used, there is still a difference of about 20µs (1 channel @16MHz) until the mosfets turn on. this
// value varies depending on the number of channels and CPU frequency
//
// this should be calibrated at a temperature close to the working temperature. the zc crossing detection being used
// in revision 1.3 with power monitoring changes about 250ns/°C while some older ones vary up to 5µs/°C
// if more precision is required, a temperature correction based on the NTC temperature can be added
#ifndef DIMMER_ZC_DELAY_US
#define DIMMER_ZC_DELAY_US                                      144  // in µs
#endif

// zero crossing interrupt trigger mode
// if CHANGE is used, the zero crossing signal is the average time between rising and
// falling measured over 2 or more halfwaves. this mode can be used for asymmetrical and symmetrical signals
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

//
// minimum on time after the zero crossing interrupt
// this is level Level::off + 1
//
// NOTE:
// leading edge mode: min. on time ends at zc delay + halfwave - min. on time
// trailing edge mode: min. on time ends at zc delay + min. on time.
//
// https://github.com/sascha432/trailing_edge_dimmer/blob/bedf1d01b5e8d3531ac5dc090c64a4bc6f67bfd3/docs/images/min_on_time.png
//
#ifndef DIMMER_MIN_ON_TIME_US
#define DIMMER_MIN_ON_TIME_US                                   300 // minimum on-time in µs
#endif

// default for DIMMER_REGISTER_MIN_OFF_TIME_TICKS
// minimum time to turn MOSFETs off before the halfwave ends
// this is level Level::max - 1
// level Level::max turns the mosfet on permanently
//
// NOTE:
// leading edge mode: min. off time starts at zc delay + halfwave - min. off time
// trailing edge mode: min. off time starts at zc delay + min. off time.
//
// https://github.com/sascha432/trailing_edge_dimmer/blob/bedf1d01b5e8d3531ac5dc090c64a4bc6f67bfd3/docs/images/min_off_time.png
//
#ifndef DIMMER_MIN_OFF_TIME_US
#define DIMMER_MIN_OFF_TIME_US                                  300 // minimum off-time before the halfwave ends
#endif

// adjustment for measuring clock cycles
// avr-gcc (atmega328p, -O2) adds 37 cpu cycles before reading the counter
#ifndef DIMMER_MEASURE_ADJ_CYCLE_CNT
#define DIMMER_MEASURE_ADJ_CYCLE_CNT                            -37
#endif

// keep dimmer enabled when loosing the ZC signal for up to
// DIMMER_OUT_OF_SYNC_LIMIT halfwaves. 250 @ 60Hz ~ 2seconds
// once the signal is lost, it will start to drift and get out of sync. adjust the
// limit to keep the drift below 200µs
#ifndef DIMMER_OUT_OF_SYNC_LIMIT
#define DIMMER_OUT_OF_SYNC_LIMIT                                250
#endif

// default mode
// 1 trailing edge
// 0 leading edge
#ifndef DIMMER_TRAILING_EDGE
#define DIMMER_TRAILING_EDGE                                    1
#endif

// 1 inverts the output signal
#ifndef DIMMER_MOSFET_ACTIVE_LOW
#define DIMMER_MOSFET_ACTIVE_LOW                                0
#endif

// pin state to turn MOSFETS on
#ifndef DIMMER_MOSFET_ON_STATE
#define DIMMER_MOSFET_ON_STATE                                  (DIMMER_MOSFET_ACTIVE_LOW ? LOW : HIGH)
#endif

// pin state to turn MOSFETS off
#ifndef DIMMER_MOSFET_OFF_STATE
#define DIMMER_MOSFET_OFF_STATE                                 (!DIMMER_MOSFET_ON_STATE)
#endif

// output pins as comma separated list
#ifndef DIMMER_MOSFET_PINS
#define DIMMER_MOSFET_PINS                                      6, 8, 9, 10
#endif

// maximum number of different dimming levels
// some non dimmable LEDs can be dimmed inside a narrow window of 10-20% of the halfwave
// this reduces the number of effective levels and should be taken in account when
// choosing this number. the limit is the number of ticks the timer
#ifndef DIMMER_MAX_LEVEL
#define DIMMER_MAX_LEVEL                                        8192
#endif

//
// the prescaler should be chosen to have maximum precision while having enough range for fine tuning

// timer1, 16 bit, used for turning MOSFETs on and off
#ifndef DIMMER_TIMER1_PRESCALER
#define DIMMER_TIMER1_PRESCALER                                 8
#endif

// timer2, 8bit, used to delay the turn on after receiving the ZC signal
#ifndef DIMMER_TIMER2_PRESCALER
#define DIMMER_TIMER2_PRESCALER                                 64
#endif

// sent event when fading has reached the target level
#ifndef HAVE_FADE_COMPLETION_EVENT
#define HAVE_FADE_COMPLETION_EVENT                              1
#endif

// do not display info during boot and disable DIMMER_COMMAND_PRINT_INFO
#ifndef HIDE_DIMMER_INFO
#define HIDE_DIMMER_INFO                                        0
#endif

// voltage divider on analog port
#ifndef HAVE_EXT_VCC
#define HAVE_EXT_VCC                                            0
#endif

// pin to read VCC from. the value is compared against the internal VREF11
// the voltage divider for measuring 5V is R1=12K, R2=3K, R1=VCC to analog pin, R2=GND to analog pin
// for getting a stable/average voltage, add C1=10nF-1uF analog pin to GND
#ifndef VCC_PIN
#define VCC_PIN                                                 A0
#endif

// potentiometer for testing purposes
#ifndef HAVE_POTI
#define HAVE_POTI                                               0
#endif

// analog PIN for potentiometer
#ifndef POTI_PIN
#define POTI_PIN                                                A1
#endif

// channel controlled by potentiometer
#ifndef POTI_CHANNEL
#define POTI_CHANNEL                                            0
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
