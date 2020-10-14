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
constexpr const uint8_t Dimmer::Channel::pins[Dimmer::Channel::size]; // = { DIMMER_MOSFET_PINS };

extern dimmer_scheduled_calls_t dimmer_scheduled_calls;

ISR(TIMER1_COMPA_vect)
{
    dimmer.compare_a_interrupt();
}

// start halfwave cycle
ISR(TIMER2_COMPA_vect)
{
    Timer<2>::pause(); // pause until next zero crossing interrupt
    dimmer._start_timer1();
}

#if FREQUENCY_TEST_DURATION

volatile uint8_t zero_crossing_int_counter = 0;
volatile unsigned long zero_crossing_frequency_time = 0;
volatile uint16_t zero_crossing_frequency_period; // milliseconds for DIMMER_AC_FREQUENCY interrupts
volatile ulong zc_min_time = 0;

float DimmerBase::_get_frequency()
{
    if (!zero_crossing_frequency_period) {
        return NAN;
    }
    auto last = millis() - zero_crossing_frequency_time;
    if (last > 1000 / kMaxTicksPerHalfWave) { // signal lost
        zero_crossing_frequency_period = 0;
        dimmer_scheduled_calls.report_error = true;
        register_mem.data.errors.frequency_low++;
        return NAN;
    }
    return 500 * kFrequency / (float)zero_crossing_frequency_period;
}

#endif

#if ZC_MAX_TIMINGS
volatile unsigned long *zc_timings = nullptr;
volatile uint8_t zc_timings_counter;
bool zc_timings_output = false;
#endif

void DimmerBase::begin()
{
    _D(5, debug_printf("ch=%u prescaler=%u/%u hwticks=%u levels=%u\n",
        Channel::size,
        Timer<1>::prescaler,
        Timer<2>::prescaler,
        kTicksPerHalfWave,
        Level::max)
    );

#if ZC_MAX_TIMINGS
    if (!zc_timings) {
        zc_timings = new ulong[ZC_MAX_TIMINGS];
    }
    zc_timings_counter = 0;
#endif

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

    pinMode(ZC_SIGNAL_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), []() {
        dimmer.zc_interrupt_handler();
    }, DIMMER_ZC_INTERRUPT_MODE);

    _D(5, debug_printf("enabling timers\n"));
    enableTimers();
}

void DimmerBase::end()
{
    _D(5, debug_printf("Removing dimmer timer...\n"));

    dimmer_scheduled_calls = {};

    cli();
    for(Channel::type i = 0; i < Dimmer::Channel::size; i++) {
        digitalWrite(Channel::pins[i], DIMMER_MOSFET_OFF_STATE);
        pinMode(Channel::pins[i], INPUT);
    }
    disableTimers();
    sei();
}

#if ZC_MAX_TIMINGS
void dimmer_record_zc_timings(ulong time) {
    if (zc_timings_output) {
        zc_timings[zc_timings_counter] = time;
        zc_timings_counter = (zc_timings_counter + 1) % ZC_MAX_TIMINGS;
    }
}
#endif

void DimmerBase::zc_interrupt_handler()
{
    auto time = micros();
    if (time < zc_min_time) { // filter misfire of the ZC circuit
        if (zc_min_time - time >= 0x7fffffffUL) {   // timer overflow
            zc_min_time = ~zc_min_time + 1;
        }
        if (time < zc_min_time) {
            register_mem.data.errors.zc_misfire++;
#if ZC_MAX_TIMINGS
            dimmer_record_zc_timings(time);
#endif
            return;
        }
    }
    if (dimmer_config.zero_crossing_delay_ticks) {
        _start_timer2(); // delay timer1 until actual zero crossing
    } else {
        _start_timer1(); // no delay, start timer1
    }
    zc_min_time = time + (ulong)(1e6 / kFrequency / 3);       // filter above 90Hz @60Hz mains
#if ZC_MAX_TIMINGS
    dimmer_record_zc_timings(time);
#endif
    memcpy(ordered_channels, ordered_channels_buffer, sizeof(ordered_channels));
    sei();
    _apply_fading();

// #if FREQUENCY_TEST_DURATION
//     zero_crossing_int_counter++;
//     if (zero_crossing_int_counter == kFrequency) {
//         auto _millis = millis();
//         zero_crossing_frequency_period = (_millis - zero_crossing_frequency_time);
//         zero_crossing_int_counter = 0;
//         zero_crossing_frequency_time = _millis;
//         if (zero_crossing_frequency_period > 500 / DIMMER_LOW_FREQUENCY) {
//             dimmer_scheduled_calls.report_error = true;
//             register_mem.data.errors.frequency_low++;
//         }
//         else if (zero_crossing_frequency_period < 500 / DIMMER_HIGH_FREQUENCY) {
//             dimmer_scheduled_calls.report_error = true;
//             register_mem.data.errors.frequency_high++;
//         }
//     }
// #endif
    //_D(10, Serial.println(F("ZC Signal Int")));
}

// turn mosfets for active channels on
void DimmerBase::_start_timer1()
{
    Channel::type i;

    TCNT1 = 0;
    OCR1A = 0;
    Timer<1>::start();

    if (ordered_channels[0].ticks) { // any channel dimmed?
        toggle_state = _config.bits.leading_edge ? DIMMER_MOSFET_OFF_STATE : DIMMER_MOSFET_ON_STATE;
        channel_ptr = 0;
        OCR1A = ordered_channels[0].ticks;
        for(i = 0; i < Channel::size; i++) {
            if (_get_level(i) == Level::off) {
                _set_mosfet_gate(i, DIMMER_MOSFET_OFF_STATE);
            }
        }
        for(i = 0; ordered_channels[i].ticks; i++) {
            _set_mosfet_gate(ordered_channels[i].channel, toggle_state);
        }
        toggle_state = toggle_state == DIMMER_MOSFET_OFF_STATE ? DIMMER_MOSFET_ON_STATE : DIMMER_MOSFET_OFF_STATE;

        for(i = 0; ordered_channels[i].ticks; i++) {
            auto &counter = on_counter[ordered_channels[i].channel];
            if (counter < kOnSwitchCounterMax) {
                counter++;
            }
        }
    }
    else {
        // enable or disable channels
        for(i = 0; i < Channel::size; i++) {
            _set_mosfet_gate(i, _get_level(i) == Level::max ? DIMMER_MOSFET_ON_STATE : DIMMER_MOSFET_OFF_STATE);
        }
    }
}

void DimmerBase::compare_a_interrupt()
{
    ChannelStateType *channel = &ordered_channels[channel_ptr++];
    ChannelStateType *next_channel = &ordered_channels[channel_ptr];
    for(;;) {
        _set_mosfet_gate(channel->channel, toggle_state);    // turn off current channel

        if (next_channel->ticks == 0) {
            // no more channels to turn off, end timer
            Timer<1>::pause();
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

// delay for zero crossing
void DimmerBase::_start_timer2()
{
    Timer<2>::start();
    TCNT2 = 0;
    OCR2A = dimmer_config.zero_crossing_delay_ticks;
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
            ordered_channels[count].ticks = _get_ticks(i, level) + dimmer_config.zero_crossing_delay_ticks;
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

    fade.count = Dimmer::kFrequency * 2.0f * time;
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

uint16_t DimmerBase::__get_ticks(Channel::type channel, Level::type level) const
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
