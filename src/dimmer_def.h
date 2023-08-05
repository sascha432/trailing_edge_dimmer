/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>

// generated by extra_script.py, reading library.json
#include "dimmer_version.h"

// enable debug code
#ifndef DEBUG
#    define DEBUG 0
#endif

// enable debug code
#ifndef DEBUG_FREQUENCY_MEASUREMENT
#    define DEBUG_FREQUENCY_MEASUREMENT 0
#endif

// enable debug commands
// ~1kb extra code size
#ifndef DEBUG_COMMANDS
#    define DEBUG_COMMANDS 1
#endif

// enable zero crossing prediction and error correction. requires re-calibration of the zero crossing since the 
// clock cycles change if enabled
// TODO unstable at the moment
#ifndef ENABLE_ZC_PREDICTION
#    define ENABLE_ZC_PREDICTION 0
#endif

// enable serial debug output
#ifndef DEBUG_ZC_PREDICTION
#    define DEBUG_ZC_PREDICTION 0
#endif

// pin for the zero crossing signal
#if DIMMER_HEADERS_ONLY
#elif !defined(ZC_SIGNAL_PIN)
#    error ZC_SIGNAL_PIN not defined
#endif

// delay after receiving the zero crossing signal and the MOSFETs being turned on
//
// this should be calibrated at a temperature close to the working temperature. the zc crossing detection being used
// in revision 1.3 with power monitoring changes about 250ns/°C while some older ones vary up to 5µs/°C. the threshold
// should be +-20µs at working temperature. if more precision is required, a temperature correction based on the ATMega/NTC 
// temperature can be added, but i highly recommend to use a proper zc detection with low temperature drift
#ifndef DIMMER_ZC_DELAY_US
#    define DIMMER_ZC_DELAY_US 144 // in µs
#endif

// zero crossing interrupt trigger mode
// older versions use a pullup and are active low (FALLING), while newer use a transistor or mosfet to invert the level (active high, RISING)
#ifndef DIMMER_ZC_INTERRUPT_MODE
#    define DIMMER_ZC_INTERRUPT_MODE RISING
// #    define DIMMER_ZC_INTERRUPT_MODE FALLING
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
#    define DIMMER_MIN_ON_TIME_US 384
#endif

static_assert(DIMMER_MIN_ON_TIME_US > 200, "DIMMER_MIN_ON_TIME_US too low");

// default for DIMMER_REGISTER_MIN_OFF_TIME_TICKS
// minimum time to turn MOSFETs off before the half wave ends
// this is level Level::max - 1
// level Level::max turns the mosfet on permanently
//
// NOTE:
// leading edge mode: min. off time starts at zc delay + half wave - min. off time
// trailing edge mode: min. off time starts at zc delay + min. off time.
//
// https://github.com/sascha432/trailing_edge_dimmer/blob/bedf1d01b5e8d3531ac5dc090c64a4bc6f67bfd3/docs/images/min_off_time.png
//
#ifndef DIMMER_MIN_OFF_TIME_US
#    define DIMMER_MIN_OFF_TIME_US 304
#endif

static_assert(DIMMER_MIN_OFF_TIME_US > 200, "DIMMER_MIN_OFF_TIME_US too low");


// keep dimmer enabled when loosing the ZC signal for up to DIMMER_OUT_OF_SYNC_LIMIT half waves
// once the signal is lost, it will start to drift and get out of sync. adjust the time limit to keep the drift below 100-200µs
#ifndef DIMMER_OUT_OF_SYNC_LIMIT
#    define DIMMER_OUT_OF_SYNC_LIMIT 2048UL
#endif

static_assert(DIMMER_OUT_OF_SYNC_LIMIT > 16, "DIMMER_OUT_OF_SYNC_LIMIT too low");

// min. number of samples to collect, should be more than 100. it requires 3 byte dynamic memory per sample and is released after the measurement is done
#ifndef DIMMER_ZC_MIN_SAMPLES
#    define DIMMER_ZC_MIN_SAMPLES 128
#endif

// valid samples after 2 stage filtering, should be at least 50% of DIMMER_ZC_MIN_SAMPLES
// should be between 50 and 80%. most of the time you get 100% during the calibration cycle
#ifndef DIMMER_ZC_MIN_VALID_SAMPLES
#    define DIMMER_ZC_MIN_VALID_SAMPLES ((uint8_t)(DIMMER_ZC_MIN_SAMPLES / 1.75))
#endif

static constexpr auto kValidSamplesPercent = DIMMER_ZC_MIN_VALID_SAMPLES * 100.0 / DIMMER_ZC_MIN_SAMPLES;
static_assert(kValidSamplesPercent >= 50 && kValidSamplesPercent <= 80, "read comment for DIMMER_ZC_MIN_VALID_SAMPLES");

