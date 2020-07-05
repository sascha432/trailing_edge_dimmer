/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <util/atomic.h>
#include "arduino_eeprom_config.h"
#if DIMMER_USE_INLINE_ASM
#include "dimmer_sfr.h"
#endif

#ifndef DIMMER_CUBIC_INTERPOLATION
#define DIMMER_CUBIC_INTERPOLATION                              1
#endif

#if DIMMER_CUBIC_INTERPOLATION
#ifndef DIMMER_INTERPOLATION_METHOD
#define DIMMER_INTERPOLATION_METHOD		CatmullSpline
// #define DIMMER_INTERPOLATION_METHOD		ConstrainedSpline
#endif
#endif

// enable extra debugging to detect invalid states
#ifndef DEBUG_FAULTS
#define DEBUG_FAULTS                                            0
#endif

// enable extra debugging to detect invalid states
#ifndef DEBUG_STATISTICS
#define DEBUG_STATISTICS                                        1
#endif

// internal signal generator on pin 11
#ifndef DIMMER_SIGNAL_GENERATOR
#define DIMMER_SIGNAL_GENERATOR                                 0
#endif

#ifndef DEBUG_PIN
// extra pin for debug output
#define DEBUG_PIN                                               0
#endif

#ifndef DIMMER_MAX_TEMP
#define DIMMER_MAX_TEMP                                         80
#endif

// reference voltage is 1.1
#ifndef DIMMER_ATMEGA_VREF11
#define DIMMER_ATMEGA_VREF11                                    1.1
#endif

// temperature offset in °C for the NTC
// -15.5 to +15.5°C, precison 0.125
#ifndef DIMMER_TEMPERATURE_OFFSET
#define DIMMER_TEMPERATURE_OFFSET                               0.0
#endif

// temperature offset in °C for the internal ATmega sensor
#ifndef DIMMER_TEMPERATURE2_OFFSET
#define DIMMER_TEMPERATURE2_OFFSET                              0.0
#endif

#define DIMMER_TEMP_OFFSET_DIVIDER                              8.0

#ifndef ZC_SIGNAL_PIN
#define ZC_SIGNAL_PIN                                           3
#endif

#if DIMMER_CHANNELS > 1
#if !defined(DIMMER_USE_INLINE_ASM) || !DIMMER_USE_INLINE_ASM
#warning For more than 1 channel it is recommended to activate inline assembler
#endif
#endif

// a positive value adds a delay after the ZC interrupt, the ZC signal occurs before the actual ZC
// a negative value assumes that the ZC signal occurs after the actual ZC
// time in microseconds
// @16Mhz there is a 12µs offset between the interrupt being triggered and the first channel turned on
// -12 would be an exact match. this time might be different depending on number of channels, optimization
// levels, CPU speed, etc...
#ifndef DIMMER_ZC_DELAY_US
#define DIMMER_ZC_DELAY_US                                      144  // in µs
#endif

#ifndef DIMMER_ZC_INTERRUPT_MODE
#define DIMMER_ZC_INTERRUPT_MODE                                RISING
#endif

// minimum on time in microseconds
#ifndef DIMMER_MIN_ON_TIME_US
#define DIMMER_MIN_ON_TIME_US                                   100
#endif

// the maximum on time is the halfwave in microseconds minus DIMMER_MIN_OFF_TIME_US
// if the value is exceeded, mosfets are not turned off anymore.
#ifndef DIMMER_MIN_OFF_TIME_US
#define DIMMER_MIN_OFF_TIME_US                                  300
#endif
#if DIMMER_MIN_OFF_TIME_US < 200
#error DIMMER_MIN_OFF_TIME_US must be greater than 200
#endif

#ifndef DIMMER_MEASURE_CYCLES
#define DIMMER_MEASURE_CYCLES                                   30
#endif

#ifndef DIMMER_CHANNELS
#define DIMMER_CHANNELS                                         4
#endif

