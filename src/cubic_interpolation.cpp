/**
 * Author: sascha_lammers@gmx.de
 */

#if DIMMER_CUBIC_INTERPOLATION

#include "dimmer_def.h"
#include "helpers.h"
#include "main.h"
#include "cubic_interpolation.h"

CubicInterpolation cubicInterpolation;

void CubicInterpolation::printState() const
{
    if (dimmer_config.bits.cubic_interpolation) {
        DIMMER_CHANNEL_LOOP(i) {
            Serial.print(_channels[i].size());
            Serial.print((i == (DIMMER_CHANNEL_COUNT - 1)) ? ',' : '/');
        }
    } else {
        Serial.print(F("off,"));
    }
}

#if HAVE_CUBIC_INT_PRINT_TABLE

void CubicInterpolation::printTable(dimmer_channel_id_t channelNum, uint8_t levelStepSize) const
{
    Serial.printf_P(PSTR("+REM=ch%d="), channelNum);
    auto &channel = _channels[channelNum];
    uint8_t maxDataPoints = channel.size();
    if (maxDataPoints) {
        Serial.print(F("x=["));
        for (uint8_t i = 0; i < maxDataPoints; i++) {
            if (i != 0) {
                Serial.print(',');
            }
            Serial.print((uint8_t)channel.getXValues()[i]);
        }
        Serial.print(F("],y=["));
        for (uint8_t i = 0; i < maxDataPoints; i++) {
            if (i != 0) {
                Serial.print(',');
            }
            Serial.print(static_cast<dimmer_level_t>(channel.getYValues()[i]));
        }
        Serial.print(F("],l=["));
        double step = 255.0 / ((DIMMER_MAX_LEVEL - 1) / (levelStepSize + 1.0));
        for (double level = 0; level < 255.4 /* floating point rounding might end up with 255.00003 instead of 255.0 */; level += step) {
            if (level != 0) {
                Serial.print(',');
            }
            Serial.print(_toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(channel.getXValues(), channel.getYValues(), maxDataPoints, level)));
        }
        Serial.println(']');
    } else {
        Serial.println(F("disabled"));
    }
}

#endif

#if HAVE_CUBIC_INT_TEST_PERFORMANCE

void CubicInterpolation::testPerformance(dimmer_channel_id_t channel) const
{
    uint32_t maxTime = 0;
    for(dimmer_level_t level = 0; level < DIMMER_MAX_LEVEL; level++) {
        auto start = micros();
        auto levelOut = getLevel(level, channel);
        auto dur = micros() - start;
        if (dur > maxTime) {
            maxTime = dur;
            Serial.printf_P(PSTR("+REM=level=%d,result=%d,time=%lu\n"), level, levelOut, (unsigned long)dur);
        }
    }
    Serial.printf_P(PSTR("+REM=channel=%u,maxtime=%lu\n"), channel, maxTime);
}

#endif

uint8_t CubicInterpolation::getInterpolatedLevels(dimmer_level_t *dstPtr, dimmer_level_t *endPtr, dimmer_level_t startLevel, uint8_t levelCount, uint8_t step, uint8_t dataPointCount, xyValueTypePtr xValues, xyValueTypePtr yValues) const
{
    uint16_t stepSize = (step + 1U);
    dimmer_level_t endLevel = startLevel + (levelCount * stepSize);
    uint8_t size = 0;
    Serial.printf("+REM=start=%u,end=%u,step=%u\n", startLevel, endLevel, stepSize);
    for (dimmer_level_t level = startLevel; (level < endLevel) && (dstPtr < endPtr); level += stepSize) {
        *dstPtr++ = _toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, dataPointCount, _toY(level)));
        size += sizeof(*dstPtr);
        Serial.printf("+REM=level=%u,%f out=%u\n", level, _toY(level), *(dstPtr - 1));
    }
    return size;
}

dimmer_level_t CubicInterpolation::_toLevel(double y) const
{
    return std::clamp<dimmer_level_t>((y * ((DIMMER_MAX_LEVEL - 1) / 255.0) + 0.5 /*round*/), 0, DIMMER_MAX_LEVEL - 1);
    // return min(DIMMER_MAX_LEVEL - 1, max(0, (dimmer_level_t)((y * ((DIMMER_MAX_LEVEL - 1) / 255.0) + 0.5 /*round*/))));
}

double CubicInterpolation::_toY(dimmer_level_t level) const
{
    return std::min<double>(static_cast<uint16_t>(level) / ((DIMMER_MAX_LEVEL - 1) / 255.0), 255);
    // return min(255.0, (uint16_t)level / ((DIMMER_MAX_LEVEL - 1) / 255.0)); // -1 = max level
}

void CubicInterpolation::Channel::copyToConfig(register_mem_cubic_int_t &cubicInt, dimmer_channel_id_t channel)
{
    cubicInt = {};
    auto ptr = &cubicInt.points[0];
    for(uint8_t i = 0; i < size(); i++) {
        ptr->x = _xValues[i];
        ptr->y = _yValues[i];
        ptr++;
    }
}

void CubicInterpolation::Channel::createFromConfig(const register_mem_cubic_int_t &cubicInt, dimmer_channel_id_t channel)
{
    auto points = &cubicInt.points[0];
    uint8_t maxX = (points++)->x;
    uint8_t count;
    for (count = 1; count < DIMMER_CUBIC_INT_DATA_POINTS; count++) {
        if (points->x <= maxX) {
            break;
        }
        maxX = (points++)->x;
    }
    if (allocate(count)) {
        points = &cubicInt.points[0];
        for (uint8_t i = 0; i < count; i++) {
            setDataPoint(i, points->x, points->y);
            points++;
        }
    }
}

#endif
