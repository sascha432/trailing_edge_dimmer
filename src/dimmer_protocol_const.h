// created with environment "printdef"
// run python ./scripts/create_const.py to convert this file to ./scripts/libs/fw_const_ver_MAJOR_MINOR_x.py
#define DIMMER_MAX_CHANNELS                      8
#define DIMMER_I2C_ADDRESS                       0x17
#define DIMMER_I2C_MASTER_ADDRESS                0x18
#define DIMMER_REGISTER_START_ADDR               0x80
#define DIMMER_REGISTER_FROM_LEVEL               0x80
#define DIMMER_REGISTER_CHANNEL                  0x82
#define DIMMER_REGISTER_TO_LEVEL                 0x83
#define DIMMER_REGISTER_TIME                     0x85
#define DIMMER_REGISTER_COMMAND                  0x89
#define DIMMER_REGISTER_READ_LENGTH              0x8a
#define DIMMER_REGISTER_COMMAND_STATUS           0x8b
#define DIMMER_REGISTER_CHANNELS_START           0x8c
#define DIMMER_REGISTER_CH0_LEVEL                0x8c
#define DIMMER_REGISTER_CH1_LEVEL                0x8e
#define DIMMER_REGISTER_CH2_LEVEL                0x90
#define DIMMER_REGISTER_CH3_LEVEL                0x92
#define DIMMER_REGISTER_CH4_LEVEL                0x94
#define DIMMER_REGISTER_CH5_LEVEL                0x96
#define DIMMER_REGISTER_CH6_LEVEL                0x98
#define DIMMER_REGISTER_CH7_LEVEL                0x9a
#define DIMMER_REGISTER_CHANNELS_END             0x9c
#define DIMMER_REGISTER_OPTIONS                  0x9c
#define DIMMER_REGISTER_MAX_TEMP                 0x9d
#define DIMMER_REGISTER_FADE_IN_TIME             0x9e
#define DIMMER_REGISTER_ZC_DELAY_TICKS           0xa2
#define DIMMER_REGISTER_MIN_ON_TIME_TICKS        0xa4
#define DIMMER_REGISTER_MIN_OFF_TIME_TICKS       0xa6
#define DIMMER_REGISTER_RANGE_BEGIN              0xa8
#define DIMMER_REGISTER_RANGE_DIVIDER            0xaa
#define DIMMER_REGISTER_INT_VREF11               0xac
#define DIMMER_REGISTER_CAL_TS_OFFSET            0xad
#define DIMMER_REGISTER_CAL_TS_GAIN              0xae
#define DIMMER_REGISTER_CAL_NTC_OFS              0xaf
#define DIMMER_REGISTER_METRICS_INT              0xb0
#define DIMMER_REGISTER_ADJ_HW_CYCLES            0xb1
#define DIMMER_REGISTER_SWITCH_ON_MIN_TIME       0xb2
#define DIMMER_REGISTER_SWITCH_ON_COUNT          0xb4
#define DIMMER_REGISTER_ERRORS                   0xb5
#define DIMMER_REGISTER_FREQUENCY                0xb8
#define DIMMER_REGISTER_NTC_TEMP                 0xbc
#define DIMMER_REGISTER_INT_TEMP                 0xc0
#define DIMMER_REGISTER_VCC                      0xc2
#define DIMMER_REGISTER_RAM                      0xc4
#define DIMMER_REGISTER_ADDRESS                  0xd4
#define DIMMER_REGISTER_END_ADDR                 0xd5
#define DIMMER_EVENT_METRICS_REPORT              0xf0
#define DIMMER_EVENT_TEMPERATURE_ALERT           0xf1
#define DIMMER_EVENT_FADING_COMPLETE             0xf2
#define DIMMER_EVENT_EEPROM_WRITTEN              0xf3
#define DIMMER_EVENT_FREQUENCY_WARNING           0xf4
#define DIMMER_EVENT_CHANNEL_ON_OFF              0xf5
#define DIMMER_EVENT_SYNC_EVENT                  0xf6
#define DIMMER_COMMAND_SET_LEVEL                 0x10
#define DIMMER_COMMAND_FADE                      0x11
#define DIMMER_COMMAND_READ_CHANNELS             0x12
#define DIMMER_COMMAND_READ_NTC                  0x20
#define DIMMER_COMMAND_READ_INT_TEMP             0x21
#define DIMMER_COMMAND_READ_VCC                  0x22
#define DIMMER_COMMAND_READ_AC_FREQUENCY         0x23
#define DIMMER_COMMAND_WRITE_EEPROM              0x50
#define DIMMER_COMMAND_RESTORE_FS                0x51
#define DIMMER_COMMAND_GET_TIMER_TICKS           0x52
#define DIMMER_COMMAND_PRINT_INFO                0x53
#define DIMMER_COMMAND_FORCE_TEMP_CHECK          0x54
#define DIMMER_COMMAND_PRINT_METRICS             0x55
#define DIMMER_COMMAND_SET_MODE                  0x56
#define DIMMER_COMMAND_ZC_TIMINGS_OUTPUT         0x60
#define DIMMER_COMMAND_PRINT_CONFIG              0x91
#define DIMMER_COMMAND_WRITE_CONFIG              0x92
#define DIMMER_COMMAND_WRITE_EEPROM_NOW          0x93
#define DIMMER_COMMAND_MEASURE_FREQ              0x94
#define DIMMER_COMMAND_INIT_EEPROM               0x95
#define DIMMER_COMMAND_INCR_ZC_DELAY             0x82
#define DIMMER_COMMAND_DECR_ZC_DELAY             0x83
#define DIMMER_COMMAND_SET_ZC_DELAY              0x84
#define DIMMER_COMMAND_INCR_HW_TICKS             0x85
#define DIMMER_COMMAND_DECR_HW_TICKS             0x86
#define DIMMER_COMMAND_SET_ZC_SYNC               0xec
#define DIMMER_COMMAND_DUMP_CHANNELS             0xed
#define DIMMER_COMMAND_DUMP_MEM                  0xee
#define DIMMER_COMMAND_STATUS_OK                 0x00
#define DIMMER_COMMAND_STATUS_ERROR              0xff
#define DIMMER_OPTIONS_RESTORE_LEVEL             0x01
#define DIMMER_OPTIONS_MODE_LEADING_EDGE         0x02
#define DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED      0x04
#define DIMMER_OPTIONS_NEGATIVE_ZC_DELAY         0x08
#define DIMMER_EEPROM_FLAGS_CONFIG_UPDATED       0x01
#define DIMMER_REGISTER_CUBIC_INT_OFS            (DIMMER_REGISTER_RAM)
#define DIMMER_REGISTER_CUBIC_INT_DATAX(n)       (DIMMER_REGISTER_CUBIC_INT_OFS + ((n) * 2))
#define DIMMER_REGISTER_CUBIC_INT_DATAY(n)       (DIMMER_REGISTER_CUBIC_INT_OFS + 1 + ((n) * 2))
