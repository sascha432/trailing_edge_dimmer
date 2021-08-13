/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"
#include "dimmer.h"
#include "i2c_slave.h"

#include <string.h>
#include <stdlib.h>
#include <avr/io.h>

#define PIN_D2_SET()                                    asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (2))
#define PIN_D2_CLEAR()                                  asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (2))
#define PIN_D2_TOGGLE()                                 asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PIND)), "I" (2))
#define PIN_D2_IS_SET()                                 ((_SFR_IO_ADDR(PIND) & _BV(2)) != 0)
#define PIN_D2_IS_CLEAR()                               ((_SFR_IO_ADDR(PIND) & _BV(2)) == 0)

#define PIN_D8_SET()                                    asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (0))
#define PIN_D8_CLEAR()                                  asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (0))
#define PIN_D8_TOGGLE()                                 asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PINB)), "I" (0))
#define PIN_D8_IS_SET()                                 ((_SFR_IO_ADDR(PINB) & _BV(0)) != 0)
#define PIN_D8_IS_CLEAR()                               ((_SFR_IO_ADDR(PINB) & _BV(0)) == 0)

#define PIN_D11_SET()                                   asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (3))
#define PIN_D11_CLEAR()                                 asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (3))
#define PIN_D11_TOGGLE()                                asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PINB)), "I" (3))
#define PIN_D11_IS_SET()                                ((_SFR_IO_ADDR(PINB) & _BV(3)) != 0)
#define PIN_D11_IS_CLEAR()                              ((_SFR_IO_ADDR(PINB) & _BV(3)) == 0)


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
}

void DimmerBase::begin()
{
    if (!Dimmer::isValidFrequency(register_mem.data.metrics.frequency)) {
        return;
    }
    halfwave_ticks = ((F_CPU / Timer<1>::prescaler / 2.0) / register_mem.data.metrics.frequency) + (_config.halfwave_adjust_cycles / Timer<1>::prescaler);
    zc_diff_ticks = 0;
    zc_diff_count = 0;

    _D(5, debug_printf("ch=%u levels=%u prescaler=%u ",
        Channel::size(),
        Level::max,
        Timer<1>::prescaler)
    );
    _D(5, debug_printf("f=%f ticks=%lu\n",
        register_mem.data.metrics.frequency,
        (uint32_t)halfwave_ticks)
    );

    queues.scheduled_calls = {};
    sync_event = {};
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
    timer2.begin();
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), []() {
        //volatile
        uint24_t ticks = timer2.get_clear_no_cli();
        //dimmer.zc_interrupt_handler(const_cast<const uint24_t &>(ticks));
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
    #if HAVE_DISABLE_ZC_SYNC
        if (zc_sync_disabled) {
            return;
        }
    #endif
    int24_t diff;
    if (dimmer_config.zero_crossing_delay_ticks) {
        // schedule next _start_halfwave() call
        Timer<1>::int_mask_enable<Timer<1>::kIntMaskCompareB>();
        diff = OCR1B - TCNT1;
        OCR1B = dimmer_config.zero_crossing_delay_ticks + TCNT1;
        Timer<1>::clear_flags<Timer<1>::kFlagsCompareB>();
    }
    else {
        diff = OCR1B - TCNT1;
        _start_halfwave(); // no delay
    }
    diff -= dimmer_config.zero_crossing_delay_ticks;

    #if DIMMER_OUT_OF_SYNC_LIMIT
        if (!sync_event.sync && (sync_event.lost || sync_event.halfwave_counter > 1)) {
            // send in-sync event
            sync_event.sync = true;
            sync_event.sync_difference_cycles = diff;
            queues.scheduled_calls.sync_event = true;
        }
        out_of_sync_counter = 0;
    #endif

    memcpy(ordered_channels, ordered_channels_buffer, sizeof(ordered_channels));
    sei();
    if (zc_diff_count < 254) { // get average of the first 250 values
        if (zc_diff_count >= 3) {
            zc_diff_ticks += diff;
            if (zc_diff_count == 253) {
                zc_diff_ticks /= 250;
            }
        }
        zc_diff_count++;
    }
    else {
        // check if the zc interrupt is off
        if (abs(zc_diff_ticks - diff) > 50) {
            // Serial.printf("%d us\n", (int)(abs(zc_diff_ticks - diff) / Timer<1>::ticksPerMicrosecond));
        }
        zc_diff_ticks = ((zc_diff_ticks * 100.0) + diff) / 101.0;
    }

    _apply_fading();

    _D(10, Serial.println(F("zc int")));

#if DEBUG && 0
    halfwave_ticks_avg = (halfwave_ticks_avg * 199 + ticks) * 0.005; // ( * 199) + ) / 200
    halfwave_ticks_avg2 = (halfwave_ticks_avg2 * 9 + ((halfwave_ticks + diff) * 8)) * 0.1;
    static int bla=0;
    bla++;
    if (bla%60==0) {
        // uint24_t tmp2 = halfwave_ticks + diff;
        // int16_t diff2 = ticks - (tmp2 * 8);
        // Serial.printf_P(PSTR("%lu %lu %d\n"), (uint32_t)tmp2 * 8, (uint32_t)halfwave_ticks_avg, diff2);
        // Serial.printf_P(PSTR("%lu %lu %f\n"), (uint32_t)halfwave_ticks_avg2, (uint32_t)halfwave_ticks_avg, halfwave_ticks_avg- halfwave_ticks_avg2);
        Serial.printf_P(PSTR("%u %.2f %.4fus\n"), halfwave_ticks, halfwave_ticks_avg / 8.0, (halfwave_ticks_avg - halfwave_ticks_avg2) * 0.0625);
    }
#endif
}

