
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


typedef struct __attribute__packed__ {
    uint32_t eeprom_cycle;
    uint16_t crc16;
    register_mem_cfg_t cfg;
    int16_t level[Dimmer::Channel::size];
} config_t;

void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);

void dimmer_init_register_mem();
void dimmer_copy_config_to(register_mem_cfg_t &config);
void dimmer_copy_config_from(const register_mem_cfg_t &config);

extern config_t config;
