/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#ifndef DIMMER_I2C_ADDRESS
#define DIMMER_I2C_ADDRESS                  0x17
#endif

#define DIMMER_REGISTER_START_ADDR          0x80
#define DIMMER_REGISTER_FROM_LEVEL          (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, from_level))
#define DIMMER_REGISTER_CHANNEL             (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, channel))
#define DIMMER_REGISTER_TO_LEVEL            (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, to_level))
#define DIMMER_REGISTER_TIME                (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, time))
#define DIMMER_REGISTER_COMMAND             (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cmd) + offsetof(register_mem_command_t, command))
#define DIMMER_REGISTER_READ_LENGTH         (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cmd) + offsetof(register_mem_command_t, read_length))
#define DIMMER_REGISTER_COMMAND_STATUS      (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cmd) + offsetof(register_mem_command_t, status))
#define DIMMER_REGISTER_CHANNELS_START      (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, level))
#define DIMMER_REGISTER_CH0_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 0)
#define DIMMER_REGISTER_CH1_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 1)
#define DIMMER_REGISTER_CH2_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 2)
#define DIMMER_REGISTER_CH3_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 3)
#define DIMMER_REGISTER_CH4_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 4)
#define DIMMER_REGISTER_CH5_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 5)
#define DIMMER_REGISTER_CH6_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 6)
#define DIMMER_REGISTER_CH7_LEVEL           (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level[0]) * 7)
#define DIMMER_REGISTER_CHANNELS_END        (DIMMER_REGISTER_CHANNELS_START + sizeof(register_mem_t().level))
#define DIMMER_REGISTER_TEMP                (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, temp))
#define DIMMER_REGISTER_VCC                 (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, vcc))
#define DIMMER_REGISTER_OPTIONS             (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, options))
#define DIMMER_REGISTER_MAX_TEMP            (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, max_temp))
#define DIMMER_REGISTER_FADE_IN_TIME        (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, fade_in_time))
#define DIMMER_REGISTER_TEMP_CHECK_INT      (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, temp_check_interval))
#define DIMMER_REGISTER_ZC_DELAY_TICKS      (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, zero_crossing_delay_ticks))
#define DIMMER_REGISTER_MIN_ON_TIME_TICKS   (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, minimum_on_time_ticks))
#define DIMMER_REGISTER_MIN_OFF_TIME_TICKS  (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, minimum_off_time_ticks))
#define DIMMER_REGISTER_INT_1_1V_REF        (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, internal_1_1v_ref))
#define DIMMER_REGISTER_INT_TEMP_OFS        (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, int_temp_offset))
#define DIMMER_REGISTER_METRICS_INT         (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, report_metrics_max_interval))
#define DIMMER_REGISTER_VERSION             0xb9
#define DIMMER_REGISTER_RANGE_BEGIN         (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, range_begin))
#define DIMMER_REGISTER_RANGE_END           (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, range_end))
#define DIMMER_REGISTER_SWITCH_ON_MIN_TIME  (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, switch_on_minimum_ticks))
#define DIMMER_REGISTER_SWITCH_ON_COUNT     (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, cfg) + offsetof(register_mem_cfg_t, switch_on_count))
#define DIMMER_REGISTER_ADDRESS             (DIMMER_REGISTER_START_ADDR + offsetof(register_mem_t, address))
#define DIMMER_REGISTER_END_ADDR            (DIMMER_REGISTER_START_ADDR + sizeof(register_mem_t))

// first byte in master mode indicates the data that was sent
#define DIMMER_METRICS_REPORT               0xf0
#define DIMMER_TEMPERATURE_ALERT            0xf1
#define DIMMER_FADING_COMPLETE              0xf2
#define DIMMER_EEPROM_WRITTEN               0xf3
#define DIMMER_FREQUENCY_WARNING            0xf4
#define DIMMER_CHANNEL_ON_OFF               0xf5

// DIMMER_REGISTER_COMMAND
#define DIMMER_COMMAND_SET_LEVEL            0x10
#define DIMMER_COMMAND_FADE                 0x11
#define DIMMER_COMMAND_READ_CHANNELS        0x12
#define DIMMER_COMMAND_READ_NTC             0x20
#define DIMMER_COMMAND_READ_INT_TEMP        0x21
#define DIMMER_COMMAND_READ_VCC             0x22
#define DIMMER_COMMAND_READ_AC_FREQUENCY    0x23
#define DIMMER_COMMAND_WRITE_EEPROM         0x50
#define DIMMER_COMMAND_RESTORE_FS           0x51
#define DIMMER_COMMAND_GET_TIMER_TICKS      0x52
#define DIMMER_COMMAND_PRINT_INFO           0x53
#define DIMMER_COMMAND_FORCE_TEMP_CHECK     0x54
#define DIMMER_COMMAND_PRINT_METRICS        0x55
#define DIMMER_COMMAND_SET_MODE             0x56
#define DIMMER_COMMAND_ZC_TIMINGS_OUTPUT    0x60
#define DIMMER_COMMAND_PRINT_CONFIG         0x91
#define DIMMER_COMMAND_WRITE_CFG_NOW        0x92
#define DIMMER_COMMAND_WRITE_EEPROM_NOW     0x93
#if DEBUG ||1
#define DIMMER_COMMAND_DUMP_CHANNELS        0xed
#define DIMMER_COMMAND_DUMP_MEM             0xee
#endif

// DIMMER_REGISTER_COMMAND_STATUS
#define DIMMER_COMMAND_STATUS_OK            0
#define DIMMER_COMMAND_STATUS_ERROR         -1

// DIMMER_REGISTER_OPTIONS
#define DIMMER_OPTIONS_RESTORE_LEVEL        0x01
#define DIMMER_OPTIONS_REPORT_TEMP          0x02
#define DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED 0x04

static_assert(DIMMER_REGISTER_VERSION == 0xb9, "Invalid offset");
