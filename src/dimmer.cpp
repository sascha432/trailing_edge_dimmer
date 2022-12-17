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

using namespace Dimmer;

DimmerBase dimmer(register_mem.data);
constexpr const uint8_t Dimmer::Channel::pins[Channel::size()];

#if not HAVE_CHANNELS_INLINE_ASM

    volatile uint8_t *dimmer_pins_addr[Channel::size()];
    uint8_t dimmer_pins_mask[Channel::size()];

#else

#    if __AVR_ATmega328P__
        static constexpr uint8_t kDimmerSignature[] = { 0x1e, 0x95, 0x0f, DIMMER_MOSFET_PINS };
#    else
#        error signature not defined
#   endif

    static constexpr int __memcmp(const uint8_t a[], const uint8_t b[], size_t len) {
        return *a != *b ? -1 : len == 1 ? 0 : __memcmp(&a[1], &b[1], len - 1);
    }
    static_assert(sizeof(kInlineAssemblerSignature) == sizeof(kDimmerSignature), "invalid signature");
    static_assert(__memcmp(kInlineAssemblerSignature, kDimmerSignature, sizeof(kDimmerSignature)) == 0, "invalid signature");

#endif

// compare a is used for switching the mosfets
ISR(TIMER1_COMPA_vect)
{
    dimmer.compare_interrupt();
}

// compare b is used for the delayed start
ISR(TIMER1_COMPB_vect)
{
    dimmer._start_halfwave();
}

// measure timer overflow interrupt
MeasureTimer timer2;

// timer 2 overflow is used as counter to trigger events and generate the artificial
// zc event if prediction is enabled
ISR(TIMER2_OVF_vect)
{
    timer2._overflow++;
    // the artificial zc event is sent 10 microseconds earlier, so this code can be executed before
    #if HAVE_FADE_COMPLETION_EVENT
        if (queues.fading_completed_events.timer > 0) {
            queues.fading_completed_events.timer--;
        }
    #endif
    if (queues.check_temperature.timer > 0) {
        queues.check_temperature.timer--;
    }
    #if ENABLE_ZC_PREDICTION && 0
        // send artificial event in case the event is not received within the range
        // in case the zero crossing overlaps with this event, the event is filtered
        auto ticks = timer2.get_timer();
        if (ticks >= dimmer.halfwave_ticks_timer2) {
            dimmer.zc_interrupt_handler(ticks);
            dimmer.debug_pred.pred_signals++;
        }
    #endif
}

void DimmerBase::begin()
{
    #if DEBUG_ZC_PREDICTION
        Serial.printf_P(PSTR("+REM=pstart(%f)\n"), register_mem.data.metrics.frequency);
    #endif
    if (!isValidFrequency(register_mem.data.metrics.frequency)) {
        return;
    }
    halfwave_ticks = ((F_CPU / Timer<1>::prescaler / 2.0) / register_mem.data.metrics.frequency);
    #if ENABLE_ZC_PREDICTION
        // calculate clock cycles for timer2 that executes the prediction
        halfwave_ticks_timer2 = ((F_CPU / 2.0) / register_mem.data.metrics.frequency);
        halfwave_ticks_integral = halfwave_ticks_timer2;
        FrequencyMeasurement::_calc_halfwave_min_max(halfwave_ticks_timer2, halfwave_ticks_min, halfwave_ticks_max);
        sync_event = { 0 , Timer<1>::ticksToMicros(halfwave_ticks) /* reports only the frequency during startup or restart */ };
    #endif

    #if DEBUG_ZC_PREDICTION
        Serial.printf_P(PSTR("+REM=%uus,r=%ld-%ld:%ld\n"), sync_event.halfwave_micros, (long)halfwave_ticks_min, (long)halfwave_ticks_max, (long)halfwave_ticks_timer2);
        Serial.flush();
    #endif

   queues.scheduled_calls = {};
    #if DIMMER_USE_QUEUE_LEVELS
        queues.levels = {};
    #endif

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

    #if DEBUG_ZC_PREDICTION
        debug_pred = {};
    #endif

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        // timer2 runs at clock speed 
        timer2.begin(); 
        // the order here is not so important, the first ZC event will be filtered if prediction is enabled
        attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), []() {

            dimmer.zc_interrupt_handler(
                #if ENABLE_ZC_PREDICTION
                    // get clock cycles since last event to filter invalid signals
                    timer2.get_timer()
                #else
                    0
                #endif
            );            
            #if DEBUG_ZC_PREDICTION
                dimmer.debug_pred.zc_signals++;
            #endif
            
        }, DIMMER_ZC_INTERRUPT_MODE);

        _D(5, debug_printf("starting timer\n"));
        Timer<1>::begin<Timer<1>::kIntMaskAll, nullptr>();
    }
}