#ifndef DIMMER_MOSFET_PINS
    #define DIMMER_MOSFET_PINS                                  { 6, 8, 9, 10 }
#endif

static constexpr uint8_t kDimmerPins[DIMMER_CHANNELS] = DIMMER_MOSFET_PINS;

// 0 to (DIMMER_MAX_LEVELS-1)
// default 0 - 8191
#ifndef DIMMER_MAX_LEVELS
#define DIMMER_MAX_LEVELS                                       8192
#endif

#if DIMMER_CUBIC_INTERPOLATION
#define DIMMER_LINEAR_LEVEL(level, channel)                     (dimmer_config.bits.cubic_interpolation == 1 ? level : cubicInterpolation.getLevel(level, channel))
#else
#define DIMMER_LINEAR_LEVEL(level, channel)                     level
#endif

// enable ZC interrupt filter
// it ignores all zc interrupts that occur before the halfwave cycle reached 94% (~88%/53Hz for 60Hz)
#ifndef DIMMER_ZC_FILTER
#define DIMMER_ZC_FILTER                                        1
#endif

// #define DIMMER_TIMER1_PRESCALER                                 1
// #define DIMMER_TIMER1_PRESCALER_BV                              _BV(CS10)

#define DIMMER_TIMER1_PRESCALER                                 8
#define DIMMER_TIMER1_PRESCALER_BV                              _BV(CS11)

// #define DIMMER_TIMER1_PRESCALER                                 256
// #define DIMMER_TIMER1_PRESCALER_BV                              _BV(CS12)

// extra ticks for compare B interrupt to finish
// requires ~176-184 cpu cycles
#define DIMMER_COMPARE_B_EXTRA_TICKS                            (512 / DIMMER_TIMER1_PRESCALER)

// extra ticks before starting new halfwave
#define DIMMER_COMPARE_A_EXTRA_TICKS                            (64 / DIMMER_TIMER1_PRESCALER)

// extra clock cycles in Dimmer::_dimmingCycle()
#define DIMMER_EXTRA_TICKS                                      ((64 / DIMMER_TIMER1_PRESCALER) + 1)

#define DIMMER_T1_TICKS_PER_US                                  (clockCyclesPerMicrosecond() / (float)DIMMER_TIMER1_PRESCALER)

#define DIMMER_T1_US_TO_TICKS(us )                              (us * (clockCyclesPerMicrosecond() / DIMMER_TIMER1_PRESCALER))
#define DIMMER_T1_TICKS_TO_US(ticks)                            (ticks / (clockCyclesPerMicrosecond() / DIMMER_TIMER1_PRESCALER))
#define DIMMER_T1_TICKS_TO_US_FLOAT(ticks)                      (ticks / (float)(clockCyclesPerMicrosecond() / DIMMER_TIMER1_PRESCALER))

#ifndef HAVE_FADE_COMPLETION_EVENT
#define HAVE_FADE_COMPLETION_EVENT                              1
#endif

// check temperature and update metrics every n milliseconds
#ifndef DIMMER_UPDATE_METRICS_INTERVAL
#define DIMMER_UPDATE_METRICS_INTERVAL                          2500UL
#endif

#ifndef DIMMER_EEPROM_WRITE_DELAY
// write EEPROM after a delay in milliseconds
#define DIMMER_EEPROM_WRITE_DELAY                               500
#endif


#define DIMMER_VERSION_WORD                                     ((3 << 10) | (0 << 5) | 0)
#define DIMMER_VERSION                                          "3.0.0"
#define DIMMER_INFO                                             "Author sascha_lammers@gmx.de"

#define _STRINGIFY(...)                                         ___STRINGIFY(__VA_ARGS__)
#define ___STRINGIFY(...)                                       #__VA_ARGS__

typedef int8_t dimmer_channel_id_t;
typedef int16_t dimmer_level_t;

#define FOR_CHANNELS(var)                                       for(dimmer_channel_id_t var = 0; var < DIMMER_CHANNELS; var++)

