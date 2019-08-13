
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

#ifndef __attribute__packed__
#define __attribute__packed__           __attribute__((packed))
#endif

typedef struct __attribute__packed__ {
    uint8_t command;
    int8_t read_length;
    int8_t status;
} register_mem_command_t;

typedef struct __attribute__packed__ {
    union {
        config_options_t bits;
        uint8_t options;
    };
    uint8_t max_temp;
    float fade_in_time;
    uint8_t temp_check_interval;
    float linear_correction_factor;
} register_mem_cfg_t;

typedef struct __attribute__packed__ {
    int16_t from_level;
    int8_t channel;
    int16_t to_level;
    float time;
    register_mem_command_t cmd;
    uint16_t level[8];
    float temp;
    uint16_t vcc;
    register_mem_cfg_t cfg;
    uint8_t address;
} register_mem_t;

typedef union __attribute__packed__ {
    register_mem_t data;
    uint8_t raw[sizeof(register_mem_t)];
} register_mem_union_t;

void dump_macros();
void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);

extern register_mem_union_t register_mem;
