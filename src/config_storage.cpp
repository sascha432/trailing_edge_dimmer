/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"
#include "dimmer.h"
#include <ArduinoEEPROM.h>
#if DIMMER_CUBIC_INTERPOLATION
#include "cubic_interpolation.h"
#endif

ConfigStorage config;

void ConfigStorage::Configuration::restoreFactoryDefaults()
{
    register_mem.data.cfg = {};
    register_mem.data.cfg.max_temperature = DIMMER_MAX_TEMP;
    register_mem.data.cfg.bits.factory_settings = true;
    register_mem.data.cfg.bits.restore_level = true;
    register_mem.data.cfg.bits.report_metrics = true;
#if DIMMER_CUBIC_INTERPOLATION
    register_mem.data.cfg.bits.cubic_interpolation = true;
    cubicInterpolation.clearTable();
#endif
    register_mem.data.cfg.fade_time = 7.5;
    register_mem.data.cfg.metrics_report_interval = 10;
    register_mem.data.cfg.zc_offset_ticks = DIMMER_T1_US_TO_TICKS(DIMMER_ZC_DELAY_US);
    register_mem.data.cfg.min_on_ticks = DIMMER_T1_US_TO_TICKS(DIMMER_MIN_ON_TIME_US);
    register_mem.data.cfg.min_off_ticks = DIMMER_T1_US_TO_TICKS(DIMMER_MIN_OFF_TIME_US);
    register_mem.data.cfg.vref11 = DIMMER_ATMEGA_VREF11;
    register_mem.data.cfg.temperature_offset = DIMMER_TEMPERATURE_OFFSET * DIMMER_TEMP_OFFSET_DIVIDER;
    register_mem.data.cfg.temperature2_offset = DIMMER_TEMPERATURE2_OFFSET * DIMMER_TEMP_OFFSET_DIVIDER;
}

void ConfigStorage::Settings::copyFrom()
{
    if (register_mem.data.cfg.bits.restore_level) {
        FOR_CHANNELS(i) {
            dimmer.setFade(i, DIMMER_FADE_FROM_CURRENT_LEVEL, _cfg.level[i], register_mem.data.cfg.fade_time);
        }
    }
    register_mem.data.errors = _cfg.errors;
}

void ConfigStorage::Settings::copyTo()
{
    dimmer.copyLevels(_cfg);
    _cfg.errors = register_mem.data.errors;
}

WearLevelData_t &ConfigStorage::Settings::getConfig()
{
    return _cfg;
}


ConfigStorage::ConfigStorage() : cfg(register_mem.data.cfg), _eepromWriteTimer(kEEPROMTimerDisabled)
{
}

void ConfigStorage::_eraseEEPROM()
{
    Serial.println(F("+REM=Intitializing EEPROM"));
    _eeprom.eraseAndInitialize(ArduinoEEPROM::DataTypeEnum::ALL);
}

void ConfigStorage::restoreFactorySettings()
{
    ConfigStorage::Settings settings;
    _read(settings, true);
}

void ConfigStorage::read(ConfigStorage::Settings &settings)
{
    _read(settings);
}

void ConfigStorage::_read(ConfigStorage::Settings &settings, bool restoreFactory)
{
#if DIMMER_CUBIC_INTERPOLATION
    StaticData_t staticData;
#else
    StaticData_t &staticData = *reinterpret_cast<StaticData_t *>(&register_mem.data.cfg);
#endif

    // read configuration
    if (restoreFactory == false && _eeprom.readStaticData(staticData)) {

#if DIMMER_CUBIC_INTERPOLATION
        memcpy(&register_mem.data.cfg, &staticData.cfg, sizeof(register_mem.data.cfg));
        FOR_CHANNELS(i) {
            cubicInterpolation.copyFromConfig(staticData.cubic_int[i], i);
        }
#endif

        // read settings
        if (!_eeprom.readWearLevelData(settings.getConfig())) {
            // invalid settings, clear wear leveling area
            settings = Settings();
            _eeprom.eraseAndInitialize(ArduinoEEPROM::DataTypeEnum::WEAR_LEVEL_DATA);
            _eeprom.writeWearLevelData(settings.getConfig());
        }
    }
    else {
        // invalid configuration, initialize entire EEPROM
        _eraseEEPROM();
        Configuration::restoreFactoryDefaults();
#if DIMMER_CUBIC_INTERPOLATION
        memcpy(&staticData.cfg, &register_mem.data.cfg, sizeof(register_mem.data.cfg));
        memset(staticData.cubic_int, 0, sizeof(staticData.cubic_int));
#endif

        settings = Settings();
        _eeprom.writeStaticData(staticData);
        _eeprom.writeWearLevelData(settings.getConfig());

    }
}

void ConfigStorage::writeSettings()
{
    ConfigStorage::Settings settings;
    settings.copyTo();
    _eeprom.writeWearLevelData(settings.getConfig());
}

void ConfigStorage::scheduleWriteSettings()
{
    if (_eepromWriteTimer == kEEPROMTimerDisabled) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            _eepromWriteTimer = millis() + kEEPROMWriteDelay;
        }
    }
}

void ConfigStorage::writeConfiguration()
{
#if DIMMER_CUBIC_INTERPOLATION
    StaticData_t staticData;
    memcpy(&staticData.cfg, &register_mem.data.cfg, sizeof(register_mem.data.cfg));
    FOR_CHANNELS(i) {
        cubicInterpolation.copyToConfig(staticData.cubic_int[i], i);
    }
#else
    StaticData_t &staticData = *reinterpret_cast<StaticData_t *>(&register_mem.data.cfg);
#endif

    register_mem.data.cfg.bits.factory_settings = false;
    _eeprom.writeStaticData(staticData);
}
