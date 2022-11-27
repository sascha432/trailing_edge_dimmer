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
    uint24_t _min = 0;
    uint24_t _max = 0;

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

        if (num > DIMMER_ZC_MIN_VALID_SAMPLES) {

            // stage 2

            _min = sum / num;
            // allow up to DIMMER_ZC_INTERVAL_MAX_DEVIATION % deviation from the filtered avg. value
            uint16_t limit = _min * DIMMER_ZC_INTERVAL_MAX_DEVIATION;
            _min = _min - limit;
            _max = _max + limit;

            // filter again with new min/max
            sum = 0;
            num = 0;
            for(int i = 0; i < _count; i++) {
                auto diff = _ticks[i + 1].diff(_ticks[i]);
                if (diff >= _min && diff <= _max) {
                    sum += diff;
                    num++;
                }
            }

            if (num > DIMMER_ZC_MIN_VALID_SAMPLES) {
                auto ticks = (sum / static_cast<float>(num));
                _frequency = 500000.0 / clockCyclesToMicroseconds(ticks);
                _D(5, debug_printf("measure=%lu/%u\n", (uint32_t)sum, num));
            } 

        }
    }
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
        _adc.end();

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