// max. deviation per half cycle 
// if the deviation is too low too low, it filters too many events leading to flickering. too high **might** lead to visible flickering
// the maximum i measured was +-0.0718% with regular mains voltage and no filter, but the MCU might be stuck with interrupts disabled etc... 0.2% seem to be 
// visible to the human eye when the dimming is at very low levels (0.1-0.5W for a 10W LED, some don't work well and flicker even at >1.5W)
// 0.75% is low, if any issues with the calibration occurs, even 2% seems to work fine for the human eye depending on the LED and the level
// during testing even a high power (15A) unfiltered induction motor starting up seems to have no effect on the dimmer, while without filtering
// the zc crossing event was pretty useless leading to flickering even after the startup. in case the zero crossing does not provide a valid signal,
// the dimmer shuts down and restarts the calibration process
#ifndef DIMMER_ZC_INTERVAL_MAX_DEVIATION
#    define DIMMER_ZC_INTERVAL_MAX_DEVIATION (0.5 / 100.0)
#endif

static constexpr auto kDeviationPercent = DIMMER_ZC_INTERVAL_MAX_DEVIATION * 100;
static_assert(kDeviationPercent >= 0.25 && kDeviationPercent <= 3, "read comment for DIMMER_ZC_INTERVAL_MAX_DEVIATION");

// default mode
// 1 trailing edge
// 0 leading edge
#ifndef DIMMER_TRAILING_EDGE
#    define DIMMER_TRAILING_EDGE 1
#endif

#if DIMMER_TRAILING_EDGE == 0
#    warning EXPERIMENTAL, requires re-calibration
#endif

// 1 inverts the output signal
#ifndef DIMMER_MOSFET_ACTIVE_LOW
#    define DIMMER_MOSFET_ACTIVE_LOW 0
#endif

// pin state to turn MOSFETS on
#ifndef DIMMER_MOSFET_ON_STATE
#    define DIMMER_MOSFET_ON_STATE (DIMMER_MOSFET_ACTIVE_LOW ? LOW : HIGH)
#endif

// pin state to turn MOSFETS off
#ifndef DIMMER_MOSFET_OFF_STATE
#    define DIMMER_MOSFET_OFF_STATE (!DIMMER_MOSFET_ON_STATE)
#endif

// output pins as comma separated list
// channels will be address from 0 to max.
#ifndef DIMMER_MOSFET_PINS
#    define DIMMER_MOSFET_PINS 6, 8, 9, 10
#endif

// number of channels
#ifndef DIMMER_CHANNEL_COUNT
#    define DIMMER_CHANNEL_COUNT 4
#endif

// support for 0xff to set or fade all channels
#ifndef DIMMER_HAVE_SET_ALL_CHANNELS_AT_ONCE
#    define DIMMER_HAVE_SET_ALL_CHANNELS_AT_ONCE 0
#endif

// maximum number of different dimming levels
// the range can be adjusted with range_begin and range_end
// for most purposes 4096 or 8192 is enough. this provides a smooth dimming experience between 
// any level over 1-2 minutes (absolute time 0-100%)
// limited to < 32767, more than 16384 is not recommended
#ifndef DIMMER_MAX_LEVEL
#    define DIMMER_MAX_LEVEL 8192
#endif

// if set to 1, some code is being removed that is not required for more than 1 channel
// more than 8 channels changes some internal structures and the I2C protocol. the controller must be compiled with the same settings
//
// IMPORTANT: dimmer_protocol_const.h and fw_const_ver_*.py (if the python tool is being used) need to be updated
//  DIMMER_EVENT_CHANNEL_ON_OFF
//  DIMMER_COMMAND_READ_CHANNELS
//  struct dimmer_channel_state_event_t, register_mem_channels_t, register_mem_t
#ifndef DIMMER_MAX_CHANNELS
#    define DIMMER_MAX_CHANNELS 8
#endif

// the prescaler should be chosen to have maximum precision while having enough range for fine tuning
// prescaler 1 is used for measuring time

// timer1, 16 bit, used for the ZC delay and turning MOSFETs on and off
// all calculations are done in clock cycles divided by the prescaler and must be lower than ~64000 with a 16 bit timer
// the prediction is running at clock speed and is limited to ~8 million cycles
#ifndef DIMMER_TIMER1_PRESCALER
#    define DIMMER_TIMER1_PRESCALER 8
#endif

// sent event when fading has reached the target level
#ifndef HAVE_FADE_COMPLETION_EVENT
#    define HAVE_FADE_COMPLETION_EVENT 1
#endif

