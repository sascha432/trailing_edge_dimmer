/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#if DIMMER_CUBIC_INTERPOLATION

#include <Arduino.h>
#include "dimmer.h"

class CubicInterpolation {
public:
    static constexpr uint8_t maxDataPoints = 8;
    static constexpr double step_size = (maxDataPoints - 1) / (double)DIMMER_MAX_LEVELS;

    typedef struct {
        double xValues[maxDataPoints];
        double yValues[maxDataPoints];
        uint8_t dataPoints;
    } Channel_t;

public:
    CubicInterpolation();

    void printState() const;
    void printTable(int8_t channel, uint8_t levelStepSize = 1) const;

    int16_t getLevel(int16_t level, int8_t channel) const;
    void getInterpolatedLevels(int16_t *dst, uint8_t size, int16_t startLevel, uint8_t step, uint8_t dataPointCount, double *xValues, double *yValues) const;
    int16_t *getRegisterMemPtr() const;

    uint8_t getValueCount(int8_t channel) const;

    bool allocateChannel(int8_t channel, uint8_t size);
    void freeChannel(int8_t channel);
    void setDataPoint(int8_t channel, uint8_t x, uint8_t y);

private:
    Channel_t *_channels[DIMMER_CHANNELS];
};

extern CubicInterpolation cubicInterpolation;

#endif
