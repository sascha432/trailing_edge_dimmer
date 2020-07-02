/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "dimmer_protocol.h"

typedef struct __attribute__packed__ {
    register_mem_cfg_t cfg;
#if DIMMER_CUBIC_INTERPOLATION
    register_mem_cubic_int_t cubic_int[DIMMER_CHANNELS];
#endif
} StaticData_t;

typedef struct __attribute__packed__ {
    int16_t level[DIMMER_CHANNELS];
    register_mem_errors_t errors;
} WearLevelData_t;

#define ARDUINO_EEPROM_STATIC_DATA_NUM_COPIES               3
#define ARDUINO_EEPROM_WEAR_LEVEL_DATA_NUM_COPIES           1
#define ARDUINO_EEPROM_STATIC_DATA_SIZE                     sizeof(StaticData_t)
#define ARDUINO_EEPROM_WEAR_LEVEL_DATA_SIZE                 sizeof(WearLevelData_t)
#define ARDUINO_EEPROM_START_OFFSET                         0
#define ARDUINO_EEPROM_LENGTH                               1024
#define ARDUINO_EEPROM_WEAR_LEVEL_DATA_SHIFTING             0
#define ARDUINO_EEPROM_HAVE_BYTEARRAY_INTERFACE             0

template<class StaticDataType, class WearLevelDataType> class ArduinoEEPROMTpl;

using ArduinoEEPROM = ArduinoEEPROMTpl<StaticData_t, WearLevelData_t>;
