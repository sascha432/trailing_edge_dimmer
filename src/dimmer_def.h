/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

// enable debug code
#ifndef DEBUG
#define DEBUG                                                   0
#endif

// enable debug commands
// ~1kb extra code size
#ifndef DEBUG_COMMANDS
#define DEBUG_COMMANDS                                          1
#endif

#if DEBUG || DEBUG_COMMANDS
#ifndef HAVE_DISABLE_ZC_SYNC
#define HAVE_DISABLE_ZC_SYNC                                    0
#endif
#else
#if HAVE_DISABLE_ZC_SYNC
#error requires DEBUG mode
#endif
#define HAVE_DISABLE_ZC_SYNC                                    0
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
#ifndef DIMMER_ZC_INTERRUPT_MODE
#define DIMMER_ZC_INTERRUPT_MODE                                RISING
//#define DIMMER_ZC_INTERRUPT_MODE                                FALLING
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
#define DIMMER_MIN_ON_TIME_US                                   300
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
#define DIMMER_MIN_OFF_TIME_US                                  300
#endif

// adjustment for measuring clock cycles due to pushing registers on
// the stack before reading TCNT1
#ifndef DIMMER_MEASURE_ADJ_CYCLE_CNT
#define DIMMER_MEASURE_ADJ_CYCLE_CNT                            -56
#endif

// keep dimmer enabled when loosing the ZC signal for up to
// DIMMER_OUT_OF_SYNC_LIMIT halfwaves. 250 @ 60Hz ~ 2seconds
// once the signal is lost, it will start to drift and get out of sync. adjust
// the time limit to keep the drift below 100-200µs
#ifndef DIMMER_OUT_OF_SYNC_LIMIT
#define DIMMER_OUT_OF_SYNC_LIMIT                                2500
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

// number of channels
#ifndef DIMMER_CHANNEL_COUNT
#define DIMMER_CHANNEL_COUNT                                    4
#endif

// maximum number of different dimming levels
// the range can be adjusted with range_begin and range_end
#ifndef DIMMER_MAX_LEVEL
#define DIMMER_MAX_LEVEL                                        8192
#endif

// if set to 1, some code is being removed that is not required for more than 1 channel
#ifndef DIMMER_MAX_CHANNELS
#define DIMMER_MAX_CHANNELS                                     8
#endif

//
// the prescaler should be chosen to have maximum precision while having enough range for fine tuning
// prescaler 1 is used for measuring time

// timer1, 16 bit, used for the ZC delay and turning MOSFETs on and off
#ifndef DIMMER_TIMER1_PRESCALER
#define DIMMER_TIMER1_PRESCALER                                 8
#endif

// sent event when fading has reached the target level
#ifndef HAVE_FADE_COMPLETION_EVENT
#define HAVE_FADE_COMPLETION_EVENT                              1
#endif

// do not display info during boot and disable DIMMER_COMMAND_PRINT_INFO
// ~1642 byte code size
#ifndef HIDE_DIMMER_INFO
#define HIDE_DIMMER_INFO                                        0
#endif

// potentiometer for testing purposes
// the ADC is read 256x in a row continuously unless other readings are performed (VCC, NTC, ...)
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

#ifndef SERIAL_I2C_BRDIGE
#define SERIAL_I2C_BRDIGE                                       0
#endif

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE                                       57600
#endif

// interval in milliseconds
#ifndef DIMMER_TEMPERATURE_CHECK_INTERVAL
#define DIMMER_TEMPERATURE_CHECK_INTERVAL                      1024UL
#endif

#ifndef HAVE_NTC
#define HAVE_NTC                                                1
#endif

#ifndef HAVE_READ_VCC
#define HAVE_READ_VCC                                           1
#endif

// default value for restore level
#ifndef DIMMER_RESTORE_LEVEL
#define DIMMER_RESTORE_LEVEL                                    1
#endif

