
/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "main.h"
#include "dimmer_protocol.h"
#include "helpers.h"

#if SERIAL_I2C_BRDIGE

#include "SerialTwoWire.h"

#else

#include <Wire.h>

#endif

#include "dimmer_reg_mem.h"

class config_t {
public:
    config_t();

    void clear();
    void read(size_t position);
    size_t write(size_t position);
    bool compare(size_t position);
    size_t size() const;

    struct __attribute__packed__ {
        uint32_t eeprom_cycle;
        uint16_t crc16;
        int16_t level[DIMMER_CHANNELS];
    };
    register_mem_cfg_t &cfg;
};

void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);

extern register_mem_union_t register_mem;
extern config_t config;
