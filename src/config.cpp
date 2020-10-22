/**
 * Author: sascha_lammers@gmx.de
 */

#include <EEPROM.h>
#include <crc16.h>
#include "config.h"


EEPROM_config_t config;
Config conf;

void Config::initRegisterMem()
{
    register_mem = {};
    register_mem.data.from_level = Dimmer::Level::invalid;
}

void Config::copyToRegisterMem(register_mem_cfg_t &config)
{
    config = register_mem.data.cfg;
}

void Config::copyFromRegisterMem(const register_mem_cfg_t &config)
{
    register_mem.data.cfg = config;
}

void Config::resetConfig()
{
    initRegisterMem();
    register_mem.data.cfg.max_temp = 75;
    register_mem.data.cfg.bits.restore_level = DIMMER_RESTORE_LEVEL;
    register_mem.data.cfg.bits.leading_edge = (DIMMER_TRAILING_EDGE == 0);
    register_mem.data.cfg.fade_in_time = 4.5f;
    register_mem.data.cfg.zero_crossing_delay_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_ZC_DELAY_US);
    register_mem.data.cfg.minimum_on_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_ON_TIME_US);
    register_mem.data.cfg.minimum_off_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_OFF_TIME_US);
#ifdef INTERNAL_TEMP_OFS
    register_mem.data.cfg.int_temp_offset = INTERNAL_TEMP_OFS;
#endif
#ifdef NTC_TEMP_OFS
    register_mem.data.cfg.ntc_temp_offset = NTC_TEMP_OFS;
#endif
    register_mem.data.cfg.range_begin = Dimmer::Level::min;
    register_mem.data.cfg.range_end = Dimmer::Level::max;
    register_mem.data.cfg.report_metrics_interval = 5;

    copyFromRegisterMem(_config.cfg);
}

void Config::initEEPROM()
{
    // initialize EEPROM and wear leveling
    // invalidates cycle number and crc only
    EEPROM_config_header_t header = { 0, ~0U };
    uint16_t pos = sizeof(EEPROM_config_t);
    while((pos + sizeof(EEPROM_config_t)) <= EEPROM.length()) {
        EEPROM.put(pos, header);
        pos += sizeof(EEPROM_config_t);
    }

    // create first valid configuration
    _eeprom_position = 0;
    _config = {};
    _config.eeprom_cycle = 1;
    resetConfig();
    _config.crc16 = crc16_update(&_config.cfg, sizeof(_config.cfg));
    EEPROM.put(0, _config);
    _D(5, debug_printf("init eeprom cycle=%lu pos=%u crc=%04x\n", (uint32_t)_config.eeprom_cycle, (unsigned)_eeprom_position, _config.crc16));

    Serial.println(F("+REM=EEPROMR,init"));
}

void Config::readConfig()
{
    uint16_t pos = 0;
    uint32_t max_cycle = 0;
    EEPROM_config_t temp_config;

    _eeprom_position = kInvalidPosition;

    // read entire eeprom and check which entries are valid
    // if the most recent configuration cannot be read, the previous one is used

    _D(5, debug_printf("reading eeprom "));
#if DEBUG
    char type;
    uint32_t start = micros();
#endif
    while((pos + sizeof(temp_config)) <= EEPROM.length()) {
        EEPROM.get(pos, temp_config);
        auto crc = crc16_update(&temp_config.cfg, sizeof(temp_config.cfg));
        if (crc == temp_config.crc16) {
            // valid configuration
            if (temp_config.eeprom_cycle >= max_cycle) {
                // if cycle is equal or greater max_cycle, the configuration is more recent
                // remember max_cycle, positition and copy data
                max_cycle = temp_config.eeprom_cycle;
                _eeprom_position = pos;
                _config = temp_config;
#if DEBUG
                type = 'N'; // new
#endif
            }
#if DEBUG
            else {
                type = 'O'; // old
            }
#endif
        }
#if DEBUG
        else {
            type = 'E'; // error
        }
        _D(5, Serial.printf_P(PSTR("%lu:%u<%c> "), temp_config.eeprom_cycle, pos, type));
#endif
        pos += sizeof(_config);
    }
    _D(5, Serial.printf_P(PSTR("max_cycle=%ld pos=%d time=%lu\n"), max_cycle, _eeprom_position, micros() - start));

    if (_eeprom_position == kInvalidPosition) { // no valid entries found
        initEEPROM();
        _D(5, debug_print_memory(&_config.cfg, sizeof(_config.cfg)));
        return;
    }

    copyToRegisterMem(_config.cfg);
    _D(5, debug_print_memory(&_config.cfg, sizeof(_config.cfg)));
    Serial.printf_P(PSTR("+REM=EEPROMR,c=%lu,p=%u,n=%lu,crc=%04x\n"), (uint32_t)max_cycle, _eeprom_position, get_eeprom_num_writes(max_cycle, _eeprom_position), _config.crc16);
}

