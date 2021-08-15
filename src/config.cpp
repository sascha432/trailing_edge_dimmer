/**
 * Author: sascha_lammers@gmx.de
 */

#include <EEPROM.h>
#include <crc16.h>
#include <util/atomic.h>
#include <avr/boot.h>
#include "config.h"
#include "sensor.h"

// EEPROM_config_t config;
Config conf;

void Config::initRegisterMem() const
{
    register_mem = {};
    register_mem.data.from_level = Dimmer::Level::invalid;
}

void Config::copyToRegisterMem(const register_mem_cfg_t &config) const
{
    register_mem.data.cfg = config;
}

void Config::copyFromRegisterMem(register_mem_cfg_t &config)
{
    config = register_mem.data.cfg;
}

#if DIMMER_CUBIC_INTERPOLATION

void Config::copyToInterpolation() const
{
    cubicInterpolation.copyFromConfig(_config.cubic_int);
}

void Config::copyFromInterpolation()
{
    cubicInterpolation.copyToConfig(_config.cubic_int);
}

#endif

void Config::resetConfig()
{
    initRegisterMem();
    register_mem.data.cfg.max_temp = 75;
    register_mem.data.cfg.bits.restore_level = DIMMER_RESTORE_LEVEL;
    register_mem.data.cfg.bits.leading_edge = (DIMMER_TRAILING_EDGE == 0);
    register_mem.data.cfg.fade_in_time = 4.5;
    register_mem.data.cfg.zero_crossing_delay_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_ZC_DELAY_US);
    register_mem.data.cfg.minimum_on_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_ON_TIME_US);
    register_mem.data.cfg.minimum_off_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_OFF_TIME_US);

#if __AVR_ATmega328P__ && MCU_IS_ATMEGA328PB == 0 && DIMMER_AVR_TEMP_TS_GAIN == 0
    register_mem.data.cfg.internal_temp_calibration = atmega328p_read_ts_values();
#else
    register_mem.data.cfg.internal_temp_calibration.ts_offset = DIMMER_AVR_TEMP_TS_OFFSET;
    register_mem.data.cfg.internal_temp_calibration.ts_gain = DIMMER_AVR_TEMP_TS_GAIN;
#endif

#ifdef NTC_TEMP_OFS
    register_mem.data.cfg.ntc_temp_cal_offset = static_cast<float>(NTC_TEMP_OFS);
#endif
    register_mem.data.cfg.report_metrics_interval = DIMMER_REPORT_METRICS_INTERVAL;
    register_mem.data.metrics.ntc_temp = NAN;
    register_mem.data.metrics.int_temp = Dimmer::kInvalidTemperature;
    register_mem.data.metrics.frequency = NAN;

    copyFromRegisterMem(_config.cfg);
    copyFromInterpolation();
}

void Config::initEEPROM()
{
    // initialize EEPROM and wear leveling
    // invalidates cycle number and crc only
    EEPROM_config_header_t header(~0);
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
    EEPROMConfig::updateCrc16(_config);
    EEPROM.put(0, _config);
    _D(5, debug_printf("init eeprom cycle=%lu pos=%u crc=%04x copies=%u\n", (uint32_t)_config.eeprom_cycle, _eeprom_position, _config.crc16, kEEPROMMaxCopies));

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        queues.scheduled_calls.write_eeprom = false;
        queues.scheduled_calls.eeprom_update_config = false;
    }

    Serial.println(F("+REM=EEPROMR,init"));
}

