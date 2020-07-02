/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"
#include "helpers.h"

#if DIMMER_CUBIC_INTERPOLATION

#include "cubic_interpolation.h"
#include <InterpolationLib.h>

CubicInterpolation cubicInterpolation;

// 29388

void CubicInterpolation::Channel::allocate(uint8_t dataPoints)
{
	free();
	_dataPoints = dataPoints;
	_xValues = new double[dataPoints];
	_yValues = new double[dataPoints];
}

void CubicInterpolation::Channel::free()
{
	if (_xValues) {
		delete _xValues;
		_xValues = nullptr;
	}
	if (_yValues) {
		delete _yValues;
		_yValues = nullptr;
	}
	_dataPoints = 0;
}

void CubicInterpolation::Channel::setDataPoint(uint8_t pos, uint8_t x, uint8_t y)
{
	if (pos < _dataPoints) {
		_xValues[pos] = x;
		_yValues[pos] = y * (DIMMER_MAX_LEVELS / 255.0);
		Serial_printf_P(PSTR("setDataPoint(%u) x=%f, y=%f\n"), pos, _xValues[pos], _yValues[pos]);
	}
}

uint8_t CubicInterpolation::Channel::getDataPoints() const
{
	return _dataPoints;
}

// double CubicInterpolation::Channel::getStepSize() const
// {
// 	return 255 / (double)DIMMER_MAX_LEVELS;
// }

CubicInterpolation::CubicInterpolation() : _channels() {
}

// uint8_t CubicInterpolation::getValueCount(dimmer_channel_id_t channel) const
// {
// 	return _channels[channel].getDataPoints();
// }

void CubicInterpolation::printState() const
{
	if (dimmer_config.bits.cubic_interpolation) {
		for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
			Serial.print(_channels[i].getDataPoints());
			Serial.print((i == (DIMMER_CHANNELS - 1)) ? ',' : '/');
		}
	}
	else {
		Serial.print(F("off,"));
	}
}

void CubicInterpolation::printTable(dimmer_channel_id_t channelNum, uint8_t levelStepSize) const
{
	Serial_printf_P(PSTR("+REM=ch%d="), channelNum);
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
		for(dimmer_level_t level = 0; level < DIMMER_MAX_LEVELS; level += levelStepSize) {
			if (level != 0) {
				Serial.print(',');
			}
			Serial.print((dimmer_level_t)Interpolation::DIMMER_INTERPOLATION_METHOD(channel.getXValues(), channel.getYValues(), maxDataPoints, level * stepSize));
		}
		Serial.println(']');
	}
	else {
		Serial.println(F("disabled"));
	}
}

dimmer_level_t CubicInterpolation::getLevel(dimmer_level_t level, dimmer_channel_id_t channelNum) const
{
	auto &channel = _channels[channelNum];
	if (channel.getDataPoints()) {
		return (dimmer_level_t)Interpolation::DIMMER_INTERPOLATION_METHOD(channel.getXValues(), channel.getYValues(), channel.getDataPoints(), level * stepSize);
	}
	return level;
}

void CubicInterpolation::getInterpolatedLevels(dimmer_level_t *dst, uint8_t size, dimmer_level_t startLevel, uint8_t step, uint8_t dataPointCount, double *xValues, double *yValues) const
{
	dimmer_level_t end = startLevel + size;
	for(dimmer_level_t level = startLevel; level < end; level += step) {
		*dst++ = Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, dataPointCount, level * stepSize);
	}
}

// CubicInterpolation::Channel &CubicInterpolation::getChannel(int8_t channel)
// {
// 	return *(&_channels[channel]);
// }

void CubicInterpolation::copyFromConfig(register_mem_cubic_int_t &cubic_int, int8_t channelNum)
{
	auto points = cubic_int.points;
	auto &channel = _channels[channelNum];
	uint8_t count;
	for(count = 0; (count < DIMMER_CUBIC_INT_DATA_POINTS) && (points[count].x != 0xff); count++) {
	}
	if (count) {
		channel.allocate(count);
		for(uint8_t i = 0; i < count; i++) {
			channel.setDataPoint(i, points[i].x, points[i].y);
		}
	}
	else {
		channel.free();
	}
}

void CubicInterpolation::copyToConfig(register_mem_cubic_int_t &cubic_int, int8_t channelNum)
{
	cubic_int = {};
	auto &channel = _channels[channelNum];
	memset(cubic_int.points, 0xff, sizeof(cubic_int.points));
	for(uint8_t i = 0; i < channel._dataPoints; i++) {
		cubic_int.points[i].x = channel._xValues[i];
		cubic_int.points[i].y = round(channel._yValues[i] / (DIMMER_MAX_LEVELS / 255.0));
	}
}


void CubicInterpolation::clearTable()
{
	FOR_CHANNELS(i) {
		_channels[i].free();
	}
}

#endif
