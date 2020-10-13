Serial.print(F("#define DIMMER_I2C_ADDRESS                       ")); Serial.printf("0x%02x\n", DIMMER_I2C_ADDRESS);
Serial.print(F("#define DIMMER_REGISTER_START_ADDR               ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_START_ADDR);
Serial.print(F("#define DIMMER_REGISTER_FROM_LEVEL               ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_FROM_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CHANNEL                  ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CHANNEL);
Serial.print(F("#define DIMMER_REGISTER_TO_LEVEL                 ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_TO_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_TIME                     ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_TIME);
Serial.print(F("#define DIMMER_REGISTER_COMMAND                  ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_COMMAND);
Serial.print(F("#define DIMMER_REGISTER_READ_LENGTH              ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_READ_LENGTH);
Serial.print(F("#define DIMMER_REGISTER_COMMAND_STATUS           ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_COMMAND_STATUS);
Serial.print(F("#define DIMMER_REGISTER_CHANNELS_START           ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CHANNELS_START);
Serial.print(F("#define DIMMER_REGISTER_CH0_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH0_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH1_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH1_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH2_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH2_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH3_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH3_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH4_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH4_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH5_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH5_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH6_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH6_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CH7_LEVEL                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CH7_LEVEL);
Serial.print(F("#define DIMMER_REGISTER_CHANNELS_END             ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_CHANNELS_END);
Serial.print(F("#define DIMMER_REGISTER_TEMP                     ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_TEMP);
Serial.print(F("#define DIMMER_REGISTER_VCC                      ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_VCC);
Serial.print(F("#define DIMMER_REGISTER_OPTIONS                  ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_OPTIONS);
Serial.print(F("#define DIMMER_REGISTER_MAX_TEMP                 ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_MAX_TEMP);
Serial.print(F("#define DIMMER_REGISTER_FADE_IN_TIME             ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_FADE_IN_TIME);
Serial.print(F("#define DIMMER_REGISTER_TEMP_CHECK_INT           ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_TEMP_CHECK_INT);
Serial.print(F("#define DIMMER_REGISTER_ZC_DELAY_TICKS           ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_ZC_DELAY_TICKS);
Serial.print(F("#define DIMMER_REGISTER_MIN_ON_TIME_TICKS        ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_MIN_ON_TIME_TICKS);
Serial.print(F("#define DIMMER_REGISTER_MIN_OFF_TIME_TICKS       ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_MIN_OFF_TIME_TICKS);
Serial.print(F("#define DIMMER_REGISTER_INT_1_1V_REF             ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_INT_1_1V_REF);
Serial.print(F("#define DIMMER_REGISTER_INT_TEMP_OFS             ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_INT_TEMP_OFS);
Serial.print(F("#define DIMMER_REGISTER_METRICS_INT              ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_METRICS_INT);
Serial.print(F("#define DIMMER_REGISTER_VERSION                  ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_VERSION);
Serial.print(F("#define DIMMER_REGISTER_RANGE_BEGIN              ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_RANGE_BEGIN);
Serial.print(F("#define DIMMER_REGISTER_RANGE_END                ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_RANGE_END);
Serial.print(F("#define DIMMER_REGISTER_SWITCH_ON_MIN_TIME       ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_SWITCH_ON_MIN_TIME);
Serial.print(F("#define DIMMER_REGISTER_SWITCH_ON_COUNT          ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_SWITCH_ON_COUNT);
Serial.print(F("#define DIMMER_REGISTER_ADDRESS                  ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_ADDRESS);
Serial.print(F("#define DIMMER_REGISTER_END_ADDR                 ")); Serial.printf("0x%02x\n", DIMMER_REGISTER_END_ADDR);
Serial.print(F("#define DIMMER_METRICS_REPORT                    ")); Serial.printf("0x%02x\n", DIMMER_METRICS_REPORT);
Serial.print(F("#define DIMMER_TEMPERATURE_ALERT                 ")); Serial.printf("0x%02x\n", DIMMER_TEMPERATURE_ALERT);
Serial.print(F("#define DIMMER_FADING_COMPLETE                   ")); Serial.printf("0x%02x\n", DIMMER_FADING_COMPLETE);
Serial.print(F("#define DIMMER_EEPROM_WRITTEN                    ")); Serial.printf("0x%02x\n", DIMMER_EEPROM_WRITTEN);
Serial.print(F("#define DIMMER_FREQUENCY_WARNING                 ")); Serial.printf("0x%02x\n", DIMMER_FREQUENCY_WARNING);
Serial.print(F("#define DIMMER_COMMAND_SET_LEVEL                 ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_SET_LEVEL);
Serial.print(F("#define DIMMER_COMMAND_FADE                      ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_FADE);
Serial.print(F("#define DIMMER_COMMAND_READ_CHANNELS             ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_READ_CHANNELS);
Serial.print(F("#define DIMMER_COMMAND_READ_NTC                  ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_READ_NTC);
Serial.print(F("#define DIMMER_COMMAND_READ_INT_TEMP             ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_READ_INT_TEMP);
Serial.print(F("#define DIMMER_COMMAND_READ_VCC                  ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_READ_VCC);
Serial.print(F("#define DIMMER_COMMAND_READ_AC_FREQUENCY         ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_READ_AC_FREQUENCY);
Serial.print(F("#define DIMMER_COMMAND_WRITE_EEPROM              ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_WRITE_EEPROM);
Serial.print(F("#define DIMMER_COMMAND_RESTORE_FS                ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_RESTORE_FS);
Serial.print(F("#define DIMMER_COMMAND_READ_TIMINGS              ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_READ_TIMINGS);
Serial.print(F("#define DIMMER_COMMAND_PRINT_INFO                ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_PRINT_INFO);
Serial.print(F("#define DIMMER_COMMAND_FORCE_TEMP_CHECK          ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_FORCE_TEMP_CHECK);
Serial.print(F("#define DIMMER_COMMAND_PRINT_METRICS             ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_PRINT_METRICS);
Serial.print(F("#define DIMMER_COMMAND_ZC_TIMINGS_OUTPUT         ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_ZC_TIMINGS_OUTPUT);
Serial.print(F("#define DIMMER_COMMAND_DUMP_MEM                  ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_DUMP_MEM);
Serial.print(F("#define DIMMER_COMMAND_STATUS_OK                 ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_STATUS_OK);
Serial.print(F("#define DIMMER_COMMAND_STATUS_ERROR              ")); Serial.printf("0x%02x\n", DIMMER_COMMAND_STATUS_ERROR);
Serial.print(F("#define DIMMER_OPTIONS_RESTORE_LEVEL             ")); Serial.printf("0x%02x\n", DIMMER_OPTIONS_RESTORE_LEVEL);
Serial.print(F("#define DIMMER_OPTIONS_REPORT_TEMP               ")); Serial.printf("0x%02x\n", DIMMER_OPTIONS_REPORT_TEMP);
Serial.print(F("#define DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED      ")); Serial.printf("0x%02x\n", DIMMER_OPTIONS_TEMP_ALERT_TRIGGERED);
Serial.print(F("#define DIMMER_TIMINGS_TMR1_TICKS_PER_US         ")); Serial.printf("0x%02x\n", DIMMER_TIMINGS_TMR1_TICKS_PER_US);
Serial.print(F("#define DIMMER_TIMINGS_TMR2_TICKS_PER_US         ")); Serial.printf("0x%02x\n", DIMMER_TIMINGS_TMR2_TICKS_PER_US);
Serial.print(F("#define DIMMER_TIMINGS_ZC_DELAY_IN_US            ")); Serial.printf("0x%02x\n", DIMMER_TIMINGS_ZC_DELAY_IN_US);
Serial.print(F("#define DIMMER_TIMINGS_MIN_ON_TIME_IN_US         ")); Serial.printf("0x%02x\n", DIMMER_TIMINGS_MIN_ON_TIME_IN_US);
Serial.print(F("#define DIMMER_TIMINGS_MIN_OFF_TIME_IN_US         ")); Serial.printf("0x%02x\n", DIMMER_TIMINGS_MIN_OFF_TIME_IN_US);
