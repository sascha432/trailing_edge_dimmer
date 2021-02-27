
/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "main.h"
#include "config.h"

void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);
