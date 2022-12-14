/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <util/atomic.h>
#include "dimmer.h"
#include "i2c_slave.h"

static_assert(DIMMER_REGISTER_MEM_SIZE + DIMMER_REGISTER_START_ADDR <= 255, "out of memory");

inline void rem()
{
    Serial.print(F("+REM="));
}

void remln(const __FlashStringHelper *str);


 // bitset
template<typename _Type>
struct dimmer_scheduled_calls_templ_t {
    using type = _Type;
    union {
        struct {
            // byte 1
            type write_eeprom: 1;
            type eeprom_update_config: 1;
            type print_info: 1;
            type report_error: 1;
            type send_channel_state: 1;
            type send_fading_events: 1;
            type sync_event: 1;
        };
        uint8_t _data;
    };

    dimmer_scheduled_calls_templ_t() : _data(0) {}
    dimmer_scheduled_calls_templ_t(const uint8_t value) : _data(value) {}
    dimmer_scheduled_calls_templ_t(const dimmer_scheduled_calls_templ_t<volatile uint8_t> &tmp) : _data(tmp._data) {}
    dimmer_scheduled_calls_templ_t(const dimmer_scheduled_calls_templ_t<uint8_t> &tmp) : _data(tmp._data) {}

    operator uint8_t() const {
        return _data;
    }
};

using dimmer_scheduled_calls_t = dimmer_scheduled_calls_templ_t<volatile uint8_t>;
using dimmer_scheduled_calls_nv_t = dimmer_scheduled_calls_templ_t<uint8_t>;

struct dimmer_scheduled_levels_t {

    enum class SetType {
        NONE = 0,
        SET = 1,
        FADE = 2,
    };

    SetType type;
    int16_t from;
    int16_t to;
    float time;

    dimmer_scheduled_levels_t() : type(SetType::NONE), from(0), to(0), time(NAN) {}
    dimmer_scheduled_levels_t(int16_t level) : type(SetType::SET), from(0), to(level), time(NAN) {}
    dimmer_scheduled_levels_t(int16_t _from, uint16_t _to, float _time) : type(SetType::FADE), from(_from), to(_to), time(_time) {}
};

struct Queues {

    static constexpr int16_t kFadingCompletedEventTimerOverFlows = Dimmer::MeasureTimer::kMillisToOverflows(100);
    static constexpr uint16_t kTemperatureCheckTimerOverflows = Dimmer::MeasureTimer::kMillisToOverflows(1000);

    #if HAVE_PRINT_METRICS
        struct {
            uint24_t timer{0};
            uint8_t interval{0};
        } print_metrics;
    #endif

    #if HAVE_FADE_COMPLETION_EVENT
        struct {
            int16_t timer{-1};
            void disableTimer() {
                timer = -1;
            }
            void resetTimer() {
                timer = kFadingCompletedEventTimerOverFlows;
            }
        } fading_completed_events;
    #endif

    struct {
        uint16_t timer{kTemperatureCheckTimerOverflows};
        uint24_t report_next{0};
        void reset() {
            timer = kTemperatureCheckTimerOverflows;
        }
    } check_temperature;

    struct {
        uint24_t timer{0};
    } report_metrics;

    dimmer_scheduled_calls_t scheduled_calls{0};
    #if DIMMER_USE_QUEUE_LEVELS
        dimmer_scheduled_levels_t levels[Dimmer::Channel::size()];
    #endif
};

extern Queues queues;

#if HIDE_DIMMER_INFO == 0
    void display_dimmer_info();
#endif

#if DIMMER_CUBIC_INTERPOLATION
#    include "cubic_interpolation.h"
#endif
