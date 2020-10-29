/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "dimmer.h"
#include "dimmer_reg_mem.h"

#define DEBUG_FREQUENCY_MEASUREMENT             1

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

#if HAVE_UINT24 == 1
    class Ticks {
    public:
        Ticks() : _value(0) {}
        Ticks(uint24_t value) : _value(value) {}
        uint24_t diff(uint24_t value) const {
            return *this - value;
        }
        operator uint24_t() const {
            return _value;
        }
        explicit operator uint32_t() const {
            return _value[0] | ((uint16_t)_value[1] << 8) | ((uint32_t)_value[2] << 16);
        }
    private:
        uint24_t _value;
    };
#else
    class Ticks {
    public:
        Ticks() : _value{} {}
        Ticks(uint24_t value) : _value{(uint8_t)value, (uint8_t)(value << 8), (uint8_t)(value << 16)} {}
        Ticks(uint32_t value) : _value{(uint8_t)value, (uint8_t)(value << 8), (uint8_t)(value << 16)} {}
        uint24_t diff(uint24_t value) const {
            auto tmp = (uint32_t)*this;
            tmp -= value;
            return tmp;
        }
        operator uint24_t() const {
            return _value[0] | ((uint16_t)_value[1] << 8) | ((uint32_t)_value[2] << 16);
        }
        explicit operator uint32_t() const {
            return _value[0] | ((uint16_t)_value[1] << 8) | ((uint32_t)_value[2] << 16);
        }
    private:
        uint8_t _value[3];
    };
#endif

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
