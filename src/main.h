/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "dimmer.h"
#include "i2c_slave.h"

 // bitset
struct dimmer_scheduled_calls_t {
    uint8_t read_vcc: 1;
    uint8_t read_int_temp: 1;
    uint8_t read_ntc_temp: 1;
    uint8_t write_eeprom: 1;
    uint8_t eeprom_update_config: 1;
    uint8_t print_info: 1;
    uint8_t report_error: 1;
    uint8_t send_channel_state: 1;
    uint8_t send_fading_events: 1;
};

#if HAVE_PRINT_METRICS
extern uint32_t print_metrics_timeout;
extern uint16_t print_metrics_interval;
#endif

extern uint32_t next_temp_check;
extern uint32_t metrics_next_event;

extern dimmer_scheduled_calls_t dimmer_scheduled_calls;

#if HIDE_DIMMER_INFO == 0
void display_dimmer_info();
#endif

