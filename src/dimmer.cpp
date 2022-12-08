/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"
#include "dimmer.h"
#include "measure_frequency.h"
#include "i2c_slave.h"

#include <string.h>
#include <stdlib.h>
#include <avr/io.h>

// old debug code

// #define PIN_D2_SET()                                    asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (2))
// #define PIN_D2_CLEAR()                                  asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (2))
// #define PIN_D2_TOGGLE()                                 asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PIND)), "I" (2))
// #define PIN_D2_IS_SET()                                 ((_SFR_IO_ADDR(PIND) & _BV(2)) != 0)
// #define PIN_D2_IS_CLEAR()                               ((_SFR_IO_ADDR(PIND) & _BV(2)) == 0)

// #define PIN_D8_SET()                                    asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (0))
// #define PIN_D8_CLEAR()                                  asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (0))
// #define PIN_D8_TOGGLE()                                 asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PINB)), "I" (0))
// #define PIN_D8_IS_SET()                                 ((_SFR_IO_ADDR(PINB) & _BV(0)) != 0)
// #define PIN_D8_IS_CLEAR()                               ((_SFR_IO_ADDR(PINB) & _BV(0)) == 0)

// #define PIN_D11_SET()                                   asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (3))
// #define PIN_D11_CLEAR()                                 asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (3))
// #define PIN_D11_TOGGLE()                                asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PINB)), "I" (3))
// #define PIN_D11_IS_SET()                                ((_SFR_IO_ADDR(PINB) & _BV(3)) != 0)
// #define PIN_D11_IS_CLEAR()                              ((_SFR_IO_ADDR(PINB) & _BV(3)) == 0)

using namespace Dimmer;

DimmerBase dimmer(register_mem.data);
constexpr const uint8_t Dimmer::Channel::pins[Dimmer::Channel::size()];

#if not HAVE_CHANNELS_INLINE_ASM
volatile uint8_t *dimmer_pins_addr[Channel::size()];
uint8_t dimmer_pins_mask[Channel::size()];

#else

#if __AVR_ATmega328P__
static constexpr uint8_t kDimmerSignature[] = { 0x1e, 0x95, 0x0f, DIMMER_MOSFET_PINS };
#else
#error signature not defined
#endif

static constexpr int __memcmp(const uint8_t a[], const uint8_t b[], size_t len) {
    return *a != *b ? -1 : len == 1 ? 0 : __memcmp(&a[1], &b[1], len - 1);
}
static_assert(sizeof(kInlineAssemblerSignature) == sizeof(kDimmerSignature), "invalid signature");
static_assert(__memcmp(kInlineAssemblerSignature, kDimmerSignature, sizeof(kDimmerSignature)) == 0, "invalid signature");

#endif

// start halfwave
ISR(TIMER1_COMPA_vect)
{
    dimmer.compare_interrupt();
}

// delayed start
ISR(TIMER1_COMPB_vect)
{
    dimmer._start_halfwave();
}

// measure timer overflow interrupt
MeasureTimer timer2;

ISR(TIMER2_OVF_vect)
{
    timer2._overflow++;
    #if HAVE_FADE_COMPLETION_EVENT
        if (queues.fading_completed_events.timer > 0) {
            queues.fading_completed_events.timer--;
        }
    #endif
    if (queues.check_temperature.timer > 0) {
        queues.check_temperature.timer--;
    }
    #if ENABLE_ZC_PREDICTION
        // send artificial event in case the event is not received within the range
        // in case the zero crossing fire already, the event is ignored
        auto ticks = timer2.get_no_cli();
        if (ticks > dimmer.halfwave_ticks_prescaler1) {
            dimmer.zc_interrupt_handler(ticks);
        }
    #endif
}

