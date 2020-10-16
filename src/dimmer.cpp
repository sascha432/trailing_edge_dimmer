/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"
#include "dimmer.h"
#include "i2c_slave.h"

using namespace Dimmer;

volatile uint8_t *dimmer_pins_addr[Channel::size];
uint8_t dimmer_pins_mask[Channel::size];
DimmerBase dimmer(register_mem.data);
constexpr const uint8_t Dimmer::Channel::pins[Dimmer::Channel::size];

extern dimmer_scheduled_calls_t dimmer_scheduled_calls;

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

#if 1 //FREQUENCY_TEST_DURATION

volatile uint8_t zero_crossing_int_counter;
volatile unsigned long zero_crossing_frequency_time;
volatile uint16_t zero_crossing_frequency_period; // milliseconds for DIMMER_AC_FREQUENCY interrupts
volatile unsigned long long zc_min_time;

#endif

void DimmerBase::begin()
{
    if (frequency == 0 || isnan(frequency)) {
        return;
    }
    halfwave_ticks = ((F_CPU / Timer<1>::prescaler / 2.0) / frequency) + _config.halfwave_adjust_ticks;
    zc_diff_ticks = 0;
    zc_diff_count = 0;

    _D(5, debug_printf("ch=%u levels=%u prescaler=%u ",
        Channel::size,
        Level::max,
        Timer<1>::prescaler)
    );
    _D(5, debug_printf("f=%f ticks=%ld\n",
        frequency,
        halfwave_ticks)
    );

    zc_min_time = 0;
    dimmer_scheduled_calls = {};
    toggle_state = DIMMER_MOSFET_OFF_STATE;

    for(Channel::type i = 0; i < Channel::size; i++) {
	    dimmer_pins_mask[i] = digitalPinToBitMask(Channel::pins[i]);
	    dimmer_pins_addr[i] = portOutputRegister(digitalPinToPort(Channel::pins[i]));
#if HAVE_FADE_COMPLETION_EVENT
        fading_completed[i] = Level::invalid;
#endif
        digitalWrite(Channel::pins[i], DIMMER_MOSFET_OFF_STATE);
        pinMode(Channel::pins[i], OUTPUT);
        _D(5, debug_printf("ch=%u pin=%u addr=%02x mask=%02x\n", i, Channel::pins[i], dimmer_pins_addr[i], dimmer_pins_mask[i]));
    }

    cli();
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), []() {
        dimmer.zc_interrupt_handler();
    }, DIMMER_ZC_INTERRUPT_MODE);

    _D(5, debug_printf("starting timer\n"));
    Timer<1>::begin();
    Timer<1>::disable();
    sei();
}

void DimmerBase::end()
{
    if (frequency == 0 || isnan(frequency)) {
        return;
    }
    _D(5, debug_printf("ending timer...\n"));

    dimmer_scheduled_calls = {};

    cli();
    detachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN));
    Timer<1>::end();
    for(Channel::type i = 0; i < Dimmer::Channel::size; i++) {
        digitalWrite(Channel::pins[i], DIMMER_MOSFET_OFF_STATE);
        pinMode(Channel::pins[i], INPUT);
    }
    sei();
}

void DimmerBase::zc_interrupt_handler()
{
    int16_t diff = 0;
    if (dimmer_config.zero_crossing_delay_ticks) {
        // schedule next _start_halfwave() call
        diff = OCR1B - TCNT1;
        Timer<1>::enable_compareB();
        OCR1B = dimmer_config.zero_crossing_delay_ticks + TCNT1;
        Timer<1>::clear_compareB_flag();
    }
    else {
        _start_halfwave(); // no delay
    }
#if DIMMER_OUT_OF_SYNC_LIMIT
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
}