#define INVALID_LEVEL                                           -1
#define DIMMER_FADE_FROM_CURRENT_LEVEL                          -1

#ifndef __attribute__packed__
#define __attribute__packed__                                   __attribute__((packed))
#endif

typedef struct {
    float level;
    float step;
    uint16_t count;
    dimmer_level_t targetLevel;
} dimmer_fade_t;

typedef struct {
    uint8_t channel;
    uint16_t ticks;
#if DEBUG_FAULTS
    uint16_t _OCR1A;
#endif
} dimmer_channel_t;

#define dimmer_level(ch)        register_mem.data.channels.level[ch]
#define dimmer_config           register_mem.data.cfg

class dimmer_t
{
public:
    dimmer_t() = default;

    dimmer_fade_t fade[DIMMER_CHANNELS];                                // calculated fading data
    dimmer_channel_t *channel_ptr;
    dimmer_channel_t ordered_channels[DIMMER_CHANNELS + 1];             // current dimming levels in ticks
    dimmer_channel_t ordered_channels_buffer[DIMMER_CHANNELS + 1];      // next dimming levels
#if DIMMER_USE_INLINE_ASM
    dimmer_enable_mask_t enable_channel_mask;
    dimmer_enable_mask_t enable_channel_mask_buffer;
#endif
};

class Dimmer : public dimmer_t
{
public:
    enum class StateEnum : uint8_t {
        MEASURE,            // measuring active
        STOPPED,            // waiting to be enabled
        START_HALFWAVE,     // waiting for halfwave to begin
        HALFWAVE,           // dimming cycle
        NEXT_HALFWAVE,      // waiting for next ZC interrupt
    };

    static constexpr uint8_t _IFOCB  = 0;           // compare B lock
    static constexpr uint8_t _IFOCA  = 1;           // compare A lock
    static constexpr uint8_t _IFZCI  = 2;           // ZC interrupt lock
    static constexpr uint8_t _IFCHL  = 3;           // calculate channel lock
    static constexpr uint8_t _IFCHA  = 4;           // calculate channel abort request

    static constexpr dimmer_channel_id_t kMaxChannels = DIMMER_CHANNELS;
    static constexpr dimmer_level_t kMaxLevels = DIMMER_MAX_LEVELS;
    static constexpr uint8_t kCubicIntMaxDataPoints = DIMMER_CUBIC_INT_DATA_POINTS;

    static constexpr bool isChannelValid(dimmer_channel_id_t channel) {
        return (uint8_t)channel < (uint8_t)kMaxChannels;
    }

public:
    Dimmer();

    void disableTimer1() const;
    void enableTimer1() const;

    void begin();
    void end();

    // enable dimmer after the frequency measurement has been completed
    void enable();

public:
    inline uint16_t getHalfWaveTicks() const {
        return _halfwaveTicks;
    }
    float getFrequency() const;

    bool measure(uint16_t timeout);             // run measurement cycles
    void addEvent(uint16_t counter);

    uint32_t getTicks(uint16_t counter);        // return ticks since last call
    uint32_t getTicksNoRst(uint16_t counter);   // return ticks since last call of getTicks()

    // toggle mosfet gates
    void enableChannel(dimmer_channel_id_t channel);
    void disableChannel(dimmer_channel_id_t channel);

    uint16_t getChannel(dimmer_level_t level) const;    // returns level in ticks or 0xffff for 100%

public:
    void setLevel(dimmer_channel_id_t channel, dimmer_level_t level);
    dimmer_level_t getLevel(dimmer_channel_id_t channel) const;

    // copy levels for all channels
    void copyLevels(WearLevelData_t &settings);

    void setFade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time, bool absolute_time = false);
    inline void setFadeTo(dimmer_channel_id_t channel, dimmer_channel_id_t to_level, float time_in_seconds, bool absolute_time = false) {
        setFade(channel, DIMMER_FADE_FROM_CURRENT_LEVEL, to_level, time_in_seconds, absolute_time);
    }

