/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"
#include "dimmer.h"
#include "i2c_slave.h"

volatile uint8_t *dimmer_pins_addr[DIMMER_CHANNELS];
uint8_t dimmer_pins_mask[DIMMER_CHANNELS];
dimmer_t dimmer;

#if FREQUENCY_TEST_DURATION

volatile uint8_t zero_crossing_int_counter = 0;
volatile unsigned long zero_crossing_frequency_time = 0;
volatile uint16_t zero_crossing_frequency_period; // milliseconds for DIMMER_AC_FREQUENCY interrupts
volatile ulong zc_min_time = 0;

float dimmer_get_frequency() {
    if (!zero_crossing_frequency_period) {
        return NAN;
    }
    auto last = millis() - zero_crossing_frequency_time;
    if (last > 1000 / DIMMER_LOW_FREQUENCY) { // signal lost
        zero_crossing_frequency_period = 0;
        dimmer_schedule_call(FREQUENCY_LOW);
        register_mem.data.errors.frequency_low++;
        return NAN;
    }
    return 500 * DIMMER_AC_FREQUENCY / (float)zero_crossing_frequency_period;
}

#endif

#if ZC_MAX_TIMINGS
volatile unsigned long *zc_timings = nullptr;
volatile uint8_t zc_timings_counter;
bool zc_timings_output = false;
#endif

void dimmer_setup() {
#if ZC_MAX_TIMINGS
    if (!zc_timings) {
        zc_timings = new ulong[ZC_MAX_TIMINGS];
    }
    zc_timings_counter = 0;
#endif
    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
	    dimmer_pins_mask[i] = digitalPinToBitMask(dimmer_pins[i]);
	    dimmer_pins_addr[i] = portOutputRegister(digitalPinToPort(dimmer_pins[i]));
        _D(5, debug_printf_P(PSTR("Channel %u, pin %u, address %02x, mask %02x\n"), i, dimmer_pins[i], dimmer_pins_addr[i], dimmer_pins_mask[i]));
    }
    dimmer_zc_setup();
    dimmer_timer_setup();
}

#if ZC_MAX_TIMINGS
void dimmer_record_zc_timings(ulong time) {
    if (zc_timings_output) {
        zc_timings[zc_timings_counter] = time;
        zc_timings_counter = (zc_timings_counter + 1) % ZC_MAX_TIMINGS;
    }
}
#endif

void dimmer_zc_interrupt_handler() {
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
        dimmer_start_timer2(); // delay timer1 until actual zero crossing
    } else {
        dimmer_start_timer1(); // no delay, start timer1
    }
    zc_min_time = time + (ulong)(1e6 / DIMMER_AC_FREQUENCY / 3);       // filter above 90Hz @60Hz mains
#if ZC_MAX_TIMINGS
    dimmer_record_zc_timings(time);
#endif
    memcpy(dimmer.ordered_channels, dimmer.ordered_channels_buffer, sizeof(dimmer.ordered_channels));
    sei();
#if DIMMER_USE_FADING
    dimmer_apply_fading();
#endif
#if FREQUENCY_TEST_DURATION
    zero_crossing_int_counter++;
    if (zero_crossing_int_counter == DIMMER_AC_FREQUENCY) {
        auto _millis = millis();
        zero_crossing_frequency_period = (_millis - zero_crossing_frequency_time);
        zero_crossing_int_counter = 0;
        zero_crossing_frequency_time = _millis;
        if (zero_crossing_frequency_period > 500 / DIMMER_LOW_FREQUENCY) {
            dimmer_schedule_call(FREQUENCY_LOW);
            register_mem.data.errors.frequency_low++;
        }
        else if (zero_crossing_frequency_period < 500 / DIMMER_HIGH_FREQUENCY) {
            dimmer_schedule_call(FREQUENCY_HIGH);
            register_mem.data.errors.frequency_high++;
        }
    }
#endif
    _D(10, Serial.println(F("ZC Signal Int")));
}

void dimmer_zc_setup() {

    _D(5, debug_printf_P(PSTR("Setting up zero crossing detection on PIN %u\n"), ZC_SIGNAL_PIN));

    memset(&dimmer, 0, sizeof(dimmer));
#if HAVE_FADE_COMPLETION_EVENT
    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        dimmer.fadingCompleted[i] = INVALID_LEVEL;
    }
#endif

#if DIMMER_USE_LINEAR_CORRECTION
    dimmer_set_lcf(DIMMER_LINEAR_FACTOR);
#endif

    pinMode(ZC_SIGNAL_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), dimmer_zc_interrupt_handler, RISING);
}

#if DIMMER_USE_LINEAR_CORRECTION
void dimmer_set_lcf(float lcf) {
    dimmer_config.linear_correction_factor = lcf;
    dimmer.linear_correction_divider = DIMMER_MAX_LEVEL / pow(DIMMER_MAX_LEVEL, dimmer_config.linear_correction_factor);
}
#endif

