
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

typedef struct __attribute__((__packed__)) {
    uint32_t eeprom_cycle;
    uint16_t crc16;
} EEPROM_config_header_t;

typedef struct __attribute__((__packed__)) {
    union {
        struct __attribute__((__packed__)) {
            uint32_t eeprom_cycle;
            uint16_t crc16;
        };
        EEPROM_config_header_t header;
    };
    register_mem_cfg_t cfg;
    int16_t level[Dimmer::Channel::size];
} EEPROM_config_t;

// size of configuration stored in EEPROM
static constexpr size_t kEEPROMConfigSize = sizeof(EEPROM_config_t);

// max. number of copies that fit into the EEPROM
static constexpr size_t kEEPROMMaxCopies = E2END / sizeof(EEPROM_config_t);

void dimmer_i2c_slave_setup();
void dimmer_i2c_on_receive(int length,  Stream *in);
void dimmer_i2c_on_request(Stream *out);

void dimmer_init_register_mem();
void dimmer_copy_config_to(register_mem_cfg_t &config);
void dimmer_copy_config_from(const register_mem_cfg_t &config);

extern EEPROM_config_t config;
