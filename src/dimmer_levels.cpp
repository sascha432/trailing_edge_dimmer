/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"
#include "cubic_interpolation.h"

template <typename T>
inline void swap(T &a, T &b) {
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

bool dimmer_is_fading()
{
    FOR_CHANNELS(i) {
        if (dimmer.fade[i].count) {
            return true;
        }
    }
    return false;
}

static dimmer_level_t dimmer_normalize_level(dimmer_level_t level)
{
    if (level < 0) {
        return 0;
    }
    else if (level >= DIMMER_MAX_LEVELS - 1) {
        return DIMMER_MAX_LEVELS - 1;
    }
    return level;
}

// calculate ticks for each channel and sort them
void Dimmer::_calculateChannels()
{
    // using cubic interpolation can cause this function to run longer than a single have wave (8.33ms@60Hz)
    // in this case, the current calculation is stopped and the step is simply skipped during fading
    // if it is the last step, it is postponed for one half cycle. a flag is set to abort the calculation
    // during my tests with 4 channels it rarely exceeded 0.9ms (@16Mhz)

    cli();
    if (_isCalcLocked()) {
        // request to abort the current calculation
        // we cannot wait here since this is called from inside an interrupt and the actual function is paused
        _setAbortCalc();
        sei();
        Serial.println(F("dimmer_calculate_channels_locked"));
        return;
    }
    _lockCalc();
    sei();

#if 0
    auto start = micros();
#endif

    dimmer_channel_t ordered_channels_tmp[DIMMER_CHANNELS + 1];
    // using a counter and pointer is a lot faster than accessing the array with the counter or calculating the count from the pointer address
    dimmer_channel_id_t count = 0;
    auto channel_ptr = ordered_channels_tmp;

    bzero(ordered_channels_tmp, sizeof(ordered_channels_tmp));

    FOR_CHANNELS(i) {
        if (_isAbortCalc()) {
            ATOMIC_BLOCK(ATOMIC_FORCEON) {
                _unsetAbortCalcAndUnlock();
            }
            Serial.println("aborted");
            return;
        }
        if (dimmer_level(i) != 0) {
#if DIMMER_CUBIC_INTERPOLATION
            uint16_t ticks = getChannel(DIMMER_LINEAR_LEVEL(dimmer_level(i), i));
#else
            uint16_t ticks = (dimmer_level(i) < DIMMER_MAX_LEVELS - 1) ?
                getChannel(DIMMER_LINEAR_LEVEL(dimmer_level(i), i)) :       // returns between min_on_ticks and (halfwave_ticks - max_on_ticks) or 0xffff
                0xffff;                                                     // without cubic inerpolation, max. level is always 100%
#endif
            channel_ptr->channel = i;
            channel_ptr->ticks = ticks;
            channel_ptr++;
            count++;
        }
    }

#if 0
    if (dimmer_is_fading()) {
        if ((rand()%100)==7) {
            Serial.println("delay test");
            for(int i = 0; i < 200; i++) {
                if (_isAbortCalc()) {
                    ATOMIC_BLOCK(ATOMIC_FORCEON) {
                        _unsetAbortCalcAndUnlock();
                    }
                    Serial.println("aborted");
                    return;
                }
                delay(1);
            }
        }
    }
#endif

    dimmer_bubble_sort(ordered_channels_tmp, count);

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        // copy double buffer with interrupts disabled
        memcpy(ordered_channels_buffer, ordered_channels_tmp, sizeof(ordered_channels_buffer));
#if 0
        if (dimmer_is_fading()) {
            auto dur = micros() - start;
            FOR_CHANNELS(i) {
                // Serial_printf_P(PSTR("%u=%u(%u) "), ordered_channels_buffer[i].channel, ordered_channels_buffer[i].ticks, dimmer_level(i));
                Serial_printf_P(PSTR("%u=%u "), ordered_channels_buffer[i].channel, ordered_channels_buffer[i].ticks);
            }
            Serial.println(dur);
        }
#endif
        _unlockCalc();
    }

}

void Dimmer::setLevel(dimmer_channel_id_t channel, dimmer_level_t level)
{
    dimmer_level(channel) = dimmer_normalize_level(level);

    fade[channel].count = 0; // disable fading for this channel
    fadingCompleted[channel] = INVALID_LEVEL;

    _calculateChannels();

    _D(5,
        Serial_printf_P(PSTR("Dimmer channel %u set %u value %u ticks %u\n"),
            (unsigned)channel,
            (unsigned)dimmer_level(channel),
            (unsigned)getChannel(dimmer_level(channel)),
            (unsigned)getChannel(DIMMER_LINEAR_LEVEL(dimmer_level(channel), channel))
        )
    );
}

dimmer_level_t Dimmer::getLevel(dimmer_channel_id_t channel) const
{
    return dimmer_level(channel);
}

void Dimmer::setFade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time, bool absolute_time)
{
    float diff;
    auto &fade = this->fade[channel];
#if HAVE_FADE_COMPLETION_EVENT
    fadingCompleted[channel] = INVALID_LEVEL;
#endif

    from = dimmer_normalize_level((from == DIMMER_FADE_FROM_CURRENT_LEVEL) ? dimmer_level(channel) : from);
    diff = dimmer_normalize_level(to) - from;

    if (!absolute_time) { // calculate relative fading time depending on the level change "diff"
        time = diff / DIMMER_MAX_LEVELS * time;
        time = abs(time);
        _D(5, Serial_printf_P(PSTR("Relative fading time %.3f\n"), time));
    }

    fade.count = 2 * getFrequency() * time;
    fade.step = (fade.count <= 1) ? 0 : (diff / fade.count);
    fade.level = from;
    fade.targetLevel = to;

    if (fade.step == 0) { // time too short or no change, force to run fading anyway = basically turns the channel on and sends events
        fade.count = 1;
    }

    _D(5, Serial_printf_P(PSTR("Set fading for channel %u: %.2f to %.2f"), channel, from, to));
    _D(5, Serial_printf_P(PSTR(", step %.3f, count %u\n"), fade.step, fade.count));
}

// this function is called from an interrupt twice the rate of the AC frequency
void Dimmer::_applyFading()
{
    FOR_CHANNELS(i) {
        auto &fade = this->fade[i]; // assigning the reference using "i" has the same code size as using a pointer and incrementing it at the end of the loop
        if (fade.count) {
            if (_isCalcLocked() && fade.count == 1) {
                // postpone last step
            }
            else {
                fade.level += fade.step;
                if (--fade.count == 0) {
                    dimmer_level(i) = dimmer_normalize_level(fade.targetLevel);
#if HAVE_FADE_COMPLETION_EVENT
                    fadingCompleted[i] = dimmer_level(i);
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

    _calculateChannels();
}
