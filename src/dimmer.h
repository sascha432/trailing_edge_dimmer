/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include "timers.h"
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
    uint8_t state;
    uint16_t ticks;
};

typedef struct __attribute__((packed)) {
    dimmer_channel_id_t channel;
    dimmer_level_t level;
} FadingCompletionEvent_t;

namespace Dimmer {

    using ChannelType = dimmer_channel_id_t;
    using ChannelStateType = dimmer_channel_t;
    using LevelType = dimmer_level_t;
    using TickType = uint16_t;
    using TickMultiplierType = uint32_t;

    enum class ModeType {
        TRAILING_EDGE,
        LEADING_EDGE
    };

    static constexpr long LevelTypeMin = static_cast<LevelType>(1UL << ((sizeof(LevelType) << 3) - 1));
    static constexpr long LevelTypeMax = (1UL << ((sizeof(LevelType) << 3) - 1));
    static constexpr TickType TickTypeMin = 0;
    static constexpr TickType TickTypeMax = ~0;
    static constexpr float kVRef = INTERNAL_VREF_1_1V;


    template<int _Timer>
    struct Timer {};

    template<>
    struct Timer<1> : Timers::TimerBase<1, DIMMER_TIMER1_PRESCALER> {
        static constexpr uint8_t __extraTicks = 48 / prescaler;
        static constexpr uint8_t extraTicks = __extraTicks == 0 ? 1 : __extraTicks;     // add 48 clock cycles but at least one tick
    };

#ifdef DIMMER_TIMER2_PRESCALER
    template<>
    struct Timer<2> : Timers::TimerBase<2, DIMMER_TIMER2_PRESCALER> {
    };
#endif

    struct FrequencyTimer : Timers::TimerBase<1, 1> {
        static inline void begin() {
            TimerBase::begin<kIntMaskOverflow>();
        }
    };

    struct MeasureTimer : Timers::TimerBase<2, 1> {
        inline void begin() {
            TimerBase::begin<TimerBase::kFlagsOverflow>();
        }
        inline void end() {
            TimerBase::end<TimerBase::kFlagsOverflow>();
        }
        inline void start() {
            TimerBase::int_mask_enable<kIntMaskOverflow>();
        }
        inline void stop() {
            TimerBase::int_mask_enable<kIntMaskOverflow>();
        }
        inline void reset() {
            TCNT2 = 0;
            TimerBase::clear_flags<TimerBase::kFlagsOverflow>();
            _overflow = 0;
        }
        inline uint24_t get() {
            uint8_t oldSREG = SREG;
            cli();
            uint8_t tmp = TCNT2;
            if (TimerBase::get_clear_flag<kFlagsOverflow>()) {
                _overflow++;
            }
            uint16_t tmp2 = _overflow;
            SREG = oldSREG;
            return ((uint24_t)tmp2 << 8) | tmp;
        }
        inline uint24_t get_no_cli() {
            uint8_t tmp = TCNT2;
            if (TimerBase::get_clear_flag<kFlagsOverflow>()) {
                _overflow++;
            }
            return ((uint24_t)_overflow << 8) | tmp;
        }
        inline uint24_t get_clear_no_cli() {
            uint8_t tmp = TCNT2;
            TCNT2 = 0;
            if (TimerBase::get_clear_flag<kFlagsOverflow>()) {
                _overflow++;
            }
            auto tmp2 = ((uint24_t)_overflow << 8) | tmp;
            _overflow = 0;
            return tmp2;
        }

        uint16_t _overflow;
    };

    struct Channel {
        using type = ChannelType;
        static constexpr type kSize = ::size_of(DIMMER_MOSFET_PINS);
        static constexpr type min = 0;
        static constexpr type max = kSize - 1;
        static constexpr type any = -1;
        static constexpr const uint8_t pins[kSize] = { DIMMER_MOSFET_PINS };

        static constexpr type size() {
            return kSize;
        }
    };

    static_assert(Channel::size() <= 8, "limited to 8 channels");
    static_assert(Channel::size() <= DIMMER_MAX_CHANNELS, "increase DIMMER_MAX_CHANNELS");

    struct Level {
        using type = LevelType;
        static constexpr type size = DIMMER_MAX_LEVEL;
        static constexpr type off = 0;
        static constexpr type min = 0;
        static constexpr type max = size;
        static constexpr type invalid = -1;
        static constexpr type current = -1;
    };

    static_assert(Level::size >= 255, "at least 255 levels required");

    // filter all zc interrupts that occur fastere than (frequency + kZCFilterFrequency)
    static constexpr int8_t kZCFilterFrequency = -5;

    static constexpr uint8_t kMinFrequency = 48;
    static constexpr uint8_t kMaxFrequency = 62;

