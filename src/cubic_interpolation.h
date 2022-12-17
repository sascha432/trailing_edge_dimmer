/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#if DIMMER_CUBIC_INTERPOLATION

#include <Arduino.h>
#include "dimmer_def.h"
#include <InterpolationLib.h>
#include "dimmer.h"

class CubicInterpolation {
public:
    using xyValueType = INTERPOLATION_LIB_XYVALUES_TYPE;
    using xyValueTypePtr = xyValueType *;
    using ChannelType = Dimmer::Channel::type;
    using LevelType = Dimmer::Level::type;

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
        uint8_t size() const;

        xyValueTypePtr getXValues() const;
        xyValueTypePtr getYValues() const;

        void copyToConfig(register_mem_cubic_int_t &cubicInt);
        void createFromConfig(const register_mem_cubic_int_t &cubicInt);

    public:
        xyValueTypePtr _xValues;
        xyValueTypePtr _yValues;
        uint8_t _dataPoints;
    };

public:
    CubicInterpolation();

    void printState() const;
    #if HAVE_CUBIC_INT_PRINT_TABLE
        void printTable(ChannelType channel, uint8_t levelStepSize = 1) const;
    #endif
    #if HAVE_CUBIC_INT_TEST_PERFORMANCE
        void testPerformance(ChannelType channel) const;
    #endif

    int16_t getLevel(LevelType level, ChannelType channel) const;
    uint8_t getInterpolatedLevels(LevelType *dst, LevelType *endPtr, LevelType startLevel, uint8_t levelCount, uint8_t step, uint8_t dataPointCount, xyValueTypePtr xValues, xyValueTypePtr yValues) const;

    void copyFromConfig(const dimmer_config_cubic_int_t &cubicInt);
    void copyToConfig(dimmer_config_cubic_int_t &cubicInt);
    void clear();
    void printConfig() const;

    Channel &getChannel(ChannelType channel);

private:
    LevelType _toLevel(double y) const;
    double _toY(LevelType level) const;

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
        _xValues = new xyValueType[dataPoints << 1]();
        _yValues = &_xValues[dataPoints];
    }
    return (_xValues != nullptr);
}

inline void CubicInterpolation::Channel::free()
{
    if (_xValues) {
        delete[] _xValues;
        _xValues = nullptr;
        _yValues = nullptr;
    }
    _dataPoints = 0;
}

inline void CubicInterpolation::Channel::setDataPoint(uint8_t pos, uint8_t x, uint8_t y)
{
    if (pos < _dataPoints) {
        _xValues[pos] = x;
        _yValues[pos] = y;
    }
}

inline uint8_t CubicInterpolation::Channel::size() const
{
    return _dataPoints;
}

inline CubicInterpolation::CubicInterpolation() :
    _channels()
{
}

inline CubicInterpolation::LevelType CubicInterpolation::getLevel(LevelType level, ChannelType channelNum) const
{
    auto &channel = _channels[channelNum];
    if (channel.size()) {
        return _toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(channel.getXValues(), channel.getYValues(), channel.size(), _toY(level)));
    }
    return level;
}

inline void CubicInterpolation::copyFromConfig(const dimmer_config_cubic_int_t &cubicInt)
{
    clear();
    DIMMER_CHANNEL_LOOP(channel) {
        _channels[channel].createFromConfig(cubicInt.channels[channel]);
    }
}

inline void CubicInterpolation::copyToConfig(dimmer_config_cubic_int_t &cubicInt)
{
    DIMMER_CHANNEL_LOOP(channel) {
        _channels[channel].copyToConfig(cubicInt.channels[channel]);
    }
}

inline void CubicInterpolation::clear()
{
    DIMMER_CHANNEL_LOOP(channel) {
        _channels[channel].free();
    }
}

inline void CubicInterpolation::printConfig() const
{
    DIMMER_CHANNEL_LOOP(channel) {
        Serial.printf_P(PSTR("+REM=cubic_int,%u,i2ct=%02x%02x%02x"), channel, DIMMER_I2C_ADDRESS, DIMMER_COMMAND_WRITE_CUBIC_INT, channel);
        Serial.flush();
        uint8_t i;
        for(i = 0; i < _channels[channel].size(); i++) {
            Serial.printf_P(PSTR("%02x%02x"), _channels[channel].getXValues()[i], _channels[channel].getYValues()[i]);
        }
        for(; i < DIMMER_CUBIC_INT_DATA_POINTS * 4; i++) {
            Serial.print('0');
        }
        Serial.println();
        Serial.flush();
    }
}

inline CubicInterpolation::Channel &CubicInterpolation::getChannel(ChannelType channel)
{
    return _channels[channel];
}

extern CubicInterpolation cubicInterpolation;

#endif