void DimmerBase::begin()
{
    if (!Dimmer::isValidFrequency(register_mem.data.metrics.frequency)) {
        return;
    }
    halfwave_ticks = ((F_CPU / Timer<1>::prescaler / 2.0) / register_mem.data.metrics.frequency);
    #if ENABLE_ZC_PREDICTION
        halfwave_ticks_prescaler1 = ((F_CPU / 2.0) / register_mem.data.metrics.frequency);
        FrequencyMeasurement::_calc_halfwave_min_max(halfwave_ticks_prescaler1, halfwave_ticks_min, halfwave_ticks_max);
        sync_event = { 0 , Timer<1>::ticksToMicros(halfwave_ticks_prescaler1) };
    #endif

    queues.scheduled_calls = {};

    toggle_state = DIMMER_MOSFET_OFF_STATE;

    DIMMER_CHANNEL_LOOP(i) {
        #if !HAVE_CHANNELS_INLINE_ASM
                dimmer_pins_mask[i] = digitalPinToBitMask(Channel::pins[i]);
                dimmer_pins_addr[i] = portOutputRegister(digitalPinToPort(Channel::pins[i]));
                _D(5, debug_printf("ch=%u pin=%u addr=%02x mask=%02x\n", i, Channel::pins[i], dimmer_pins_addr[i], dimmer_pins_mask[i]));
        #else
                _D(5, debug_printf("ch=%u pin=%u\n", i, Channel::pins[i]));
        #endif
        #if HAVE_FADE_COMPLETION_EVENT
                fading_completed[i] = Level::invalid;
        #endif
        digitalWrite(Channel::pins[i], DIMMER_MOSFET_OFF_STATE);
        pinMode(Channel::pins[i], OUTPUT);
    }

    cli();
    timer2.begin(); // timer2 runs at clock speed 
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), []() {

        uint24_t ticks = timer2.get_clear_no_cli(); // this is not used with ENABLE_ZC_PREDICTION disabled
        dimmer.zc_interrupt_handler(ticks);
        
    }, DIMMER_ZC_INTERRUPT_MODE);

    _D(5, debug_printf("starting timer\n"));
    Timer<1>::begin<Timer<1>::kIntMaskAll, nullptr>();
    sei();
}

void DimmerBase::end()
{
    if (register_mem.data.metrics.frequency == 0 || isnan(register_mem.data.metrics.frequency)) {
        return;
    }
    _D(5, debug_printf("ending timer...\n"));

    queues.scheduled_calls = {};

    cli();
    detachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN));
    Timer<1>::end();
    DIMMER_CHANNEL_LOOP(i) {
        digitalWrite(Channel::pins[i], DIMMER_MOSFET_OFF_STATE);
        pinMode(Channel::pins[i], INPUT);
    }
    timer2.end();
    sei();
}

void DimmerBase::zc_interrupt_handler(uint24_t ticks)
{
    #if ENABLE_ZC_PREDICTION
        // check if the ticks since the last call are in range
        if (!is_ticks_within_range(ticks)) {
            // invalid signal
            sync_event.invalid_signals++;
            return;
        }
        // the signal seems valid, reset counter
        sync_event.invalid_signals = 0;
    #endif

    // enable timer for delayed zero crossing
    Timer<1>::int_mask_enable<Timer<1>::kIntMaskCompareB>();
    OCR1B = dimmer_config.zero_crossing_delay_ticks;
    OCR1B += TCNT1;
    Timer<1>::clear_flags<Timer<1>::kFlagsCompareB>();

    sei();

    _apply_fading();

    _D(10, Serial.println(F("zc int")));
}

#if ENABLE_ZC_PREDICTION
    bool DimmerBase::is_ticks_within_range(uint24_t ticks) 
    {
        // check if ticks is within the range
        // ticks is the clock cycles since the last
        return (ticks >= halfwave_ticks_min && ticks <= halfwave_ticks_max);
    }
#endif

// turn mosfets for active channels on
void DimmerBase::_start_halfwave()
{
    // copying the data and checking if the signal is valid has a fixed number of clock cycles and can be 
    // compensated by the zero crossing delay during calibration

    #if ENABLE_ZC_PREDICTION
        // increase counter for an invalid signal. the counter is reset somewhere else
        // at this point the signal might be invalid or not
        if (++sync_event.invalid_signals >= DIMMER_OUT_OF_SYNC_LIMIT) {
            Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareAB>();
            end();
            // store counter and send event. dimmer needs to be reset to continue
            queues.scheduled_calls.sync_event = true;
            return;
        }
    #endif

    // double buffering makes sure that the levels stay the same during one half cycle even if they are modified between interrupts
    memcpy(ordered_channels, ordered_channels_buffer, sizeof(ordered_channels));

    // reset timer for the halfwave
    TCNT1 = 0;
    // next dimming event
    OCR1A = 0;
    // next predicted zero crossing event
    OCR1B = halfwave_ticks;
    // clear any pending interrupts
    Timer<1>::clear_flags<Timer<1>::kFlagsCompareAB>();

    toggle_state = _config.bits.leading_edge ? DIMMER_MOSFET_OFF_STATE : DIMMER_MOSFET_ON_STATE;

    #if DIMMER_MAX_CHANNELS > 1
        channel_ptr = 0;
    #endif

    // switch channels on in prioritized order
    OCR1A = ordered_channels[0].ticks;
    for(Channel::type i = 0; ordered_channels[i].ticks; i++) {
        _set_mosfet_gate(ordered_channels[i].channel, toggle_state);
    }

    // channels that are fully on or off
    DIMMER_CHANNEL_LOOP(i) {
        // those 2 states usually do not change every halfwave and have a lower priority
        if (levels_buffer[i] == Level::off) {
            _set_mosfet_gate(i, !toggle_state);
        }
        else if (levels_buffer[i] >= Level::max) {
            _set_mosfet_gate(i, toggle_state);
        }
    }
    // toggle state for the compare a interrupt
    toggle_state = !toggle_state;

    #if ENABLE_ZC_PREDICTION
        Timer<1>::int_mask_enable<Timer<1>::kIntMaskCompareB>();
    #else
        Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareB>();
    #endif

    if (ordered_channels[0].ticks && ordered_channels[0].ticks <= Dimmer::TickTypeMax) { // any channel dimmed?
        // run compare a interrupt to switch MOSFETs
        Timer<1>::int_mask_enable<Timer<1>::kIntMaskCompareA>();
    }
    else {
        // nothing to do this halfwave, make sure compare a does not run
        Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareA>();
    }
}

