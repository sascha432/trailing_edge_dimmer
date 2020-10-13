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
    uint8_t read_vcc: 1;
    uint8_t read_int_temp: 1;
    uint8_t read_ntc_temp: 1;
    uint8_t write_eeprom: 1;
    uint8_t print_info: 1;
    uint8_t print_metrics: 1;
    uint8_t report_error: 1;
};

#if USE_TEMPERATURE_CHECK
extern unsigned long next_temp_check;
#endif

#if HAVE_PRINT_METRICS
extern unsigned long print_metrics_timeout;
#endif

extern unsigned long metrics_next_event;

extern dimmer_scheduled_calls_t dimmer_scheduled_calls;

#if HAVE_READ_INT_TEMP
extern bool is_Atmega328PB;
#define setAtmega328PB(value) is_Atmega328PB = value;
float get_internal_temperature();
#else
#define setAtmega328PB(value) ;
#endif


#if HIDE_DIMMER_INFO == 0
void display_dimmer_info();
#endif

#if HAVE_READ_VCC
uint16_t read_vcc();
#endif

#if HAVE_NTC
float get_ntc_temperature();
#endif