void DimmerBase::end()
{
    _D(5, debug_printf("ending timer...\n"));

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        queues.scheduled_calls = {};
        #if DIMMER_USE_QUEUE_LEVELS
            queues.levels = {};
        #endif

        detachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN));
        Timer<1>::end();
        DIMMER_CHANNEL_LOOP(i) {
            digitalWrite(Channel::pins[i], DIMMER_MOSFET_OFF_STATE);
            pinMode(Channel::pins[i], INPUT);
        }
        timer2.end();
    }

    #if DEBUG_ZC_PREDICTION
        Serial.println(F("+REM=pend"));
    #endif
}

void DimmerBase::zc_interrupt_handler(uint24_t ticks)
{
    #if ENABLE_ZC_PREDICTION
        // get clock cycles since last call of this method
        auto dur = ticks - last_ticks;
        last_ticks = ticks;

        // check if the ticks since the last call are in range
        if (!is_ticks_within_range(dur)) {
            // invalid signal
            sync_event.invalid_signals++;

            #if DEBUG_ZC_PREDICTION
                debug_pred.times[debug_pred.pos++] = -dur;
                if (debug_pred.pos >= kTimeStorage) {
                    debug_pred.pos = 0;
                }
            #endif

            return;
        }
        // the signal seems valid, reset counter
        sync_event.invalid_signals = 0;
    #endif

    // enable timer for delayed zero crossing
    Timer<1>::int_mask_enable<Timer<1>::kIntMaskCompareB>();
    OCR1B = register_mem.data.cfg.zero_crossing_delay_ticks;
    // assume that this operation takes at least 6 clock cycles including clearing the compare event
    OCR1B += ((6 + (Timer<1>::prescaler - 1)) / Timer<1>::prescaler);
    OCR1B += TCNT1;
    // clear any pending events
    Timer<1>::clear_flags<Timer<1>::kFlagsCompareB>();

    sei();
    
    // apply fading with interrupts enabled
    _apply_fading();

    _D(10, Serial.println(F("zc int")));
}

// turn mosfets for active channels on
void DimmerBase::_start_halfwave()
{
    // copying the data and checking if the signal is valid has a fixed number of clock cycles and can be 
    // compensated by the zero crossing delay during calibration

    #if DEBUG_ZC_PREDICTION
        auto t = timer2.get_timer();
        debug_pred.times[debug_pred.pos++ % kTimeStorage] = t - debug_pred.last_time;
        debug_pred.last_time = t;
        debug_pred.start_halfwave++;
    #endif

    #if ENABLE_ZC_PREDICTION
        // increase counter for an invalid signal. the counter is reset in the zc crossing handler to avoid any delay here doing more calculations
        if (++sync_event.invalid_signals >= DIMMER_OUT_OF_SYNC_LIMIT) {
            Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareAB>();
            end();
            // store counter and send event. dimmer needs to be reset to continue safely
            queues.scheduled_calls.sync_event = true;
            return;
        }
    #endif

    #if DEBUG_ZC_PREDICTION
        debug_pred.valid_signals++;
    #endif

    // double buffering makes sure that the levels stay the same during a single half cycle even if they are modified between interrupts
    // _apply_fading() and _calculate_channels() is asynchronous
    memcpy(ordered_channels, ordered_channels_buffer, sizeof(ordered_channels));

    // reset timer for the halfwave
    TCNT1 = 0;
    // next dimming event
    OCR1A = 0;
    Timer<1>::clear_flags<Timer<1>::kFlagsCompareA>();

    toggle_state = _config.bits.leading_edge ? DIMMER_MOSFET_OFF_STATE : DIMMER_MOSFET_ON_STATE;

    #if DIMMER_MAX_CHANNELS > 1
        channel_ptr = 0;
    #endif

    // switch channels on in prioritized order
    OCR1A = ordered_channels[0].ticks;
    for(Channel::type i = 0; ordered_channels[i].ticks; i++) {
        _set_mosfet_gate(ordered_channels[i].channel, toggle_state);
    }

    // now there is some time to run the code before compare a can be triggered (by default ~300 microseconds / DIMMER_MIN_ON_TIME_US)

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

    // disable timer for delayed zero crossing
    Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareB>();

    if (ordered_channels[0].ticks && ordered_channels[0].ticks <= TickTypeMax) { // any channel dimmed?
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
        auto channel = &ordered_channels[channel_ptr++];
        auto next_channel = channel;
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
                // extraTicks should be at least 1 tick more than this code takes to run or the interrupt won't be triggered
                // TODO count clock cycles in disassembled code, 54 is probably too high but should not have any visible effect
                OCR1A = std::max<uint16_t>(Timer<1>::extraTicks + TCNT1, next_channel->ticks);
                break;
            }
            // next channel that is on
            channel = next_channel;
            channel_ptr++;
            next_channel++;
        }
    #endif
}

namespace Dimmer {

    void delay(uint32_t ms) 
    {
        // should be a constexpr and optimized out on most MCUs
        // if not defined, check dimmer.h
        if (!can_yield()) {
            return;
        }
        uint32_t start = micros();
        serialEvent();
        while (ms > 0) {
            // if not defined, check dimmer.h
            optimistic_yield(1000);
            while (ms > 0 && (micros() - start) >= 1000) {
                ms--;
                start += 1000;
            }
            serialEvent();
        }
    }

