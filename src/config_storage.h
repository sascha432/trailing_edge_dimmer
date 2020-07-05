/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <ArduinoEEPROM.h>
#include "dimmer_protocol.h"
#include "dimmer.h"

class ConfigStorage {
public:

    class Settings {
    public:

        Settings() = default;

        void copyFrom();
        void copyTo();

        WearLevelData_t &getConfig();

    private:
        WearLevelData_t _cfg;
    };

    class Configuration {
    public:
        Configuration() = default;

        static void restoreFactoryDefaults();
    };

public:
    ConfigStorage();

    void restoreFactorySettings();
    // reads Configuration and Settings
    void read(ConfigStorage::Settings &settings);
    // writes settings
    void writeSettings();
    // write settings after kEEPROMWriteDelay milliseconds. a second call will not extend the delay
    void scheduleWriteSettings();
    // writes configuration
    void writeConfiguration();

    // if restore levels is enabled, set levels from _settings and call fade()
    void setLevelsFromSettings();
    // copy levels to _settings
    void copyLevelToSettings();

    // void printBasicInfo(const BaseArduinoEEPROM::BasicInfo_t &info);

   register_mem_cfg_t &cfg;

public:
   ArduinoEEPROM &getEEPROM() {
       return _eeprom;
   }

private:
    friend void loop();
    static constexpr unsigned long kEEPROMTimerDisabled = ~0;
    static constexpr uint16_t kEEPROMWriteDelay = DIMMER_EEPROM_WRITE_DELAY;
    volatile unsigned long _eepromWriteTimer;

private:
    void _eraseEEPROM();
    void _read(ConfigStorage::Settings &settings, bool restoreFactory = false);

    ArduinoEEPROM _eeprom;
};

extern ConfigStorage config;
