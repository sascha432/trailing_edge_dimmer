/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>

#ifndef ZC_SIGNAL_PIN
#define ZC_SIGNAL_PIN                                           3
#endif

#ifndef DIMMER_ZC_DELAY
// the exact delay depends on the zero crossing detection, the prescaler and the CPU speed
// I strongly recommend to check with an oscilloscope to get the exact time
#define DIMMER_ZC_DELAY                                         1670UL          // microseconds
#endif

#ifndef DIMMER_MIN_ON_TIME
#define DIMMER_MIN_ON_TIME                                  200 // minimum "on"-time in µs
#endif
#ifndef DIMMER_ADJUST_HALFWAVE
#define DIMMER_ADJUST_HALFWAVE                              300 // reduce "on"-time in µs to match the exact level
#endif

// some LEDs have a soft start function. to get smooth fading, the minimum level is set
// and a specific delay occurs before fading starts
#ifndef DIMMER_MIN_LEVEL
#define DIMMER_MIN_LEVEL                                        0 // 8
#define DIMMER_MIN_LEVEL_TIME_IN_MS                             800
#endif

#define DIMMER_USE_FADING                                       1

// for more than 10 channels it might be necessary to disable the linear correction or use a different method to calculate it. see DIMMER_LINEAR_LEVEL()
#ifndef DIMMER_CHANNELS
#define DIMMER_CHANNELS                                         4
#endif

#ifndef DIMMER_MOSFET_PINS
    #define DIMMER_MOSFET_PINS                                  { 6, 8, 9, 10 }
#endif

#ifndef DIMMER_MAX_LEVEL
    #define DIMMER_MAX_LEVEL                                    min(32767, DIMMER_TICKS_PER_HALFWAVE)
    // #define DIMMER_MAX_LEVEL                            8191
    // #define DIMMER_MAX_LEVEL                            1023
    // #define DIMMER_MAX_LEVEL                            255
    // #define DIMMER_MAX_LEVEL                            100
#endif

#ifndef DIMMER_USE_LINEAR_CORRECTION
    #define DIMMER_USE_LINEAR_CORRECTION                        1
#endif

#ifndef DIMMER_LINEAR_FACTOR
    #define DIMMER_LINEAR_FACTOR                                1.0
#endif

#if DIMMER_USE_LINEAR_CORRECTION
// pow() is pretty slow
#define DIMMER_LINEAR_LEVEL(level)                           (dimmer.linear_correction_factor == 1 ? level : pow(level, dimmer.linear_correction_factor) * dimmer.linear_correction_factor_div)
#else
#define DIMMER_LINEAR_LEVEL(level)                           level
#endif

#ifndef DIMMER_TIMER1_PRESCALER
    #define DIMMER_TIMER1_PRESCALER                         8
#endif

#define DIMMER_TIMER2_PRESCALER                             64
#define DIMMER_TIMER2_PRESCALER_BV                          (1 << CS22)
// #define DIMMER_TIMER2_PRESCALER                             128
// #define DIMMER_TIMER2_PRESCALER_BV                          ((1 << CS22) | (1 << CS20))
// #define DIMMER_TIMER2_PRESCALER                             256
// #define DIMMER_TIMER2_PRESCALER_BV                          ((1 << CS22) | (1 << CS21))
// #define DIMMER_TIMER2_PRESCALER                             1024
// #define DIMMER_TIMER2_PRESCALER_BV                          ((1 << CS22) | (1 << CS21) | (1 << CS20))

#if DIMMER_TIMER1_PRESCALER == 8
    #define DIMMER_TIMER1_PRESCALER_BV                      (1 << CS11)
    #define DIMMER_EXTRA_TICKS                              8           // add some extra ticks that the timer interrupt doesn't skip turning off a mosfet if the timer interrupts are very close
#elif DIMMER_TIMER1_PRESCALER == 64
    #define DIMMER_TIMER1_PRESCALER_BV                      ((1 << CS11) | (1 << CS10))
    #define DIMMER_EXTRA_TICKS                              1
#elif DIMMER_TIMER1_PRESCALER == 256
    #define DIMMER_TIMER1_PRESCALER_BV                      (1 << CS12)
    #define DIMMER_EXTRA_TICKS                              1
