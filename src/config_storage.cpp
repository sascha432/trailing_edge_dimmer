/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"
#include "crc16.h"
#include <EEPROM.h>

ConfigStorage config;

ConfigStorage::ConfigStorage() : cfg(register_mem.data.cfg)
{
    clear();
}

void ConfigStorage::clear()
{
    eeprom_cycle = 0;
    crc16 = 0;
    bzero(level, sizeof(level));
}

void ConfigStorage::read(size_t position)
{
    EEPROM.get(position, eeprom_cycle);
    position += sizeof(eeprom_cycle);
    EEPROM.get(position, crc16);
    position += sizeof(crc16);
    EEPROM.get(position, level);
    position += sizeof(level);
#if DIMMER_CUBIC_INTERPOLATION
    {
        register_mem_cubic_int_t tmp_cubic_int[DIMMER_CHANNELS];
        EEPROM.get(position, tmp_cubic_int);
        memcpy(register_mem.data.cubic_int, tmp_cubic_int, sizeof(tmp_cubic_int));
        position += sizeof(tmp_cubic_int);
    }
#endif
    EEPROM.get(position, register_mem.data.cfg);
}

size_t ConfigStorage::write(size_t position)
{
    EEPROM.put(position, eeprom_cycle);
    position += sizeof(eeprom_cycle);
    EEPROM.put(position, crc16);
    position += sizeof(crc16);
    EEPROM.put(position, level);
    position += sizeof(level);
#if DIMMER_CUBIC_INTERPOLATION
    {
        register_mem_cubic_int_t tmp_cubic_int[DIMMER_CHANNELS];
        memcpy(tmp_cubic_int, register_mem.data.cubic_int, sizeof(tmp_cubic_int));
        EEPROM.put(position, tmp_cubic_int);
        position += sizeof(tmp_cubic_int);
    }
#endif
    EEPROM.put(position, register_mem.data.cfg);
    position += sizeof(register_mem.data.cfg);
    return position;
}

bool ConfigStorage::compare(size_t position)
{
    {
        uint32_t tmp_eeprom_cycle;
        EEPROM.get(position, tmp_eeprom_cycle);
        if (tmp_eeprom_cycle != eeprom_cycle) {
            return false;
        }
        position += sizeof(tmp_eeprom_cycle);
    }
    {
        uint16_t tmp_crc16;
        EEPROM.get(position, tmp_crc16);
        if (tmp_crc16 != crc16) {
            return false;
        }
        position += sizeof(tmp_crc16);
    }
    {
        int16_t tmp_level[DIMMER_CHANNELS];
        EEPROM.get(position, tmp_level);
        if (memcmp(tmp_level, level, sizeof(tmp_level))) {
            return false;
        }
        position += sizeof(tmp_level);
    }
#if DIMMER_CUBIC_INTERPOLATION
    {
        register_mem_cubic_int_t tmp_cubic_int[DIMMER_CHANNELS];
        EEPROM.get(position, tmp_cubic_int);
        if (memcmp(tmp_cubic_int,&register_mem.data.cubic_int, sizeof(tmp_cubic_int))) {
            return false;
        }
        position += sizeof(tmp_cubic_int);
    }
#endif
    {
        auto ptr = reinterpret_cast<const uint8_t *>(&register_mem.data.cfg);
        for(size_t i = 0; i < sizeof(register_mem.data.cfg); i++)  {
            auto data = EEPROM.read(position);
            if (*ptr++ != data) {
                return false;
            }
            position++;
        }
    }
    return true;
}

void ConfigStorage::copyLevels()
{
    memcpy(level, register_mem.data.level, sizeof(level));
}

uint16_t ConfigStorage::crc() const
{
    uint16_t crc = crc16_update(~0, reinterpret_cast<const uint8_t *>(&register_mem.data.cfg), sizeof(register_mem.data.cfg));
    crc = crc16_update(crc, reinterpret_cast<const uint8_t *>(level), sizeof(level));
#if DIMMER_CUBIC_INTERPOLATION
    crc = crc16_update(crc, reinterpret_cast<const uint8_t *>(register_mem.data.cubic_int), cubicIntSize());
#endif
    return crc;
}

void ConfigStorage::updateCrc()
{
    crc16 = crc();
}
