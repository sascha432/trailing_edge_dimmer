/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "dimmer.h"

#if DIMMER_CUBIC_INTERPOLATION

class CubicInterpolation {
public:
    class Channel {
    public:
        Channel() = default;
        ~Channel() {
            free();
        }

        Channel &operator=(const Channel &) = delete;
        Channel &operator=(Channel &&) = delete;

        void allocate(uint8_t dataPoints);
        void free();

        void setDataPoint(uint8_t pos, uint8_t x, uint8_t y);
        uint8_t getDataPoints() const;
        // double getStepSize() const;

        double *getXValues() const {
            return _xValues;
        }
        double *getYValues() const {
            return _yValues;
        }

    public:
        double *_xValues;
        double *_yValues;
        uint8_t _dataPoints;
    };

public:
    CubicInterpolation();

    void printState() const;
    void printTable(int8_t channel, uint8_t levelStepSize = 1) const;

    int16_t getLevel(int16_t level, int8_t channel) const;
    void getInterpolatedLevels(int16_t *dst, uint8_t size, int16_t startLevel, uint8_t step, uint8_t dataPointCount, double *xValues, double *yValues) const;

    // uint8_t getValueCount(int8_t channel) const;

    Channel &getChannel(int8_t channel);

    void copyFromConfig(register_mem_cubic_int_t &cubic_int, int8_t channel);
    void copyToConfig(register_mem_cubic_int_t &cubic_int, int8_t channel);
    void clearTable();

private:
    static constexpr double stepSize = 254 / (double)DIMMER_MAX_LEVELS;
    Channel _channels[DIMMER_CHANNELS];
};

extern CubicInterpolation cubicInterpolation;

#endif
