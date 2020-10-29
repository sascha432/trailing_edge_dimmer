/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>

// Timer 1 & 2
// tested with Atmega328P and Atmega328PB @ 8 and 16MHz

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__)
#else
#warning Verify that timers are compatible with the MCU
#endif

#if (F_CPU == 16000000L) || (F_CPU == 8000000L)
#else
#warning Verify that timers are compatible with the CPU frequency
#endif

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

static_assert(
    _BV(1) == (1 << 1) &&
    _BV(2) == (1 << 2) &&
    _BV(3) == (1 << 3) &&
    _BV(4) == (1 << 4) &&
    _BV(5) == (1 << 5) &&
    _BV(6) == (1 << 6) &&
    _BV(7) == (1 << 7) &&
    _BV(8) == (1 << 8), "_BV() is not compatible"
);

namespace Timers {

    template<int _Timer, uint8_t _Prescaler>
    struct TimerBase {};

    template<uint8_t _Prescaler>
    struct TimerBase<1, _Prescaler> {
        static constexpr uint16_t prescaler = _Prescaler;
        static constexpr uint8_t prescalerBV =
            prescaler == 1 ?
                _BV(CS10) :
                prescaler == 8 ?
                    _BV(CS11) :
                    prescaler == 64 ?
                        ((1 << CS10) | (1 << CS11)) :
                        prescaler == 256 ?
                            (1 << CS12) :
                            prescaler == 1024 ?
                                ((1 << CS10) | (1 << CS12)) : -1;

        static_assert(prescalerBV != -1, "prescaler not defined");
        static constexpr float ticksPerMicrosecond =  (F_CPU / prescaler / 1000000.0);

        static constexpr uint8_t kFlagsOverflow = _BV(TOV1);
        static constexpr uint8_t kFlagsCompareA = _BV(OCF1A);
        static constexpr uint8_t kFlagsCompareB = _BV(OCF1B);
        static constexpr uint8_t kFlagsCapture = _BV(ICF1);
        static constexpr uint8_t kFlagsCompareAB = kFlagsCompareA|kFlagsCompareB;
        static constexpr uint8_t kFlagsCompareAOverflow = kFlagsCompareA|kFlagsOverflow;
        static constexpr uint8_t kFlagsCompareBOverflow = kFlagsCompareB|kFlagsOverflow;
        static constexpr uint8_t kFlagsCompareABOverflow = kFlagsCompareA|kFlagsCompareB|kFlagsOverflow;
        static constexpr uint8_t kFlagsAll = kFlagsOverflow|kFlagsCompareA|kFlagsCompareB|kFlagsCapture;

        template<uint8_t mask = kFlagsAll>
        static inline void clear_flags() {
            TIFR1 |= mask;
        }

        static constexpr uint8_t kIntMaskOverflow = _BV(TOIE1);
        static constexpr uint8_t kIntMaskCompareA = _BV(OCIE1A);
        static constexpr uint8_t kIntMaskCompareB = _BV(OCIE1B);
        static constexpr uint8_t kIntMaskCapture = _BV(ICIE1);
        static constexpr uint8_t kIntMaskCompareAB = kIntMaskCompareA|kIntMaskCompareB;
        static constexpr uint8_t kIntMaskCompareAOverflow = kIntMaskCompareA|kIntMaskOverflow;
        static constexpr uint8_t kIntMaskCompareBOverflow = kIntMaskCompareB|kIntMaskOverflow;
        static constexpr uint8_t kIntMaskCompareABOverflow = kIntMaskCompareA|kIntMaskCompareB|kIntMaskOverflow;
        static constexpr uint8_t kIntMaskAll = kIntMaskOverflow|kIntMaskCompareA|kIntMaskCompareB|kIntMaskCapture;
        static constexpr uint8_t kIntMaskNone = 0;

        template<uint8_t _Enable>
        static inline void int_mask_enable() {
            TIMSK1 |= _Enable;
        }

        template<uint8_t _Disable>
        static inline void int_mask_disable() {
            TIMSK1 &= ~_Disable;
        }

        template<uint8_t _Enable, uint8_t _Disable>
        static inline void int_mask_toggle() {
            TIMSK1 = (TIMSK1 & ~_Disable) | _Enable;
        }

