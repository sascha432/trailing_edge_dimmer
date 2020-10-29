/**
 * Author: sascha_lammers@gmx.de
 */

#include "measure_frequency.h"

// currently only single filter stage implemented
// WORK IN PROGRESS

// TODO
// improve algorithm for invalid ZC signals
//
// after initial frequency detection, measure the halfwave time again filtering invalid signals
//
// the halfwave resolution is 62.5ns but the timer runs with prescaler 8 and 500ns - to match the excact halfwave length, one tick can be removed and replaced with
// a short delay. right now the halfwave stays pretty much in sync when disconnecting the ZC signal, moving a few 100µs back and forth but over several seconds it gets out of sync
// i also noticed that the ZC signal coming from the dimmer is a bit asymmetrical, one half wave is detected ~18µs ealier using RISING as interrupt source... checking with the oscilloscope
// shows the same but the center of the signal matches the zerocrossing. using CHANGE as trigger might be a solution. the C0G capacitors still seems to be a bit temperature sensitive
// moving the signal a few µs per °C, but not like the X5R which had 100µs offset per a few degree...
//
// what effect does the load have on the zero crossing? and the snubber network? you can see a certain offset when the mosfets are open (no load, no snubber, just a resistor)
// testing some transformers seems to cause a pretty big shift, as well as some LEDs with buck regulators. the spike when turning the mosfets off sometimes causes a voltage drop at the gate
// driver turning them on again. the 1nF capacitor might not be enough when switching inductive loads like transformers

static void attach_zc_measure_handler();
static void detach_zc_measure_handler();
static void reset_measurement_timeout();

static constexpr uint32_t kFrequencyWaitTimerInit = 0;
static constexpr uint32_t kFrequencyWaitTimerDone = ~0;

uint32_t frequency_wait_timer;
bool frequency_measurement;

volatile uint16_t timer1_overflow;

ISR(TIMER1_OVF_vect)
{
    timer1_overflow++;
}

FrequencyMeasurement *measure;

void FrequencyMeasurement::calc_min_max()
{
    uint24_t _min;
    uint24_t _max;

    _min = 0;
    _max = 0;
    _frequency = NAN;

    _D(5, debug_printf("frequency errors=%u,zc=%u\n", _errors, _count));
    if (_count > 10) {
        //uint24_t ticks_sum = _ticks[_count - 1]._ticks - _ticks[0]._ticks;
        uint32_t sum = 0;
        uint8_t num = 0;
        for(int i = 0; i < _count - 1; i++) {
            auto diff = _ticks[i + 1].diff(_ticks[i]);
            if (diff >= Dimmer::kMinCyclesPerHalfWave && diff <= Dimmer::kMaxCyclesPerHalfWave) { // filter between 48 and 62Hz
                //Serial.println(diff);
                sum += diff;
                num++;
            }
        }
        if (num > 10) {
            _min = sum / num;
            _max = _min;
            // allow up to +-0.75% deviation from the filtered avg value
            uint16_t limit = _min * 0.0075;
            _min = _min - limit;
            _max = _max + limit;

            // filter again with new min/max
            sum = 0;
            num = 0;
            for(int i = 0; i < _count - 1; i++) {
                auto diff = _ticks[i + 1].diff(_ticks[i]);
                if (diff >= _min && diff <= _max) {
                    //Serial.println(diff);
                    sum += diff;
                    num++;
                }
            }

            if (num > 10) {
                float ticks = (sum / (float)num) + DIMMER_MEASURE_ADJ_CYCLE_CNT;
                _frequency = 1000000.0 / clockCyclesToMicroseconds(ticks) / 2.0;
                // Serial.println((uint32_t)sum);
                // Serial.println((uint32_t)num);
                // Serial.println(_frequency);
            }

        }
        //_count--;
        //float ticks = (ticks_sum / (float)_count) + DIMMER_MEASURE_ADJ_CYCLE_CNT;
        //_D(5, debug_printf("ticks=%lu f=%f cnt=%u err=%u\n", ticks_sum, _frequency, _count, _errors));
    }
    // else {
    //     Serial.printf_P(PSTR("+REM=errors=%u,zc=%u\n"), _errors, _count);
    // }
}

