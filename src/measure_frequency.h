/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "dimmer.h"
#include "dimmer_reg_mem.h"

using overflow_counter_t = uint16_t;

extern volatile overflow_counter_t timer1_overflow;

class FrequencyMeasurement {
public:
    static constexpr uint8_t kMeasurementBufferSize = DIMMER_ZC_MIN_SAMPLES; // number of samples to collect
    static constexpr uint16_t kTimeoutMillis = (static_cast<uint32_t>(kMeasurementBufferSize) * Dimmer::kMaxMicrosPerHalfWave) * 1.5 / 1000;
    static constexpr size_t kMaxCycles_uint24 = (1UL << 24) / Dimmer::kMaxCyclesPerHalfWave;

    static_assert(kTimeoutMillis > 500, "timeout should not be less than 500ms");
    static_assert(kTimeoutMillis < 5000, "timeout should not exceed 5 seconds");

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

    FrequencyMeasurement() : 
        _frequency(NAN), 
        _errors(0), 
        _count(-5),
        _start(millis())
    {}

    void zc_measure_handler(uint16_t lo, uint16_t hi);

    bool is_timeout() const;
    inline bool is_done() const;
    float get_frequency() const;

    static void attach_handler();
    static void detach_handler();
    static void cleanup();
    static bool run();

private:
    void calc_min_max();

private:
public:
    float _frequency;
    uint16_t _errors;
    int16_t _count;
    uint16_t _start;
    Ticks _ticks[kMeasurementBufferSize];
};

extern FrequencyMeasurement *measure;

inline bool FrequencyMeasurement::is_timeout() const
{
    return (static_cast<uint16_t>(millis()) - _start) > kTimeoutMillis;
}

inline bool FrequencyMeasurement::is_done() const
{
    return !isnan(_frequency);
}

inline float FrequencyMeasurement::get_frequency() const 
{
    return _frequency == 0 ? NAN : _frequency;
}

inline void FrequencyMeasurement::detach_handler() 
{
    detachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN));
}
