/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#ifndef __attribute__packed__
#define __attribute__packed__           __attribute__((packed))
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
    uint8_t frequency_low: 1;
    uint8_t frequency_high: 1;
    uint8_t leading_edge: 1;
    uint8_t ___reserved: 2;
} config_options_t;

typedef struct __attribute__packed__ {
    union {
        config_options_t bits;
        uint8_t options;
    };
    uint8_t max_temp;
    float fade_in_time;
    uint8_t temp_check_interval;
    uint8_t __empty[2];
    int8_t halfwave_adjust_ticks;           // correction for measured ticks
    uint16_t zero_crossing_delay_ticks;
    uint16_t minimum_on_time_ticks;
    uint16_t minimum_off_time_ticks;
    float internal_1_1v_ref;
    int8_t int_temp_offset;
    int8_t ntc_temp_offset;
    uint8_t report_metrics_max_interval;
    int16_t range_begin;
    int16_t range_end;
    uint16_t switch_on_minimum_ticks;       // if switch_on_minimum_ticks > minimum_on_time_ticks
    uint8_t switch_on_count;                // increase it for switch_on_count half cycles after switching on
} register_mem_cfg_t;

typedef struct __attribute__packed__ {
    uint8_t frequency_low;
    uint8_t frequency_high;
    uint8_t zc_misfire;
} register_mem_errors_t;

typedef struct __attribute__packed__ {
    int16_t from_level;
    int8_t channel;
    int16_t to_level;
    float time;
    register_mem_command_t cmd;
    uint16_t level[8];
    float temp;
    uint16_t vcc;
    register_mem_cfg_t cfg;
    register_mem_errors_t errors;
    uint8_t address;
} register_mem_t;

typedef union __attribute__packed__ {
    register_mem_t data;
    uint8_t raw[sizeof(register_mem_t)];
} register_mem_union_t;

typedef struct __attribute__packed__ {
    uint8_t temp_check_value;
    uint16_t vcc;
    float frequency;
    float ntc_temp;
    float internal_temp;
} dimmer_metrics_t;

typedef struct __attribute__packed__ {
    uint32_t write_cycle;
    uint16_t write_position;
    uint8_t bytes_written;      // might be 0 if the data has not been changed
} dimmer_eeprom_written_t;

typedef struct __attribute__packed__ {
    uint8_t channel;
    uint16_t level;
} dimmer_fading_complete_event_t;

typedef struct __attribute__packed__ {
    uint8_t channel_state;
} dimmer_channel_state_event_t;

static constexpr uint16_t dimmer_version_to_uint16(uint8_t major, uint8_t minor, uint8_t revision) {
    return (major << 10) | (minor << 5) | revision;
}

extern register_mem_union_t register_mem;
