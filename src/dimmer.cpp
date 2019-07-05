/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"
#include "dimmer.h"

uint8_t dimmer_pins[] = DIMMER_MOSFET_PINS;
dimmer_t dimmer;

void dimmer_setup() {
    dimmer_zc_setup();
    dimmer_timer_setup();
}

void dimmer_zc_interrupt_handler() {

#if DIMMER_ZC_DELAY_TICKS == 0
    dimmer_start_timer1(); // no delay, start timer1
#else
    dimmer_start_timer2(); // delay timer1 until actual zero crossing
#endif
    memcpy(dimmer.ordered_channels, dimmer.ordered_channels_buffer, sizeof(dimmer.ordered_channels));
    sei();
#if DIMMER_USE_FADING
    dimmer_apply_fading();
#endif
    _D(10, Serial.println(F("ZC Signal Int")));
}

void dimmer_zc_setup() {

    _D(5, SerialEx.printf_P(PSTR("Setting up zero crossing detection on PIN %u\n"), ZC_SIGNAL_PIN));

    memset(&dimmer, 0, sizeof(dimmer));
#if DIMMER_USE_LINEAR_CORRECTION
    dimmer_set_lcf(DIMMER_LINEAR_FACTOR);
#endif

    pinMode(ZC_SIGNAL_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), dimmer_zc_interrupt_handler, RISING);
}

#if DIMMER_USE_LINEAR_CORRECTION
void dimmer_set_lcf(float lcf) {
    dimmer.linear_correction_factor = lcf;
    dimmer.linear_correction_factor_div = DIMMER_MAX_LEVEL / pow(DIMMER_MAX_LEVEL, dimmer.linear_correction_factor);
}
#endif

void dimmer_timer_setup() {

    _D(5, SerialEx.printf_P(PSTR("Dimmer channels %u\n"), (unsigned)DIMMER_CHANNELS));
    _D(5, SerialEx.printf_P(PSTR("Timer prescaler %u\n"), (unsigned)DIMMER_PRESCALER));
    _D(5, SerialEx.printf_P(PSTR("Half wave resolution %lu ticks\n"), (unsigned long)DIMMER_TICKS_PER_HALFWAVE));
    _D(5, SerialEx.printf_P(PSTR("ZC signal delay %u us\n"), (unsigned)DIMMER_ZC_DELAY));
    _D(5, SerialEx.printf_P(PSTR("Dimming levels %u\n"), (unsigned)DIMMER_MAX_LEVEL));
#if DIMMER_USE_LINEAR_CORRECTION
    _D(5, SerialEx.printf_P(PSTR("Linear correction factor %s\n"), float_to_str(dimmer.linear_correction_factor)));
#endif

    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
        digitalWrite(dimmer_pins[i], LOW);
        pinMode(dimmer_pins[i], OUTPUT);
        _D(5, SerialEx.printf_P(PSTR("Channel %u Pin %u\n"), i, dimmer_pins[i]));
    }

    DIMMER_ENABLE_TIMERS();
}

void dimmer_timer_remove() {

    _D(5, Serial.println(F("Removing dimmer timer...")));

    cli();
    dimmer_set_mosfet_gate(0, false);
    DIMMER_DISABLE_TIMERS();
    sei();
}