// do not display info during boot and disable DIMMER_COMMAND_PRINT_INFO
// ~1600 byte code size
#ifndef HIDE_DIMMER_INFO
#    define HIDE_DIMMER_INFO 0
#endif

// the ADC interrupt takes a lot of cycles blocking interrupts, only for fast MCUs
// ~360 byte less code
// not recommended anymore due to code size and blocking
#ifndef DIMMER_USE_ADC_INTERRUPT
#    define DIMMER_USE_ADC_INTERRUPT 0
#endif

// potentiometer for testing purposes
// the ADC is read 256x in a row continuously unless other readings are performed (VCC, NTC, ...)
#ifndef HAVE_POTI
#    define HAVE_POTI 0
#endif

// analog PIN for potentiometer
#ifndef POTI_PIN
#    define POTI_PIN A1
#endif

// channel controlled by potentiometer
#ifndef POTI_CHANNEL
#    define POTI_CHANNEL 0
#endif

#ifndef SERIAL_I2C_BRIDGE
#    define SERIAL_I2C_BRIDGE 0
#endif

#ifndef DEFAULT_BAUD_RATE
#    define DEFAULT_BAUD_RATE 57600
#endif

// interval in milliseconds
#ifndef DIMMER_TEMPERATURE_CHECK_INTERVAL
#    define DIMMER_TEMPERATURE_CHECK_INTERVAL 1024UL
#endif

static constexpr auto kDimmerCheckIntervalCycles = microsecondsToClockCycles(DIMMER_TEMPERATURE_CHECK_INTERVAL * 1000);

#ifndef HAVE_NTC
#    define HAVE_NTC 1
#endif

#ifndef HAVE_READ_VCC
#    define HAVE_READ_VCC 1
#endif

// default value for restore level
#ifndef DIMMER_RESTORE_LEVEL
#    define DIMMER_RESTORE_LEVEL 1
#endif

#ifndef DIMMER_REPORT_METRICS_INTERVAL
#    define DIMMER_REPORT_METRICS_INTERVAL 5
#endif

// after calibration VCC readings are pretty accurate, ±1-2mV
// NOTE: VCC is read 64x in a row, once per second and the capacitance of the ADC is very low,
// which can lead to jumping values if the VCC is not stable
// default for cfg.internal_1_1v_ref
#ifndef INTERNAL_VREF_1_1V
#    define INTERNAL_VREF_1_1V 1.1
#endif

// to get more stable (average) VCC readings, an additional circuit with more capacitance can be
// added to an analog port

// voltage divider on analog port
#ifndef HAVE_EXT_VCC
#    define HAVE_EXT_VCC 0
#endif

// pin to read VCC from. the value is compared against the internal VREF11
// the voltage divider for measuring 5V is R1=12K, R2=3K, R1=VCC to analog pin, R2=GND to analog pin
// for getting stable average voltage readings, add C1=1-10uF from analog pin to GND
#ifndef VCC_PIN
#    define VCC_PIN A0
#endif

// use internal temperature sensor
#ifndef HAVE_READ_INT_TEMP
#    define HAVE_READ_INT_TEMP 1
#endif

// default values for TS_OFFSET and TS_GAIN
//
// see data sheet for more infomation
// https://microchipdeveloper.com/8avr:avrtemp
// https://microchipdeveloper.com/8avr:avradc
// The voltage sensitivity is approximately 1 mV/°C, the accuracy of the temperature measurement is ±10°C.
//
// The values described in the table above are typical values. However, due to process variation the
// temperature sensor output voltage varies from one chip to another. To be capable of achieving more
// accurate results the temperature measurement can be calibrated in the application software
#if DIMMER_HEADERS_ONLY
#elif __AVR_ATmega328PB__ || MCU_IS_ATMEGA328PB == 1

#    ifndef DIMMER_AVR_TEMP_TS_OFFSET
#       define DIMMER_AVR_TEMP_TS_OFFSET 112
#    endif
#    ifndef DIMMER_AVR_TEMP_TS_GAIN
#       define DIMMER_AVR_TEMP_TS_GAIN 156
#   endif

#elif __AVR_ATmega328P__ && MCU_IS_ATMEGA328PB == 0

// Atmega328P only: DIMMER_AVR_TEMP_TS_GAIN = 0 reads the internal calibration values from the signature bytes
#    ifndef DIMMER_AVR_TEMP_TS_OFFSET
#        define DIMMER_AVR_TEMP_TS_OFFSET 0
#        define DIMMER_AVR_TEMP_TS_GAIN   0
#    endif

#else

#    error DIMMER_AVR_TEMP_TS_GAIN and DIMMER_AVR_TEMP_TS_OFFSET must be defined

