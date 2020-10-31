/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "helpers.h"
#include "dimmer.h"

#if !defined(__AVR_ATmega328P__)
#error check if compatible with MCU
#endif

constexpr int kNumBitsRequired(uint32_t value, int n = 0) {
    return value ? kNumBitsRequired(value >> 1, n + 1) : n;
}

class ADCHandler {
public:

#if HAVE_NTC
    static constexpr uint8_t kHaveNtc = 1;
#else
    static constexpr uint8_t kHaveNtc = 0;
#endif
#if HAVE_EXT_VCC || HAVE_READ_VCC
    static constexpr uint8_t kHaveReadVcc = 1;
#else
    static constexpr uint8_t kHaveReadVcc = 0;
#endif
#if HAVE_READ_INT_TEMP
    static constexpr uint8_t kReadIntTemp = 1;
#else
    static constexpr uint8_t kReadIntTemp = 0;
#endif
#if HAVE_POTI
    static constexpr uint8_t kHavePoti = 1;
#else
    static constexpr uint8_t kHavePoti = 0;
#endif

    static constexpr uint8_t kMaxPositon = kHaveNtc + kHaveReadVcc + kReadIntTemp + kHavePoti;
    static constexpr uint8_t kPosNTC = kHaveNtc - 1;
    static constexpr uint8_t kPosVCC = kPosNTC + kHaveReadVcc;
    static constexpr uint8_t kPosIntTemp = kPosVCC + kReadIntTemp;
    static constexpr uint8_t kPosPoti = kPosIntTemp + kHavePoti;

#if HAVE_POTI
    static constexpr uint8_t kPosLast = kPosPoti;
#else
    static constexpr uint8_t kPosLast = kMaxPositon - 1;
#endif


    static_assert(kMaxPositon > 0, "nothing to do for the ADC");


    using sum_t = uint24_t;
    static constexpr size_t kSumTypeSize = sizeof_uint24_t; // sizeof(sum_t) <- intelli(non)sense doesnt like avr-gcc extensions

    static constexpr int kCpuMhz = F_CPU / 1000000UL;

    // max. number of ADC values that fit into out variable
    static constexpr uint32_t kMaxValues = (1UL << (kSumTypeSize * 8)) / 1024 - 1;
    static constexpr int kMaxShift = kNumBitsRequired(kMaxValues);

    // discard first reading... to use the first reading, the ADC / interrupt flags must be cleared etc...
    static constexpr uint8_t kDefaultDiscard = 1;

    // the average value is multiplied by 64 or left shifted 6
    static constexpr uint8_t kLeftShift = 6;

    static constexpr uint8_t kADCSRA_Enable = _BV(ADEN);
    static constexpr uint8_t kADCSRA_StartConversion = _BV(ADSC);
    static constexpr uint8_t kADCSRA_AutoTriggerEnable = _BV(ADATE);
    static constexpr uint8_t kADCSRA_InterruptEnable = _BV(ADIE);
    static constexpr uint8_t kADCSRA_Prescaler2 = _BV(ADPS1);
    static constexpr uint8_t kADCSRA_Prescaler4 = _BV(ADPS1);
    static constexpr uint8_t kADCSRA_Prescaler8 = _BV(ADPS1) | _BV(ADPS0);
    static constexpr uint8_t kADCSRA_Prescaler16 = _BV(ADPS2);
    static constexpr uint8_t kADCSRA_Prescaler32 = _BV(ADPS2) | _BV(ADPS0);
    static constexpr uint8_t kADCSRA_Prescaler64 = _BV(ADPS2) | _BV(ADPS1);
    static constexpr uint8_t kADCSRA_Prescaler128 = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

    static constexpr uint8_t kADCSRA_PrescalerDefault = kADCSRA_Prescaler128;


    static constexpr uint8_t kADCSRB_FreeRunning = 0;
    static constexpr uint8_t kADCSRB_AnalogComperator = _BV(ADTS0);