void dimmer_timer_setup() {

    _D(5, debug_printf_P(PSTR("Dimmer channels %u\n"), DIMMER_CHANNELS));
    _D(5, debug_printf_P(PSTR("Timer prescaler %u / %u\n"), DIMMER_TIMER1_PRESCALER, DIMMER_TIMER2_PRESCALER));
    _D(5, debug_printf_P(PSTR("Half wave resolution %lu ticks\n"), (unsigned long)DIMMER_TICKS_PER_HALFWAVE));
    _D(5, debug_printf_P(PSTR("Dimming levels %u\n"), DIMMER_MAX_LEVEL));
#if DIMMER_USE_LINEAR_CORRECTION
    _D(5, debug_printf_P(PSTR("Linear correction factor %.3f\n"), dimmer_config.linear_correction_factor));
#endif

    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        digitalWrite(dimmer_pins[i], LOW);
        pinMode(dimmer_pins[i], OUTPUT);
    }

    DIMMER_ENABLE_TIMERS();
}

void dimmer_timer_remove() {

    _D(5, Serial.println(F("Removing dimmer timer...")));

    cli();
    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        dimmer_set_mosfet_gate(i, false);
        pinMode(dimmer_pins[i], INPUT);
    }
    DIMMER_DISABLE_TIMERS();
    sei();
}

// turn mosfets for active channels on
void dimmer_start_timer1() {
    dimmer_channel_id_t i;

    TCNT1 = 0;
    OCR1A = 0;
    DIMMER_START_TIMER1();

    if (dimmer.ordered_channels[0].ticks) { // any channel active?
        dimmer.channel_ptr = 0;
        OCR1A = dimmer.ordered_channels[0].ticks;
        for(i = 0; i < DIMMER_CHANNELS; i++) {
            if (!dimmer_level(i)) {
                dimmer_set_mosfet_gate(i, false);
            }
        }
        for(i = 0; dimmer.ordered_channels[i].ticks; i++) {
            dimmer_set_mosfet_gate(dimmer.ordered_channels[i].channel, true);
        }
    } else {
        // all channels off
        for(i = 0; i < DIMMER_CHANNELS; i++) {
            dimmer_set_mosfet_gate(i, false);
        }
    }
}

// turn channels off
ISR(TIMER1_COMPA_vect) {
    dimmer_channel_t *channel = &dimmer.ordered_channels[dimmer.channel_ptr++];
    dimmer_channel_t *next_channel = &dimmer.ordered_channels[dimmer.channel_ptr];
    for(;;) {
        dimmer_set_mosfet_gate(channel->channel, false);    // turn off current channel

        if (next_channel->ticks == 0 || next_channel->ticks == 0xffff) {
            // no more channels to turn off, end timer
            DIMMER_PAUSE_TIMER1();
            break;
        } else if (next_channel->ticks > channel->ticks) {
            // next channel has a different time slot, re-schedule
            OCR1A = max(TCNT1 + DIMMER_EXTRA_TICKS, next_channel->ticks);  // make sure to trigger an interrupt even if the time slot is in the past by using TCNT1 + 1 as minimum
            break;
        }
        //
        channel = next_channel;
        dimmer.channel_ptr++;
        next_channel = &dimmer.ordered_channels[dimmer.channel_ptr];
    }
}

// delay for zero crossing
void dimmer_start_timer2() {
    DIMMER_START_TIMER2();
    TCNT2 = 0;
    OCR2A = dimmer_config.zero_crossing_delay_ticks;
}

// start halfwave cycle
ISR(TIMER2_COMPA_vect){
    DIMMER_PAUSE_TIMER2();  // pause until next zero crossing interrupt
    dimmer_start_timer1();
}

template <typename T>
void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
};

static inline void dimmer_bubble_sort(dimmer_channel_t channels[], dimmer_channel_id_t count) {
   dimmer_channel_id_t i, j;
   if (count >= 2) {
        count--;
        for (i = 0; i < count; i++) {
            for (j = 0; j < count - i; j++)   {
                if (channels[j].ticks > channels[j + 1].ticks) {
                    swap<dimmer_channel_t>(channels[j], channels[j + 1]);
                }
            }
        }
   }
}

// calculate ticks for each channel and sort them
void dimmer_calculate_channels() {

    dimmer_channel_t ordered_channels[DIMMER_CHANNELS + 1];
    dimmer_channel_id_t count = 0;

    memset(ordered_channels, 0, sizeof(ordered_channels));

    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        if (dimmer_level(i) == DIMMER_MAX_LEVEL) {
            ordered_channels[count].ticks = 0xffff;
            ordered_channels[count].channel = i;
            count++;
        } else if (dimmer_level(i) != 0) {
            uint16_t ticks = DIMMER_GET_TICKS(DIMMER_LINEAR_LEVEL(dimmer_level(i)));
            if (ticks) {
                ordered_channels[count].ticks = ticks + dimmer_config.zero_crossing_delay_ticks;
                ordered_channels[count].channel = i;
                count++;
            }
        }
    }

    dimmer_bubble_sort(ordered_channels, count);
    cli(); // copy double buffer with interrupts disabled
    memcpy(dimmer.ordered_channels_buffer, ordered_channels, sizeof(dimmer.ordered_channels_buffer));
    sei();
}