    __attribute_always_inline__
    inline void bubble_sort(ChannelType channels[], Channel::type count)
    {
        Channel::type i, j;
        if (count >= 2) {
            count--;
            for (i = 0; i < count; i++) {
                for (j = 0; j < count - i; j++) {
                    if (channels[j].ticks > channels[j + 1].ticks) {
                        swap<ChannelType>(channels[j], channels[j + 1]);
                    }
                }
            }
        }
    }
}

// NOTE: this method is only called in _apply_fading()
// copy data from register memory to buffers
// calculate ticks for each channel and sort them
// channels that are off or fully on won't be added
void DimmerBase::_calculate_channels()
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        // with cubic interpolation enabled, this method can take quite a while
        if (calculate_channels_locked) {
            return;
        }
        calculate_channels_locked = true;
    }

    ChannelType ordered_channels_tmp[Channel::size() + 1];
    Channel::type count = 0;
    StateType new_channel_state = 0;

    // copy levels from register memory
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
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
    ordered_channels_tmp[count] = nullptr; // end marker

    #if DIMMER_MAX_CHANNELS > 1
        bubble_sort(ordered_channels_tmp, count);
    #endif

    // copy double buffer with interrupts disabled
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (new_channel_state != channel_state) {
            channel_state = new_channel_state;
            queues.scheduled_calls.send_channel_state = true;
        }
        memcpy(ordered_channels_buffer, ordered_channels_tmp, sizeof(ordered_channels_buffer));

        calculate_channels_locked = false;
    }
}

void DimmerBase::set_channel_level(Channel::type channel, Level::type level)
{
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

    _D(5, debug_printf("ch=%u level=%u ticks=%u zcd=%u\n", channel, _get_level(channel), _get_ticks(channel, level), _config.zero_crossing_delay_ticks));
}

void DimmerBase::fade_channel_from_to(Channel::type channel, Level::type from, Level::type to, float time, bool absolute_time)
{
    float diff;
    auto &fade = fading[channel];
    #if HAVE_FADE_COMPLETION_EVENT
        fading_completed[channel] = Level::invalid;
    #endif

    _D(5, debug_printf("fade_channel_from_to from=%d to=%d time=%f\n", from, to, time));

    // get real level not what is stored in the register memory
    Level::type current_level;
    auto ptr = &levels_buffer[channel];
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        current_level = *ptr;
    }
    // auto current_level = _get_level(channel);

    // Serial.printf_P(PSTR("+REM=ch=%u,f=%d,t=%d,t=%f,l=%d\n"), channel, from, to, time, current_level);

    // stop fading at current level
    if (to == Level::freeze) {
        if (fade.count == 0) {
            // fading not in progress
            return;
        }
        fade.count = 1;
        fade.step = 0; // keep current level
        fade.level = current_level;
        fade.targetLevel = fade.level;
        return;
    }

    from = from == Level::current ? current_level : _normalize_level(from);
    diff = _normalize_level(to) - from;
    if (diff == 0) {
        _D(5, debug_printf("fade normalized -> from=%d to=%d\n", from, to));
        // make sure the level is stored
        set_channel_level(channel, to);
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
        set_channel_level(channel, to);
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

void DimmerBase::_apply_fading()
{
    #if HAVE_FADE_COMPLETION_EVENT
        bool send_fading_events = false;
    #endif
    DIMMER_CHANNEL_LOOP(i) {
        auto &fade = fading[i];
        if (fade.count) {
            fade.level += fade.step;
            if (--fade.count == 0) {
                _set_level(i, fade.targetLevel);
                #if HAVE_FADE_COMPLETION_EVENT
                    fading_completed[i] = fade.targetLevel;
                    send_fading_events = true;
                #endif
            } 
            else {
                _set_level(i, fade.level);
            }
        }
    }
    #if HAVE_FADE_COMPLETION_EVENT
        if (send_fading_events) {
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                queues.scheduled_calls.send_fading_events = true;
                queues.fading_completed_events.resetTimer();
            }
        }
    #endif

    _calculate_channels();
}

TickType DimmerBase::__get_ticks(Channel::type channel, Level::type level) const
{
    auto halfWaveTicks = _get_ticks_per_halfwave();
    TickType rangeTicks = halfWaveTicks - _config.minimum_on_time_ticks - _config.minimum_off_time_ticks;
    TickType ticks;

    if (_config.range_divider == 0) {
        ticks = (static_cast<TickMultiplierType>(rangeTicks) * level) / Level::max;
    }
    else {
        ticks = (static_cast<TickMultiplierType>(rangeTicks) * (level + _config.range_begin)) / _config.range_divider;
    }
    ticks += _config.minimum_on_time_ticks;

    return std::clamp<uint16_t>(ticks, _config.minimum_on_time_ticks, halfWaveTicks - _config.minimum_off_time_ticks);
}

