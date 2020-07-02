
/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "main.h"
#include "dimmer_protocol.h"
#include "helpers.h"
#include "config_storage.h"

void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);

extern register_mem_union_t register_mem;

