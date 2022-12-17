// translates defines into constexpr to read the values with intellisense
#include <stddef.h>
#include <stdint.h>
#include "dimmer_def.h"
#include "dimmer_protocol.h"
#include "dimmer_reg_mem.h"
static constexpr size_t __DIMMER_MAX_CHANNELS = DIMMER_MAX_CHANNELS;
static constexpr size_t __DIMMER_REGISTER_START_ADDR = DIMMER_REGISTER_START_ADDR;
static constexpr size_t __DIMMER_REGISTER_FROM_LEVEL = DIMMER_REGISTER_FROM_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CHANNEL = DIMMER_REGISTER_CHANNEL;
static constexpr size_t __DIMMER_REGISTER_TO_LEVEL = DIMMER_REGISTER_TO_LEVEL;
static constexpr size_t __DIMMER_REGISTER_TIME = DIMMER_REGISTER_TIME;
static constexpr size_t __DIMMER_REGISTER_COMMAND = DIMMER_REGISTER_COMMAND;
static constexpr size_t __DIMMER_REGISTER_READ_LENGTH = DIMMER_REGISTER_READ_LENGTH;
static constexpr size_t __DIMMER_REGISTER_COMMAND_STATUS = DIMMER_REGISTER_COMMAND_STATUS;
static constexpr size_t __DIMMER_REGISTER_CHANNELS_START = DIMMER_REGISTER_CHANNELS_START;
static constexpr size_t __DIMMER_REGISTER_CH0_LEVEL = DIMMER_REGISTER_CH0_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CH1_LEVEL = DIMMER_REGISTER_CH1_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CH2_LEVEL = DIMMER_REGISTER_CH2_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CH3_LEVEL = DIMMER_REGISTER_CH3_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CH4_LEVEL = DIMMER_REGISTER_CH4_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CH5_LEVEL = DIMMER_REGISTER_CH5_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CH6_LEVEL = DIMMER_REGISTER_CH6_LEVEL;
static constexpr size_t __DIMMER_REGISTER_CH7_LEVEL = DIMMER_REGISTER_CH7_LEVEL;
#if DIMMER_MAX_CHANNELS > 8
    static constexpr size_t __DIMMER_REGISTER_CH8_LEVEL = DIMMER_REGISTER_CH8_LEVEL;
    static constexpr size_t __DIMMER_REGISTER_CH9_LEVEL = DIMMER_REGISTER_CH9_LEVEL;
    static constexpr size_t __DIMMER_REGISTER_CH10_LEVEL = DIMMER_REGISTER_CH10_LEVEL;
    static constexpr size_t __DIMMER_REGISTER_CH11_LEVEL = DIMMER_REGISTER_CH11_LEVEL;
    static constexpr size_t __DIMMER_REGISTER_CH12_LEVEL = DIMMER_REGISTER_CH12_LEVEL;
    static constexpr size_t __DIMMER_REGISTER_CH13_LEVEL = DIMMER_REGISTER_CH13_LEVEL;
    static constexpr size_t __DIMMER_REGISTER_CH14_LEVEL = DIMMER_REGISTER_CH14_LEVEL;
    static constexpr size_t __DIMMER_REGISTER_CH15_LEVEL = DIMMER_REGISTER_CH15_LEVEL;
