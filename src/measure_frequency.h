/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "dimmer.h"

#define DEBUG_FREQUENCY_MEASUREMENT             1

class FrequencyMeasurement;

using overflow_counter_t = uint16_t;

extern unsigned long frequency_wait_timer;
extern FrequencyMeasurement *measure;
extern volatile overflow_counter_t timer1_overflow;
extern bool frequency_measurement;

bool run_frequency_measurement();
void start_measure_frequency();

class FrequencyMeasurement {
public:
    static constexpr uint8_t kMeasurementBufferSize = 100; // 1 second @ 50hz
    static constexpr uint32_t kTimeout = (kMeasurementBufferSize * Dimmer::kMaxMicrosPerHalfWave) * 1.5; // maximum time * 1.5

#if HAVE_UINT24
    using tick_counter_t = __uint24;
    static constexpr size_t kMaxCycles_uint24 =  (1UL << 24) / Dimmer::kMaxCyclesPerHalfWave;
    //static_assert(kMeasurementBufferSize < (kMaxCycles_uint24 * 0.85), "reduce kMeasurementBufferSize");
#else
    using tick_counter_t = uint32_t;
#endif

    enum class StateType : uint8_t {
        INIT,
        MEASURE
    };

    struct Ticks {
        tick_counter_t _ticks;

        Ticks() {}
        Ticks(tick_counter_t ticks) : _ticks(ticks) {}
    };

    static constexpr size_t TicksSize = sizeof(Ticks);

    FrequencyMeasurement() : _frequency(NAN), _errors(0), _count(-5) /*, _state(StateType::INIT)*/ {}

    void calc_min_max();
    // void calc();

    void zc_measure_handler(uint16_t lo, uint16_t hi);

    float get_frequency() const {
        return _frequency;
    }

    float _frequency;
    uint16_t _errors;
    Ticks _ticks[kMeasurementBufferSize];
    int16_t _count;
    // StateType _state;
    // tick_counter_t _min;
    // tick_counter_t _max;
};
