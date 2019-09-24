
/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "main.h"
#include "dimmer_protocol.h"

#if SERIAL_I2C_BRDIGE

#include "SerialTwoWire.h"

#else

#include <Wire.h>

#endif

#include "dimmer_reg_mem.h"

typedef struct __attribute__packed__ {
    uint32_t eeprom_cycle;
    uint16_t crc16;
    register_mem_cfg_t cfg;
    int16_t level[DIMMER_CHANNELS];
} config_t;

void dump_macros();
void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);

extern register_mem_union_t register_mem;
extern config_t config;
