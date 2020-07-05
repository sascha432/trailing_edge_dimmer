/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"
#include "helpers.h"

#if DIMMER_CUBIC_INTERPOLATION

#include "cubic_interpolation.h"
#include <InterpolationLib.h>


CubicInterpolation cubicInterpolation;

bool CubicInterpolation::Channel::allocate(uint8_t dataPoints)
{
	free();
	if (dataPoints > 1) {
		_dataPoints = dataPoints;
		_xValues = reinterpret_cast<xyValueTypePtr>(malloc(sizeof(xyValueType) * dataPoints * 2));
		DEBUG_VALIDATE_ALLOC(_xValues, sizeof(xyValueType) * dataPoints * 2);
		_yValues = &_xValues[dataPoints];
	}
	return (_xValues != nullptr);
}

void CubicInterpolation::Channel::free()
{
	if (_xValues) {
		::free(_xValues);
		_xValues = nullptr;
	}
	_yValues = nullptr;
	_dataPoints = 0;
}

void CubicInterpolation::Channel::setDataPoint(uint8_t pos, uint8_t x, uint8_t y)
{
	if (pos < _dataPoints) {
		_xValues[pos] = x;
		_yValues[pos] = y;
	}
}

uint8_t CubicInterpolation::Channel::getDataPoints() const
{
	return _dataPoints;
}

CubicInterpolation::CubicInterpolation() : _channels() {
}

void CubicInterpolation::printState() const
{
	if (dimmer_config.bits.cubic_interpolation) {
		for(dimmer_channel_id_t i = 0; i < Dimmer::kMaxChannels; i++) {
			Serial.print(_channels[i].getDataPoints());
			Serial.print((i == (Dimmer::kMaxChannels - 1)) ? ',' : '/');
		}
	}
	else {
		Serial.print(F("off,"));
	}
}

#if HAVE_CUBIC_INT_PRINT_TABLE

void CubicInterpolation::printTable(dimmer_channel_id_t channelNum, uint8_t levelStepSize) const
{
	Serial.printf_P(PSTR("+REM=ch%d="), channelNum);
	auto &channel = _channels[channelNum];
	uint8_t maxDataPoints = channel.getDataPoints();
	if (maxDataPoints) {
		Serial.print(F("x=["));
		for(uint8_t i = 0; i < maxDataPoints; i++) {
			if (i != 0) {
				Serial.print(',');
			}
			Serial.print((uint8_t)channel.getXValues()[i]);
		}
		Serial.print(F("],y=["));
		for(uint8_t i = 0; i < maxDataPoints; i++) {
			if (i != 0) {
				Serial.print(',');
			}
			Serial.print(static_cast<dimmer_level_t>(channel.getYValues()[i]));
		}
		Serial.print(F("],l=["));
		double step = 255.0 / ((Dimmer::kMaxLevels - 1) / (levelStepSize + 1.0));
		for(double level = 0; level < 255.4/* floating point rounding might end up with 255.00003 instead of 255.0 */; level += step) {
			if (level != 0) {
				Serial.print(',');
			}
			Serial.print(_toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(channel.getXValues(), channel.getYValues(), maxDataPoints, level)));
		}
		Serial.println(']');
	}
	else {
		Serial.println(F("disabled"));
	}
}

#endif

#if HAVE_CUBIC_INT_TEST_PERFORMANCE

void CubicInterpolation::testPerformance(dimmer_channel_id_t channel) const
{
	uint32_t maxTime = 0;
	for(dimmer_level_t level = 0; level < Dimmer::kMaxLevels; level++) {
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

dimmer_level_t CubicInterpolation::getLevel(dimmer_level_t level, dimmer_channel_id_t channelNum) const
{
	auto &channel = _channels[channelNum];
	if (channel.getDataPoints()) {
		return _toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(channel.getXValues(), channel.getYValues(), channel.getDataPoints(), _toY(level)));
	}
	return level;
}

uint8_t CubicInterpolation::getInterpolatedLevels(dimmer_level_t *dstPtr, dimmer_level_t *endPtr, dimmer_level_t startLevel, uint8_t levelCount, uint8_t step, uint8_t dataPointCount, xyValueTypePtr xValues, xyValueTypePtr yValues) const
{
	uint16_t stepSize = (step + 1U);
	dimmer_level_t endLevel = startLevel + (levelCount * stepSize);
	uint8_t size = 0;
	Serial.printf("+REM=start=%u,end=%u,step=%u\n", startLevel, endLevel, stepSize);
	for(dimmer_level_t level = startLevel; (level < endLevel) && (dstPtr < endPtr); level += stepSize) {
		*dstPtr++ = _toLevel(Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, dataPointCount, _toY(level)));
		size += sizeof(*dstPtr);
		Serial.printf("+REM=level=%u,%f out=%u\n", level, _toY(level), *(dstPtr-1));
	}
	return size;
}

void CubicInterpolation::copyFromConfig(register_mem_cubic_int_t &cubic_int, dimmer_channel_id_t channelNum)
{
	auto points = cubic_int.points;

	uint8_t maxX = (points++)->x, count;
	for(count = 1; count < Dimmer::kCubicIntMaxDataPoints; count++) {
		if (points->x <= maxX) {
			break;
		}
		maxX = (points++)->x;
	}

	auto &channel = _channels[channelNum];
	if (channel.allocate(count)) {
		points = cubic_int.points;
		for(uint8_t i = 0; i < count; i++) {
			channel.setDataPoint(i, points->x, points->y);
			points++;
		}
	}
}

void CubicInterpolation::copyToConfig(register_mem_cubic_int_t &cubic_int, dimmer_channel_id_t channelNum)
{
	auto &channel = _channels[channelNum];
	auto xValues = channel._xValues;
	auto yValues = channel._yValues;
	auto points = cubic_int.points;
	cubic_int = {};
	for(uint8_t i = 0; i < channel._dataPoints; i++) {
		points->x = *xValues++;
		points->y = *yValues++;
		points++;
	}
}

void CubicInterpolation::clearTable()
{
	FOR_CHANNELS(i) {
		_channels[i].free();
	}
}

dimmer_level_t CubicInterpolation::_toLevel(double y) const
{
	return min(Dimmer::kMaxLevels - 1, max(0, (dimmer_level_t)((y * ((Dimmer::kMaxLevels - 1) / 255.0) + 0.5/*round*/))));
}

double CubicInterpolation::_toY(dimmer_level_t level) const
{
	return min(255.0, (uint16_t)level / ((Dimmer::kMaxLevels - 1) / 255.0)); // -1 = max level
}

#endif
