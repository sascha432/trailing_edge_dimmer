/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <util/atomic.h>
#include "dimmer.h"
#include "i2c_slave.h"

 // bitset
template<typename _Type>
struct dimmer_scheduled_calls_templ_t {
    using type = _Type;
    union {
        struct {
            // byte 1
            type read_vcc: 1;
            type read_int_temp: 1;
            type read_ntc_temp: 1;
            type write_eeprom: 1;
            type eeprom_update_config: 1;
            type print_info: 1;
            type report_error: 1;
            type send_channel_state: 1;
            // byte 2
            type send_fading_events: 1;
            type sync_event: 1;
        };
        uint16_t _data;
    };

    dimmer_scheduled_calls_templ_t() : _data(0) {}
    dimmer_scheduled_calls_templ_t(const uint16_t value) : _data(value) {}

    operator uint16_t() const {
        return _data;
    }

    // atomic operations

    // if write_eeprom == false, set write_eeprom to true and return true
    // if write_eeprom == true, return false
    bool set_if_false_write_eeprom() {
        bool tmp;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            tmp = write_eeprom;
            if (!tmp) {
                write_eeprom = true;
            }
        }
        return !tmp;
    }

    static inline uint8_t lock() {
        uint8_t oldSREG = SREG;
        cli();
        return oldSREG;
    }

    static inline void unlock(uint8_t oldSREG) {
	    SREG = oldSREG;
    }
};

using dimmer_scheduled_calls_t = dimmer_scheduled_calls_templ_t<volatile uint8_t>;
using dimmer_scheduled_calls_nv_t = dimmer_scheduled_calls_templ_t<uint8_t>;

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