private:
    void _setFade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time, bool absolute_time = false);
    void _applyFading();
    void _calculateChannels();

    // calculate channel helpers
    inline void _unlockCalc() {
        _intFlags &= ~_BV(_IFCHL);
    }
    inline void _lockCalc() {
        _intFlags |= _BV(_IFCHL);
    }
    inline bool _isCalcLocked() const {
        return _intFlags & _BV(_IFCHL);
    }
    inline void _setAbortCalc() {
        _intFlags |= _BV(_IFCHA);
    }
    inline void _unsetAbortCalcAndUnlock() {
        _intFlags &= ~(_BV(_IFCHA)|_BV(_IFCHL));
    }
    inline bool _isAbortCalc() const {
        return _intFlags & _BV(_IFCHA);
    }

    // other helpers
    inline void _lockCompareA() {
        _intFlags |= _BV(_IFOCA);
    }
    inline void _unlockCompareA() {
        _intFlags &= ~_BV(_IFOCA);
    }
    inline bool  _isCompareALocked() const {
        return _intFlags & _BV(_IFOCA);
    }

    inline void _lockCompareB() {
        _intFlags |= _BV(_IFOCB);
    }
    inline void _unlockCompareB() {
        _intFlags &= ~_BV(_IFOCB);
    }
    inline bool _isCompareBLocked() const {
        return _intFlags & _BV(_IFOCB);
    }

    inline void _lockZC() {
        _intFlags |= _BV(_IFZCI);
    }
    inline void _unlockZC() {
        _intFlags &= ~_BV(_IFZCI);
    }
    inline bool _isZCLocked() const {
        return _intFlags & _BV(_IFZCI);
    }

public:
    inline bool _isOvfPending() const {
        return TIFR1 & _BV(TOV1);
    }

public:
    // interrupt handler
    void _zcHandler(uint16_t counter);
    void _compareA();
    void _compareB();
    void _overflow();

private:
    void _startHalfwave();
    void _dimmingCycle(uint16_t startOCR1A);
    void _endHalfwave();

private:
    volatile uint16_t _halfwaveTicks;

    volatile int32_t _ticks;
    uint8_t _cycleCounter;

#if DIMMER_ZC_FILTER
    uint32_t _zcIntTimer;
    uint32_t _zcIntMinTime;
#endif

#if DEBUG_FAULTS
private:
    void _fault(const char *msg);

    volatile uint16_t _prevOCR1B;
    volatile uint16_t _dcOCR1A;
    volatile uint8_t _startCounter;
    volatile uint8_t _endCounter;
#endif

private:
    volatile StateEnum _state;
    volatile uint16_t _startOCR1A;
    volatile uint8_t _missedZCCounter;
    volatile uint8_t _intFlags;
    float _halfwaveTicksIntegral;

#if !DIMMER_USE_INLINE_ASM
    volatile uint8_t *_pinsAddr[DIMMER_CHANNELS];
    uint8_t _pinsMask[DIMMER_CHANNELS];
#endif

#if HAVE_FADE_COMPLETION_EVENT

public:
    inline void sendFadingCompletedEvents() {
        _fadingCompletedEvents.sendEvents();
    }

private:
    class FadingCompletedEvents {
    public:
        static constexpr uint8_t kMaxFadingCompletedEvents = kMaxChannels * 8;

    public:
        FadingCompletedEvents();

        void addEvent(dimmer_channel_id_t channel, dimmer_level_t level);
        void sendEvents();

        uint8_t size() const;
        bool notEmpty() const;

    private:
        volatile uint8_t _readIndex;
        volatile uint8_t _writeIndex;
        dimmer_fading_completed_event_t _fadingCompletedBuffer[kMaxFadingCompletedEvents];
    };

    FadingCompletedEvents _fadingCompletedEvents;

#else

    inline void sendFadingCompletedEvents() {}

#endif
};

extern Dimmer dimmer;

#if DEBUG_STATISTICS

#include "dimmer_stats.h"

#endif
