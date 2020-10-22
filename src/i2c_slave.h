
/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "main.h"

#if SERIAL_I2C_BRDIGE

#include "SerialTwoWire.h"

#else

#include <Wire.h>

#endif

#include "config.h"

void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);