#endif
static constexpr size_t __DIMMER_REGISTER_CHANNELS_END = DIMMER_REGISTER_CHANNELS_END;
static constexpr size_t __DIMMER_REGISTER_OPTIONS = DIMMER_REGISTER_OPTIONS;
static constexpr size_t __DIMMER_REGISTER_MAX_TEMP = DIMMER_REGISTER_MAX_TEMP;
static constexpr size_t __DIMMER_REGISTER_FADE_IN_TIME = DIMMER_REGISTER_FADE_IN_TIME;
static constexpr size_t __DIMMER_REGISTER_ZC_DELAY_TICKS = DIMMER_REGISTER_ZC_DELAY_TICKS;
static constexpr size_t __DIMMER_REGISTER_MIN_ON_TIME_TICKS = DIMMER_REGISTER_MIN_ON_TIME_TICKS;
static constexpr size_t __DIMMER_REGISTER_MIN_OFF_TIME_TICKS = DIMMER_REGISTER_MIN_OFF_TIME_TICKS;
static constexpr size_t __DIMMER_REGISTER_RANGE_BEGIN = DIMMER_REGISTER_RANGE_BEGIN;
static constexpr size_t __DIMMER_REGISTER_RANGE_DIVIDER = DIMMER_REGISTER_RANGE_DIVIDER;
static constexpr size_t __DIMMER_REGISTER_INT_VREF11 = DIMMER_REGISTER_INT_VREF11;
static constexpr size_t __DIMMER_REGISTER_CAL_TS_OFFSET = DIMMER_REGISTER_CAL_TS_OFFSET;
static constexpr size_t __DIMMER_REGISTER_CAL_TS_GAIN = DIMMER_REGISTER_CAL_TS_GAIN;
static constexpr size_t __DIMMER_REGISTER_CAL_NTC_OFS = DIMMER_REGISTER_CAL_NTC_OFS;
static constexpr size_t __DIMMER_REGISTER_METRICS_INT = DIMMER_REGISTER_METRICS_INT;
static constexpr size_t __DIMMER_REGISTER_ERRORS = DIMMER_REGISTER_ERRORS;
static constexpr size_t __DIMMER_REGISTER_FREQUENCY = DIMMER_REGISTER_FREQUENCY;
static constexpr size_t __DIMMER_REGISTER_NTC_TEMP = DIMMER_REGISTER_NTC_TEMP;
static constexpr size_t __DIMMER_REGISTER_INT_TEMP = DIMMER_REGISTER_INT_TEMP;
static constexpr size_t __DIMMER_REGISTER_VCC = DIMMER_REGISTER_VCC;
static constexpr size_t __DIMMER_REGISTER_RAM = DIMMER_REGISTER_RAM;
static constexpr size_t __DIMMER_REGISTER_ADDRESS = DIMMER_REGISTER_ADDRESS;
static constexpr size_t __DIMMER_REGISTER_END_ADDR = DIMMER_REGISTER_END_ADDR;
static constexpr size_t __DIMMER_REGISTER_CUBIC_INT_OFS = DIMMER_REGISTER_CUBIC_INT_OFS;
static constexpr size_t __DIMMER_REGISTER_CUBIC_INT_DATAX_0 = DIMMER_REGISTER_CUBIC_INT_DATAX(0);
static constexpr size_t __DIMMER_REGISTER_CUBIC_INT_DATAY_0 = DIMMER_REGISTER_CUBIC_INT_DATAY(0);
static constexpr size_t __DIMMER_REGISTER_MEM_SIZE = DIMMER_REGISTER_MEM_SIZE;
static constexpr size_t __DIMMER_EVENT_METRICS_REPORT = DIMMER_EVENT_METRICS_REPORT;
static constexpr size_t __DIMMER_EVENT_TEMPERATURE_ALERT = DIMMER_EVENT_TEMPERATURE_ALERT;
static constexpr size_t __DIMMER_EVENT_FADING_COMPLETE = DIMMER_EVENT_FADING_COMPLETE;
static constexpr size_t __DIMMER_EVENT_EEPROM_WRITTEN = DIMMER_EVENT_EEPROM_WRITTEN;
static constexpr size_t __DIMMER_EVENT_FREQUENCY_WARNING = DIMMER_EVENT_FREQUENCY_WARNING;
static constexpr size_t __DIMMER_EVENT_CHANNEL_ON_OFF = DIMMER_EVENT_CHANNEL_ON_OFF;
static constexpr size_t __DIMMER_EVENT_SYNC_EVENT = DIMMER_EVENT_SYNC_EVENT;
static constexpr size_t __DIMMER_EVENT_RESTART = DIMMER_EVENT_RESTART;
static constexpr size_t __DIMMER_COMMAND_SET_LEVEL = DIMMER_COMMAND_SET_LEVEL;
static constexpr size_t __DIMMER_COMMAND_FADE = DIMMER_COMMAND_FADE;
static constexpr size_t __DIMMER_COMMAND_READ_CHANNELS = DIMMER_COMMAND_READ_CHANNELS;
static constexpr size_t __DIMMER_COMMAND_READ_NTC = DIMMER_COMMAND_READ_NTC;
static constexpr size_t __DIMMER_COMMAND_READ_INT_TEMP = DIMMER_COMMAND_READ_INT_TEMP;
static constexpr size_t __DIMMER_COMMAND_READ_VCC = DIMMER_COMMAND_READ_VCC;
static constexpr size_t __DIMMER_COMMAND_READ_AC_FREQUENCY = DIMMER_COMMAND_READ_AC_FREQUENCY;
static constexpr size_t __DIMMER_COMMAND_WRITE_EEPROM = DIMMER_COMMAND_WRITE_EEPROM;
static constexpr size_t __DIMMER_COMMAND_RESTORE_FS = DIMMER_COMMAND_RESTORE_FS;
static constexpr size_t __DIMMER_COMMAND_GET_TIMER_TICKS = DIMMER_COMMAND_GET_TIMER_TICKS;
static constexpr size_t __DIMMER_COMMAND_PRINT_INFO = DIMMER_COMMAND_PRINT_INFO;
static constexpr size_t __DIMMER_COMMAND_FORCE_TEMP_CHECK = DIMMER_COMMAND_FORCE_TEMP_CHECK;
static constexpr size_t __DIMMER_COMMAND_PRINT_METRICS = DIMMER_COMMAND_PRINT_METRICS;
static constexpr size_t __DIMMER_COMMAND_SET_MODE = DIMMER_COMMAND_SET_MODE;
static constexpr size_t __DIMMER_COMMAND_ZC_TIMINGS_OUTPUT = DIMMER_COMMAND_ZC_TIMINGS_OUTPUT;
static constexpr size_t __DIMMER_COMMAND_PRINT_CONFIG = DIMMER_COMMAND_PRINT_CONFIG;
static constexpr size_t __DIMMER_COMMAND_WRITE_CONFIG = DIMMER_COMMAND_WRITE_CONFIG;
static constexpr size_t __DIMMER_COMMAND_WRITE_EEPROM_NOW = DIMMER_COMMAND_WRITE_EEPROM_NOW;
static constexpr size_t __DIMMER_COMMAND_PRINT_CUBIC_INT = DIMMER_COMMAND_PRINT_CUBIC_INT;
static constexpr size_t __DIMMER_COMMAND_GET_CUBIC_INT = DIMMER_COMMAND_GET_CUBIC_INT;
static constexpr size_t __DIMMER_COMMAND_READ_CUBIC_INT = DIMMER_COMMAND_READ_CUBIC_INT;
static constexpr size_t __DIMMER_COMMAND_WRITE_CUBIC_INT = DIMMER_COMMAND_WRITE_CUBIC_INT;
static constexpr size_t __DIMMER_COMMAND_CUBIC_INT_TEST_PERF = DIMMER_COMMAND_CUBIC_INT_TEST_PERF;
static constexpr size_t __DIMMER_COMMAND_MEASURE_FREQ = DIMMER_COMMAND_MEASURE_FREQ;
static constexpr size_t __DIMMER_COMMAND_INIT_EEPROM = DIMMER_COMMAND_INIT_EEPROM;
static constexpr size_t __DIMMER_COMMAND_INCR_ZC_DELAY = DIMMER_COMMAND_INCR_ZC_DELAY;
static constexpr size_t __DIMMER_COMMAND_DEC_ZC_DELAY = DIMMER_COMMAND_DEC_ZC_DELAY;
static constexpr size_t __DIMMER_COMMAND_SET_ZC_DELAY = DIMMER_COMMAND_SET_ZC_DELAY;
static constexpr size_t __DIMMER_COMMAND_INCR_HW_TICKS = DIMMER_COMMAND_INCR_HW_TICKS;
static constexpr size_t __DIMMER_COMMAND_DEC_HW_TICKS = DIMMER_COMMAND_DEC_HW_TICKS;
static constexpr size_t __DIMMER_COMMAND_SET_ZC_SYNC = DIMMER_COMMAND_SET_ZC_SYNC;
static constexpr size_t __DIMMER_COMMAND_DUMP_CHANNELS = DIMMER_COMMAND_DUMP_CHANNELS;
static constexpr size_t __DIMMER_COMMAND_DUMP_MEM = DIMMER_COMMAND_DUMP_MEM;
static constexpr size_t __DIMMER_COMMAND_STATUS_OK = DIMMER_COMMAND_STATUS_OK;
static constexpr size_t __DIMMER_COMMAND_STATUS_ERROR = DIMMER_COMMAND_STATUS_ERROR;
static constexpr size_t __DIMMER_OPTIONS_RESTORE_LEVEL = DIMMER_OPTIONS_RESTORE_LEVEL;
static constexpr size_t __DIMMER_OPTIONS_MODE_LEADING_EDGE = DIMMER_OPTIONS_MODE_LEADING_EDGE;
static constexpr size_t __DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED = DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED;
static constexpr size_t __DIMMER_OPTIONS_NEGATIVE_ZC_DELAY = DIMMER_OPTIONS_NEGATIVE_ZC_DELAY;
static constexpr size_t __DIMMER_EEPROM_FLAGS_CONFIG_UPDATED = DIMMER_EEPROM_FLAGS_CONFIG_UPDATED;