#ifndef DIMMER_REPORT_METRICS_INTERVAL
#define DIMMER_REPORT_METRICS_INTERVAL                          5
#endif

// after calibration VCC readings are pretty accurate, ±1-2mV
// NOTE: VCC is read 64x in a row, once per second and the capacitence of the ADC is very low,
// which can lead to jumping values if the VCC is not stable
// default for cfg.internal_1_1v_ref
#ifndef INTERNAL_VREF_1_1V
#define INTERNAL_VREF_1_1V                                      1.1
#endif

// to get more stable (average) VCC readings, an additonal circuit with more capacitance can be
// added to an analog port

// voltage divider on analog port
#ifndef HAVE_EXT_VCC
#define HAVE_EXT_VCC                                            0
#endif

// pin to read VCC from. the value is compared against the internal VREF11
// the voltage divider for measuring 5V is R1=12K, R2=3K, R1=VCC to analog pin, R2=GND to analog pin
// for getting stable average voltage readings, add C1=1-10uF from analog pin to GND
#ifndef VCC_PIN
#define VCC_PIN                                                 A0
#endif

// use internal temperature sensor
#ifndef HAVE_READ_INT_TEMP
#define HAVE_READ_INT_TEMP                                      1
#endif

// default values for TS_OFFSET and TS_GAIN
//
// see datasheet for more infomation
//
// The values described in the table above are typical values. However, due to process variation the
// temperature sensor output voltage varies from one chip to another. To be capable of achieving more
// accurate results the temperature measurement can be calibrated in the application software
#if __AVR_ATmega328PB__ || MCU_IS_ATMEGA328PB == 1

#define DIMMER_AVR_TEMP_TS_OFFSET                               103
#define DIMMER_AVR_TEMP_TS_GAIN                                 128

#elif __AVR_ATmega328P__ && MCU_IS_ATMEGA328PB == 0

// Atmega328P only: DIMMER_AVR_TEMP_TS_GAIN = 0 reads the calibration values from the signature bytes
#ifndef DIMMER_AVR_TEMP_TS_OFFSET
// #define DIMMER_AVR_TEMP_TS_OFFSET                               21
// #define DIMMER_AVR_TEMP_TS_GAIN                                 164
#define DIMMER_AVR_TEMP_TS_OFFSET                               0
#define DIMMER_AVR_TEMP_TS_GAIN                                 0
#endif

#else

#error DIMMER_AVR_TEMP_TS_GAIN and DIMMER_AVR_TEMP_TS_OFFSET must be defined

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
#define HAVE_PRINT_METRICS                                      0
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

#if DIMMER_MAX_CHANNELS > 1
#define DIMMER_CHANNEL_LOOP(var)                                for(Dimmer::Channel::type var = 0; var < Dimmer::Channel::size(); var++)
#else
#define DIMMER_CHANNEL_LOOP(var)                                constexpr Dimmer::Channel::type var = 0;
#endif

#if __GNUC__ > 3
#define __GNUC_STR__                                            ",gcc=" _STRINGIFY(__GNUC__) "." _STRINGIFY(__GNUC_MINOR__) "." _STRINGIFY(__GNUC_PATCHLEVEL__)
#else
#define __GNUC_STR__                                            ""
#endif

#if F_CPU == 160000000UL
#define F_CPU_MHZ 160
#elif F_CPU == 80000000UL
#define F_CPU_MHZ 80
#elif F_CPU == 20000000UL
#define F_CPU_MHZ 20
#elif F_CPU == 16000000UL
#define F_CPU_MHZ 16
#elif F_CPU == 8000000UL
#define F_CPU_MHZ 8
#elif F_CPU == 4000000UL
#define F_CPU_MHZ 4
#elif F_CPU == 2000000UL
#define F_CPU_MHZ 2
#elif F_CPU == 1000000UL
#define F_CPU_MHZ 1
#else
#error define F_CPU_MHZ
#endif
