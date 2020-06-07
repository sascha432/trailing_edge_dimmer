/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#if DIMMER_CUBIC_INTERPOLATION

#include <Arduino.h>

void print_cubic_int_table(int8_t channel);
int16_t getInterpolatedLevel(int16_t level, int8_t channel);

#endif