dimmer_level_t dimmer_normalize_level(dimmer_level_t level) {

    if (level < 0) {
        return 0;
    } else if (level > DIMMER_MAX_LEVEL) {
        return DIMMER_MAX_LEVEL;
    }
    return level;
}

void dimmer_set_level(dimmer_channel_id_t channel, dimmer_level_t level) {

    dimmer_level(channel) = dimmer_normalize_level(level);

#if DIMMER_USE_FADING
    dimmer.fade[channel].count = 0; // disable fading for this channel
    dimmer.fadingCompleted[channel] = INVALID_LEVEL;
#endif

    dimmer_calculate_channels();

    _D(5, debug_printf_P(PSTR("Dimmer channel %u set %u value %u ticks %u\n"),
        (unsigned)channel,
        (unsigned)dimmer_level(channel),
        (unsigned)DIMMER_GET_TICKS(dimmer_level(channel)),
        (unsigned)DIMMER_GET_TICKS(DIMMER_LINEAR_LEVEL(dimmer_level(channel)))
    ));

}

dimmer_level_t dimmer_get_level(dimmer_channel_id_t channel) {
    return dimmer_level(channel);
}

#if DIMMER_USE_FADING

void dimmer_fade(dimmer_channel_id_t channel, dimmer_channel_id_t to_level, float time_in_seconds, bool absolute_time) {
    dimmer_set_fade(channel, DIMMER_FADE_FROM_CURRENT_LEVEL, to_level, time_in_seconds, absolute_time);
}

// dimmer_set_level() + dimmer_fade()
void dimmer_set_fade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time, bool absolute_time) {

    float diff;
    dimmer_fade_t &fade = dimmer.fade[channel];
#if HAVE_FADE_COMPLETION_EVENT
    dimmer.fadingCompleted[channel] = INVALID_LEVEL;
#endif

#if DIMMER_MIN_LEVEL
    if (from == DIMMER_FADE_FROM_CURRENT_LEVEL && dimmer_level(channel) < DIMMER_MIN_LEVEL * DIMMER_MAX_LEVEL / 100) {
        dimmer_level(channel) = from = DIMMER_MIN_LEVEL * DIMMER_MAX_LEVEL / 100;
        delay(DIMMER_MIN_LEVEL_TIME_IN_MS);
    }
#endif

    from = dimmer_normalize_level(from == DIMMER_FADE_FROM_CURRENT_LEVEL ? dimmer_level(channel) : from);
    diff = dimmer_normalize_level(to) - from;

    if (!absolute_time) { // calculate relative fading time depending on "diff"
        time = abs(diff / DIMMER_MAX_LEVEL * time);
        _D(5, debug_printf_P(PSTR("Relative fading time %.3f\n"), time));
    }

    fade.count = DIMMER_AC_FREQUENCY * 2.0f * time;
    fade.step = diff / (float)fade.count;
    fade.level = from;
    fade.targetLevel = to;

    if (fade.count < 1 || fade.step == 0) { // time too short, force to run fading anyway = basically turns the channel on and sends events
        fade.count = 1;
    }

    _D(5, debug_printf_P(PSTR("Set fading for channel %u: %.2f to %.2f"), channel, from, to));
    _D(5, Serial_printf_P(PSTR(", step %.3f, count %u\n"), fade.step, fade.count));
}

void dimmer_apply_fading() {

    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        dimmer_fade_t &fade = dimmer.fade[i];
        if (fade.count) {
            fade.level += fade.step;
            if (--fade.count == 0) {
                dimmer_level(i) = dimmer_normalize_level(fade.targetLevel);
#if HAVE_FADE_COMPLETION_EVENT
                dimmer.fadingCompleted[i] = dimmer_level(i);
#endif
            } else {
                dimmer_level(i) = dimmer_normalize_level(fade.level);
            }
#if DEBUG
            if (fade.count % 60 == 0) {
                _D(5, debug_printf_P(PSTR("Fading channel %u: %u ticks %.2f\n"), i, dimmer_level(i), DIMMER_GET_TICKS(DIMMER_LINEAR_LEVEL(dimmer_level(i)))));
            }
#endif
        }
    }

    dimmer_calculate_channels();
}
#endif

void dimmer_set_mosfet_gate(dimmer_channel_id_t channel, bool state) {
	if (!state) {
		*dimmer_pins_addr[channel] &= ~dimmer_pins_mask[channel];
	} else {
		*dimmer_pins_addr[channel] |= dimmer_pins_mask[channel];
	}
}
