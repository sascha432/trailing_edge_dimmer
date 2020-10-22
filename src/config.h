/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "main.h"

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

extern EEPROM_config_t config;

class Config {
public:
    // size of configuration stored in EEPROM
    static constexpr size_t kEEPROMConfigSize = sizeof(EEPROM_config_t);
    // max. number of copies that fit into the EEPROM
    static constexpr size_t kEEPROMMaxCopies = E2END / sizeof(EEPROM_config_t);
    // marker for invalid position
    static constexpr uint16_t kInvalidPosition = ~0;

public:
    Config() :
        _config(config),
        _eeprom_position(0),
        _eeprom_write_timer(-EEPROM_REPEATED_WRITE_DELAY)
    {}

    // clear EEPROM and store default settings
    void initEEPROM();

    // read configuration
    void readConfig();

    // schedule storing the configuration
    inline void scheduleWriteConfig() {
        writeConfig();
    }

    // force set to true writes the EEPROM even if no changes are detected
    void _writeConfig(bool force);

    static uint32_t get_eeprom_num_writes(uint32_t cycle, uint16_t position) {
        return (kEEPROMMaxCopies * (cycle - 1)) + (position / sizeof(_config));
    }

    uint32_t getEEPROMWriteCount() const {
        return get_eeprom_num_writes(_config.eeprom_cycle, _eeprom_position);
    }

    bool isEEPROMWriteTimerExpired() const {
        return (millis() >= _eeprom_write_timer);
    }

private:
    friend void dimmer_i2c_slave_setup();

    void initRegisterMem();
    void copyToRegisterMem(register_mem_cfg_t &config);
    void copyFromRegisterMem(const register_mem_cfg_t &config);

    void resetConfig();
    void writeConfig();

private:
    EEPROM_config_t &_config;
    uint16_t _eeprom_position;
    uint32_t _eeprom_write_timer;
};

extern Config conf;
