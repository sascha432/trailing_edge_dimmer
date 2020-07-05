// AUTO GENERATED FILE - DO NOT MODIFY
/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#ifndef DIMMER_I2C_ADDRESS
#define DIMMER_I2C_ADDRESS                              0x17 //  23
#endif

#ifndef DIMMER_I2C_MASTER_ADDRESS
#define DIMMER_I2C_MASTER_ADDRESS                       0x18 //  24
#endif

#include <stdint.h>

#ifndef __attribute__packed__
#define __attribute__packed__                           __attribute__((packed))
#endif

#if _MSC_VER
#pragma pack(push, 1)
#endif

typedef struct __attribute__packed__ {
    int8_t channel;
    int16_t level;
} dimmer_fading_completed_event_t;

typedef struct __attribute__packed__ {
    int16_t start_level;
    uint8_t level_count;
    uint8_t step_size;
} dimmer_get_cubic_int_header_t;

typedef struct __attribute__packed__ {
    uint8_t command;
    int8_t read_length;
} register_mem_command_t;

typedef struct __attribute__packed__ {
    uint8_t x;
    uint8_t y;
} register_mem_cubic_int_data_point_t;

typedef union __attribute__packed__ {
    register_mem_cubic_int_data_point_t points[8];
    int16_t levels[8];
} register_mem_cubic_int_t;

typedef struct __attribute__packed__ {
    uint8_t factory_settings: 1;
    uint8_t cubic_interpolation: 1;
    uint8_t report_metrics: 1;
    uint8_t restore_level: 1;
} register_mem_options_bits_t;

typedef struct __attribute__packed__ {
    union {
        uint8_t options;
        register_mem_options_bits_t bits;
    };
    uint8_t max_temperature;
    float fade_time;
    uint8_t temp_check_interval;
    uint8_t metrics_report_interval;
    int16_t zc_offset_ticks;
    uint16_t min_on_ticks;
    uint16_t min_off_ticks;
    float vref11;
    int8_t temperature_offset;
    int8_t temperature2_offset;
} register_mem_cfg_t;

typedef struct __attribute__packed__ {
    float frequency;
    float temperature;
    float temperature2;
    uint16_t vcc;
} register_mem_metrics_t;

typedef register_mem_metrics_t dimmer_metrics_t;

typedef struct __attribute__packed__ {
    uint8_t current_temperature;
    uint8_t max_temperature;
} dimmer_temperature_alert_t;

typedef struct __attribute__packed__ {
    int16_t from_level;
    float time;
    int8_t channel;
    int16_t to_level;
} register_mem_channel_t;

typedef struct __attribute__packed__ {
    uint8_t zc_misfire;
    uint8_t temperature;
    uint8_t i2c_errors;
} register_mem_errors_t;

typedef struct __attribute__packed__ {
    uint8_t has_cubic_interpolation: 1;
    uint8_t has_temperature: 1;
    uint8_t has_temperature2: 1;
    uint8_t has_vcc: 1;
    uint8_t has_fading_completed_event: 1;
} register_mem_info_options_bits_t;

typedef struct __attribute__packed__ {
    uint16_t version;
    int16_t num_levels;
    int8_t num_channels;
    union {
        uint8_t options;
        register_mem_info_options_bits_t bits;
    };
} register_mem_info_t;

typedef struct __attribute__packed__ {
    int16_t level[8];
} register_mem_channels_t;

typedef struct __attribute__packed__ {
    register_mem_cubic_int_t cubic_int;
    register_mem_metrics_t metrics;
    register_mem_channel_t channel;
    register_mem_command_t cmd;
    register_mem_cfg_t cfg;
    register_mem_channels_t channels;
    register_mem_errors_t errors;
    register_mem_info_t info;
    uint8_t address;
} register_mem_t;

typedef union __attribute__packed__ {
    register_mem_t data;
    uint8_t raw[87];
} register_mem_union_t;