#endif

// NTC pin
#ifndef NTC_PIN
#    define NTC_PIN A1
#endif
// beta coefficient
#ifndef NTC_BETA_COEFF
#    define NTC_BETA_COEFF 3950
#endif
// resistor in series with the NTC
#ifndef NTC_SERIES_RESISTANCE
#    define NTC_SERIES_RESISTANCE 3300
#endif
// ntc resistance @ 25°C
#ifndef NTC_NOMINAL_RESISTANCE
#    define NTC_NOMINAL_RESISTANCE 10000
#endif

#ifndef NTC_NOMINAL_TEMP
#    define NTC_NOMINAL_TEMP 25
#endif

#define SERIAL_INPUT_BUFFER_MAX_LENGTH 64
#define SERIAL_MAX_ARGUMENTS           10

#ifndef HAVE_PRINT_METRICS
#    define HAVE_PRINT_METRICS 0
#endif

#ifndef EEPROM_WRITE_DELAY
#    define EEPROM_WRITE_DELAY 500
#endif

#ifndef EEPROM_REPEATED_WRITE_DELAY
#    define EEPROM_REPEATED_WRITE_DELAY 5000
#endif

#ifndef DIMMER_CUBIC_INTERPOLATION
#   define DIMMER_CUBIC_INTERPOLATION 0
#endif

// run set_level and fade_to in main loop
// speeds up _dimmer_i2c_on_receive() and should be enabled if this method is called inside an ISR
#ifndef DIMMER_USE_QUEUE_LEVELS
#    define DIMMER_USE_QUEUE_LEVELS 0
#endif

#if DIMMER_CUBIC_INTERPOLATION
#    define DIMMER_LINEAR_LEVEL(level, channel) (register_mem.data.cfg.bits.cubic_interpolation ? cubicInterpolation.getLevel(level, channel) : level)
#    if DIMMER_CUBIC_INTERPOLATION
#        ifndef DIMMER_INTERPOLATION_METHOD
#            define DIMMER_INTERPOLATION_METHOD CatmullSpline
// #            define DIMMER_INTERPOLATION_METHOD ConstrainedSpline
#        endif
#    endif
#   ifndef INTERPOLATION_LIB_XYVALUES_TYPE
#       error define INTERPOLATION_LIB_XYVALUES_TYPE=uint8_t
#   endif
#else
#    define DIMMER_LINEAR_LEVEL(level, channel) level
#endif

// the performance depends on the actual points that have been defined, not the maximum
// if the calculation cannot be performed within one half wave (~8.33-10ms), it will not update the values until all channels have been finished
// 4 channels @ 8MHz and 4 demanding curves work well
#ifndef DIMMER_CUBIC_INT_DATA_POINTS
#   define DIMMER_CUBIC_INT_DATA_POINTS 8
#endif

#if DIMMER_CUBIC_INT_DATA_POINTS > 8
#   error DIMMER_CUBIC_INT_DATA_POINTS is limited to 8
#endif

#ifndef DIMMER_VERSION_MAJOR
#    error version not defined
#endif

#define DIMMER_VERSION               \
    _STRINGIFY(DIMMER_VERSION_MAJOR) \
    "." _STRINGIFY(DIMMER_VERSION_MINOR) "." _STRINGIFY(DIMMER_VERSION_REVISION)
#define DIMMER_INFO "Author sascha_lammers@gmx.de"

#if DIMMER_MAX_CHANNELS > 1
#    define DIMMER_CHANNEL_LOOP(var) for (Dimmer::Channel::type var = 0; var < Dimmer::Channel::size(); var++)
#else
#    define DIMMER_CHANNEL_LOOP(var) constexpr Dimmer::Channel::type var = 0;
#endif

#if __GNUC__ > 3
#    define __GNUC_STR__ ",gcc=" _STRINGIFY(__GNUC__) "." _STRINGIFY(__GNUC_MINOR__) "." _STRINGIFY(__GNUC_PATCHLEVEL__)
#else
#    define __GNUC_STR__ ""
#endif

#if DIMMER_HEADERS_ONLY
#    define F_CPU_MHZ 0
#elif F_CPU == 20000000UL
#    define F_CPU_MHZ 20
#elif F_CPU == 16000000UL
#    define F_CPU_MHZ 16
#elif F_CPU == 8000000UL
#    define F_CPU_MHZ 8
#elif F_CPU == 4000000UL
#    define F_CPU_MHZ 4
#elif F_CPU == 2000000UL
#    define F_CPU_MHZ 2
#elif F_CPU == 1000000UL
#    define F_CPU_MHZ 1
#else
#    error define F_CPU_MHZ
#endif