// turn mosfets for active channels on
void DimmerBase::_start_halfwave()
{
    PIN_D11_SET();
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = halfwave_ticks;
    Timer<1>::clear_flags<Timer<1>::kFlagsCompareAB>();

    Channel::type i;
    toggle_state = _config.bits.leading_edge ? DIMMER_MOSFET_OFF_STATE : DIMMER_MOSFET_ON_STATE;

    #if DIMMER_MAX_CHANNELS > 1
        channel_ptr = 0;
    #endif

    #if DIMMER_OUT_OF_SYNC_LIMIT
        if (++out_of_sync_counter >= DIMMER_OUT_OF_SYNC_LIMIT) {
            Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareAB>();
            _set_all_mosfet_gates(DIMMER_MOSFET_OFF_STATE);
            // store counter and send event
            sync_event.lost = true;
            sync_event.halfwave_counter = out_of_sync_counter;
            queues.scheduled_calls.sync_event = true;
            return;
        }
    #else
        Timer<1>::disable_compareB();
    #endif

    if (ordered_channels[0].ticks) { // any channel dimmed?
        #if DIMMER_OUT_OF_SYNC_LIMIT
            //Timer<1>::enable_compareA_disable_compareB();
            Timer<1>::int_mask_toggle<Timer<1>::kIntMaskCompareA, Timer<1>::kIntMaskCompareB>();
        #else
            //Timer<1>::enable_compareA();
            Timer<1>::int_mask_enable<Timer<1>::kIntMaskCompareA>();
        #endif
        OCR1A = ordered_channels[0].ticks;
        for(i = 0; ordered_channels[i].ticks; i++) {
            _set_mosfet_gate(ordered_channels[i].channel, toggle_state);
        }
        DIMMER_CHANNEL_LOOP(j) {
            if (_get_level(j) == Level::off) {
                _set_mosfet_gate(j, DIMMER_MOSFET_OFF_STATE);
            }
        }
        toggle_state = !toggle_state;

        for(i = 0; ordered_channels[i].ticks; i++) {
            auto &counter = on_counter[ordered_channels[i].channel];
            if (counter < kOnSwitchCounterMax) {
                counter++;
            }
        }
    }
    else {
        #if DIMMER_OUT_OF_SYNC_LIMIT
            Timer<1>::int_mask_toggle<Timer<1>::kFlagsCompareB, Timer<1>::kFlagsCompareA>();
            //Timer<1>::enable_compareB_disable_compareA();
        #else
            Timer<1>::int_mask_disable<Timer<1>::kFlagsCompareA>();
            // Timer<1>::disable_compareA();
        #endif

        // enable or disable channels
        DIMMER_CHANNEL_LOOP(i) {
            _set_mosfet_gate(i, _get_level(i) == Level::max ? DIMMER_MOSFET_ON_STATE : DIMMER_MOSFET_OFF_STATE);
        }
    }
    #if DIMMER_OUT_OF_SYNC_LIMIT
        // keep counter up to date
        if (!sync_event.lost && !sync_event.sync) {
            sync_event.halfwave_counter = out_of_sync_counter;
        }
    #endif
    PIN_D11_CLEAR();
}