void dimmer_start_timer1() {
    uint8_t i;

    TCNT1 = 0;
    OCR1A = 0;
    DIMMER_START_TIMER1();

    if (dimmer.ordered_channels[0].ticks) { // any channel active?
        dimmer.channel_ptr = 0;
        OCR1A = dimmer.ordered_channels[0].ticks;
        for(i = 0; i < DIMMER_CHANNELS; i++) {
            if (!dimmer.level[i]) {
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

void dimmer_start_timer2() {
    DIMMER_START_TIMER2();
    TCNT2 = 0;
    OCR2A = (uint8_t)DIMMER_ZC_DELAY_TICKS;
}

ISR(TIMER2_COMPA_vect){
    DIMMER_PAUSE_TIMER2();  // pause until next zero crossing interrupt
    dimmer_start_timer1();
}


static inline void dimmer_bubble_sort(dimmer_channel_t channels[], uint8_t count) {
   uint8_t i, j;
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
    uint8_t count = 0;

    memset(ordered_channels, 0, sizeof(ordered_channels));

    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
        if (dimmer.level[i] == DIMMER_MAX_LEVEL) {
            ordered_channels[count].ticks = 0xffff;
            ordered_channels[count].channel = i;
            count++;
        } else if (dimmer.level[i] != 0) {
            uint16_t ticks = DIMMER_GET_TICKS(DIMMER_LINEAR_LEVEL(dimmer.level[i]));
            if (ticks) {
                ordered_channels[count].ticks = ticks + DIMMER_ZC_DELAY_TICKS;
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

int16_t dimmer_normalize_level(int16_t level) {

    if (level < 0) {
        return 0;
    } else if (level > DIMMER_MAX_LEVEL) {
        return DIMMER_MAX_LEVEL;
    }
    return level;
}

void dimmer_set_level(uint8_t channel, int16_t level) {

    dimmer.level[channel] = dimmer_normalize_level(level);
#if DIMMER_USE_FADING
    dimmer.fade[channel].count = 0; // disable fading for this channel
#endif

    dimmer_calculate_channels();

    _D(5, SerialEx.printf_P(PSTR("Dimmer channel %u set %u value %u ticks %u\n"),
        (unsigned)channel,
        (unsigned)dimmer.level[channel],
        (unsigned)DIMMER_GET_TICKS(dimmer.level[channel]),
        (unsigned)DIMMER_GET_TICKS(DIMMER_LINEAR_LEVEL(dimmer.level[channel]))
    ));

}

uint16_t dimmer_get_level(uint8_t channel) {

    return dimmer.level[channel];
}

#if DIMMER_USE_FADING

void dimmer_fade(uint8_t channel, int16_t to_level, float time_in_seconds, bool absolute_time) {
    dimmer_set_fade(channel, DIMMER_FADE_FROM_CURRENT_LEVEL, to_level, time_in_seconds, absolute_time);
}

// dimmer_set_level() + dimmer_fade()
void dimmer_set_fade(uint8_t channel, int16_t from, int16_t to, float time, bool absolute_time) {

    float diff;
    dimmer_fade_t *fade = &dimmer.fade[channel];

#if DIMMER_MIN_LEVEL
    if (from == DIMMER_FADE_FROM_CURRENT_LEVEL && dimmer.level[channel] < DIMMER_MIN_LEVEL * DIMMER_MAX_LEVEL / 100) {
        dimmer.level[channel] = from = DIMMER_MIN_LEVEL * DIMMER_MAX_LEVEL / 100;
        delay(DIMMER_MIN_LEVEL_TIME_IN_MS);
    }
#endif

    from = dimmer_normalize_level(from == DIMMER_FADE_FROM_CURRENT_LEVEL ? dimmer.level[channel] : from);
    diff = dimmer_normalize_level(to) - from;

    if (!absolute_time) { // calculate relative fading time depending on "diff"
        time = abs(diff / DIMMER_MAX_LEVEL * time);
        _D(5, SerialEx.printf_P(PSTR("Relative fading time %s\n"), float_to_str(time)));
    }

    fade->count = DIMMER_AC_FREQUENCY * 2.0 * time;
    fade->step = diff / (float)fade->count;
    fade->level = from;

    if (fade->step == 0) {
        fade->count = 0;
    }

    _D(5, SerialEx.printf_P(PSTR("Set fading for channel %u: %s to %s"), (unsigned)channel, float_to_str(from), float_to_str(to)));
    _D(5, SerialEx.printf_P(PSTR(", step %s, count %u\n"), float_to_str(fade->step), (unsigned)fade->count));
}

void dimmer_apply_fading() {

#if !SLIM_VERSION
    bool run_calc = false;
#endif

    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
        dimmer_fade_t *fade = &dimmer.fade[i];
        if (fade->count) {
#if !SLIM_VERSION
            run_calc = true;
#endif
            fade->level += fade->step;
            fade->count--;
            dimmer.level[i] = dimmer_normalize_level(fade->level);
#if DEBUG
            if (fade->count % 60 == 0) {
                _D(5, SerialEx.printf_P(PSTR("Fading channel %u: %u ticks %s\n"), (unsigned)i, (unsigned)dimmer.level[i], float_to_str(DIMMER_GET_TICKS(DIMMER_LINEAR_LEVEL(dimmer.level[i])))));
            }
#endif
        }
    }

#if !SLIM_VERSION
    if (run_calc)
#endif
    {
        dimmer_calculate_channels();
    }
}
#endif

#if SLIM_VERSION

void dimmer_set_mosfet_gate(uint8_t channel, bool state) {
    digitalWrite(dimmer_pins[channel], state);
}

#else

void dimmer_set_mosfet_gate(uint8_t channel, bool state) {
    uint8_t pin = dimmer_pins[channel];
	uint8_t bit = digitalPinToBitMask(pin);
	volatile uint8_t *out = portOutputRegister(digitalPinToPort(pin));
	if (!state) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}
}

#endif
