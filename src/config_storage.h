/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <ArduinoEEPROM.h>
#include "dimmer_protocol.h"

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
    // writes Settings
    void writeSettings();
    // writes Configuration
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
    void _eraseEEPROM();
    void _read(ConfigStorage::Settings &settings, bool restoreFactory = false);

   ArduinoEEPROM _eeprom;
};

extern ConfigStorage config;
