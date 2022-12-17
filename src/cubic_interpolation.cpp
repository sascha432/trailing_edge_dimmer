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
    if (register_mem.data.cfg.bits.cubic_interpolation) {
        DIMMER_CHANNEL_LOOP(i) {
            Serial.print(_channels[i].size());
            Serial.print((i == (DIMMER_CHANNEL_COUNT - 1)) ? ',' : '/');
        }
    } else {
        Serial.print(F("off,"));
    }
}

#if HAVE_CUBIC_INT_PRINT_TABLE

void CubicInterpolation::printTable(Dimmer::Channel::type channelNum, uint8_t levelStepSize) const
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
            Serial.print(static_cast<Dimmer::Level::type>(channel.getYValues()[i]));
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

void CubicInterpolation::testPerformance(Dimmer::Channel::type channel) const
{
    uint32_t maxTime = 0;
    for(Dimmer::Level::type level = 0; level < DIMMER_MAX_LEVEL; level++) {
        auto start = micros();
        auto levelOut = getLevel(level, channel);
        unsigned dur = micros() - start;
        if (dur > maxTime) {
            maxTime = dur;
            Serial.printf_P(PSTR("+REM=level=%d,result=%d,time=%u\n"), level, levelOut, dur);
        }
    }
    Serial.printf_P(PSTR("+REM=channel=%u,maxtime=%lu\n"), channel, maxTime);
}

#endif

uint8_t CubicInterpolation::getInterpolatedLevels(Dimmer::Level::type *dstPtr, Dimmer::Level::type *endPtr, Dimmer::Level::type startLevel, uint8_t levelCount, uint8_t step, uint8_t dataPointCount, xyValueTypePtr xValues, xyValueTypePtr yValues) const
{
    uint16_t stepSize = (step + 1U);
    Dimmer::Level::type endLevel = startLevel + (levelCount * stepSize);
    uint8_t size = 0;
    Serial.printf("+REM=start=%u,end=%u,step=%u\n", startLevel, endLevel, stepSize);
    for (Dimmer::Level::type level = startLevel; (level < endLevel) && (dstPtr < endPtr); level += stepSize) {
        *dstPtr++ = _toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, dataPointCount, _toY(level)));
        size += sizeof(*dstPtr);
        Serial.printf("+REM=level=%u,%f out=%u\n", level, _toY(level), *(dstPtr - 1));
    }
    return size;
}

Dimmer::Level::type CubicInterpolation::_toLevel(double y) const
{
    return std::clamp<Dimmer::Level::type>((y * ((DIMMER_MAX_LEVEL - 1) / 255.0) + 0.5 /*round*/), 0, DIMMER_MAX_LEVEL - 1);
}

double CubicInterpolation::_toY(Dimmer::Level::type level) const
{
    return std::min<double>(static_cast<uint16_t>(level) / ((DIMMER_MAX_LEVEL - 1) / 255.0), 255);
}

void CubicInterpolation::Channel::copyToConfig(register_mem_cubic_int_t &cubicInt)
{
    cubicInt = {};
    auto ptr = &cubicInt.points[0];
    for(uint8_t i = 0; i < size(); i++) {
        ptr->x = _xValues[i];
        ptr->y = _yValues[i];
        ptr++;
    }
}

void CubicInterpolation::Channel::createFromConfig(const register_mem_cubic_int_t &cubicInt)
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
