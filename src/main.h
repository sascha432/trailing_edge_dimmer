/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "dimmer.h"
#include "i2c_slave.h"

void read_config();
void write_config();

// clear EEPROM and store default settings
void init_eeprom();

// set force=true to write the eeprom without changes
// set update_regmem_cfg=true to update register_mem.data.cfg
void _write_config(bool force = false, bool update_regmem_cfg = true);

 // bitset
struct dimmer_scheduled_calls_t {
    uint8_t read_vcc: 1;                // 0
    uint8_t read_int_temp: 1;           // 1
    uint8_t read_ntc_temp: 1;           // 2
    uint8_t write_eeprom: 1;            // 3
    uint8_t print_info: 1;              // 4
    uint8_t report_error: 1;            // 5
    uint8_t send_channel_state: 1;      // 6
    uint8_t send_fading_events: 1;      // 7
};

#if USE_TEMPERATURE_CHECK
extern unsigned long next_temp_check;
#endif

#if HAVE_PRINT_METRICS
extern unsigned long print_metrics_timeout;
extern uint16_t print_metrics_interval;
#endif

extern unsigned long metrics_next_event;

extern dimmer_scheduled_calls_t dimmer_scheduled_calls;

#if HIDE_DIMMER_INFO == 0
void display_dimmer_info();
#endif

