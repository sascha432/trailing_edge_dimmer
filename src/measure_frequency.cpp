/**
 * Author: sascha_lammers@gmx.de
 */

#include "measure_frequency.h"
#include "adc.h"
#include <avr/io.h>

// measure the interval between the zero crossing events
//
// first stage filter is 48-62Hz, DIMMER_ZC_MIN_VALID_SAMPLES valid results must be present
//
// second state filter is to compare all results and generate an average. values that are +-0.75% are removed.
// DIMMER_ZC_MIN_VALID_SAMPLES valid values must be present here as well to calculate the frequency
//
// this makes sure all zc events that are received are within the range of the initial measurement over many cycles (DIMMER_ZC_INTERVAL_MAX_DEVIATION)
// if too many invalid signals are received, the dimmer is stopped (DIMMER_OUT_OF_SYNC_LIMIT) and a new frequency measurement started

volatile uint16_t timer1_overflow;
FrequencyMeasurement *measure = nullptr;

ISR(TIMER1_OVF_vect)
{
    timer1_overflow++;
}

void FrequencyMeasurement::calc_min_max()
{
    uint24_t _min;
    uint24_t _max;
    #if DEBUG_FREQUENCY_MEASUREMENT
        uint8_t stage1 = 0;
        uint8_t stage2 = 0;
        int16_t count = _count;
    #endif

    _frequency = 0;

    // stage 0

    _D(5, debug_printf("frequency errors=%u,zc=%u\n", _errors, _count));
    if (_count-- > DIMMER_ZC_MIN_VALID_SAMPLES) {

        // stage 1

        uint32_t sum = 0;
        uint8_t num = 0;
        for(int i = 0; i < _count; i++) {
            auto diff = _ticks[i + 1].diff(_ticks[i]);
            if (diff >= Dimmer::kMinCyclesPerHalfWave && diff <= Dimmer::kMaxCyclesPerHalfWave) { // filter between 48 and 62Hz
                sum += diff;
                num++;
            }
        }
        #if DEBUG_FREQUENCY_MEASUREMENT
            stage1 = num;
        #endif

        if (num > DIMMER_ZC_MIN_VALID_SAMPLES) {

            // stage 2

            _calc_halfwave_min_max(sum / num, _min, _max);

            #if DEBUG_FREQUENCY_MEASUREMENT
                sei();
            #endif

            // filter again with new min/max
            sum = 0;
            num = 0;
            for(int i = 0; i < _count; i++) {
                auto diff = _ticks[i + 1].diff(_ticks[i]);
                #if DEBUG_FREQUENCY_MEASUREMENT
                    char ch = '-';
                #endif
                if (diff >= _min && diff <= _max) {
                    sum += diff;
                    num++;
                    #if DEBUG_FREQUENCY_MEASUREMENT
                        ch = '+';
                    #endif
                }
                #if DEBUG_FREQUENCY_MEASUREMENT
                    Serial.printf_P(PSTR("+REM=%lu%c\n"), (long)diff, ch);
                    Serial.flush();
                #endif
            }
            #if DEBUG_FREQUENCY_MEASUREMENT
                stage2 = num;
            #endif

            if (num > DIMMER_ZC_MIN_VALID_SAMPLES) {
                auto ticks = (sum / static_cast<float>(num));
                _frequency = 500000.0 / clockCyclesToMicroseconds(ticks);
                #if DEBUG_FREQUENCY_MEASUREMENT
                    Serial.printf_P(PSTR("+REM=f-sync=%f,c=%u,s1=%u,s2=%u,mi=%lu,ma=%lu\n"), _frequency, count, stage1, stage2, (long)_min, (long)_max);
                #endif
                return;
            } 
        }
    }
    #if DEBUG_FREQUENCY_MEASUREMENT
        Serial.printf_P(PSTR("+REM=f-sync failed,c=%u,s1=%u,s2=%u,mi=%lu,ma=%lu\n"), count, stage1, stage2, (long)_min, (long)_max);
    #endif
}

void FrequencyMeasurement::zc_measure_handler(uint16_t lo, uint16_t hi)
{
    if (_count < 0) { // warm up run
        _count++;
        return;
    }
    _ticks[_count++] = lo | (uint24_t)hi << 16;
    if (_count == kMeasurementBufferSize) {
        // detach handler and do calculations
        FrequencyMeasurement::detach_handler();
        calc_min_max();
    }
}

static inline void zc_intr_measure_handler()
{
    uint16_t counter = TCNT1;
    if ((TIFR1 & _BV(TOV1)) && counter < 0xffff) {
        timer1_overflow++;
        TIFR1 |= _BV(TOV1);
    }
    measure->zc_measure_handler(counter, timer1_overflow);
}

void FrequencyMeasurement::attach_handler() 
{
    #if digitalPinToInterrupt(ZC_SIGNAL_PIN) == -1
        // check if the pin supports external interrupts
        #error ZC_SIGNAL_PIN not supported
    #endif
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), zc_intr_measure_handler, DIMMER_ZC_INTERRUPT_MODE);
}

void FrequencyMeasurement::cleanup()
{
    cli();
    FrequencyMeasurement::detach_handler();
    Dimmer::FrequencyTimer::end();
    delete measure;
    measure = nullptr;
    sei();
}

// returns true when finished
bool FrequencyMeasurement::run()
{
    if (measure == nullptr) {
        _D(5, debug_printf("measuring...\n"));
        dimmer.end();
        #if DIMMER_USE_ADC_INTERRUPT
            _adc.end();
        #endif

        // give everything some time to settle before starting the measurement
        delay(100);

        measure = new FrequencyMeasurement();
        if (measure) {
            cli();
            measure->attach_handler();            
            Dimmer::FrequencyTimer::begin();
            sei();
        }
        return false;
    }

    if (measure->is_done()) {
        _D(5, debug_printf("measurement done\n"));
        dimmer.set_frequency(measure->get_frequency());
        cleanup();
        return true;
    }

    if (measure->is_timeout()) {
        _D(5, debug_printf("timeout during measuring\n"));
        dimmer.set_frequency(NAN);
        cleanup();
        return true;
    }

    return false;
}