void DimmerBase::compare_interrupt()
{
#if DIMMER_MAX_CHANNELS == 1

    _set_mosfet_gate(ordered_channels[0].channel, toggle_state);
    //Timer<1>::enable_compareB_disable_compareA();
    Timer<1>::int_mask_toggle<Timer<1>::kFlagsCompareB, Timer<1>::kFlagsCompareA>();

#else
    ChannelStateType *channel = &ordered_channels[channel_ptr++];
//    ChannelStateType *next_channel = &ordered_channels[channel_ptr];
    ChannelStateType *next_channel = channel;
    ++next_channel;
    for(;;) {
        _set_mosfet_gate(channel->channel, toggle_state);    // turn off current channel

        if (next_channel->ticks == 0) {
            // no more channels to change, disable timer
            //Timer<1>::enable_compareB_disable_compareA();
            Timer<1>::int_mask_toggle<Timer<1>::kFlagsCompareB, Timer<1>::kFlagsCompareA>();
            break;
        }
        else if (next_channel->ticks > channel->ticks) {
            // next channel has a different time slot, re-schedule
            OCR1A = max(TCNT1 + Dimmer::Timer<1>::extraTicks, next_channel->ticks);  // make sure to trigger an interrupt even if the time slot is in the past by using TCNT1 + 1 as minimum
            break;
        }
        //
        channel = next_channel;
        channel_ptr++;
        // next_channel = &ordered_channels[channel_ptr];
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

// calculate ticks for each channel and sort them
// channels that are off or fully on won't be added
void DimmerBase::_calculate_channels()
{
    ChannelStateType ordered_channels[Channel::size() + 1];
    Channel::type count = 0;
    uint8_t new_channel_state = 0;

    DIMMER_CHANNEL_LOOP(i) {
        auto level = DIMMER_LINEAR_LEVEL(_get_level(i), i);
        if (level >= Level::max) {
            new_channel_state |= (1 << i);
        }
        else if (level > Level::off) {
            new_channel_state |= (1 << i);
            ordered_channels[count].ticks = _get_ticks(i, level);
            ordered_channels[count].channel = i;
            count++;
        }
    }
    ordered_channels[count] = {};

    #if DIMMER_MAX_CHANNELS > 1

        dimmer_bubble_sort(ordered_channels, count);

    #endif

    cli(); // copy double buffer with interrupts disabled
    if (new_channel_state != channel_state) {
        channel_state = new_channel_state;
        queues.scheduled_calls.send_channel_state = true;
    }
    memcpy(ordered_channels_buffer, ordered_channels, sizeof(ordered_channels_buffer));
    sei();
}

void DimmerBase::set_channel_level(ChannelType channel, Level::type level)
{
    // _D(5, debug_printf("set_channel_level ch=%d level=%d\n", channel, level))
    if (_get_level(channel) == 0) {
        on_counter[channel] = 0;
    }
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

    _calculate_channels();

    _D(5, debug_printf("ch=%u level=%u ticks=%u zcdelay=%u\n", channel, _get_level(channel), _get_ticks(channel, level), _config.zero_crossing_delay_ticks));
}

void DimmerBase::set_level(Channel::type channel, Level::type level)
{
    // _D(5, debug_printf("set_level ch=%d level=%d\n", channel, level))
    if (channel == Channel::any) {
        DIMMER_CHANNEL_LOOP(i) {
            set_channel_level(i, level);
        }
    } else {
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

    if (_get_level(channel) == 0) {
        on_counter[channel] = 0;
    }

    _D(5, debug_printf("fade_channel_from_to from=%d to=%d time=%f\n", from, to, time));

    // stop fading at current level
    if (to == Level::freeze) {
        if (fade.count == 0) {
            // fading not in progress
            return;
        }
        fade.count = 1;
        fade.step = 0; // keep current level
        fade.level = _normalize_level(_get_level(channel));
        fade.targetLevel = fade.level;
        return;
    }

    from = _normalize_level(from == Level::current ? _get_level(channel) : from);
    diff = _normalize_level(to) - from;
    if (diff == 0) {
        _D(5, debug_printf("fade normalized -> from=%d to=%d\n", from, to));
        return;
    }

    if (!absolute_time) { // calculate relative fading time depending on "diff"
        time = abs(diff / Level::size * time);
        _D(5, debug_printf("Relative fading time %.3f\n", time));
    }

    fade.count = register_mem.data.metrics.frequency * time * 2;
    if (fade.count == 0) {
        _D(5, debug_printf("count=%u time=%f\n", fade.count, time));
        return;
    }
    fade.step = diff / (float)fade.count;
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
            } else {
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

    TickType max_ticks = halfWaveTicks - _config.minimum_off_time_ticks;
    if (ticks > max_ticks) {
        return max_ticks;
    }
    auto min_ticks = _get_min_on_ticks(channel);
    if (ticks < min_ticks) {
        return min_ticks;
    }
    return ticks;
}
