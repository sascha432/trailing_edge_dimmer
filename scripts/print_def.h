Serial.print(F("#define DIMMER_MAX_CHANNELS                      ")); Serial.printf("%u\n", (uint8_t)DIMMER_MAX_CHANNELS);
Serial.print(F("#define DIMMER_REGISTER_START_ADDR               ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_START_ADDR);
Serial.print(F("#define DIMMER_REGISTER_FROM_LEVEL               ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_FROM_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CHANNEL                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CHANNEL);
Serial.print(F("#define DIMMER_REGISTER_TO_LEVEL                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_TO_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_TIME                     ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_TIME);
Serial.print(F("#define DIMMER_REGISTER_COMMAND                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_COMMAND);
Serial.print(F("#define DIMMER_REGISTER_READ_LENGTH              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_READ_LENGTH);
Serial.print(F("#define DIMMER_REGISTER_COMMAND_STATUS           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_COMMAND_STATUS);
Serial.print(F("#define DIMMER_REGISTER_CHANNELS_START           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CHANNELS_START);
Serial.print(F("#define DIMMER_REGISTER_CH0_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH0_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH1_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH1_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH2_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH2_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH3_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH3_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH4_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH4_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH5_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH5_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH6_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH6_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH7_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH7_LEVEL);
#ifdef DIMMER_MAX_CHANNELS > 8
    Serial.print(F("#define DIMMER_REGISTER_CH8_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH8_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH9_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH9_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH10_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH10_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH11_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH11_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH12_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH12_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH13_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH13_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH14_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH14_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH15_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH15_LEVEL);
    Serial.print(F("#define DIMMER_REGISTER_CH16_LEVEL                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CH16_LEVEL);
#endif
Serial.print(F("#define DIMMER_REGISTER_CHANNELS_END             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CHANNELS_END);
Serial.print(F("#define DIMMER_REGISTER_OPTIONS                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_OPTIONS);
Serial.print(F("#define DIMMER_REGISTER_MAX_TEMP                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_MAX_TEMP);
Serial.print(F("#define DIMMER_REGISTER_FADE_IN_TIME             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_FADE_IN_TIME);
Serial.print(F("#define DIMMER_REGISTER_ZC_DELAY_TICKS           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_ZC_DELAY_TICKS);
Serial.print(F("#define DIMMER_REGISTER_MIN_ON_TIME_TICKS        ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_MIN_ON_TIME_TICKS);
Serial.print(F("#define DIMMER_REGISTER_MIN_OFF_TIME_TICKS       ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_MIN_OFF_TIME_TICKS);
Serial.print(F("#define DIMMER_REGISTER_RANGE_BEGIN              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_RANGE_BEGIN);
Serial.print(F("#define DIMMER_REGISTER_RANGE_DIVIDER            ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_RANGE_DIVIDER);
Serial.print(F("#define DIMMER_REGISTER_INT_VREF11               ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_INT_VREF11);
Serial.print(F("#define DIMMER_REGISTER_CAL_TS_OFFSET            ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CAL_TS_OFFSET);
Serial.print(F("#define DIMMER_REGISTER_CAL_TS_GAIN              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CAL_TS_GAIN);
Serial.print(F("#define DIMMER_REGISTER_CAL_NTC_OFS              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CAL_NTC_OFS);
Serial.print(F("#define DIMMER_REGISTER_METRICS_INT              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_METRICS_INT);
Serial.print(F("#define DIMMER_REGISTER_ADJ_HW_CYCLES            ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_ADJ_HW_CYCLES);
Serial.print(F("#define DIMMER_REGISTER_ERRORS                   ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_ERRORS);
Serial.print(F("#define DIMMER_REGISTER_FREQUENCY                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_FREQUENCY);
Serial.print(F("#define DIMMER_REGISTER_NTC_TEMP                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_NTC_TEMP);
Serial.print(F("#define DIMMER_REGISTER_INT_TEMP                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_INT_TEMP);
Serial.print(F("#define DIMMER_REGISTER_VCC                      ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_VCC);
Serial.print(F("#define DIMMER_REGISTER_RAM                      ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_RAM);
Serial.print(F("#define DIMMER_REGISTER_ADDRESS                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_ADDRESS);
Serial.print(F("#define DIMMER_REGISTER_END_ADDR                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_END_ADDR);
Serial.print(F("#define DIMMER_REGISTER_CUBIC_INT_OFS            ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_CUBIC_INT_OFS);
Serial.print(F("#define DIMMER_REGISTER_CUBIC_INT_DATAX(n)       (DIMMER_REGISTER_CUBIC_INT_OFS + ((n) * 2))\n"));
Serial.print(F("#define DIMMER_REGISTER_CUBIC_INT_DATAY(n)       (DIMMER_REGISTER_CUBIC_INT_OFS + 1 + ((n) * 2))\n"));
Serial.print(F("#define DIMMER_REGISTER_MEM_SIZE                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_REGISTER_MEM_SIZE);
Serial.print(F("#define DIMMER_EVENT_METRICS_REPORT              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_METRICS_REPORT);
Serial.print(F("#define DIMMER_EVENT_TEMPERATURE_ALERT           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_TEMPERATURE_ALERT);
Serial.print(F("#define DIMMER_EVENT_FADING_COMPLETE             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_FADING_COMPLETE);
Serial.print(F("#define DIMMER_EVENT_EEPROM_WRITTEN              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_EEPROM_WRITTEN);
Serial.print(F("#define DIMMER_EVENT_FREQUENCY_WARNING           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_FREQUENCY_WARNING);
Serial.print(F("#define DIMMER_EVENT_CHANNEL_ON_OFF              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_CHANNEL_ON_OFF);
Serial.print(F("#define DIMMER_EVENT_SYNC_EVENT                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_SYNC_EVENT);
Serial.print(F("#define DIMMER_EVENT_RESTART                     ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EVENT_RESTART);
Serial.print(F("#define DIMMER_COMMAND_SET_LEVEL                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_SET_LEVEL);
Serial.print(F("#define DIMMER_COMMAND_FADE                      ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_FADE);
Serial.print(F("#define DIMMER_COMMAND_READ_CHANNELS             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_READ_CHANNELS);
Serial.print(F("#define DIMMER_COMMAND_READ_NTC                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_READ_NTC);
Serial.print(F("#define DIMMER_COMMAND_READ_INT_TEMP             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_READ_INT_TEMP);
Serial.print(F("#define DIMMER_COMMAND_READ_VCC                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_READ_VCC);
Serial.print(F("#define DIMMER_COMMAND_READ_AC_FREQUENCY         ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_READ_AC_FREQUENCY);
Serial.print(F("#define DIMMER_COMMAND_WRITE_EEPROM              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_WRITE_EEPROM);
Serial.print(F("#define DIMMER_COMMAND_RESTORE_FS                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_RESTORE_FS);
Serial.print(F("#define DIMMER_COMMAND_GET_TIMER_TICKS           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_GET_TIMER_TICKS);
Serial.print(F("#define DIMMER_COMMAND_PRINT_INFO                ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_PRINT_INFO);
Serial.print(F("#define DIMMER_COMMAND_FORCE_TEMP_CHECK          ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_FORCE_TEMP_CHECK);
Serial.print(F("#define DIMMER_COMMAND_PRINT_METRICS             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_PRINT_METRICS);
Serial.print(F("#define DIMMER_COMMAND_SET_MODE                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_SET_MODE);
Serial.print(F("#define DIMMER_COMMAND_ZC_TIMINGS_OUTPUT         ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_ZC_TIMINGS_OUTPUT);
Serial.print(F("#define DIMMER_COMMAND_PRINT_CONFIG              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_PRINT_CONFIG);
Serial.print(F("#define DIMMER_COMMAND_WRITE_CONFIG              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_WRITE_CONFIG);
Serial.print(F("#define DIMMER_COMMAND_WRITE_EEPROM_NOW          ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_WRITE_EEPROM_NOW);
Serial.print(F("#define DIMMER_COMMAND_PRINT_CUBIC_INT           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_PRINT_CUBIC_INT);
Serial.print(F("#define DIMMER_COMMAND_GET_CUBIC_INT             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_GET_CUBIC_INT);
Serial.print(F("#define DIMMER_COMMAND_READ_CUBIC_INT            ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_READ_CUBIC_INT);
Serial.print(F("#define DIMMER_COMMAND_WRITE_CUBIC_INT           ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_WRITE_CUBIC_INT);
Serial.print(F("#define DIMMER_COMMAND_CUBIC_INT_TEST_PERF       ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_CUBIC_INT_TEST_PERF);
Serial.print(F("#define DIMMER_COMMAND_MEASURE_FREQ              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_MEASURE_FREQ);
Serial.print(F("#define DIMMER_COMMAND_INIT_EEPROM               ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_INIT_EEPROM);
Serial.print(F("#define DIMMER_COMMAND_INCR_ZC_DELAY             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_INCR_ZC_DELAY);
Serial.print(F("#define DIMMER_COMMAND_DEC_ZC_DELAY              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_DEC_ZC_DELAY);
Serial.print(F("#define DIMMER_COMMAND_SET_ZC_DELAY              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_SET_ZC_DELAY);
Serial.print(F("#define DIMMER_COMMAND_INCR_HW_TICKS             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_INCR_HW_TICKS);
Serial.print(F("#define DIMMER_COMMAND_DEC_HW_TICKS              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_DEC_HW_TICKS);
Serial.print(F("#define DIMMER_COMMAND_SET_ZC_SYNC               ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_SET_ZC_SYNC);
Serial.print(F("#define DIMMER_COMMAND_DUMP_CHANNELS             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_DUMP_CHANNELS);
Serial.print(F("#define DIMMER_COMMAND_DUMP_MEM                  ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_DUMP_MEM);
Serial.print(F("#define DIMMER_COMMAND_STATUS_OK                 ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_STATUS_OK);
Serial.print(F("#define DIMMER_COMMAND_STATUS_ERROR              ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_COMMAND_STATUS_ERROR);
Serial.print(F("#define DIMMER_OPTIONS_RESTORE_LEVEL             ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_OPTIONS_RESTORE_LEVEL);
Serial.print(F("#define DIMMER_OPTIONS_MODE_LEADING_EDGE         ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_OPTIONS_MODE_LEADING_EDGE);
Serial.print(F("#define DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED      ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED);
Serial.print(F("#define DIMMER_OPTIONS_NEGATIVE_ZC_DELAY         ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_OPTIONS_NEGATIVE_ZC_DELAY);
Serial.print(F("#define DIMMER_EEPROM_FLAGS_CONFIG_UPDATED       ")); Serial.printf("0x%02x\n", (uint8_t)DIMMER_EEPROM_FLAGS_CONFIG_UPDATED);