void DimmerBase::compare_interrupt()
{
    #if DIMMER_MAX_CHANNELS == 1

        _set_mosfet_gate(ordered_channels[0].channel, toggle_state);
        Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareA>();

    #else
        // this code needs to run as fast as possible
        ChannelStateType *channel = &ordered_channels[channel_ptr++];
        ChannelStateType *next_channel = channel;
        ++next_channel;
        for(;;) {
            _set_mosfet_gate(channel->channel, toggle_state);    // toggle current channel

            if (next_channel->ticks == 0) {
                // no more channels to change, disable compare a interrupt
                Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareA>();
                break;
            }
            else if (next_channel->ticks > channel->ticks) {
                // next channel has a different time slot, re-schedule
                OCR1A = std::max<uint16_t>(TCNT1 + Dimmer::Timer<1>::extraTicks, next_channel->ticks);  // make sure to trigger an interrupt even if the time slot is in the past by using TCNT1 + 1 as minimum
                break;
            }
            // next channel that is on
            channel = next_channel;
            channel_ptr++;
            next_channel++;
        }
    #endif
}

static inline void dimmer_bubble_sort(ChannelStateType channels[], Channel::type count)
{
   Channel::type i, j;
   if (count >= 2) {
        count--;
        for (i = 0; i < count; i++) {
            for (j = 0; j < count - i; j++)   {
                if (channels[j].ticks > channels[j + 1].ticks) {
                    swap<ChannelStateType>(channels[j], channels[j + 1]);
                }
            }
        }
   }
}

// copy data from register memory to buffers
// calculate ticks for each channel and sort them
// channels that are off or fully on won't be added
void DimmerBase::_calculate_channels()
{
    ChannelStateType ordered_channels_tmp[Channel::size() + 1];
    Channel::type count = 0;
    StateType new_channel_state = 0;

    // copy levels from register memory
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        memcpy(levels_buffer, _register_mem.channels.level, sizeof(levels_buffer));
    }

    DIMMER_CHANNEL_LOOP(i) {
        auto level = DIMMER_LINEAR_LEVEL(levels_buffer[i], i);
        if (level >= Level::max) {
            new_channel_state |= (1 << i);
        }
        else if (level > Level::off) {
            new_channel_state |= (1 << i);
            ordered_channels_tmp[count].ticks = _get_ticks(i, level); // this always returns the min, number of ticks
            ordered_channels_tmp[count].channel = i;
            count++;
        }
    }
    ordered_channels_tmp[count] = {}; // end marker

    #if DIMMER_MAX_CHANNELS > 1
        dimmer_bubble_sort(ordered_channels_tmp, count);
    #endif

    // copy double buffer with interrupts disabled
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        if (new_channel_state != channel_state) {
            channel_state = new_channel_state;
            queues.scheduled_calls.send_channel_state = true;
        }
        memcpy(ordered_channels_buffer, ordered_channels_tmp, sizeof(ordered_channels_buffer));
    }
}

void DimmerBase::set_channel_level(ChannelType channel, Level::type level, bool calc_channels)
{
    // _D(5, debug_printf("set_channel_level ch=%d level=%d\n", channel, level))
    _set_level(channel, _normalize_level(level));

    fading[channel].count = 0; // disable fading for this channel
    #if HAVE_FADE_COMPLETION_EVENT
        if (fading_completed[channel] != Level::invalid) {
            // send event with the new level
            fading_completed[channel] = _get_level(channel);
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                queues.scheduled_calls.send_fading_events = true;
                queues.fading_completed_events.resetTimer();
            }
        }
    #endif

    if (calc_channels) {
        _calculate_channels();
    }

    _D(5, debug_printf("ch=%u level=%u ticks=%u zcdelay=%u\n", channel, _get_level(channel), _get_ticks(channel, level), _config.zero_crossing_delay_ticks));
}

