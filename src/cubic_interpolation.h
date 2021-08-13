/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#if DIMMER_CUBIC_INTERPOLATION

#include <Arduino.h>
#include "dimmer_def.h"
#include <InterpolationLib.h>

class CubicInterpolation {
public:
    using xyValueType = INTERPOLATION_LIB_XYVALUES_TYPE;
    using xyValueTypePtr = xyValueType *;

public:
    class Channel {
    public:
        Channel() = default;
        ~Channel() {
            free();
        }

        Channel(const Channel &) = delete;
        Channel(Channel &&) = delete;
        Channel &operator=(const Channel &) = delete;
        Channel &operator=(Channel &&) = delete;

        bool allocate(uint8_t dataPoints);
        void free();

        void setDataPoint(uint8_t pos, uint8_t x, uint8_t y);
        uint8_t getDataPoints() const;

        xyValueTypePtr getXValues() const;
        xyValueTypePtr getYValues() const;

    public:
        xyValueTypePtr _xValues;
        xyValueTypePtr _yValues;
        uint8_t _dataPoints;
    };

public:
    CubicInterpolation();

    void printState() const;
    #if HAVE_CUBIC_INT_PRINT_TABLE
        void printTable(dimmer_channel_id_t channel, uint8_t levelStepSize = 1) const;
    #endif
    #if HAVE_CUBIC_INT_TEST_PERFORMANCE
        void testPerformance(dimmer_channel_id_t channel) const;
    #endif

    int16_t getLevel(dimmer_level_t level, dimmer_channel_id_t channel) const;
    uint8_t getInterpolatedLevels(dimmer_level_t *dst, dimmer_level_t *endPtr, dimmer_level_t startLevel, uint8_t levelCount, uint8_t step, uint8_t dataPointCount, xyValueTypePtr xValues, xyValueTypePtr yValues) const;

    void copyFromConfig(register_mem_cubic_int_t &cubic_int, dimmer_channel_id_t channel);
    void copyToConfig(register_mem_cubic_int_t &cubic_int, dimmer_channel_id_t channel);
    void clearTable();

private:
    dimmer_level_t _toLevel(double y) const;
    double _toY(dimmer_level_t level) const;

    Channel _channels[DIMMER_CHANNEL_COUNT];
};


inline CubicInterpolation::xyValueTypePtr CubicInterpolation::Channel::getXValues() const
{
    return _xValues;
}

inline CubicInterpolation::xyValueTypePtr CubicInterpolation::Channel::getYValues() const
{
    return _yValues;
}

inline bool CubicInterpolation::Channel::allocate(uint8_t dataPoints)
{
    free();
    if (dataPoints > 1) {
        _dataPoints = dataPoints;
        _xValues = reinterpret_cast<xyValueTypePtr>(malloc(sizeof(xyValueType) * dataPoints * 2));
        _yValues = &_xValues[dataPoints];
    }
    return (_xValues != nullptr);
}

inline void CubicInterpolation::Channel::free()
{
    if (_xValues) {
        ::free(_xValues);
        _xValues = nullptr;
    }
    _yValues = nullptr;
    _dataPoints = 0;
}

inline void CubicInterpolation::Channel::setDataPoint(uint8_t pos, uint8_t x, uint8_t y)
{
    if (pos < _dataPoints) {
        _xValues[pos] = x;
        _yValues[pos] = y;
    }
}

inline uint8_t CubicInterpolation::Channel::getDataPoints() const
{
    return _dataPoints;
}

inline CubicInterpolation::CubicInterpolation() :
    _channels()
{
}

inline dimmer_level_t CubicInterpolation::getLevel(dimmer_level_t level, dimmer_channel_id_t channelNum) const
{
    auto &channel = _channels[channelNum];
    if (channel.getDataPoints()) {
        return _toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(channel.getXValues(), channel.getYValues(), channel.getDataPoints(), _toY(level)));
    }
    return level;
}

extern CubicInterpolation cubicInterpolation;

#endif
