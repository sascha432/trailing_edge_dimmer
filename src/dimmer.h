/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>

#ifndef ZC_SIGNAL_PIN
#define ZC_SIGNAL_PIN                                           3
#endif

// **********************************
//  NOTE:
//  for timing see docs/timings.svg
// **********************************

// the exact delay depends on the zero crossing detection, the prescaler and the CPU speed, the propagation delay and overall
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

// default for DIMMER_REGISTER_ZC_DELAY_TICKS
#ifndef DIMMER_ZC_DELAY_US
#define DIMMER_ZC_DELAY_US                                      104  // in µs
#endif

// default for DIMMER_REGISTER_MIN_ON_TIME_TICKS
#ifndef DIMMER_MIN_ON_TIME_US
// minimum on time is dead space at the dimming range. a level lower than the minimum on
// time does not have any affect until it is 0 and the mosfets are turned off completely
#define DIMMER_MIN_ON_TIME_US                                   200 // minimum "on"-time in µs
#endif

// default for DIMMER_REGISTER_ADJ_HALFWAVE_TICKS
#ifndef DIMMER_ADJUST_HALFWAVE_US
// some LEDs have issues and are flickering if the mosfets are turned on over 95% of the half wave, but not 100%
// this adjustment reduces the maximum on time while it does not reduce the dimming range (max level). if max level
// is set to 100%, the mosfets do not turn off anymore.
// basically: HALFWAVE_TIME_US - DIMMER_ADJUST_HALFWAVE_US = DIMMER_MAX_ON_TIME_US
#define DIMMER_ADJUST_HALFWAVE_US                               200 // reduce "on"-time in µs
#endif

// some LEDs have a soft start function. to get smooth fading, the minimum level is set
// and a specific delay occurs before fading starts. that leaves enough time until the
// LED has finished the soft start.
#ifndef DIMMER_MIN_LEVEL
#define DIMMER_MIN_LEVEL                                        0 // 8
#define DIMMER_MIN_LEVEL_TIME_IN_MS                             800
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

// fading command
#define DIMMER_USE_FADING                                       1

// for more than 10 channels it might be necessary to disable the linear correction or use a different method to calculate it. see DIMMER_LINEAR_LEVEL()
#ifndef DIMMER_CHANNELS
#define DIMMER_CHANNELS                                         4
#endif

#ifndef DIMMER_MOSFET_PINS
    #define DIMMER_MOSFET_PINS                                  { 6, 8, 9, 10 }
#endif

static const uint8_t dimmer_pins[DIMMER_CHANNELS] = DIMMER_MOSFET_PINS;

// sets the maximum level (100%)
#ifndef DIMMER_MAX_LEVEL
    #define DIMMER_MAX_LEVEL                                    min(32767, DIMMER_TICKS_PER_HALFWAVE)
    // #define DIMMER_MAX_LEVEL                            8191
    // #define DIMMER_MAX_LEVEL                            1023
    // #define DIMMER_MAX_LEVEL                            255
    // #define DIMMER_MAX_LEVEL                            100
#endif

// adjust the time to have a linear level. most LEDs have a built in compensation.
// using the factor 1.0 disables the time consuming calculations with having the option
// to change it without a firmware upgrade
#ifndef DIMMER_USE_LINEAR_CORRECTION
    #define DIMMER_USE_LINEAR_CORRECTION                        1
#endif

#ifndef DIMMER_LINEAR_FACTOR
    #define DIMMER_LINEAR_FACTOR                                1.0
#endif

#if DIMMER_USE_LINEAR_CORRECTION
// pow() is pretty slow
#define DIMMER_LINEAR_LEVEL(level)                              (dimmer_config.linear_correction_factor == 1 ? level : (float)pow(level, dimmer_config.linear_correction_factor) * dimmer.linear_correction_divider)
#else
#define DIMMER_LINEAR_LEVEL(level)                              level
#endif

// the prescaler should be chosen to have maximum precision while having enough range for fine tuning

// timer1, 16 bit, used for turning MOSFETs on and off
#ifndef DIMMER_TIMER1_PRESCALER
#define DIMMER_TIMER1_PRESCALER                                 8
#endif

// timer2, 8bit, used to delay the turn on after receiving the ZC signal
#ifndef DIMMER_TIMER2_PRESCALER
#define DIMMER_TIMER2_PRESCALER                                 64
#endif

#if DIMMER_TIMER2_PRESCALER == 64
#define DIMMER_TIMER2_PRESCALER_BV                              (1 << CS22)
#elif DIMMER_TIMER2_PRESCALER == 128
#define DIMMER_TIMER2_PRESCALER_BV                              ((1 << CS22) | (1 << CS20))
#elif DIMMER_TIMER2_PRESCALER == 256
#define DIMMER_TIMER2_PRESCALER_BV                              ((1 << CS22) | (1 << CS21))
#elif DIMMER_TIMER2_PRESCALER == 1024
#define DIMMER_TIMER2_PRESCALER_BV                              ((1 << CS22) | (1 << CS21) | (1 << CS20))
#else
#error prescaler not supported
#endif

#if DIMMER_TIMER1_PRESCALER == 8
    #define DIMMER_TIMER1_PRESCALER_BV                          (1 << CS11)
    #define DIMMER_EXTRA_TICKS                                  8           // add some extra ticks that the timer interrupt doesn't skip turning off a mosfet if the timer interrupts are very close
#elif DIMMER_TIMER1_PRESCALER == 64
    #define DIMMER_TIMER1_PRESCALER_BV                          ((1 << CS11) | (1 << CS10))
    #define DIMMER_EXTRA_TICKS                                  1
