/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>

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

#ifndef DEBUG_COMPARE_B_PIN
// toggle pin each time the compare B interrupt gets called
#define DEBUG_COMPARE_B_PIN                                     0
#endif

#ifndef DIMMER_CUBIC_INT_TABLE_SIZE
#define DIMMER_CUBIC_INT_TABLE_SIZE                             8
#endif

#ifndef DIMMER_SIMULATE_ZC
#define DIMMER_SIMULATE_ZC                                      0
#endif

#ifndef DIMMER_MAX_TEMP
#define DIMMER_MAX_TEMP                                         80
#endif

#define DIMMER_TEMP_OFFSET_DIVIDER                              4.0f

#ifndef ZC_SIGNAL_PIN
#define ZC_SIGNAL_PIN                                           3
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

// the maximum on time is the halfwave in microseconds minus DIMMER_MAX_ON_TIME_US
// if the value is exceeded, mosfets are not turned off anymore.
#ifndef DIMMER_MAX_ON_TIME_US
#define DIMMER_MAX_ON_TIME_US                                   300
#endif
#if DIMMER_MAX_ON_TIME_US < 200
#error DIMMER_MAX_ON_TIME_US must be greater than 200
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

static constexpr uint8_t dimmer_pins[DIMMER_CHANNELS] = DIMMER_MOSFET_PINS;

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

// extra clock cycles in Dimmer::_dimmingCycle()
#define DIMMER_EXTRA_TICKS                                      ((64 / DIMMER_TIMER1_PRESCALER) + 1)

#define DIMMER_T1_TICKS_PER_US                                  (clockCyclesPerMicrosecond() / (float)DIMMER_TIMER1_PRESCALER)

#define DIMMER_T1_US_TO_TICKS(us )                              (us * (clockCyclesPerMicrosecond() / DIMMER_TIMER1_PRESCALER))
#define DIMMER_T1_TICKS_TO_US(ticks)                            (ticks / (clockCyclesPerMicrosecond() / DIMMER_TIMER1_PRESCALER))
#define DIMMER_T1_TICKS_TO_US_FLOAT(ticks)                      (ticks / (float)(clockCyclesPerMicrosecond() / DIMMER_TIMER1_PRESCALER))

#ifndef HAVE_FADE_COMPLETION_EVENT
#define HAVE_FADE_COMPLETION_EVENT                              1
#endif

#define DIMMER_VERSION_WORD                                     ((3 << 10) | (0 << 5) | 0)
#define DIMMER_VERSION                                          "3.0.0"
#define DIMMER_INFO                                             "Author sascha_lammers@gmx.de"

#ifndef DIMMER_I2C_SLAVE
#define DIMMER_I2C_SLAVE                                        1
#endif

#define DIMMER_REGISTER_MEM_END_PTR                             &register_mem.raw[sizeof(register_mem_t)]

#define _STRINGIFY(...)                                         ___STRINGIFY(__VA_ARGS__)
#define ___STRINGIFY(...)                                       #__VA_ARGS__

typedef int8_t dimmer_channel_id_t;
typedef int16_t dimmer_level_t;

#define FOR_CHANNELS(var)                                       for(dimmer_channel_id_t var = 0; var < DIMMER_CHANNELS; var++)

struct dimmer_fade_t {
    float level;
    float step;
    uint16_t count;
    dimmer_level_t targetLevel;
};

struct dimmer_channel_t {
    uint8_t channel;
    uint16_t ticks;
#if DEBUG_FAULTS
    uint16_t _OCR1A;
#endif
};

typedef struct __attribute__packed__ {
    dimmer_channel_id_t channel;
    dimmer_level_t level;
} FadingCompletionEvent_t;

#define INVALID_LEVEL                                           -1

#if DIMMER_I2C_SLAVE
#define dimmer_level(ch)        register_mem.data.level[ch]
#define dimmer_config           register_mem.data.cfg
#else
#define dimmer_level(ch)        dimmer.level[ch]
#define dimmer_config           dimmer.cfg
#endif

class dimmer_t
{
public:
    dimmer_t() = default;

#if !DIMMER_I2C_SLAVE
    dimmer_level_t level[DIMMER_CHANNELS];                              // current level
    struct {
        uint8_t zero_crossing_delay_ticks;
        uint16_t minimum_on_time_ticks;
        uint16_t adjust_halfwave_time_ticks;
    } cfg;
#endif
    dimmer_fade_t fade[DIMMER_CHANNELS];                                // calculated fading data
    dimmer_channel_t *channel_ptr;
    dimmer_channel_t ordered_channels[DIMMER_CHANNELS + 1];             // current dimming levels in ticks
    dimmer_channel_t ordered_channels_buffer[DIMMER_CHANNELS + 1];      // next dimming levels

#if HAVE_FADE_COMPLETION_EVENT
    volatile dimmer_level_t fadingCompleted[DIMMER_CHANNELS];
#endif
};

#define DIMMER_FADE_FROM_CURRENT_LEVEL                          -1

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

    // typedef struct {
    //     uint8_t compareABLock: 1;
    //     uint8_t ZCIntLock: 1;
    //     uint8_t calculateChannelsLock: 1;
    //     uint8_t calculateChannelsAbort: 1;
    // } IntFlags_t;

    static constexpr uint8_t _IFCAB  = 0;           // compare A/B lock
    static constexpr uint8_t _IFZCI  = 1;           // ZC interrupt lock
    static constexpr uint8_t _IFCHL  = 2;           // calculate channel lock
    static constexpr uint8_t _IFCHA  = 3;           // calculate channel abort request

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

#if HAVE_ASM_CHANNELS

    #include "dimmer_inline_asm.h"

#else
    // toggle mosfet gates
    void enableChannel(dimmer_channel_id_t channel);
    void disableChannel(dimmer_channel_id_t channel);

#endif

    uint16_t getChannel(dimmer_level_t level) const;    // returns level in ticks or 0xffff for 100%

public:
    void setLevel(dimmer_channel_id_t channel, dimmer_level_t level);
    dimmer_level_t getLevel(dimmer_channel_id_t channel) const;

    void setFade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time, bool absolute_time = false);
    inline void setFadeTo(dimmer_channel_id_t channel, dimmer_channel_id_t to_level, float time_in_seconds, bool absolute_time = false) {
        setFade(channel, DIMMER_FADE_FROM_CURRENT_LEVEL, to_level, time_in_seconds, absolute_time);
    }

private:
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
    inline void _unsetAbortCalc() {
        _intFlags &= ~_BV(_IFCHA);
    }
    inline void _unsetAbortCalcAndUnlock() {
        _intFlags &= ~(_BV(_IFCHA)|_BV(_IFCHL));
    }
    inline bool _isAbortCalc() const {
        // return ((IntFlags_t *)&_intFlags)->calculateChannelsAbort;
        return _intFlags & _BV(_IFCHA);
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
    volatile uint8_t _cycleCounter;

#if DIMMER_ZC_FILTER
    volatile uint32_t _zcIntTimer;
    volatile uint32_t _zcIntMinTime;
#endif

#if DEBUG_FAULTS
private:
    void _fault(const char *msg);

    volatile uint16_t _prevOCR1B;
    volatile uint16_t _dcOCR1A;
#endif

private:
    volatile StateEnum _state;
    volatile uint8_t _intFlags;
    volatile float _halfwaveTicksIntegral;

#if !HAVE_ASM_CHANNELS
    volatile uint8_t *_pinsAddr[DIMMER_CHANNELS];
    uint8_t _pinsMask[DIMMER_CHANNELS];
#endif
};

extern Dimmer dimmer;