void Config::restoreFactory()
{
    _D(5, debug_printf("restore factory settings\n"));
    resetConfig();
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        queues.scheduled_calls.eeprom_update_config = true;
    }
    _writeConfig(true);
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
        if (EEPROMConfig::crc16(temp_config) == temp_config.crc16) {
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
    _D(5, Serial.printf_P(PSTR("mxcy=%lu p=%d t=%.3fms\n"), max_cycle, _eeprom_position, (micros() - start) / 1000.0));

    if (_eeprom_position == kInvalidPosition) { // no valid entries found
        initEEPROM();
        _D(5, debug_print_memory(&_config.cfg, sizeof(_config.cfg)));
        return;
    }

    if (_config.cfg.max_temp < 55) {
        _config.cfg.max_temp = 55;
    }
    else if (_config.cfg.max_temp > 125) {
        _config.cfg.max_temp = 125;
    }

    copyToRegisterMem(_config.cfg);
    _D(5, debug_print_memory(&_config.cfg, sizeof(_config.cfg)));
    // if this does not compile check RREADME.md "Patching the Arduino libary"
    Serial.printf_P(PSTR("+REM=EEPROMR,c=%lu,p=%u,n=%lu,crc=%04x\n"), (uint32_t)max_cycle, _eeprom_position, get_eeprom_num_writes(max_cycle, _eeprom_position), _config.crc16);
}

void Config::writeConfig()
{
    int32_t lastWrite = millis() - _eeprom_write_timer;
    if (!queues.scheduled_calls.write_eeprom) { // no write scheduled
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            queues.scheduled_calls.write_eeprom = true;
        };
        _D(5, debug_printf("scheduling eeprom write cycle, last write %d seconds ago\n", (int)(lastWrite / 1000U)));
        _eeprom_write_timer = millis() + ((lastWrite > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
    }
    else {
        _D(5, debug_printf("eeprom write cycle already scheduled in %d seconds\n", (int)(lastWrite / -1000)));
    }
}

void Config::_writeConfig(bool force)
{
    EEPROM_config_t temp_config;
    dimmer_eeprom_written_t event = {};

    if (queues.scheduled_calls.eeprom_update_config) {
        event.config_updated = true;
        copyFromRegisterMem(_config.cfg);
        copyFromInterpolation();
    }

    _config.channels = register_mem.data.channels;
    EEPROMConfig::updateCrc16(_config);

    EEPROM.get(_eeprom_position, temp_config);

    _D(5, debug_printf("_write_config force=%u modified=%d\n", force, event.config_updated, _config != temp_config));

    if (force || _config != temp_config) {
#if DEBUG
        auto __cycle = _config.eeprom_cycle;
        auto __position = _eeprom_position;
#endif
        _eeprom_position += sizeof(_config);
        if (_eeprom_position + sizeof(_config) >= EEPROM.length()) { // end reached, start from beginning and increase cycle counter
            _eeprom_position = 0;
            _config.eeprom_cycle++;
            EEPROMConfig::updateCrc16(_config);
        }
        _D(5, debug_printf("old eeprom write cycle %lu:%u, new cycle %lu:%u\n", __cycle, __position, _config.eeprom_cycle, _eeprom_position));
        EEPROM.put(_eeprom_position, _config);
        event.bytes_written = sizeof(_config);
    }
    else {
        _D(5, debug_printf("configuration didn't change, skipping write cycle\n"));
        event.bytes_written = 0;
    }
    _eeprom_write_timer = millis();

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        queues.scheduled_calls.write_eeprom = false;
        queues.scheduled_calls.eeprom_update_config = false;
    }

    event.write_cycle = _config.eeprom_cycle;
    event.write_position = _eeprom_position;

    _D(5, debug_printf("eeprom written event: cycle %lu:%u, written %u\n", event.write_cycle, event.write_position, event.bytes_written));
    Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
    Wire.write(DIMMER_EVENT_EEPROM_WRITTEN);
    Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
    Wire.endTransmission();

    Serial.printf_P(PSTR("+REM=EEPROMW,c=%lu,p=%u,n=%lu,w=%u,f=%u,crc=%04x,cfg=%u\n"),
        event.write_cycle,
        _eeprom_position,
        conf.getEEPROMWriteCount(),
        event.bytes_written,
        event.flags,
        _config.crc16,
        event.config_updated
    );
}

