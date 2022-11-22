/**
 * Author: sascha_lammers@gmx.de
 */

#include "measure_frequency.h"
#include "adc.h"
#include <avr/io.h>

// measure the interval between the zero crossing events
//
// first stage filter is 48-62Hz, 10 valid results must be present
//
// second state filter is to compare all results and generate an average. values that are +-0.75% are removed.
// 10 valid values must be present here as well to calculate the frequency
//
// the timer for the prediction will run at this rate and synchronized by the zero crossing events. invalid events are 
// filtered. the dimmer will turn off after 2500 (DIMMER_OUT_OF_SYNC_LIMIT) half waves (25 seconds @ 50Hz). this value
// should be adjusted how precise the MCU is triggering the zero crossing timer (external crystal, internal one, heat changes etc...)
// under good conditions the timer might stay in sync for minutes or get out of sync after seconds already

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
    if (_count > DIMMER_ZC_MIN_VALID_SAMPLES) {

        // stage 1

        uint32_t sum = 0;
        uint8_t num = 0;
        for(int i = 0; i < _count - 1; i++) {
            auto diff = _ticks[i + 1].diff(_ticks[i]);
            if (diff >= Dimmer::kMinCyclesPerHalfWave && diff <= Dimmer::kMaxCyclesPerHalfWave) { // filter between 48 and 62Hz
                sum += diff;
                num++;
            }
        }

        if (num > DIMMER_ZC_MIN_VALID_SAMPLES) {

            // stage 2

            _min = sum / num;
            _max = _min;
            // allow up to +-0.75% deviation from the filtered avg. value
            uint16_t limit = _min * DIMMER_ZC_INTERVAL_MAX_DEVIATION;
            _min = _min - limit;
            _max = _max + limit;

            // filter again with new min/max
            sum = 0;
            num = 0;
            for(int i = 0; i < _count - 1; i++) {
                auto diff = _ticks[i + 1].diff(_ticks[i]);
                if (diff >= _min && diff <= _max) {
                    sum += diff;
                    num++;
                }
            }

            if (num > DIMMER_ZC_MIN_VALID_SAMPLES) {
                auto ticks = (sum / static_cast<float>(num)) + DIMMER_MEASURE_ADJ_CYCLE_CNT;
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
    volatile uint16_t counter = TCNT1;
    volatile uint16_t overflow = timer1_overflow;
    #if 0
        if (TIFR1 & TOV1) { //TODO check if that ever happens, counter should be close to 0
            Serial.printf_P(PSTR("timer overflow TCNT=%u\n"), counter);
        }
    #endif
    #if DIMMER_ZC_MIN_PULSE_WIDTH_US
        // wait min. pulse with
        delayMicroseconds(DIMMER_ZC_MIN_PULSE_WIDTH_US);
        // check if any interrupt has occurred
        asm volatile("sbic %0, %1" :: "I" (_SFR_IO_ADDR(EIFR)), "I" (digitalPinToInterrupt(ZC_SIGNAL_PIN)));
        asm volatile("rjmp SKIP");
        // check if zero crossing pin is still high/low
        #if DIMMER_ZC_INTERRUPT_MODE == RISING
            DIMMER_SFR_ZC_JMP_IF_CLR(SKIP);
        #elif DIMMER_ZC_INTERRUPT_MODE == FALLING
            DIMMER_SFR_ZC_JMP_IF_SET(SKIP);
        #endif
    #endif
    measure->zc_measure_handler(counter, overflow);
    #if DIMMER_ZC_MIN_PULSE_WIDTH_US
        asm volatile("SKIP:");
    #endif
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
        #if 0
            else {
                remln(F("MEM"));
                delay(2000);
            }
        #endif
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