void DimmerBase::set_level(Channel::type channel, Level::type level)
{
    // _D(5, debug_printf("set_level ch=%d level=%d\n", channel, level))
    if (channel == Channel::any) {
        DIMMER_CHANNEL_LOOP(i) {
            set_channel_level(i, level, false);
        }
        _calculate_channels();
    } 
    else {
        set_channel_level(channel, level);
    }
}

void DimmerBase::fade_channel_from_to(ChannelType channel, Level::type from, Level::type to, float time, bool absolute_time)
{
    float diff;
    dimmer_fade_t &fade = fading[channel];
    #if HAVE_FADE_COMPLETION_EVENT
        fading_completed[channel] = Level::invalid;
    #endif

    _D(5, debug_printf("fade_channel_from_to from=%d to=%d time=%f\n", from, to, time));

    // get real level not what is stored in the register memory
    Level::type current_level;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        current_level = levels_buffer[channel];
    }

    // stop fading at current level
    if (to == Level::freeze) {
        if (fade.count == 0) {
            // fading not in progress
            return;
        }
        fade.count = 1;
        fade.step = 0; // keep current level
        fade.level = _normalize_level(current_level);
        fade.targetLevel = fade.level;
        // make sure the level is stored
        set_channel_level(channel, fade.targetLevel, false);
        return;
    }

    from = _normalize_level(from == Level::current ? current_level : from);
    diff = _normalize_level(to) - from;
    if (diff == 0) {
        _D(5, debug_printf("fade normalized -> from=%d to=%d\n", from, to));
        // make sure the level is stored
        set_channel_level(channel, to, false);
        return;
    }

    if (!absolute_time) { // calculate relative fading time depending on "diff"
        time = abs(diff / Level::size * time);
        _D(5, debug_printf("Relative fading time %.3f\n", time));
    }

    fade.count = register_mem.data.metrics.frequency * time * 2.0;
    if (fade.count == 0) {
        _D(5, debug_printf("count=%u time=%f\n", fade.count, time));
        // make sure the level is stored
        set_channel_level(channel, to, false);
        return;
    }
    fade.step = diff / static_cast<float>(fade.count);
    fade.level = from;
    fade.targetLevel = to;

    if (fade.count < 1 || fade.step == 0) { // time too short, force to run fading anyway = basically turns the channel on and sends events
        fade.count = 1;
    }

    _D(5, debug_printf("fading ch=%u from=%d to=%d, step=%f count=%u\n", channel, from, to, fade.step, fade.count));
}

void DimmerBase::fade_from_to(Channel::type channel, Level::type from_level, Level::type to_level, float time, bool absolute_time)
{
    _D(5, debug_printf("fade_from_to ch=%d from=%d to=%d time=%f\n", channel, from_level, to_level, time))
    if (channel == Channel::any) {
        DIMMER_CHANNEL_LOOP(i) {
            fade_channel_from_to(i, from_level, to_level, time, absolute_time);
        }
    }
    else {
        fade_channel_from_to(channel, from_level, to_level, time, absolute_time);
    }
}

void DimmerBase::_apply_fading()
{
    DIMMER_CHANNEL_LOOP(i) {
        dimmer_fade_t &fade = fading[i];
        if (fade.count) {
            fade.level += fade.step;
            if (--fade.count == 0) {
                _set_level(i, fade.targetLevel);
                #if HAVE_FADE_COMPLETION_EVENT
                    fading_completed[i] = _get_level(i);
                    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                        queues.scheduled_calls.send_fading_events = true;
                        queues.fading_completed_events.resetTimer();
                    }
                #endif
            } 
            else {
                _set_level(i, fade.level);
            }
            #if DEBUG
                if (fade.count % 60 == 0) {
                    _D(5, debug_printf("fading ch=%u lvl=%u ticks=%u\n", i, _get_level(i), _get_ticks(i, _get_level(i))));
                }
            #endif
        }
    }

    _calculate_channels();
}

TickType DimmerBase::__get_ticks(Channel::type channel, Level::type level) const
{
    auto halfWaveTicks = _get_ticks_per_halfwave();
    TickType rangeTicks = halfWaveTicks - _config.minimum_on_time_ticks - _config.minimum_off_time_ticks;
    TickType ticks;

    if (_config.range_divider == 0) {
        ticks = ((TickMultiplierType)rangeTicks * level) / Level::max;
    }
    else {
        ticks = ((TickMultiplierType)rangeTicks * (level + _config.range_begin)) / _config.range_divider;
    }
    ticks += _config.minimum_on_time_ticks;

    return std::clamp<uint16_t>(ticks, _config.minimum_on_time_ticks, halfWaveTicks - _config.minimum_off_time_ticks);
}
