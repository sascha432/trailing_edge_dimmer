/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "dimmer.h"

#if DIMMER_CUBIC_INTERPOLATION

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

        xyValueTypePtr getXValues() const {
            return _xValues;
        }
        xyValueTypePtr getYValues() const {
            return _yValues;
        }

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

    Channel _channels[Dimmer::kMaxChannels];
};

extern CubicInterpolation cubicInterpolation;

#endif
