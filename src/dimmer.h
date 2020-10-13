/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "helpers.h"
#include "dimmer_def.h"
#include "dimmer_protocol.h"
#include "dimmer_reg_mem.h"

extern register_mem_union_t register_mem;

using dimmer_channel_id_t = int8_t;
using dimmer_level_t = int16_t;

struct dimmer_fade_t {
    float level;
    float step;
    uint16_t count;
    dimmer_level_t targetLevel;
};

struct dimmer_channel_t {
    uint8_t channel;
    uint16_t ticks;
};

typedef struct __attribute__packed__ {
    dimmer_channel_id_t channel;
    dimmer_level_t level;
} FadingCompletionEvent_t;

namespace Dimmer {

    using ChannelType = dimmer_channel_id_t;
    using ChannelStateType = dimmer_channel_t;
    using LevelType = dimmer_level_t;
    using TickType = uint16_t;
    using TickMultiplierType = uint32_t;

    static constexpr long LevelTypeMin = static_cast<LevelType>(1UL << ((sizeof(LevelType) << 3) - 1));
    static constexpr long LevelTypeMax = (1UL << ((sizeof(LevelType) << 3) - 1));

    static constexpr TickType TickTypeMin = 0;
    static constexpr TickType TickTypeMax = ~0;

    static constexpr float kVRef = INTERNAL_VREF_1_1V;

    template<int _Timer>
    struct Timer {};

    template<>
    struct Timer<1> {
        static constexpr uint16_t prescaler = DIMMER_TIMER1_PRESCALER;
        static constexpr uint8_t extraTicks = (prescaler == 8 ? (8) : (1));
        static constexpr uint8_t prescalerBV =
            prescaler == 1 ?
                (1 << CS10) :
                prescaler == 8 ?
                    (1 << CS11) :
                    prescaler == 64 ?
                        ((1 << CS10) | (1 << CS11)) :
                        prescaler == 256 ?
                            (1 << CS12) :
                            prescaler == 1024 ?
                                ((1 << CS10) | (1 << CS12)) : -1;

        static_assert(prescalerBV != -1, "prescaler not defined");
        static constexpr float ticksPerMicrosecond =  (F_CPU / prescaler / 1000000.0);

        static inline void start() {
            TCCR1B |= prescalerBV;
        }

        static inline void pause() {
            TCCR1B = 0;
        }

        static inline TickType microsToTicks(uint32_t micros) {
            return micros * ticksPerMicrosecond;
        }

        static inline TickType ticksToMicros(uint32_t ticks) {
            return ticks / ticksPerMicrosecond;
        }

    };

    template<>
    struct Timer<2> {
        static constexpr uint16_t prescaler = DIMMER_TIMER2_PRESCALER;
        static constexpr uint8_t prescalerBV =
            prescaler == 1 ?
                (1 << CS20) :
                prescaler == 8 ?
                    (1 << CS21) :
                    prescaler == 32 ?
                        ((1 << CS20) | (1 << CS21)) :
                        prescaler == 64 ?
                            (1 << CS22) :
                            prescaler == 128 ?
                                ((1 << CS20) | (1 << CS22)) :
                                prescaler == 256 ?
                                    ((1 << CS21) | (1 << CS22)) :
                                    prescaler == 1024 ?
                                        ((1 << CS20) | (1 << CS21) | (1 << CS22)) : -1;

        static_assert(prescalerBV != -1, "prescaler not defined");

        static constexpr float ticksPerMicrosecond =  (F_CPU / prescaler / 1000000.0);

        static inline void start() {
            TCCR2B |= prescalerBV;
        }

        static inline void pause() {
            TCCR2B = 0;
        }

        static inline TickType microsToTicks(uint32_t micros) {
            return micros * ticksPerMicrosecond;
        }

        static inline TickType ticksToMicros(uint32_t ticks) {
            return ticks / ticksPerMicrosecond;
        }

    };

    static inline void enableTimers() {
        TIMSK1 |= (1 << OCIE1A);
        TCCR1A = 0;
        TCCR1B = 0;
        TIMSK2 |= (1 << OCIE2A);
        TCCR2A = 0;
        TCCR2B = 0;
    }

    static inline void disableTimers() {
        TIMSK1 &= ~(1 << OCIE1A);
        TIMSK2 &= ~(1 << OCIE2A);
    }

    struct Channel {
        using type = ChannelType;
        static constexpr type size = ::size_of(DIMMER_MOSFET_PINS);
        static constexpr type min = 0;
        static constexpr type max = size - 1;
        static constexpr type any = -1;
        static constexpr const uint8_t pins[size] = { DIMMER_MOSFET_PINS };
    };

    struct Level {
        using type = LevelType;
        static constexpr type size = DIMMER_MAX_LEVEL;
        static constexpr type off = 0;
        static constexpr type min = 0;
        static constexpr type max = size;
        static constexpr type min_on = off + 1;
        static constexpr type max_on = size;
        static constexpr type invalid = -1;
        static constexpr type current = -1;
    };

    static constexpr uint8_t kFrequency = DIMMER_AC_FREQUENCY;
    static constexpr uint8_t kMinFrequency = 48;
    static constexpr uint8_t kMaxFrequency = 62;

    static constexpr TickType kTicksPerHalfWave = (F_CPU / Timer<1>::prescaler / (kFrequency * 2));
    static constexpr TickMultiplierType kMaxTicksPerHalfWave = (F_CPU / Timer<1>::prescaler / (kMinFrequency * 2));

