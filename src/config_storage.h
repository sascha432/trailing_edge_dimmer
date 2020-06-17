/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "dimmer_reg_mem.h"

class ConfigStorage {
public:
    ConfigStorage();

    void clear();
    // read from EEPROM at position
    void read(size_t position);
    // write to EEPROM at position
    size_t write(size_t position);
    // compare stored configuration with EEPROM at position
    bool compare(size_t position);

    // copy dimming levels to storage
    // function restore_level() is copying levels from the storage and fading it in
    void copyLevels();

    // get CRC
    uint16_t crc() const;
    // update CRC
    void updateCrc();

    static constexpr size_t cubicIntSize() {
#if DIMMER_CUBIC_INTERPOLATION
        return sizeof(register_mem_cubic_int_t) * DIMMER_CHANNELS;
#else
        return 0;
#endif
    }
    static constexpr size_t size() {
        return sizeof(eeprom_cycle) + sizeof(crc16) + sizeof(level) + cubicIntSize() + sizeof(register_mem_cfg_t);
    }

    struct __attribute__packed__ {
        uint32_t eeprom_cycle;
        uint16_t crc16;
        int16_t level[DIMMER_CHANNELS];
    };
    register_mem_cfg_t &cfg;
};

extern ConfigStorage config;
