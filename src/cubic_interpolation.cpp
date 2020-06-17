/**
 * Author: sascha_lammers@gmx.de
 */

#if DIMMER_CUBIC_INTERPOLATION

#include "cubic_interpolation.h"
#include "main.h"
#include <InterpolationLib.h>

CubicInterpolation cubicInterpolation;

constexpr uint8_t max_data_points = 8;
constexpr double step_size = (max_data_points - 1) / (double)DIMMER_MAX_LEVELS;

double xValues[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
double yValues[8] = { 0, 100, 2300, 6246, 7291, 7300, 7401, 8192 };

CubicInterpolation::CubicInterpolation() : _channels() {
}

uint8_t CubicInterpolation::getValueCount(dimmer_channel_id_t channel) const
{
	if (_channels[channel]) {
		return _channels[channel]->dataPoints;
	}
	return 0;
}

void CubicInterpolation::printState() const
{
	if (dimmer_config.bits.cubic_interpolation) {
		for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
			Serial.print(getValueCount(i));
			Serial.print((i == (DIMMER_CHANNELS - 1)) ? ',' : '/');
		}
	}
	else {
		Serial.print(F("off,"));
	}
}

void CubicInterpolation::printTable(dimmer_channel_id_t channel, uint8_t levelStepSize) const
{
	Serial_printf_P(PSTR("+REM=ch%d="), channel);
	uint8_t count = getValueCount(channel);
	if (count) {
		Serial.print(F("x=["));
		for(uint8_t i = 0; i < count; i++) {
			if (i != 0) {
				Serial.print(',');
			}
			Serial.print((uint8_t)xValues[i]);
		}
		Serial.print(F("],y=["));
		for(uint8_t i = 0; i < count; i++) {
			if (i != 0) {
				Serial.print(',');
			}
			Serial.print((uint8_t)yValues[i]);
		}
		Serial.print(F("],l=["));
		for(dimmer_level_t level = 0; level < DIMMER_MAX_LEVELS; level += levelStepSize) {
			if (level != 0) {
				Serial.print(',');
			}
			Serial.print((dimmer_level_t)Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, max_data_points, level * step_size));
		}
		Serial.println(']');
	}
	else {
		Serial.println(F("disabled"));
	}
}

dimmer_level_t CubicInterpolation::getLevel(dimmer_level_t level, dimmer_channel_id_t channel) const
{
	return (dimmer_level_t)Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, max_data_points, level * step_size);
}

void CubicInterpolation::getInterpolatedLevels(dimmer_level_t *dst, uint8_t size, dimmer_level_t startLevel, uint8_t step, uint8_t dataPointCount, double *xValues, double *yValues) const
{
	dimmer_level_t end = startLevel + size;
	for(dimmer_level_t level = startLevel; level < end; level += step) {
		*dst++ = Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, dataPointCount, level * step_size);
	}
}

dimmer_level_t *CubicInterpolation::getRegisterMemPtr() const
{
	return reinterpret_cast<dimmer_level_t *>(&register_mem.data.level[0]);
}

bool CubicInterpolation::allocateChannel(int8_t channel, uint8_t size)
{
	return false;
}

void CubicInterpolation::freeChannel(int8_t channel)
{

}

void CubicInterpolation::setDataPoint(int8_t channel, uint8_t x, uint8_t y)
{

}

#endif