#elif DIMMER_TIMER1_PRESCALER == 256
    #define DIMMER_TIMER1_PRESCALER_BV                          (1 << CS12)
    #define DIMMER_EXTRA_TICKS                                  1
#else
    #error prescaler not supported
#endif

#define DIMMER_START_TIMER1()                                   TCCR1B |= DIMMER_TIMER1_PRESCALER_BV;
#define DIMMER_PAUSE_TIMER1()                                   TCCR1B = 0;
#define DIMMER_START_TIMER2()                                   TCCR2B |= DIMMER_TIMER2_PRESCALER_BV;
#define DIMMER_PAUSE_TIMER2()                                   TCCR2B = 0;

#define DIMMER_GET_TICKS(level)                                 max(dimmer_config.minimum_on_time_ticks, (level * DIMMER_TICKS_PER_HALFWAVE) / DIMMER_MAX_LEVEL - dimmer_config.adjust_halfwave_time_ticks)

#define DIMMER_ENABLE_TIMERS()                                  { TIMSK1 |= (1 << OCIE1A); TCCR1A = 0; TCCR1B = 0; TIMSK2 |= (1 << OCIE2A); TCCR2A = 0; TCCR2B = 0; }
#define DIMMER_DISABLE_TIMERS()                                 { TIMSK1 &= ~(1 << OCIE1A); TIMSK2 &= ~(1 << OCIE2A); }

#define DIMMER_TICKS_PER_HALFWAVE                               (F_CPU / DIMMER_TIMER1_PRESCALER / (DIMMER_AC_FREQUENCY * 2))
#define DIMMER_TMR1_TICKS_PER_US                                (F_CPU / DIMMER_TIMER1_PRESCALER / 1000000.0)
#define DIMMER_TMR2_TICKS_PER_US                                (F_CPU / DIMMER_TIMER2_PRESCALER / 1000000.0)

#define DIMMER_US_TO_TICKS(us, ticks_per_us)                    (us * ticks_per_us)
#define DIMMER_TICKS_TO_US(ticks, ticks_per_us)                 (ticks / ticks_per_us)


#if DIMMER_TICKS_PER_HALFWAVE > 32767
    #error TICKS are limited to 32767 per half wave, increase prescaler
#endif

#ifndef HAVE_FADE_COMPLETION_EVENT
#if DIMMER_USE_FADING == 0
#define HAVE_FADE_COMPLETION_EVENT                              0
#else
#define HAVE_FADE_COMPLETION_EVENT                              1
#endif
#endif

#ifndef HIDE_DIMMER_INFO
#define HIDE_DIMMER_INFO                                        0
#endif

// the frequency is updated twice per second
// 0 disables frequency messuring
#ifndef FREQUENCY_TEST_DURATION
#define FREQUENCY_TEST_DURATION                                 600

float dimmer_get_frequency();
#endif

#define DIMMER_VERSION_WORD                                     ((2 << 10) | (1 << 5) | 0)
#define DIMMER_VERSION                                          "2.1.0"
#define DIMMER_INFO                                             "Author sascha_lammers@gmx.de"

#ifndef DIMMER_I2C_SLAVE
#define DIMMER_I2C_SLAVE                                        1
#endif

typedef int8_t dimmer_channel_id_t;
typedef int16_t dimmer_level_t;

struct dimmer_fade_t {
    float level;
    float step;
    uint16_t count;
    dimmer_level_t targetLevel;
};

struct dimmer_channel_t {
    uint8_t channel;
    uint16_t ticks;
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

struct dimmer_t {
#if !DIMMER_I2C_SLAVE
    dimmer_level_t level[DIMMER_CHANNELS];                              // current level
    struct {
        uint8_t zero_crossing_delay_ticks;
        uint16_t minimum_on_time_ticks;
        uint16_t adjust_halfwave_time_ticks;
        float linear_correction_factor;
    } cfg;
#endif
#if DIMMER_USE_FADING
    dimmer_fade_t fade[DIMMER_CHANNELS];                                // calculated fading data
#endif
#if DIMMER_USE_LINEAR_CORRECTION
    float linear_correction_divider;
#endif
    dimmer_channel_id_t channel_ptr;
    dimmer_channel_t ordered_channels[DIMMER_CHANNELS + 1];             // current dimming levels in ticks
    dimmer_channel_t ordered_channels_buffer[DIMMER_CHANNELS + 1];      // next dimming levels

#if HAVE_FADE_COMPLETION_EVENT
    dimmer_level_t fadingCompleted[DIMMER_CHANNELS];
#endif
};

#define DIMMER_FADE_FROM_CURRENT_LEVEL -1

extern dimmer_t dimmer;

void dimmer_setup();
void dimmer_zc_interrupt_handler();
void dimmer_zc_setup();
void dimmer_timer_setup();
void dimmer_timer_remove();
void dimmer_start_timer1();
void dimmer_start_timer2();
void dimmer_set_level(dimmer_channel_id_t channel, dimmer_level_t level);
dimmer_level_t dimmer_get_level(dimmer_channel_id_t channel);
#if DIMMER_USE_LINEAR_CORRECTION
void dimmer_set_lcf(float lcf);
#endif
#if DIMMER_USE_FADING
void dimmer_set_fade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time, bool absolute_time = false);
void dimmer_fade(dimmer_channel_id_t channel, dimmer_level_t to, float time_in_seconds, bool absolute_time = false);
void dimmer_apply_fading();
#endif
void dimmer_set_mosfet_gate(dimmer_channel_id_t channel, bool state);