        template<uint8_t _Mask>
        static inline uint8_t int_mask_get() {
            return TIMSK1 | _Mask;
        }

        template<uint8_t _Mask>
        static inline bool int_mask_is_enabled() {
            return TIMSK1 | _Mask;
        }

        template<uint8_t _Disable, nullptr_t _DoDisable>
        static inline void begin() {
            TCCR1A = 0;
            TCCR1B = prescalerBV;
            int_mask_disable<_Disable>();
        }

        template<uint8_t _Enable>
        static inline void begin() {
            TCCR1A = 0;
            TCCR1B = prescalerBV;
            int_mask_enable<_Enable>();
        }

        static inline void begin() {
            TCCR1A = 0;
            TCCR1B = prescalerBV;
        }

        template<uint8_t _Disable = kIntMaskAll>
        static inline void end() {
            int_mask_disable<_Disable>();
            TCCR1B = 0;
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

        static constexpr uint8_t kFlagsOverflow = _BV(TOV2);
        static constexpr uint8_t kFlagsCompareA = _BV(OCF2A);
        static constexpr uint8_t kFlagsCompareB = _BV(OCF2B);
        static constexpr uint8_t kFlagsCompareAB = kFlagsCompareA|kFlagsCompareB;
        static constexpr uint8_t kFlagsCompareAOverflow = kFlagsCompareA|kFlagsOverflow;
        static constexpr uint8_t kFlagsCompareBOverflow = kFlagsCompareB|kFlagsOverflow;
        static constexpr uint8_t kFlagsCompareABOverflow = kFlagsCompareA|kFlagsCompareB|kFlagsOverflow;
        static constexpr uint8_t kFlagsAll = kFlagsOverflow|kFlagsCompareA|kFlagsCompareB;

        template<uint8_t mask = kFlagsAll>
        static inline void clear_flags() {
            TIFR2 |= mask;
        }

        static constexpr uint8_t kIntMaskOverflow = _BV(TOIE2);
        static constexpr uint8_t kIntMaskCompareA = _BV(OCIE2A);
        static constexpr uint8_t kIntMaskCompareB = _BV(OCIE2B);
        static constexpr uint8_t kIntMaskCompareAB = kIntMaskCompareA|kIntMaskCompareB;
        static constexpr uint8_t kIntMaskCompareAOverflow = kIntMaskCompareA|kIntMaskOverflow;
        static constexpr uint8_t kIntMaskCompareBOverflow = kIntMaskCompareB|kIntMaskOverflow;
        static constexpr uint8_t kIntMaskCompareABOverflow = kIntMaskCompareA|kIntMaskCompareB|kIntMaskOverflow;
        static constexpr uint8_t kIntMaskAll = kIntMaskOverflow|kIntMaskCompareA|kIntMaskCompareB;
        static constexpr uint8_t kIntMaskNone = 0;

        template<uint8_t _Enable>
        static inline void int_mask_enable() {
            TIMSK2 |= _Enable;
        }

        template<uint8_t _Disable>
        static inline void int_mask_disable() {
            TIMSK2 &= ~_Disable;
        }

        template<uint8_t _Enable, uint8_t _Disable>
        static inline void int_mask_toggle() {
            TIMSK2 = (TIMSK2 & ~_Disable) | _Enable;
        }

        template<uint8_t _Mask>
        static inline uint8_t int_mask_get() {
            return TIMSK2 | _Mask;
        }

        template<uint8_t _Mask>
        static inline bool int_mask_is_enabled() {
            return TIMSK2 | _Mask;
        }

        template<uint8_t _Enable>
        static inline void begin() {
            TCCR2A = 0;
            TCCR2B = prescalerBV;
            int_mask_enable<_Enable>();
        }

        template<uint8_t _Disable, nullptr_t _DoDisable>
        static inline void begin() {
            TCCR2A = 0;
            TCCR2B = prescalerBV;
            int_mask_disable<_Disable>();
        }

        static inline void begin() {
            TCCR2A = 0;
            TCCR2B = prescalerBV;
        }

        template<uint8_t _Disable = kIntMaskAll>
        static inline void end() {
            int_mask_disable<_Disable>();
            TCCR2B = 0;
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