// turn mosfets for active channels on
void DimmerBase::_start_halfwave()
{
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = halfwave_ticks;
    Timer<1>::clear_compareA_B_flag();

    Channel::type i;
    toggle_state = _config.bits.leading_edge ? DIMMER_MOSFET_OFF_STATE : DIMMER_MOSFET_ON_STATE;
    channel_ptr = 0;
#if DIMMER_OUT_OF_SYNC_LIMIT
    if (++out_of_sync_counter > DIMMER_OUT_OF_SYNC_LIMIT) {
        Timer<1>::disable();
        for(i = 0; i < Channel::size; i++) {
            _set_mosfet_gate(i, DIMMER_MOSFET_OFF_STATE);
        }
        Serial.println(F("+REM=out of sync"));
        return;
    }
#else
    Timer<1>::disable_compareB();
#endif

    if (ordered_channels[0].ticks) { // any channel dimmed?
#if DIMMER_OUT_OF_SYNC_LIMIT
        Timer<1>::enable_compareA_disable_compareB();
#else
        Timer<1>::enable_compareA();
#endif
        OCR1A = ordered_channels[0].ticks;
        for(i = 0; ordered_channels[i].ticks; i++) {
            _set_mosfet_gate(ordered_channels[i].channel, toggle_state);
        }
        for(i = 0; i < Channel::size; i++) {
            if (_get_level(i) == Level::off) {
                _set_mosfet_gate(i, DIMMER_MOSFET_OFF_STATE);
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
        Timer<1>::enable_compareB_disable_compareA();
#else
        Timer<1>::disable_compareA();
#endif

        // enable or disable channels
        for(i = 0; i < Channel::size; i++) {
            _set_mosfet_gate(i, _get_level(i) == Level::max ? DIMMER_MOSFET_ON_STATE : DIMMER_MOSFET_OFF_STATE);
        }
    }
}

void DimmerBase::compare_interrupt()
{
    ChannelStateType *channel = &ordered_channels[channel_ptr++];
    ChannelStateType *next_channel = &ordered_channels[channel_ptr];
    for(;;) {
        _set_mosfet_gate(channel->channel, toggle_state);    // turn off current channel

        if (next_channel->ticks == 0) {
            // no more channels to change, disable timer
            Timer<1>::enable_compareB_disable_compareA();
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
        next_channel = &ordered_channels[channel_ptr];
    }
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
    ChannelStateType ordered_channels[Channel::size + 1];
    Channel::type count = 0;
    uint8_t new_channel_state = 0;

    for(Channel::type i = 0; i < Channel::size; i++) {
        auto level = _get_level(i);
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

    dimmer_bubble_sort(ordered_channels, count);
    cli(); // copy double buffer with interrupts disabled
    if (new_channel_state != channel_state) {
        channel_state = new_channel_state;
        dimmer_scheduled_calls.send_channel_state = true;
    }
    memcpy(ordered_channels_buffer, ordered_channels, sizeof(ordered_channels_buffer));
    sei();
}

void DimmerBase::set_channel_level(ChannelType channel, Level::type level)
{
     _D(5, debug_printf("set_channel_level ch=%d level=%d\n", channel, level))
   if (_get_level(channel) == 0) {
        on_counter[channel] = 0;
    }
    _set_level(channel, _normalize_level(level));

    fading[channel].count = 0; // disable fading for this channel
#if HAVE_FADE_COMPLETION_EVENT
    if (fading_completed[channel] != Level::invalid) {
        // send event with the new level
        fading_completed[channel] = _get_level(channel);
        dimmer_scheduled_calls.send_fading_events = true;
    }
#endif

    _calculate_channels();

    _D(5, debug_printf("ch=%u level=%u ticks=%u zcdelay=%u\n", channel, _get_level(channel), _get_ticks(channel, level), _config.zero_crossing_delay_ticks));
}

void DimmerBase::set_level(Channel::type channel, Level::type level)
{
    _D(5, debug_printf("set_level ch=%d level=%d\n", channel, level))
    if (channel == Channel::any) {
        for(Channel::type i = 0; i < Channel::size; i++) {
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

    fade.count = frequency * time * 2;
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
        for(Channel::type i = 0; i < Channel::size; i++) {
            fade_channel_from_to(i, from_level, to_level, time, absolute_time);
        }
    }
    else {
        fade_channel_from_to(channel, from_level, to_level, time, absolute_time);
    }
}

void DimmerBase::_apply_fading()
{
    for(Channel::type i = 0; i < Dimmer::Channel::size; i++) {
        dimmer_fade_t &fade = fading[i];
        if (fade.count) {
            fade.level += fade.step;
            if (--fade.count == 0) {
                _set_level(i, fade.targetLevel);
#if HAVE_FADE_COMPLETION_EVENT
                fading_completed[i] = _get_level(i);
                dimmer_scheduled_calls.send_fading_events = true;
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
    TickType ticks = ((TickMultiplierType)rangeTicks * (TickType)(level + _config.range_begin) ) / (TickType)(_config.range_begin + _config.range_end) + _config.minimum_on_time_ticks;
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

void DimmerBase::_set_mosfet_gate(Channel::type channel, bool state)
{
	if (state) {
		*dimmer_pins_addr[channel] |= dimmer_pins_mask[channel];
	}
    else {
		*dimmer_pins_addr[channel] &= ~dimmer_pins_mask[channel];
	}
}