#define DIMMER_REGISTER_MEM_START_OFFSET                0x00 //  0
#define DIMMER_REGISTER_CUBIC_INT_DATA_POINTS_X(N)      (0x00 + ((N) * 2)) // 0:8 uint8_t
#define DIMMER_REGISTER_CUBIC_INT_DATA_POINTS_OFFSET    0x00 //  0  uint8_t
#define DIMMER_REGISTER_CUBIC_INT_DATA_POINTS_Y(N)      (0x01 + ((N) * 2)) // 1:8 uint8_t
#define DIMMER_REGISTER_CUBIC_INT_LEVELS(N)             (0x00 + ((N) * 2)) // 0:8 int16_t
#define DIMMER_REGISTER_METRICS_FREQUENCY               0x10 //  16 float
#define DIMMER_REGISTER_METRICS_TEMPERATURE             0x14 //  20 float
#define DIMMER_REGISTER_METRICS_TEMPERATURE2            0x18 //  24 float
#define DIMMER_REGISTER_METRICS_VCC                     0x1c //  28 uint16_t
#define DIMMER_REGISTER_CHANNEL_FROM_LEVEL              0x1e //  30 int16_t
#define DIMMER_REGISTER_CHANNEL_TIME                    0x20 //  32 float
#define DIMMER_REGISTER_CHANNEL_CHANNEL                 0x24 //  36 int8_t
#define DIMMER_REGISTER_CHANNEL_TO_LEVEL                0x25 //  37 int16_t
#define DIMMER_REGISTER_CMD_COMMAND                     0x27 //  39 uint8_t
#define DIMMER_REGISTER_CMD_READ_LENGTH                 0x28 //  40 int8_t
#define DIMMER_REGISTER_OPTIONS                         0x29 //  41 uint8_t
#define DIMMER_REGISTER_CFG_MAX_TEMPERATURE             0x2a //  42 uint8_t
#define DIMMER_REGISTER_CFG_FADE_TIME                   0x2b //  43 float
#define DIMMER_REGISTER_CFG_TEMP_CHECK_INTERVAL         0x2f //  47 uint8_t
#define DIMMER_REGISTER_CFG_METRICS_REPORT_INTERVAL     0x30 //  48 uint8_t
#define DIMMER_REGISTER_CFG_ZC_OFFSET_TICKS             0x31 //  49 int16_t
#define DIMMER_REGISTER_CFG_MIN_ON_TICKS                0x33 //  51 uint16_t
#define DIMMER_REGISTER_CFG_MIN_OFF_TICKS               0x35 //  53 uint16_t
#define DIMMER_REGISTER_CFG_VREF11                      0x37 //  55 float
#define DIMMER_REGISTER_CFG_TEMPERATURE_OFFSET          0x3b //  59 int8_t
#define DIMMER_REGISTER_CFG_TEMPERATURE2_OFFSET         0x3c //  60 int8_t
#define DIMMER_REGISTER_CHANNELS_LEVEL(N)               (0x3d + ((N) * 2)) // 61:8 int16_t
#define DIMMER_REGISTER_ERRORS_ZC_MISFIRE               0x4d //  77 uint8_t
#define DIMMER_REGISTER_ERRORS_TEMPERATURE              0x4e //  78 uint8_t
#define DIMMER_REGISTER_ERRORS_I2C_ERRORS               0x4f //  79 uint8_t
#define DIMMER_REGISTER_INFO_VERSION                    0x50 //  80 uint16_t
#define DIMMER_REGISTER_INFO_NUM_LEVELS                 0x52 //  82 int16_t
#define DIMMER_REGISTER_INFO_NUM_CHANNELS               0x54 //  84 int8_t
#define DIMMER_REGISTER_INFO_OPTIONS                    0x55 //  85 uint8_t
#define DIMMER_REGISTER_ADDRESS                         0x56 //  86 uint8_t
#define DIMMER_REGISTER_MEM_SIZE                        0x57 //  87
#define DIMMER_REGISTER_COMMAND                         DIMMER_REGISTER_CMD_COMMAND

#define DIMMER_OPTIONS_FACTORY_SETTINGS                 0x01 // 0b00000001
#define DIMMER_OPTIONS_CUBIC_INTERPOLATION              0x02 // 0b00000010
#define DIMMER_OPTIONS_REPORT_METRICS                   0x04 // 0b00000100
#define DIMMER_OPTIONS_RESTORE_LEVEL                    0x08 // 0b00001000

#define DIMMER_OPTIONS_INFO_HAS_CUBIC_INTERPOLATION     0x01 // 0b00000001
#define DIMMER_OPTIONS_INFO_HAS_TEMPERATURE             0x02 // 0b00000010
#define DIMMER_OPTIONS_INFO_HAS_TEMPERATURE2            0x04 // 0b00000100
#define DIMMER_OPTIONS_INFO_HAS_VCC                     0x08 // 0b00001000
#define DIMMER_OPTIONS_INFO_HAS_FADING_COMPLETED_EVENT  0x10 // 0b00010000

#define DIMMER_COMMAND_SET_LEVEL                        0x10 //  16
#define DIMMER_COMMAND_FADE                             0x11 //  17
#define DIMMER_COMMAND_READ_CHANNELS                    0x12 //  18
#define DIMMER_COMMAND_READ_TEMPERATURE                 0x20 //  32
#define DIMMER_COMMAND_READ_TEMPERATURE2                0x21 //  33
#define DIMMER_COMMAND_READ_VCC                         0x22 //  34
#define DIMMER_COMMAND_READ_FREQUENCY                   0x23 //  35
#define DIMMER_COMMAND_READ_METRICS                     0x24 //  36
#define DIMMER_COMMAND_WRITE_SETTINGS                   0x50 //  80
#define DIMMER_COMMAND_RESTORE_FACTORY                  0x51 //  81
#define DIMMER_COMMAND_PRINT_INFO                       0x53 //  83
#define DIMMER_COMMAND_FORCE_TEMP_CHECK                 0x54 //  84
#define DIMMER_COMMAND_PRINT_METRICS                    0x55 //  85
#define DIMMER_COMMAND_PRINT_CUBIC_INT                  0x60 //  96
#define DIMMER_COMMAND_GET_CUBIC_INT                    0x61 //  97
#define DIMMER_COMMAND_READ_CUBIC_INT                   0x62 //  98
#define DIMMER_COMMAND_WRITE_CUBIC_INT                  0x63 //  99
#define DIMMER_COMMAND_CUBIC_INT_TEST_PERF              0x64 //  100
#define DIMMER_COMMAND_SET_ZC_OFS                       0x92 //  146
#define DIMMER_COMMAND_WRITE_EEPROM                     0x93 //  147

#define DIMMER_MASTER_COMMAND_METRICS_REPORT            0xf0 //  240
#define DIMMER_MASTER_COMMAND_TEMPERATURE_ALERT         0xf1 //  241
#define DIMMER_MASTER_COMMAND_FADING_COMPLETE           0xf2 //  242

#define DIMMER_CUBIC_INT_DATA_POINTS                    0x08 //  8

#if _MSC_VER
#pragma pack(pop)
#endif

