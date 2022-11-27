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
static uint8_t startUpCounter;
constexpr uint8_t kMinStartupCounter = 10; // number of valid events before starting the dimmer

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
    // send artificial event if dimmer is running
    if (startUpCounter > kMinStartupCounter) {
        auto ticks = timer2.get_no_cli();
        if (ticks > dimmer.halfwave_ticks_prescaler1 + dimmer.halfwave_ticks_prescaler1 * DIMMER_ZC_INTERVAL_MAX_DEVIATION) {
            // change TCNT1 to the time when it should have been occurred
            dimmer.zc_interrupt_handler(TCNT1, ticks);
        }
    }
}

static bool is_ticks_within_range(uint24_t ticks) 
{
    uint24_t _min = dimmer.halfwave_ticks_prescaler1;
    uint24_t _max;
    // allow up to DIMMER_ZC_INTERVAL_MAX_DEVIATION % deviation from the filtered avg. value
    uint16_t limit = _min * DIMMER_ZC_INTERVAL_MAX_DEVIATION;
    _min = _min - limit;
    _max = _max + limit;

    // check if ticks is within the range
    // ticks is the clock cycles since the last
    return (ticks >= _min && ticks <= _max);
}

void DimmerBase::begin()
{
    if (!Dimmer::isValidFrequency(register_mem.data.metrics.frequency)) {
        return;
    }
    halfwave_ticks = ((F_CPU / Timer<1>::prescaler / 2.0) / register_mem.data.metrics.frequency);
    halfwave_ticks_prescaler1 = ((F_CPU / 2.0) / register_mem.data.metrics.frequency);

    queues.scheduled_calls = {};
    sync_event = { 0 , Timer<1>::ticksToMicros(halfwave_ticks_prescaler1) };

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
    startUpCounter = 0;
    timer2.begin(); // timer2 runs at clock speed 
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), []() {
        // clear timers
        auto ticks = timer2.get_clear_no_cli();
        TCNT1 = 0;
        // ignore first zc interrupt
        if (startUpCounter++ == 0) {
            return;
        }
        // check if interrupt is in valid range
        if (!is_ticks_within_range(ticks)) {
            // restart the test
            startUpCounter = 0;
            return;
        }
        // start the dimmer if we got kMinStartupCounter valid signals in a row
        if (startUpCounter++ == kMinStartupCounter) {

            attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), []() {
                uint24_t ticks = timer2.get_clear_no_cli();
                uint16_t counter = TCNT1;
                dimmer.zc_interrupt_handler(counter, ticks);
            }, DIMMER_ZC_INTERRUPT_MODE);

            // clear timers
            auto ticks = timer2.get_clear_no_cli();
            TCNT1 = 0;
        }
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

void DimmerBase::zc_interrupt_handler(uint16_t counter, uint24_t ticks)
{
    if (!is_ticks_within_range(ticks)) {
        // event was too early
        sync_event.invalid_signals++;
        return;
    }

    Timer<1>::int_mask_enable<Timer<1>::kIntMaskCompareB>();
    OCR1B = dimmer_config.zero_crossing_delay_ticks;
    OCR1B += TCNT1;
    Timer<1>::clear_flags<Timer<1>::kFlagsCompareB>();

    sync_event.invalid_signals = 0;

    memcpy(ordered_channels, ordered_channels_buffer, sizeof(ordered_channels));
    sei();

    _apply_fading();

    _D(10, Serial.println(F("zc int")));
}

// turn mosfets for active channels on
void DimmerBase::_start_halfwave()
{
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = halfwave_ticks;
    Timer<1>::clear_flags<Timer<1>::kFlagsCompareAB>();

    Channel::type i;
    toggle_state = _config.bits.leading_edge ? DIMMER_MOSFET_OFF_STATE : DIMMER_MOSFET_ON_STATE;

    #if DIMMER_MAX_CHANNELS > 1
        channel_ptr = 0;
    #endif

    if (++sync_event.invalid_signals >= DIMMER_OUT_OF_SYNC_LIMIT) {
        Timer<1>::int_mask_disable<Timer<1>::kIntMaskCompareAB>();
        end();
        // store counter and send event
        queues.scheduled_calls.sync_event = true;
        return;
    }

    if (ordered_channels[0].ticks) { // any channel dimmed?
        Timer<1>::int_mask_toggle<Timer<1>::kIntMaskCompareA, Timer<1>::kIntMaskCompareB>();
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
    }
    else {
        Timer<1>::int_mask_toggle<Timer<1>::kFlagsCompareB, Timer<1>::kFlagsCompareA>();

        // enable or disable channels
        DIMMER_CHANNEL_LOOP(i) {
            _set_mosfet_gate(i, _get_level(i) == Level::max ? DIMMER_MOSFET_ON_STATE : DIMMER_MOSFET_OFF_STATE);
        }
    }
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
            OCR1A = std::max<uint16_t>(TCNT1 + Dimmer::Timer<1>::extraTicks, next_channel->ticks);  // make sure to trigger an interrupt even if the time slot is in the past by using TCNT1 + 1 as minimum
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

    return std::clamp<uint16_t>(ticks, _config.minimum_on_time_ticks, halfWaveTicks - _config.minimum_off_time_ticks);
}
