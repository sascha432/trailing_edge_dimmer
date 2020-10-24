/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <crc16.h>
#include "main.h"

typedef struct __attribute__((__packed__)) EEPROM_config_header_t {
    uint16_t crc16;
    uint32_t eeprom_cycle;
    EEPROM_config_header_t() = default;
    EEPROM_config_header_t(uint16_t _crc) : crc16(_crc), eeprom_cycle(0) {}
} EEPROM_config_header_t;

typedef struct __attribute__((__packed__)) EEPROM_config_t {
    union __attribute__((__packed__)) {
        struct __attribute__((__packed__)) {
            uint16_t crc16;
            uint32_t eeprom_cycle;
        };
        EEPROM_config_header_t header;
    };
    register_mem_cfg_t cfg;
    int16_t level[Dimmer::Channel::size()];

    bool operator==(const EEPROM_config_t &config) const {
        return memcmp(this, &config, sizeof(*this)) == 0;
    }

    bool operator!=(const EEPROM_config_t &config) const {
        return memcmp(this, &config, sizeof(*this)) != 0;
    }

} EEPROM_config_t;

struct __attribute__((__packed__)) EEPROMConfig {
    struct __attribute__((__packed__)) {
        decltype(EEPROM_config_t().crc16) crc;
        uint8_t data[sizeof(EEPROM_config_t) - sizeof(EEPROM_config_t().crc16)];
    };

    static constexpr size_t size() {
        return sizeof(data);
    }

    static inline uint16_t crc16(const EEPROM_config_t &config) {
        return crc16_update((reinterpret_cast<const EEPROMConfig *>(&config))->data, size());
    }

    static inline void updateCrc16(EEPROM_config_t &config) {
        config.crc16 = crc16(config);
    }
};

static constexpr size_t EEPROM_config_t_Size = sizeof(EEPROM_config_t);

// extern EEPROM_config_t config;

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
        _config(),
        _eeprom_position(0),
        _eeprom_write_timer(-EEPROM_REPEATED_WRITE_DELAY)
    {}

    // clear EEPROM and store default settings
    void initEEPROM();

    // restore default settings
    void restoreFactory();

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

    EEPROM_config_t &config() {
        return _config;
    }

    dimmer_level_t &level(dimmer_channel_id_t channel) {
        return _config.level[channel];
    }
    dimmer_level_t level(dimmer_channel_id_t channel) const {
        return _config.level[channel];
    }

private:
    friend void dimmer_i2c_slave_setup();

    void initRegisterMem() const;
    void copyToRegisterMem(const register_mem_cfg_t &config) const;
    void copyFromRegisterMem(register_mem_cfg_t &config);

    void resetConfig();
    void writeConfig();

private:
    EEPROM_config_t _config;
    uint16_t _eeprom_position;
    uint32_t _eeprom_write_timer;
};

extern Config conf;
