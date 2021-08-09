/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "dimmer.h"
#include "dimmer_reg_mem.h"

#define DEBUG_FREQUENCY_MEASUREMENT 1

class FrequencyMeasurement;

using overflow_counter_t = uint16_t;

extern uint32_t frequency_wait_timer;
extern FrequencyMeasurement *measure;
extern volatile overflow_counter_t timer1_overflow;
extern bool frequency_measurement;

bool run_frequency_measurement();
void start_measure_frequency();

class FrequencyMeasurement {
public:
    static constexpr uint8_t kMeasurementBufferSize = 100; // 1 second @ 50hz
    static constexpr uint32_t kTimeout = (kMeasurementBufferSize * Dimmer::kMaxMicrosPerHalfWave) * 1.5; // maximum time * 1.5

    static constexpr size_t kMaxCycles_uint24 =  (1UL << 24) / Dimmer::kMaxCyclesPerHalfWave;

    enum class StateType : uint8_t {
        INIT,
        MEASURE
    };

    class Ticks {
    public:
        Ticks() : _value(0) {}
        Ticks(uint24_t value) : _value(value) {}
        uint24_t diff(uint24_t value) const {
            return _value - value;
        }
        operator uint24_t() const {
            return _value;
        }
        Ticks &operator=(uint24_t value) {
            _value = value;
            return *this;
        }
    private:
        uint24_t _value;
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
    int16_t _count;
    Ticks _ticks[kMeasurementBufferSize];
};

static constexpr size_t FrequencyMeasurementSize = sizeof(FrequencyMeasurement);

static_assert(FrequencyMeasurement::kMeasurementBufferSize * 3 + 8 == FrequencyMeasurementSize, "invalid size");