void Config::writeConfig()
{
    int32_t lastWrite = millis() - _eeprom_write_timer;
    if (!dimmer_scheduled_calls.write_eeprom) { // no write scheduled
        _D(5, debug_printf("scheduling eeprom write cycle, last write %d seconds ago\n", (int)(lastWrite / 1000U)));
        _eeprom_write_timer = millis() + ((lastWrite > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
        dimmer_scheduled_calls.write_eeprom = true;
    }
    else {
        _D(5, debug_printf("eeprom write cycle already scheduled in %d seconds\n", (int)(lastWrite / -1000)));
    }
}

void Config::_writeConfig(bool force)
{
    EEPROM_config_t temp_config;
    dimmer_eeprom_written_t event = {};

    if (dimmer_scheduled_calls.eeprom_update_config) {
        event.config_updated = true;
        copyFromRegisterMem(_config.cfg);
    }

    memcpy(&_config.level, &register_mem.data.level, sizeof(_config.level));
    _config.crc16 = crc16_update(&_config.cfg, sizeof(_config.cfg));

    EEPROM.get(_eeprom_position, temp_config);

    _D(5, debug_printf("_write_config force=%u reg_mem=%u memcmp=%d\n", force, event.config_updated, memcmp(&_config, &temp_config, sizeof(_config))));

    if (force || memcmp(&_config, &temp_config, sizeof(_config))) {
        _D(5, debug_printf("old eeprom write cycle %lu, position %u, ", (uint32_t)_config.eeprom_cycle, _eeprom_position));
        _eeprom_position += sizeof(_config);
        if (_eeprom_position + sizeof(_config) >= EEPROM.length()) { // end reached, start from beginning and increase cycle counter
            _eeprom_position = 0;
            _config.eeprom_cycle++;
            _config.crc16 = crc16_update(&_config.cfg, sizeof(_config.cfg)); // recalculate CRC
        }
        _D(5, debug_printf("new cycle %lu, position %u\n", (uint32_t)_config.eeprom_cycle, _eeprom_position));
        EEPROM.put(_eeprom_position, _config);
        event.bytes_written = sizeof(_config);
    }
    else {
        _D(5, debug_printf("configuration didn't change, skipping write cycle\n"));
        event.bytes_written = 0;
    }
    _eeprom_write_timer = millis();

    dimmer_scheduled_calls.write_eeprom = false;
    dimmer_scheduled_calls.eeprom_update_config = false;

    event.write_cycle = _config.eeprom_cycle;
    event.write_position = _eeprom_position;

    _D(5, debug_printf("eeprom written event: cycle %lu, pos %u, written %u\n", (uint32_t)event.write_cycle, event.write_position, event.bytes_written));
    Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
    Wire.write(DIMMER_EEPROM_WRITTEN);
    Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
    Wire.endTransmission();

    Serial.printf_P(PSTR("+REM=EEPROMW,c=%lu,p=%u,n=%lu,w=%u,f=%u,crc=%04x\n"),
        (uint32_t)event.write_cycle,
        _eeprom_position,
        get_eeprom_num_writes(event.write_cycle, _eeprom_position),
        event.bytes_written,
        event.flags,
        _config.crc16
    );
}