    static constexpr float timer1TicksPerMicroSeconds =  Timer<1>::ticksPerMicrosecond;
    static constexpr float timer2TicksPerMicroSeconds =  Timer<2>::ticksPerMicrosecond;

    static_assert(kMaxTicksPerHalfWave < LevelTypeMax, "Increase prescaler to reduce ticks per halfwave");
    static_assert(Level::max > 63, "64 or more levels required");
    static_assert(Level::max <= LevelTypeMax, "Max. level exceeds type size");

    struct Version {
        static constexpr uint8_t kMajor = DIMMER_VERSION_MAJOR;
        static constexpr uint8_t kMinor = DIMMER_VERSION_MINOR;
        static constexpr uint8_t kRevision = DIMMER_VERSION_REVISION;
        static constexpr uint16_t kVersion = (kMajor << 10) | (kMinor << 5) | kRevision;
    };

    struct dimmer_t {
        Level::type level[Channel::size];                                       // current level
        dimmer_fade_t fading[Channel::size];                                    // calculated fading data
        Channel::type channel_ptr;
        dimmer_channel_t ordered_channels[Channel::size + 1];                   // current dimming levels in ticks
        dimmer_channel_t ordered_channels_buffer[Channel::size + 1];            // next dimming levels
        uint8_t on_counter[Channel::size];                                      // counts halfwaves from 0 to 254 after switching on
        uint32_t halfwave_ticks;
        uint16_t channel_state;                                                  // bitset of the channel state and if the state has been reported (+ Channel::size bits)

#if HAVE_FADE_COMPLETION_EVENT
        Level::type fading_completed[Channel::size];
#endif
        bool on_state: 1;                                                       // value to set when turning the mosfets on
        bool off_state: 1;                                                      // value to set when turning the mosfets off
    };

    class DimmerBase : public dimmer_t {
    public:
        DimmerBase(register_mem_t &register_mem) :
            dimmer_t({}),
            _config(register_mem.cfg),
            _register_mem(register_mem)
        {
        }

        void begin();
        void end();
        void zc_interrupt_handler();

        // Set channel to level
        //
        // channel          Channel::min - Channel::max
        // level            Level::min - Level::max
        void set_channel_level(Channel::type channel, Level::type level);

        // Set channel to level
        //
        // channel          Channel::any, Channel::min - Channel::max
        // level            Level::min - Level::max
        void set_level(Channel::type channel, Level::type level)
        {
            if (channel == Channel::any) {
                for(Channel::type i = 0; i < Channel::size; i++) {
                    set_channel_level(i, level);
                }
            } else {
                set_channel_level(channel, level);
            }
        }

        // Change level from "from_level" to "to_level" within "time"
        //
        // channel          Channel::min - Channel::max
        // from_level       Level::current, Level::min - Level::max
        // to_level         Level::min - Level::max
        // time             time for fading from Level::min to Level::max in seconds
        //                  if absolute_time is set to true, the time is from_level to to_level
        void fade_channel_from_to(Channel::type channel, Level::type from_level, Level::type to_level, float time, bool absolute_time = false);

        // Change level from current level to "to_level" within "time"
        //
        // channel          Channel::min - Channel::max
        // to_level         Level::min - Level::max
        // time             time for fading from Level::min to Level::max in seconds
        inline void fade_channel_to(Channel::type channel, Level::type to_level, float time) {
            fade_channel_from_to(channel, Level::current, to_level, time, false);
        }

        // Change level for one or all channels from current level to "to_level" within "time"
        //
        // channel          Channel::any, Channel::min - Channel::max
        // from_level       Level::current, Level::min - Level::max
        // to_level         Level::min - Level::max
        // time             time for fading from Level::min to Level::max in seconds
        //                  if absolute_time is set to true, the time is from_level to to_level
        void fade_from_to(Channel::type channel, Level::type from_level, Level::type to_level, float time, bool absolute_time = false);

    //private:
        void _apply_fading();

        uint16_t _get_ticks(Channel::type channel, Level::type level);

        inline uint16_t _get_min_on_ticks(Channel::type channel)
        {
            if (_config.switch_on_count && _config.switch_on_minimum_ticks && on_counter[channel] < _config.switch_on_count) {
                return _config.switch_on_minimum_ticks;
            }
            return _config.minimum_on_time_ticks;
        }

        inline uint16_t _get_level(Channel::type channel) const
        {
            return level(channel);
        }

        inline void _set_level(Channel::type channel, Level::type level)
        {
            _register_mem.level[channel] = level;
        }

        inline Level::type _normalize_level(Level::type level)
        {
            if (level < Level::off) {
                return Level::off;
            }
            if (level > Level::max) {
                return Level::max;
            }
            return level;
        }

        void compare_a_interrupt();

        void _timer_setup();
        void _timer_remove();
        void _start_timer1();
        void _start_timer2();
        float _get_frequency();
        void _set_mosfet_gate(Channel::type channel, bool state);
        void _calculate_channels();
        void send_fading_completion_events();

    public:
        inline register_mem_cfg_t &config() {
            return _config;
        }

        inline uint16_t &level(Channel::type channel) {
            return _register_mem.level[channel];
        }

        inline uint16_t level(Channel::type channel) const {
            return _register_mem.level[channel];
        }

    private:
        register_mem_cfg_t &_config;
        register_mem_t &_register_mem;
    };

}

using dimmer_t = Dimmer::dimmer_t;

extern Dimmer::DimmerBase dimmer;

#define dimmer_config register_mem.data.cfg