#else
    #error prescaler not supported
#endif

#ifndef DIMMER_AC_FREQUENCY
    #define DIMMER_AC_FREQUENCY                             60
#endif

#define DIMMER_START_TIMER1()                                TCCR1B |= DIMMER_TIMER1_PRESCALER_BV;
#define DIMMER_PAUSE_TIMER1()                                TCCR1B = 0;
#define DIMMER_START_TIMER2()                                TCCR2B |= DIMMER_TIMER2_PRESCALER_BV;
#define DIMMER_PAUSE_TIMER2()                                TCCR2B = 0;

#define DIMMER_GET_TICKS(level)                             max(DIMMER_MIN_ON_TIME * DIMMER_TICKS_PER_US, (level * DIMMER_TICKS_PER_HALFWAVE) / DIMMER_MAX_LEVEL - DIMMER_ADJUST_HALFWAVE * DIMMER_TICKS_PER_US)

#define DIMMER_ENABLE_TIMERS()                              { TIMSK1 |= (1 << OCIE1A); TCCR1A = 0; TCCR1B = 0; TIMSK2 |= (1 << OCIE2A); TCCR2A = 0; TCCR2B = 0; }
#define DIMMER_DISABLE_TIMERS()                             { TIMSK1 &= ~(1 << OCIE1A); TIMSK2 &= ~(1 << OCIE2A); }

#define DIMMER_TICKS_PER_HALFWAVE                           (F_CPU / DIMMER_TIMER1_PRESCALER / (DIMMER_AC_FREQUENCY * 2))
#define DIMMER_TICKS_PER_US                                 (F_CPU / DIMMER_TIMER1_PRESCALER / 1000000.0)
#define DIMMER_TICKS_PER_US_TIMER2                          (F_CPU / DIMMER_TIMER2_PRESCALER / 1000000.0)

#define DIMMER_ZC_DELAY_TICKS                               (F_CPU / DIMMER_TIMER2_PRESCALER * DIMMER_ZC_DELAY / 1000000UL)

#if DIMMER_TICKS_PER_HALFWAVE > 32767
    #error TICKS are limited to 32767 per half wave, increase prescaler
#endif

#if DIMMER_ZC_DELAY_TICKS == 0
#elif DIMMER_ZC_DELAY_TICKS > 255
    #error timer 2 is 8bit only, increase prescaler
#elif DIMMER_ZC_DELAY_TICKS < 64
    #warning consider decreasing the prescaler for a more precise timing
#endif

#define DIMMER_VERSION                                      "1.0.9"
#define DIMMER_INFO                                         "Author: sascha_lammers@gmx.de"

#if DIMMER_USE_FADING
struct dimmer_fade_t {
    float level;
    float step;
    uint16_t count;
};
#endif

struct dimmer_channel_t {
    uint8_t channel;
    uint16_t ticks;
};

struct dimmer_t {
#if DIMMER_USE_LINEAR_CORRECTION
    float linear_correction_factor;
    float linear_correction_factor_div;
#endif

    uint16_t level[DIMMER_CHANNELS];                                    // current level
#if DIMMER_USE_FADING
    dimmer_fade_t fade[DIMMER_CHANNELS];                                // calculated fading data
#endif

    uint8_t channel_ptr;
    dimmer_channel_t ordered_channels[DIMMER_CHANNELS + 1];             // current dimming levels in ticks
    dimmer_channel_t ordered_channels_buffer[DIMMER_CHANNELS + 1];      // next dimming levels
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
void dimmer_set_level(uint8_t channel, int16_t level);
uint16_t dimmer_get_level(uint8_t channel);
#if DIMMER_USE_LINEAR_CORRECTION
void dimmer_set_lcf(float lcf);
#endif
#if DIMMER_USE_FADING
void dimmer_set_fade(uint8_t channel, int16_t from, int16_t to, float time, bool absolute_time = false);
void dimmer_fade(uint8_t channel, int16_t to_level, float time_in_seconds, bool absolute_time = false);
void dimmer_apply_fading();
#endif
void dimmer_set_mosfet_gate(uint8_t channel, bool state);