    static constexpr uint8_t kADMUX_AREF = 0;
    static constexpr uint8_t kADMUX_AVCC = _BV(REFS0);
    static constexpr uint8_t kADMUX_VREF11 = _BV(REFS1) | _BV(REFS0);
    static constexpr uint8_t kADMUX_InternalTemperature = kADMUX_VREF11 | _BV(MUX3);
    static constexpr uint8_t kADMUX_InternalVCC = kADMUX_AVCC | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);

    template<uint8_t _Reference, uint8_t _Pin>
    static constexpr uint8_t kADMUX_Reference() {
        static_assert(_Reference != kADMUX_InternalTemperature && _Reference != kADMUX_InternalVCC, "invalid _Reference");
        static_assert(_Pin >= PIN_A0 && _Pin <= PIN_A6, "invalid _Pin");
        return _Reference | (_Pin - PIN_A0);
    }

    template<uint8_t _Reference>
    static constexpr uint8_t kADMUX_Reference() {
        static_assert(_Reference == kADMUX_InternalTemperature || _Reference == kADMUX_InternalVCC, "invalid _Reference");
        return _Reference;
    }

    ADCHandler() : _values{}, _scheduleNext(false) {}

    ~ADCHandler() {
        end();
    }

    // initialize ADC
    inline void begin() {
        end();
#if DEBUG
        memset(&_duration[0], 0, sizeof(_duration));
        memset(&_count[0], 0, sizeof(_count));
#endif
        ADCSRB = kADCSRB_FreeRunning;
    }

    inline void end() {
        ADCSRA = 0;
        _scheduleNext = false;
    }

    inline void setInternalTemp() {
        ADMUX = kADMUX_Reference<kADMUX_InternalTemperature>();
    }

    inline void setInternalVCC() {
        ADMUX = kADMUX_Reference<kADMUX_InternalVCC>();
    }

    template<uint8_t _Pin = PIN_A0>
    void setPinAndAVCC() {
        ADMUX = kADMUX_Reference<kADMUX_AVCC, _Pin>();
    }

    template<uint8_t _Pin = PIN_A0>
    void setPinAndVRef11() {
        ADMUX = kADMUX_Reference<kADMUX_VREF11, _Pin>();
    }

    // start reading ADC values
    // maxCount = maximum values to read before stopping automatically (power of 2)
    // maxCount=6/readings=64 up to maxCount=14/readings=16384
    // discard = number of readings to discard before counting
    inline void start(const uint8_t maxCount = kMaxShift, const uint16_t discard = kDefaultDiscard) {
        _ASSERTE(maxCount >= kLeftShift && maxCount <= kMaxShift);
#if DEBUG
        _start = micros();
        _intCounter = 0;
        _count[_pos] = 0;
#endif
//30628
        _maxCount = 1U << maxCount;
        _shiftSum = maxCount - kLeftShift;
        _counter = discard;
        _counter = -_counter;
        _sum = 0;
        ADCSRA = kADCSRA_Enable|kADCSRA_StartConversion|kADCSRA_AutoTriggerEnable|kADCSRA_InterruptEnable|kADCSRA_PrescalerDefault;
    }

    // stop reading
    inline void stop() {
        ADCSRA = 0;
        //ADCSRA &= ~(kADCSRA_InterruptEnable|kADCSRA_StartConversion|kADCSRA_AutoTriggerEnable);
    }

    inline bool canScheduleNext() const {
        return _scheduleNext;
    }

    inline uint8_t getPosition() const {
        return _pos;
    }

    inline void setPosition(uint8_t pos) {
        _pos = pos;
    }

    static constexpr uint8_t getMaxPosition() {
        return kPosLast;
    }

    inline void adc_handler(uint16_t value) {
#if DEBUG
        _intCounter++;
#endif
        if (++_counter <= 0) {
            return;
        }
        _sum += value;
        if ((uint16_t)_counter >= _maxCount) {
#if DEBUG
            _duration[_pos] = micros() - _start;
            _count[_pos] = _intCounter;
#endif
            stop();
            _scheduleNext = true;
        }
    }

    // select next positon and call restart
    void next();

    // restart read cycle for current position
    void restart();

    // returns average ADC reading multiplied by 64 (or left shifted by 6)
    // values 0 - 65472
    uint16_t getValue(uint8_t pos) const {
        return _values[pos];
    }

#if DEBUG
    void dump();
#endif

private:
    uint16_t _values[kMaxPositon];
    int16_t _counter;
    uint16_t _maxCount;
    sum_t _sum;
    uint8_t _shiftSum;
    uint8_t _pos;
    bool _scheduleNext;
#if DEBUG
    uint32_t _start;
    uint16_t _duration[kMaxPositon];
    uint16_t _count[kMaxPositon];
    uint16_t _intCounter;
#endif
};

extern ADCHandler _adc;
