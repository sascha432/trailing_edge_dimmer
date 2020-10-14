/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>

namespace Timers {

    template<int _Timer, uint8_t _Prescaler>
    struct TimerBase {};

    template<uint8_t _Prescaler>
    struct TimerBase<1, _Prescaler> {
        static constexpr uint16_t prescaler = _Prescaler;
        static constexpr uint8_t prescalerBV =
            prescaler == 1 ?
                (1 << CS10) :
                prescaler == 8 ?
                    (1 << CS11) :
                    prescaler == 64 ?
                        ((1 << CS10) | (1 << CS11)) :
                        prescaler == 256 ?
                            (1 << CS12) :
                            prescaler == 1024 ?
                                ((1 << CS10) | (1 << CS12)) : -1;

        static_assert(prescalerBV != -1, "prescaler not defined");
        static constexpr float ticksPerMicrosecond =  (F_CPU / prescaler / 1000000.0);

        static inline void begin() {
            TCCR1A = 0;
            TCCR1B = prescalerBV;
        }

        static inline void end() {
            disable();
            TCCR1B = 0;
        }

        static inline void clear_compareA_B_flag() {
            TIFR1 |= _BV(OCF1A) | _BV(OCF1B);
        }

        static inline void clear_compareA_flag() {
            TIFR1 |= _BV(OCF1A);
        }

        static inline void clear_compareB_flag() {
            TIFR1 |= _BV(OCF1B);
        }

        static inline void enable_compareA_disable_compareB() {
            TIMSK1 = (TIMSK1 & ~_BV(OCIE1B)) | _BV(OCIE1A);
        }

        static inline void enable_compareB_disable_compareA() {
            TIMSK1 = (TIMSK1 & ~_BV(OCIE1A)) | _BV(OCIE1B);
        }

        static inline void enable_compareA() {
            TIMSK1 |= _BV(OCIE1A);
        }

        static inline void enable_compareB() {
            TIMSK1 |= _BV(OCIE1B);
        }

        static inline bool is_compareA_enabled() {
            return TIMSK1 | _BV(OCIE1A);
        }

        static inline bool is_compareB_enabled() {
            return TIMSK1 | _BV(OCIE1B);
        }

        static inline void disable_compareA() {
            TIMSK1 &= ~_BV(OCIE1A);
        }

        static inline void disable_compareB() {
            TIMSK1 &= ~_BV(OCIE1B);
        }

        static inline void disable() {
            TIMSK1 &= ~(_BV(OCIE1A) | _BV(OCIE1B));
        }

        static inline uint32_t microsToTicks32(uint32_t micros) {
            return micros * ticksPerMicrosecond;
        }

        static inline uint32_t ticksToMicros32(uint32_t ticks) {
            return ticks / ticksPerMicrosecond;
        }

        static inline uint16_t microsToTicks(uint16_t micros) {
            return micros * ticksPerMicrosecond;
        }

        static inline uint16_t ticksToMicros(uint16_t ticks) {
            return ticks / ticksPerMicrosecond;
        }

    };

    template<uint8_t _Prescaler>
    struct TimerBase<2, _Prescaler> {
        static constexpr uint16_t prescaler = _Prescaler;
        static constexpr uint8_t prescalerBV =
            prescaler == 1 ?
                (1 << CS20) :
                prescaler == 8 ?
                    (1 << CS21) :
                    prescaler == 32 ?
                        ((1 << CS20) | (1 << CS21)) :
                        prescaler == 64 ?
                            (1 << CS22) :
                            prescaler == 128 ?
                                ((1 << CS20) | (1 << CS22)) :
                                prescaler == 256 ?
                                    ((1 << CS21) | (1 << CS22)) :
                                    prescaler == 1024 ?
                                        ((1 << CS20) | (1 << CS21) | (1 << CS22)) : -1;

        static_assert(prescalerBV != -1, "prescaler not defined");

        static constexpr float ticksPerMicrosecond =  (F_CPU / prescaler / 1000000.0);

        static inline void begin() {
            TCCR2A = 0;
            TCCR2B = prescalerBV;
        }

        static inline void end() {
            disable();
            TCCR2B = 0;
        }

        static inline void enable_compareA() {
            TIFR2 |= _BV(OCF2A);
            TIMSK2 |= _BV(OCIE2A);
        }

        static inline void enable_compareB() {
            TIFR2 |= _BV(OCF2B);
            TIMSK2 |= _BV(OCIE2B);
        }

        static inline void disable_compareA() {
            TIFR2 |= _BV(OCF2A);
            TIMSK2 &= ~_BV(OCIE2A);
        }

        static inline void disable_compareB() {
            TIFR2 |= _BV(OCF2B);
            TIMSK2 &= ~_BV(OCIE2B);
        }

        static inline void disable() {
            TIMSK2 &= ~(_BV(OCIE2A) | _BV(OCIE2B));
        }

        static inline uint32_t microsToTicks32(uint32_t micros) {
            return micros * ticksPerMicrosecond;
        }

        static inline uint32_t ticksToMicros32(uint32_t ticks) {
            return ticks / ticksPerMicrosecond;
        }

        static inline uint16_t microsToTicks(uint16_t micros) {
            return micros * ticksPerMicrosecond;
        }

        static inline uint16_t ticksToMicros(uint16_t ticks) {
            return ticks / ticksPerMicrosecond;
        }

    };

}