    static constexpr uint16_t kMinMicrosPerHalfWave = (1000000 / (kMaxFrequency * 2.0));
    static constexpr uint16_t kMaxMicrosPerHalfWave = (1000000 / (kMinFrequency * 2.0));

    static constexpr TickMultiplierType kMinCyclesPerHalfWave = (F_CPU / (kMaxFrequency * 2));
    static constexpr TickMultiplierType kMaxCyclesPerHalfWave = (F_CPU / (kMinFrequency * 2));

    static constexpr TickType kMinTicksPerHalfWave = kMinCyclesPerHalfWave / Timer<1>::prescaler;
    static constexpr TickType kMaxTicksPerHalfWave = kMaxCyclesPerHalfWave / Timer<1>::prescaler;

    static_assert((F_CPU / Timer<1>::prescaler / (kMinFrequency * 2)) < TickTypeMax, "adjust timer 1 prescaler");

    static constexpr uint8_t kOnSwitchCounterMax = 0xfe;

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
        Level::type level[Channel::size()];                                     // current level
        dimmer_fade_t fading[Channel::size()];                                  // calculated fading data
#if DIMMER_MAX_CHANNELS > 1
        Channel::type channel_ptr;
#endif
        dimmer_channel_t ordered_channels[Channel::size() + 1];                 // current dimming levels in ticks
        dimmer_channel_t ordered_channels_buffer[Channel::size() + 1];          // next dimming levels
        uint8_t on_counter[Channel::size()];                                    // counts halfwaves from 0 to 254 after switching on
        TickType halfwave_ticks;
        float zc_diff_ticks;
        uint8_t zc_diff_count;
        float frequency;
        uint8_t channel_state;                                                  // bitset of the channel state
        bool toggle_state: 1;
#if HAVE_DISABLE_ZC_SYNC
        bool zc_sync_disabled: 1;
#endif

#if DIMMER_OUT_OF_SYNC_LIMIT
        uint16_t out_of_sync_counter;
        dimmer_sync_event_t sync_event;
#endif

#if HAVE_FADE_COMPLETION_EVENT
        Level::type fading_completed[Channel::size()];
#endif
        float halfwave_ticks_avg;
        float halfwave_ticks_avg2;
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
        void zc_interrupt_handler(uint24_t ticks);

        inline void set_frequency(float freq) {
            frequency = freq;
        }

        inline void set_mode(ModeType mode) {
            _config.bits.leading_edge = (mode == ModeType::LEADING_EDGE);
        }

        // Set channel to level
        //
        // channel          Channel::min - Channel::max
        // level            Level::min - Level::max
        void set_channel_level(Channel::type channel, Level::type level);

        // Set channel to level
        //
        // channel          Channel::any, Channel::min - Channel::max
        // level            Level::min - Level::max
        void set_level(Channel::type channel, Level::type level);

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

        //
        // send fading complention events for all channels
        //
        void send_fading_completion_events();

        void _apply_fading();

        inline TickType _get_ticks_per_halfwave() const {
            return halfwave_ticks;
        }

        TickType __get_ticks(Channel::type channel, Level::type level) const;

        inline TickType _get_ticks(Channel::type channel, Level::type level) {
            return _config.bits.leading_edge ?
                (_get_ticks_per_halfwave() - __get_ticks(channel, level)) :
                __get_ticks(channel, level);
        }

        inline TickType _get_min_on_ticks(Channel::type channel) const {
            if (_config.switch_on_count && _config.switch_on_minimum_ticks && (on_counter[channel] < kOnSwitchCounterMax) && (on_counter[channel] < _config.switch_on_count - 1)) {
                return _config.switch_on_minimum_ticks;
            }
            return _config.minimum_on_time_ticks;
        }

        inline uint16_t _get_level(Channel::type channel) const {
            return _register_mem.level[channel];
        }

        inline void _set_level(Channel::type channel, Level::type level) {
            _register_mem.level[channel] = level;
        }

        inline Level::type _normalize_level(Level::type level) const {
            if (level < Level::off) {
                return Level::off;
            }
            if (level > Level::max) {
                return Level::max;
            }
            return level;
        }

        void compare_interrupt();

        void _timer_setup();
        void _timer_remove();
        void _start_halfwave();
        void _delay_halfwave();
        inline float _get_frequency() const {
            return frequency;
        }
        void _set_mosfet_gate(Channel::type channel, bool state);
        void _calculate_channels();

        register_mem_cfg_t &_config;
        register_mem_t &_register_mem;
    };

}

using dimmer_t = Dimmer::dimmer_t;

extern Dimmer::DimmerBase dimmer;

#define dimmer_config register_mem.data.cfg
