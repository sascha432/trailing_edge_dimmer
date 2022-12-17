/**
 * Author: sascha_lammers@gmx.de
 */

#include "adc.h"

ADCHandler _adc;

#if DIMMER_USE_ADC_INTERRUPT

ISR(ADC_vect)
{
    _adc.adc_handler(ADC);
}

void ADCHandler::next()
{
    if (_pos >= kMaxPosition) {
        return;
    }
    if (_counter > 0) {
        // ADC values are 0-0x3ff, ~64.06 readings fit into an uint16_t
        //_values[_pos] = _sum / (_counter >> 6);
        _values[_pos] = _sum >> _shiftSum;
    }

    // cycle through all positions until the end has been reached
    // if the poti is available, it keeps reading its value
    if (_pos < kPosLast)  {
        _pos++;
    }
    restart();
}

#if DEBUG

void ADCHandler::dump()
{
    for(uint8_t i = 0; i < kMaxPosition; i++) {
        Serial.printf_P(PSTR("%u: v=%u ø=%.2f d=%uus t=%u c=%u\n"), i, _values[i], _values[i] / 64.0, _duration[i], (uint16_t)(_duration[i] / _count[i]), _count[i]);
        Serial.flush();
    }
    Serial.println();
}

#endif

void ADCHandler::restart()
{
    // discard at least the first 2 readings after switching
    constexpr uint8_t kDiscard = 8;
    // when selecting vref11 it takes a while until the voltage drops
    // reading a value with prescaler 128 takes ~105µs, giving it ~6.6ms time to discharge when discarding the first 64 cycles
    // testing with an arduino nano @5V shows ~2.4ms to discharge to 1.1V. Adding additional 120nF capacity increased the time to ~5.9ms
    constexpr uint8_t kDiscardVRef11 = kCpuMhz * 4;
    constexpr float kDischargeTimeMillis = kDiscardVRef11 * 0.104 * (16000000UL / F_CPU);
    static_assert(kDischargeTimeMillis > 5.0 && kADCSRA_PrescalerDefault == kADCSRA_Prescaler128, "check discharge cycles");

    _scheduleNext = false;
    switch(_pos) {
        #if HAVE_NTC
            case kPosNTC:
                setPinAndAVCC<NTC_PIN>();
                start(kNumReadNtc, kDiscard);
                break;
        #endif
        #if HAVE_EXT_VCC
            case kPosVCC:
                setPinAndVRef11<VCC_PIN>();
                start(kNumReadVcc, kDiscardVRef11);
                break;
        #elif HAVE_READ_VCC
            case kPosVCC:
                setInternalVCC();
                start(kNumReadVcc, kDiscard);
                break;
        #endif
        #if HAVE_READ_INT_TEMP
            case kPosIntTemp:
                setInternalTemp();
                start(kNumReadTemp, kDiscardVRef11);
                break;
        #endif
        #if HAVE_POTI
            case kPosPoti:
                setPinAndAVCC<POTI_PIN>();
                start(kNumReadPoti, kDiscard);
                break;
        #endif
        #if DEBUG && 0
            default:
                debug_printf("invalid position %d\n", _pos);
                break;
        #endif
    }
}

#endif
