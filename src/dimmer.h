/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <util/atomic.h>
#include "timers.h"
#include "helpers.h"
#include "int24_types.h"
#include "dimmer_def.h"
#include "dimmer_protocol.h"
#include "dimmer_reg_mem.h"
#if HAVE_CHANNELS_INLINE_ASM
#    include "dimmer_inline_asm.h"
#endif

void remln(const __FlashStringHelper *str);

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

struct __attribute__((packed)) FadingCompletionEvent_t {
    dimmer_channel_id_t channel;
    dimmer_level_t level;
};

#if not HAVE_CHANNELS_INLINE_ASM
    extern volatile uint8_t *dimmer_pins_addr[::size_of(DIMMER_MOSFET_PINS)];
    extern uint8_t dimmer_pins_mask[::size_of(DIMMER_MOSFET_PINS)];
#endif

namespace Dimmer {

    using ChannelType = dimmer_channel_id_t;
    using ChannelStateType = dimmer_channel_t;
    using LevelType = dimmer_level_t;
    using TickType = uint16_t;
    using TickMultiplierType = uint32_t;
    #if DIMMER_MAX_CHANNELS > 8
        using StateType = uint16_t;
    #else
        using StateType = uint8_t;
    #endif

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
        static constexpr uint8_t __extraTicks = 54 / prescaler;
        static constexpr uint8_t extraTicks = __extraTicks < 6 ? 6 : __extraTicks;     // add __extraTicks clock cycles but at least 6
    };

    #ifdef DIMMER_TIMER2_PRESCALER
        template<>
        struct Timer<2> : Timers::TimerBase<2, DIMMER_TIMER2_PRESCALER> {
        };
    #endif

    // timer 1 using prescaler 1 to get the most precise mains frequency during the measurement cycle
    struct FrequencyTimer : Timers::TimerBase<1, 1> {
        static void begin();
    };

    inline void FrequencyTimer::begin() 
    {
        TimerBase::clear_counter();
        TimerBase::begin<kIntMaskOverflow>();
        TimerBase::clear_flags<kFlagsOverflow>();
    }

    // timer 2 running to prescaler 1 to predict the next zc crossing event
    struct MeasureTimer : Timers::TimerBase<2, 1> {

        using TickType = uint32_t;

        // start timer using the overflow interrupt
        void begin();
        // end timer
        void end();

        // get clock cycles
        // interrupts must be disabled when calling from outside an ISR
        TickType get_timer();

        volatile Dimmer::TickType _overflow;
    };

    inline void MeasureTimer::begin() 
    {
        TCNT2 = 0;
        TimerBase::begin<TimerBase::kIntMaskOverflow>();
        TimerBase::clear_flags<TimerBase::kFlagsOverflow>();
        // TCNT2 won't reach 256 while resetting the overflow, interrupts can be enabled
        _overflow = 0;
    }

    inline void MeasureTimer::end() 
    {
        TimerBase::end<TimerBase::kIntMaskOverflow>();
    }
    
    inline MeasureTimer::TickType MeasureTimer::get_timer() 
    {
        // similar to micros() but more precise depending on the MCU frequency
        auto tmp_overflow = _overflow;
        auto tmp_counter = TCNT2;
        if (TimerBase::get_flag<kFlagsOverflow>() && tmp_counter < 255) { 
            // we got an overflow during reading TCNT2
            tmp_overflow++;
        }
        return (tmp_counter | (static_cast<TickType>(tmp_overflow) << 8)) * TimerBase::prescaler;
    }

    struct Channel {
        using type = ChannelType;
        static constexpr type kSize = DIMMER_CHANNEL_COUNT;
        static constexpr type min = 0;
        static constexpr type max = kSize - 1;
        static constexpr type any = -1;
        static constexpr const uint8_t pins[kSize] = { DIMMER_MOSFET_PINS };

        static constexpr type size() {
            return kSize;
        }
    };

    struct Level {
        using type = LevelType;
        static constexpr type size = DIMMER_MAX_LEVEL;
        static constexpr type off = 0;
        static constexpr type min = 0;
        static constexpr type max = size;
        static constexpr type invalid = -1;
        static constexpr type current = -1;
        static constexpr type freeze = -1;
    };

    static constexpr float kZCFilterFrequencyDeviation = DIMMER_ZC_INTERVAL_MAX_DEVIATION;

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

    // do basic parameter checks
    static_assert(DIMMER_CHANNEL_COUNT == ::size_of(DIMMER_MOSFET_PINS), "channel count mismatch");
    static_assert(Channel::size() <= 16, "limited to 16 channels");
    static_assert(Channel::size() <= DIMMER_MAX_CHANNELS, "increase DIMMER_MAX_CHANNELS");
    static_assert(Level::size >= 255, "at least 255 levels required");
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
        Level::type levels_buffer[Channel::size()];                             // single buffer for levels since they are used only when the halfwave starts
        dimmer_fade_t fading[Channel::size()];                                  // calculated fading data
        #if DIMMER_MAX_CHANNELS > 1
            Channel::type channel_ptr;                                          // internal pointer used between interrupts
        #endif
        // for double bufferring. the calculation is done on the stack and copied into the first buffer
        // before the half wave starts the first buffer is copied into the second buffer, which is used inside the interrupts
        ChannelStateType ordered_channels[Channel::size() + 1];                 // current dimming levels in ticks, second buffer
        ChannelStateType ordered_channels_buffer[Channel::size() + 1];          // next dimming levels, first buffer
        TickType halfwave_ticks;
        StateType channel_state;                                                // bitset of the channel state
        volatile bool toggle_state;                                             // next state of the mosfets
        volatile bool calculate_channels_locked;

        #if ENABLE_ZC_PREDICTION
            // avg, min and max. clock cycles
            uint24_t halfwave_ticks_timer2;
            uint24_t halfwave_ticks_min;
            uint24_t halfwave_ticks_max;
            // last value to calculate difference
            uint24_t last_ticks;
            // keeps track if the frequency changes to adjust halfwave_ticks_timer2
            float halfwave_ticks_integral;
            dimmer_sync_event_t sync_event;
        #endif
        #if HAVE_FADE_COMPLETION_EVENT
            Level::type fading_completed[Channel::size()];
        #endif
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
        #if ENABLE_ZC_PREDICTION
            bool is_ticks_within_range(uint24_t ticks);
        #endif

        void set_frequency(float freq);
        void set_mode(ModeType mode);

        // Set channel to level
        //
        // channel          Channel::min - Channel::max
        // level            Level::min - Level::max
        // calc_channels    run _calculate_channels()
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
        void fade_channel_to(Channel::type channel, Level::type to_level, float time);

        // Change level for one or all channels from current level to "to_level" within "time"
        //
        // channel          Channel::any, Channel::min - Channel::max
        // from_level       Level::current, Level::min - Level::max
        // to_level         Level::min - Level::max
        // time             time for fading from Level::min to Level::max in seconds
        //                  if absolute_time is set to true, the time is from_level to to_level
        void fade_from_to(Channel::type channel, Level::type from_level, Level::type to_level, float time, bool absolute_time = false);

        //
        // send fading completion events for all channels
        //
        void send_fading_completion_events();

        //
        // apply fading (interrupts enabled) and calculate new levels
        // depending on the number of channels and cubic interpolation, this method can be slow when calling calls _calculate_channels()
        //
        void _apply_fading();

        TickType _get_ticks_per_halfwave() const;
        TickType __get_ticks(Channel::type channel, Level::type level) const;
        TickType _get_ticks(Channel::type channel, Level::type level);
        uint16_t _get_level(Channel::type channel) const;
        void _set_level(Channel::type channel, Level::type level);
        Level::type _normalize_level(Level::type level) const;

        void compare_interrupt();

        void _timer_setup();
        void _timer_remove();
        void _start_halfwave();
        void _delay_halfwave();
        float _get_frequency() const;

        #if HAVE_CHANNELS_INLINE_ASM
            inline void _set_all_mosfet_gates(bool state) {
                if (state) {
                    // if it fails to build here, run the build process again. the required include file is created automatically
                    DIMMER_SFR_ENABLE_ALL_CHANNELS();
                }
                else {
                    DIMMER_SFR_DISABLE_ALL_CHANNELS();
                }
            }
            inline void _set_mosfet_gate(Channel::type channel, bool state) {
                if (state) {
                    DIMMER_SFR_CHANNELS_ENABLE(channel);
                }
                else {
                    DIMMER_SFR_CHANNELS_DISABLE(channel);
                }
            }
        #else
            inline void _set_all_mosfet_gates(bool state) {
                DIMMER_CHANNEL_LOOP(i) {
                    _set_mosfet_gate(i, state);
                }
            }
            inline void _set_mosfet_gate(Channel::type channel, bool state) {
                if (state) {
                    *dimmer_pins_addr[channel] |= dimmer_pins_mask[channel];
                }
                else {
                    *dimmer_pins_addr[channel] &= ~dimmer_pins_mask[channel];
                }
            }
        #endif

        void _calculate_channels();
        static void _calc_halfwave_min_max(uint24_t ticks, uint24_t &hMin, uint24_t &hMax);

        register_mem_cfg_t &_config;
        register_mem_t &_register_mem;

        #if DEBUG_ZC_PREDICTION
            static constexpr uint8_t kTimeStorage = 16;
            struct {
                uint16_t zc_signals;
                uint16_t next_cycle;
                uint16_t valid_signals;
                uint16_t pred_signals;
                uint16_t start_halfwave;
                MeasureTimer::TickType last_time;
                MeasureTimer::TickType times[kTimeStorage];
                uint8_t pos;
            } debug_pred;
        #endif
    };

    inline void DimmerBase::set_frequency(float freq) 
    {
        register_mem.data.metrics.frequency = freq;
    }

    inline void DimmerBase::set_mode(ModeType mode) 
    {
        _config.bits.leading_edge = (mode == ModeType::LEADING_EDGE);
    }

    inline void DimmerBase::fade_channel_to(Channel::type channel, Level::type to_level, float time) 
    {
        fade_channel_from_to(channel, Level::current, to_level, time, false);
    }

    inline TickType DimmerBase::_get_ticks_per_halfwave() const 
    {
        return halfwave_ticks;
    }

    inline TickType DimmerBase::_get_ticks(Channel::type channel, Level::type level) 
    {
        return _config.bits.leading_edge ?
            (_get_ticks_per_halfwave() - __get_ticks(channel, level)) :
            __get_ticks(channel, level);
    }

    inline uint16_t DimmerBase::_get_level(Channel::type channel) const 
    {
        return _register_mem.channels.level[channel];
    }

    inline void DimmerBase::_set_level(Channel::type channel, Level::type level) 
    {
        _register_mem.channels.level[channel] = level;
    }

    inline Level::type DimmerBase::_normalize_level(Level::type level) const 
    {
        return std::clamp(level, Level::off, Level::max);
    }


    inline float DimmerBase::_get_frequency() const 
    {
        return register_mem.data.metrics.frequency;
    }

    #if ENABLE_ZC_PREDICTION
        inline bool DimmerBase::is_ticks_within_range(uint24_t ticks) 
        {
            // check if ticks is within the range
            // ticks is the clock cycles since the last
            return (ticks >= halfwave_ticks_min && ticks <= halfwave_ticks_max);
        }
    #endif

    // i2c response template
    template<uint8_t _Event>
    struct DimmerEvent {

        inline static void _send(const uint8_t *buffer, uint8_t length)
        {
            Wire.write(buffer, length);
            Wire.endTransmission();
        }

        template<typename _Type>
        static void send(const _Type &data, uint8_t length)
        {
            Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
            Wire.write(_Event);
            _send(reinterpret_cast<const uint8_t *>(&data), length);
        }

        template<typename _Type>
        static void send(const _Type &data)
        {
            Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
            Wire.write(_Event);
            _send(reinterpret_cast<const uint8_t *>(&data), static_cast<uint8_t>(sizeof(data)));
        }

        template<typename _Type>
        static void send(const uint8_t extraByte, const _Type &data)
        {
            Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
            Wire.write(_Event);
            Wire.write(extraByte);
            _send(reinterpret_cast<const uint8_t *>(&data), static_cast<uint8_t>(sizeof(data)));
        }
    };

}


using dimmer_t = Dimmer::dimmer_t;

extern Dimmer::DimmerBase dimmer;
