/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"

volatile bool dimmer_calculate_channels_lock = false;
volatile bool dimmer_calculate_channels_abort = false;

template <typename T>
void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
};

static inline void dimmer_bubble_sort(dimmer_channel_t channels[], dimmer_channel_id_t count)
{
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
void dimmer_calculate_channels()
{
    // using cubic interpolation can cause this function to run longer than a single have wave (8.33ms)
    // in this case, the current calculation is stopped and the step is simply skipped during fading
    // if it is the last step, it is postponed for one half cycle
    // during my tests with 4 channels it rarely exceeded 0.9ms (@16Mhz)

    cli();
    if (dimmer_calculate_channels_lock) {
        // request to abort the current calculation
        // we cannot wait here since this is probably called from an interrupt and the actual function is paused
        dimmer_calculate_channels_abort = true;
        sei();
        Serial.println(F("dimmer_calculate_channels_locked"));
        return;
    }
    dimmer_calculate_channels_lock = true;
    sei();

#if 0
    auto start = micros();
#endif

    dimmer_channel_t ordered_channels[DIMMER_CHANNELS + 1];
    dimmer_channel_id_t count = 0;

    bzero(ordered_channels, sizeof(ordered_channels));

    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        if (dimmer_calculate_channels_abort) {
            cli();
            dimmer_calculate_channels_abort = false;
            dimmer_calculate_channels_lock = false;
            sei();
            Serial.println("aborted");
            return;
        }
        if (dimmer_level(i) >= DIMMER_MAX_LEVELS - 1) {
            ordered_channels[count].ticks = 0xffff;
            ordered_channels[count].channel = i;
            count++;
        }
        else if (dimmer_level(i) != 0) {
            uint16_t ticks = dimmer.getChannel(DIMMER_LINEAR_LEVEL(dimmer_level(i), i));
            if (ticks) {
                ordered_channels[count].ticks = ticks;
                ordered_channels[count].channel = i;
                count++;
            }
        }
    }

    // if (dimmer_is_fading()) {
    //     if ((rand()%100)==7) {
    //         Serial.println("delay test");
    //         for(int i = 0; i < 200; i++) {
    //             if (dimmer_calculate_channels_abort) {
    //                 cli();
    //                 dimmer_calculate_channels_abort = false;
    //                 dimmer_calculate_channels_lock = false;
    //                 sei();
    //                 Serial.println("aborted");
    //                 return;
    //             }
    //             delay(1);
    //         }
    //     }
    // }

    dimmer_bubble_sort(ordered_channels, count);
    cli(); // copy double buffer with interrupts disabled
    memcpy(dimmer.ordered_channels_buffer, ordered_channels, sizeof(dimmer.ordered_channels_buffer));

#if 0
    if (dimmer_is_fading()) {
        auto dur = micros() - start;
        for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
            Serial_printf_P(PSTR("%u=%u(%u) "), ordered_channels[i].channel, ordered_channels[i].ticks, dimmer_level(i));
        }
        Serial.println(dur);
    }
#endif
    dimmer_calculate_channels_lock = false;
    sei();

}

dimmer_level_t dimmer_normalize_level(dimmer_level_t level)
{
    if (level < 0) {
        return 0;
    }
    else if (level >= DIMMER_MAX_LEVELS - 1) {
        return DIMMER_MAX_LEVELS - 1;
    }
    return level;
}

void dimmer_set_level(dimmer_channel_id_t channel, dimmer_level_t level)
{
    dimmer_level(channel) = dimmer_normalize_level(level);

    dimmer.fade[channel].count = 0; // disable fading for this channel
    dimmer.fadingCompleted[channel] = INVALID_LEVEL;

    dimmer_calculate_channels();

    // _D(5,
    Serial_printf_P(PSTR("Dimmer channel %u set %u value %u ticks %u\n"),
        (unsigned)channel,
        (unsigned)dimmer_level(channel),
        (unsigned)dimmer.getChannel(dimmer_level(channel)),
        (unsigned)dimmer.getChannel(DIMMER_LINEAR_LEVEL(dimmer_level(channel), channel))
    );
    // );

}

dimmer_level_t dimmer_get_level(dimmer_channel_id_t channel)
{
    return dimmer_level(channel);
}

void dimmer_fade(dimmer_channel_id_t channel, dimmer_channel_id_t to_level, float time_in_seconds, bool absolute_time)
{
    dimmer_set_fade(channel, DIMMER_FADE_FROM_CURRENT_LEVEL, to_level, time_in_seconds, absolute_time);
}

// dimmer_set_level() + dimmer_fade()
void dimmer_set_fade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time, bool absolute_time)
{
    float diff;
    dimmer_fade_t &fade = dimmer.fade[channel];
#if HAVE_FADE_COMPLETION_EVENT
    dimmer.fadingCompleted[channel] = INVALID_LEVEL;
#endif

    from = dimmer_normalize_level(from == DIMMER_FADE_FROM_CURRENT_LEVEL ? dimmer_level(channel) : from);
    diff = dimmer_normalize_level(to) - from;

    if (!absolute_time) { // calculate relative fading time depending on "diff"
        time = abs(diff / DIMMER_MAX_LEVELS * time);
        _D(5, Serial_printf_P(PSTR("Relative fading time %.3f\n"), time));
    }

    fade.count = 2 * dimmer.getFrequency() * time;
    fade.step = diff / (float)fade.count;
    fade.level = from;
    fade.targetLevel = to;

    if (fade.count < 1 || fade.step == 0) { // time too short, force to run fading anyway = basically turns the channel on and sends events
        fade.count = 1;
    }

    _D(5, Serial_printf_P(PSTR("Set fading for channel %u: %.2f to %.2f"), channel, from, to));
    _D(5, Serial_printf_P(PSTR(", step %.3f, count %u\n"), fade.step, fade.count));
}

bool dimmer_is_fading()
{
    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        if (dimmer.fade[i].count) {
            return true;
        }
    }
    return false;
}

// this function is called from an interrupt at the rate of the AC frequency
void dimmer_apply_fading()
{
    for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
        dimmer_fade_t &fade = dimmer.fade[i];
        if (fade.count) {
            if (dimmer_calculate_channels_lock && fade.count == 1) {
                // postpone last step
            }
            else {
                fade.level += fade.step;
                if (--fade.count == 0) {
                    dimmer_level(i) = dimmer_normalize_level(fade.targetLevel);
#if HAVE_FADE_COMPLETION_EVENT
                    dimmer.fadingCompleted[i] = dimmer_level(i);
#endif
                } else {
                    dimmer_level(i) = dimmer_normalize_level(fade.level);
                }
            }
#if DEBUG
            if (fade.count % 60 == 0) {
                _D(5, debug_printf_P(PSTR("Fading channel %u: %u ticks %.2f\n"), i, dimmer_level(i), DIMMER_GET_TICKS(DIMMER_LINEAR_LEVEL(dimmer_level(i), i))));
            }
#endif
        }
    }

    dimmer_calculate_channels();
}
