/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#ifndef __attribute__packed__
#define __attribute__packed__           __attribute__((packed))
#endif

#ifndef DIMMER_CUBIC_INT_TABLE_SIZE
#define DIMMER_CUBIC_INT_TABLE_SIZE                             8
#endif

typedef struct __attribute__packed__ {
    uint8_t command;
    int8_t read_length;
    int8_t status;
} register_mem_command_t;

typedef struct {
    uint8_t restore_level: 1;
    uint8_t report_metrics: 1;
    uint8_t temperature_alert: 1;
    uint8_t cubic_interpolation: 1;
    uint8_t factory_settings: 1;
    uint8_t ____reserved: 3;
} config_options_t;

typedef struct __attribute__packed__ {
    union {
        uint8_t points[DIMMER_CUBIC_INT_TABLE_SIZE];
        int16_t levels[DIMMER_CUBIC_INT_TABLE_SIZE / 2];
    };
} register_mem_cubic_int_t;

typedef struct __attribute__packed__ {
    union {
        config_options_t bits;
        uint8_t options;
    };
    uint8_t max_temp;
    float fade_in_time;
    uint8_t temp_check_interval;
    int16_t zc_offset_ticks;
    uint16_t min_on_ticks;
    uint16_t max_on_ticks;
    float internal_1_1v_ref;
    int8_t int_temp_offset;
    int8_t ntc_temp_offset;
    uint8_t report_metrics_max_interval;    // multiple of "temp_check_interval"
} register_mem_cfg_t;

typedef struct __attribute__packed__ {
    uint8_t zc_misfire;
    uint8_t temperature;
} register_mem_errors_t;

typedef struct __attribute__packed__ {
    uint16_t version;
    uint16_t num_levels;
    uint8_t num_channels;
} register_mem_info_t;

typedef struct __attribute__packed__ {
    float frequency;
    float temperature;
    float temperature2;
    uint16_t vcc;
} register_mem_metrics_t;

#ifndef max
#define max(a,b)                                            (((a) > (b)) ? (a) : (b))
#endif

 typedef struct __attribute__packed__ {
    int16_t level[8];
} register_mem_channels_t;

typedef struct __attribute__packed__ {
    int16_t from_level;
    int8_t channel;
    int16_t to_level;
    float time;
} register_mem_channel_t;

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

static_assert((sizeof(register_mem_t) + 1) < SERIALTWOWIRE_MAX_INPUT_LENGTH, "Increase SERIALTWOWIRE_MAX_INPUT_LENGTH");

typedef char _adjust_SERIALTWOWIRE_MAX_INPUT_LENGTH_if_this_fails[(sizeof(register_mem_t) + 1) >= SERIALTWOWIRE_MAX_INPUT_LENGTH ? -1 : 0];

typedef union __attribute__packed__ {
    register_mem_t data;
    uint8_t raw[sizeof(register_mem_t)];
} register_mem_union_t;

typedef struct __attribute__packed__ {
    uint8_t trigger_temp;
    uint8_t max_temp;
} dimmer_temperature_alert;

typedef register_mem_metrics_t dimmer_metrics_t;

typedef struct __attribute__packed__ {
    int16_t start_level;
    uint8_t level_count;
    uint8_t step_size;
} dimmer_get_cubic_int_header_t;