// void FrequencyMeasurement::calc()
// {
//     //_D(5, debug_printf("frequency errors=%u,zc=%u\n", _errors, _count));
//     if (_count > 4) {
//         uint24_t ticks_sum = _ticks[_count - 1]._ticks - _ticks[0]._ticks;

//         _count--;
//         Serial.printf_P(PSTR("AVG %f Hz\n"), 1000000.0 / clockCyclesToMicroseconds(ticks_sum / (float)_count));
//         Serial.printf_P(PSTR("AVG ticks=%f\n"), clockCyclesToMicroseconds(ticks_sum / (float)_count));

//         Serial.printf_P(PSTR("%ld\n"), (long)_ticks[_count - 1]._ticks);

//         float ticks = (ticks_sum / (float)_count) + DIMMER_MEASURE_ADJ_CYCLE_CNT;
//         _frequency = 1000000.0 / clockCyclesToMicroseconds(ticks) / 2.0;

//         _D(5, debug_printf("ticks=%lu f=%f cnt=%u err=%u\n", ticks_sum, _frequency, _count, _errors));
//     }
//     else {
//         Serial.printf_P(PSTR("+REM=errors=%u,zc=%u\n"), _errors, _count);
//     }
// }

void FrequencyMeasurement::zc_measure_handler(uint16_t lo, uint16_t hi)
{
    if (_count < 0) { // warm up run
        _count++;
        return;
    }
    _ticks[_count++] = lo | (uint24_t)hi << 16;
    if (_count == kMeasurementBufferSize) {
        cli();
        // detach handler while doing calculations
        detach_zc_measure_handler();
        sei();
        calc_min_max();
        frequency_wait_timer = kFrequencyWaitTimerDone;

#if 0
        switch(_state) {
            // initial run determines the base frequency 50/60hz
            case StateType::INIT:
                _state = StateType::MEASURE;
                calc_min_max();

                reset_measurement_timeout();
                cli();
                _count = -5;
                attach_zc_measure_handler();
                sei();


                break;
            // second run filters all events that are not close to the base frequency
            case StateType::MEASURE:
                //TODO
                calc();
                frequency_wait_timer = kFrequencyWaitTimerDone;
                break;
        }
#endif
    }
}

static inline void zc_measure_handler()
{
    volatile uint16_t counter = TCNT1;
    volatile uint16_t overflow = timer1_overflow;
    if (TIFR1 & TOV1) { //TODO check if that ever happens, counter should be close to 0
        Serial.printf_P(PSTR("timer overflow TCNT=%u\n"), counter);
    }
    sei();
    measure->zc_measure_handler(counter, overflow);
}

static void attach_zc_measure_handler()
{
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), zc_measure_handler, DIMMER_ZC_INTERRUPT_MODE);
}

static void detach_zc_measure_handler()
{
    detachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN));
}

static void reset_measurement_timeout()
{
    frequency_wait_timer = millis() + FrequencyMeasurement::kTimeout;
}

static void cleanup_measurement()
{
    cli();
    detach_zc_measure_handler();
    Dimmer::FrequencyTimer::end();
    sei();
    frequency_measurement = false;
    delete measure;
}

// returns true when finished
bool run_frequency_measurement()
{
    if (frequency_wait_timer == kFrequencyWaitTimerInit) {
        _D(5, debug_printf("measuring...\n"));
        dimmer.end();

        // give everything some time to settle before starting the measurement
        delay(100);

        reset_measurement_timeout();
        measure = new FrequencyMeasurement();
        cli();
        attach_zc_measure_handler();
        Dimmer::FrequencyTimer::begin();
        TCNT1 = 0;
        TIFR1 |= _BV(TOV1);
        sei();
        return false;
    }

    if (frequency_wait_timer == kFrequencyWaitTimerDone) {
        _D(5, debug_printf("measurement done\n"));
        dimmer.set_frequency(measure->get_frequency());
        cleanup_measurement();
        return true;
    }
    if (millis() >= frequency_wait_timer) {
        _D(5, debug_printf("timeout during measuring\n"));
        dimmer.set_frequency(NAN);
        cleanup_measurement();
        return true;
    }

    return false;
}

void start_measure_frequency()
{
    frequency_measurement = true;
    frequency_wait_timer = 0;
}
