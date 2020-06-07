/**
 * Author: sascha_lammers@gmx.de
 */

#if DIMMER_CUBIC_INTERPOLATION

#include "cubic_interpolation.h"
#include "main.h"
#include <InterpolationLib.h>

const static uint8_t max_points = 8;
const static double step_size = max_points / (double)DIMMER_MAX_LEVEL;

const int numValues = 6;
double xValues[6] = {   0,  1, 2, 4, 7, 8 };
double yValues[6] = { 0, 3123, 5205, 6246, 7291, 8333 };

static uint8_t cubic_int_value_count(dimmer_channel_id_t channel)
{
	return 6;
}

void print_cubic_int_table(dimmer_channel_id_t channel)
{
	if (!dimmer_config.bits.cubic_interpolation) {
		Serial.println(F("+REM=disabled"));
	}
	else {
		Serial_printf_P(PSTR("+REM=ch%d="), channel);
		uint8_t count = cubic_int_value_count(channel);
		if (count) {
			Serial.print(F("x=["));
			for(uint8_t i = 0; i < count; i++) {
				if (i != 0) {
					Serial.print(',');
				}
				Serial.print((dimmer_level_t)xValues[i]);
			}
			Serial.print(F("],y=["));
			for(uint8_t i = 0; i < count; i++) {
				if (i != 0) {
					Serial.print(',');
				}
				Serial.print((dimmer_level_t)yValues[i]);
			}
			Serial.print(F("],l=["));
			for (float xValue = 0; xValue <= max_points; xValue += step_size)
			{
				if (xValue != 0) {
					Serial.print(',');
				}
				Serial.print((dimmer_level_t)Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, numValues, xValue));
			}
			Serial.println(']');
		}
		else {
			Serial.println(F("disabled"));
		}
	}
}

dimmer_level_t getInterpolatedLevel(dimmer_level_t level, dimmer_channel_id_t channel)
{
	return (dimmer_level_t)Interpolation::DIMMER_INTERPOLATION_METHOD(xValues, yValues, numValues, level * step_size);
}

#endif
