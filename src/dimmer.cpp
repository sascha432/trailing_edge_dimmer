/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"
#include "dimmer.h"
#include "i2c_slave.h"
#include "cubic_interpolation.h"

Dimmer dimmer;

#if DEBUG_PIN
volatile uint8_t *debugPinAddr;
uint8_t debugPinMask;

void debugPinToggle()
{
    *debugPinAddr = *debugPinAddr ^ debugPinMask;
}

void debugPinSignalHigh(uint8_t time = 10)
{
    *debugPinAddr |= debugPinMask;
    delayMicroseconds(time);
    *debugPinAddr &= ~debugPinMask;
}

#endif

Dimmer::Dimmer() : dimmer_t(), _halfwaveTicks(0), _cycleCounter(0), _state(StateEnum::MEASURE), _intFlags(0)
{
#if DEBUG_PIN
    pinMode(DEBUG_PIN, OUTPUT);
    debugPinMask = digitalPinToBitMask(DEBUG_PIN);
    debugPinAddr = portOutputRegister(digitalPinToPort(DEBUG_PIN));
#endif

#if DIMMER_SIGNAL_GENERATOR

    pinMode(11, OUTPUT);
    cli();
    OCR2A = 150;
    TCCR2A = _BV(COM2A0)|_BV(WGM20);
    // TCCR2A = _BV(COM2A0)|_BV(WGM21)|_BV(WGM20);
    TCCR2B = _BV(WGM22)|_BV(CS21)|_BV(CS22);
    sei();

#endif

#if 0
    // generate defines for inline assembler
    for(int j = 0; j < 8; j++) {
        for(int i = 0; i < 16; i++) {
            Serial_printf_P(PSTR("#if xBI_CHANNEL%u==%u\n"), j, i);
            Serial_printf_P(PSTR("    #define xBI_ARGS_CHANNEL%u \"0x%02x,%d\"\n"), j, portOutputRegister(digitalPinToPort(i)) - __SFR_OFFSET, _BV2B(digitalPinToBitMask(i)));
            Serial_println(F("#endif"));
        }
    }
#endif

#if !DIMMER_USE_INLINE_ASM
    FOR_CHANNELS(i) {
	    _pinsMask[i] = digitalPinToBitMask(dimmer_pins[i]);
	    _pinsAddr[i] = portOutputRegister(digitalPinToPort(dimmer_pins[i]));
        _D(5,
            {
                Serial_printf_P(PSTR("Channel %u, pin %u, address %02x, mask %02x\n"), i, dimmer_pins[i], _pinsAddr[i], _pinsMask[i]);
            }
        );
    }
#endif

#if HAVE_FADE_COMPLETION_EVENT
    FOR_CHANNELS(i) {
        fadingCompleted[i] = INVALID_LEVEL;
    }
#endif

#if DIMMER_ZC_FILTER
    _zcIntTimer = 0;
    _zcIntMinTime = 1000000 / (65 * 2) * 0.94;          // allows a max. frequency of 65Hz + ~10% tolerance
#endif
}

void Dimmer::disableTimer1() const
{
    // disable timer compare a/b and overflow interrupt
    TIMSK1 &= ~(_BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1));
}

void Dimmer::enableTimer1() const
{
    // clear compare a/b and overflow flag
    TIFR1 |= (_BV(OCF1A) | _BV(OCF1B) | _BV(TOV1));
    // enable timer overflow interrupt
    TIMSK1 |= _BV(TOIE1);
}

float Dimmer::getFrequency() const
{
    // if (_halfwaveTicks) {
    //     return (F_CPU / DIMMER_TIMER1_PRESCALER / 2) / (float)_halfwaveTicks;
    // }
    // return NAN;
    return register_mem.data.metrics.frequency;
}

bool Dimmer::measure(uint16_t timeout)
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        // reset timer state
        disableTimer1();
        enableTimer1();
        _state = StateEnum::MEASURE;
        _halfwaveTicks = 0;
        _cycleCounter = 0;
    }
    register_mem.data.metrics.frequency = NAN;

    uint32_t end = millis() + timeout;
    while(_halfwaveTicks == 0) {
        if (millis() > end) {
            return false;
        }
    }
    return true;
}

void Dimmer::addEvent(uint16_t counter)
{
    if (_cycleCounter == 0) {
        _cycleCounter = 1;
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            _ticks = -(int32_t)counter;
        }
    }
    else {
        if (_cycleCounter == DIMMER_MEASURE_CYCLES) {
            uint32_t ticks = getTicks(counter);
            _halfwaveTicks = ticks / _cycleCounter;
            _halfwaveTicksIntegral = _halfwaveTicks;

            register_mem.data.metrics.frequency = (F_CPU / DIMMER_TIMER1_PRESCALER / 2) / (float)_halfwaveTicks;

            _D(5,
                Serial_printf_P(PSTR("measure %lu hw %u zcmt %lu\n"), (long)ticks, _halfwaveTicks, (long)clockCyclesToMicroseconds(_halfwaveTicks * (94UL * DIMMER_TIMER1_PRESCALER)) / 100)
            );

#if DIMMER_ZC_FILTER
            _zcIntMinTime = clockCyclesToMicroseconds(_halfwaveTicks * (94UL * DIMMER_TIMER1_PRESCALER)) / 100;
#endif
        }
        _cycleCounter++;
    }
}

uint32_t Dimmer::getTicks(uint16_t counter)
{
    uint32_t result;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        result = _ticks;
        _ticks = -(int32_t)counter;
        if (_isOvfPending()) {
            result += (1UL << 16);
            _ticks -= (1UL << 16);
        }
    };
    result += counter;
    return result;
}

uint32_t Dimmer::getTicksNoRst(uint16_t counter)
{
    uint32_t result;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        result = _ticks;
        if (_isOvfPending()) {
            result += (1UL << 16);
        }
    };
    result += counter;
    return result;
}

ISR(TIMER1_OVF_vect)
{
    dimmer._overflow();
#if DEBUG_STATISTICS
    debugStats._overflow();
#endif
}

ISR(TIMER1_COMPA_vect)
{
    dimmer._compareA();
}

ISR(TIMER1_COMPB_vect)
{
    dimmer._compareB();
}

static inline void dimmer_zc_interrupt_handler()
{
    dimmer._zcHandler(TCNT1);
}

void Dimmer::begin()
{
    _D(5, Serial_printf_P(PSTR("Dimmer channels %u\n"), DIMMER_CHANNELS));
    _D(5, Serial_printf_P(PSTR("Timer prescaler %u\n"), DIMMER_TIMER1_PRESCALER));
    _D(5, Serial_printf_P(PSTR("Dimming levels %u\n"), DIMMER_MAX_LEVELS));
    _D(5, Serial_printf_P(PSTR("Zero crossing detection on PIN %u\n"), ZC_SIGNAL_PIN));

    ATOMIC_BLOCK(ATOMIC_FORCEON) {

        _halfwaveTicks = 0;
        _cycleCounter = 0;
#if DIMMER_ZC_FILTER
        _zcIntTimer = 0;
#endif
        _state = StateEnum::MEASURE;
#if DEBUG_FAULTS
        _startCounter = 0;
        _endCounter = 0;
#endif

        FOR_CHANNELS(i) {
            disableChannel(i);
            pinMode(dimmer_pins[i], OUTPUT);
        }

        TCCR1A = 0;
        TCCR1B = DIMMER_TIMER1_PRESCALER_BV;
        TCCR1C = 0;

        pinMode(ZC_SIGNAL_PIN, INPUT);
        attachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN), dimmer_zc_interrupt_handler, DIMMER_ZC_INTERRUPT_MODE);

        enableTimer1();

    }

}

void Dimmer::enable()
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        _state = StateEnum::STOPPED;
        _intFlags = 0;
    }
}

void Dimmer::end()
{
    _D(5, Serial.println(F("Stopping dimmer...")));

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        detachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN));

        FOR_CHANNELS(i) {
            disableChannel(i);
            pinMode(dimmer_pins[i], INPUT);
        }
        _state = StateEnum::STOPPED;
        disableTimer1();
    }
}

void Dimmer::enableChannel(dimmer_channel_id_t channel)
{
#if DIMMER_USE_INLINE_ASM
    DIMMER_CHANNELS_ENABLE_CHANNEL(channel);
#else
    *_pinsAddr[channel] |= _pinsMask[channel];
#endif
}

void Dimmer::disableChannel(dimmer_channel_id_t channel)
{
#if DIMMER_USE_INLINE_ASM
    DIMMER_CHANNELS_DISABLE_CHANNEL(channel);
#else
    *_pinsAddr[channel] &= ~_pinsMask[channel];
#endif
}

uint16_t Dimmer::getChannel(dimmer_level_t level) const
{
    uint16_t ticks = (level * (uint32_t)_halfwaveTicks) / DIMMER_MAX_LEVELS;
    if (ticks < dimmer_config.min_on_ticks) {
        return dimmer_config.min_on_ticks;
    }
    uint16_t max = _halfwaveTicks - dimmer_config.min_off_ticks;
    if (ticks >= max) {
        return 0xffff;
    }
    return ticks;
}

#if DIMMER_ZC_FILTER

static inline uint32_t get_time_diff(uint32_t start, uint32_t end) {
    if (end >= start) {
        return end - start;
    }
    // handle overflow
    return end + ~start + 1;
};

#endif

void Dimmer::_zcHandler(uint16_t counter)
{
#if DEBUG_FAULTS
    static volatile uint8_t count = 0;
    if (_isZCLocked()) {
        if (++count > 200) {
            _fault("ZC locked 200 times");
        }
        return;
    }
    count = 0;
#else
    if (_isZCLocked()) {
        return;
    }
#endif

#if DIMMER_ZC_FILTER

    // filter out any zero crossing signals that occur before 94% of a halfwave is done. for 60Hz that would be less than 53Hz
    uint32_t time = micros();
    if (_zcIntTimer) {
        if (get_time_diff(time, _zcIntTimer) < _zcIntMinTime) {
            register_mem.data.errors.zc_misfire++;
            return;
        }
    }
    else {
        _zcIntTimer = time;
    }

#endif
    _lockZC();
    sei();

    if (_state == StateEnum::MEASURE) { // wait until the measurement has been completed
        addEvent(counter);
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            _unlockZC();
        }
    }
    else {

        uint16_t endTicks = _halfwaveTicks + counter;
        endTicks += dimmer_config.zc_offset_ticks; // add zero crossing delay
        endTicks -= DIMMER_COMPARE_B_EXTRA_TICKS;

        // wait until compare B is unlocked
        while (_isCompareBLocked()) {
        }

        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            _lockCompareB();
            OCR1B = endTicks;
            // clear interrupt B flag and enable interrupt
            TIFR1 |= _BV(OCF1B);
            TIMSK1 |= _BV(OCIE1B);
        }

        // update _halfwaveTicks
        // 64-76µs @ 16MHz
        uint32_t ticks = getTicks(counter);
        // if ticks are within a reasonable range
        uint16_t minMaxLimit = _halfwaveTicks / 20; // +-5%
        if (ticks > (_halfwaveTicks - minMaxLimit) && ticks < (_halfwaveTicks + minMaxLimit)) {
            constexpr uint8_t factor = 240; // integrate over 2 seconds for 60Hz
            _halfwaveTicksIntegral = ((factor * _halfwaveTicksIntegral) + ticks) / (factor + 1.0);
            uint16_t tmp = _halfwaveTicksIntegral;
            if (tmp != _halfwaveTicks) {
                cli();
                _halfwaveTicks = _halfwaveTicksIntegral;
            }
        }
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            _unlockZC();
        }

        _D(10, Serial.println(F("ZC int")));
        _applyFading();
    }
}

void Dimmer::_compareA()
{
    switch(_state) {
        case StateEnum::NEXT_HALFWAVE:
            if (++_missedZCCounter == 240) {
                // we missed 240 zero crossings, stop and wait for one
                _unlockCompareA();
                _unlockCompareB();
                TIMSK1 &= ~_BV(OCIE1A);
#if DEBUG_FAULTS
                _fault("lost ZC signal");
#endif
                return;
            }
            // fallthrough
        case StateEnum::START_HALFWAVE:
            _startHalfwave();
            break;
        case StateEnum::HALFWAVE:
            _dimmingCycle(OCR1A);
            break;
        default:
            break;
    }
}

void Dimmer::_compareB()
{
// #if DEBUG_PIN
//     debugPinToggle();
// #endif
#if DEBUG_FAULTS
//     if (_state == StateEnum::START_HALFWAVE) {
//         _fault("compare B during start");
//         return;
//     }
//     else if (_state == StateEnum::HALFWAVE) {
//         _fault("compare B during dimming cycle");
//         return;
//     }
//     else if (TIMSK1 & _BV(OCIE1A)) {
//         _fault("compare A still active"); // most likely it was skipped due to insufficient time between compare B and A interrupt (DIMMER_COMPARE_B_EXTRA_TICKS)
//         return;
//     }
    _prevOCR1B = OCR1B;
#endif
    if (_isCompareALocked()) {
        // compare A already running
        TIMSK1 &= ~_BV(OCIE1B);
#if DEBUG_PIN
        uint16_t diff = _startOCR1A + _halfwaveTicks;
        diff -= OCR1B + DIMMER_COMPARE_B_EXTRA_TICKS;
        if (diff) {
            debugPinSignalHigh();
        }
#endif
    }
    else {
        _state = StateEnum::START_HALFWAVE;
        _lockCompareA();
        // disable compare B, enable compare A interrupt
        TIMSK1 = (TIMSK1 & ~_BV(OCIE1B)) | _BV(OCIE1A);
// point OCR1A to the beginning of the halfwave
OCR1A = OCR1B + DIMMER_COMPARE_B_EXTRA_TICKS;
    }
    // clear compare A interrupt flag
    TIFR1 |= _BV(OCF1A);
    // point OCR1A to the beginning of the halfwave
    // OCR1A = OCR1B + DIMMER_COMPARE_B_EXTRA_TICKS;
    // copy double buffer
    memcpy(ordered_channels, ordered_channels_buffer, sizeof(ordered_channels));
#if DIMMER_USE_INLINE_ASM
    DIMMER_CHANNELS_ENABLE_MASK_COPY(enable_channel_mask, enable_channel_mask_buffer);
#endif
    // reset sync counter
    _missedZCCounter = 0;
    sei();

    // // measure CPU cycles
    // sei();
    // Serial_printf("OCIE1B %u\n", (TCNT1 - OCR1B) * DIMMER_TIMER1_PRESCALER);
}

void Dimmer::_overflow()
{
    // increment hi-word
    _ticks += (1UL << 16);
}

void Dimmer::_startHalfwave()
{
    DebugStats_addFrame();
#if DEBUG_FAULTS
    if (_startCounter != _endCounter) {
        Serial_printf("%u %u\n", _startCounter, _endCounter);
        _fault("out of sync");
        return;
    }
    _startCounter++;
#endif
    // allow a new compare B interrupt to be scheduled
    _unlockCompareB();
    _state = StateEnum::HALFWAVE;
    _startOCR1A = OCR1A;
    sei();
    auto channel = ordered_channels;
    if (channel->ticks) { // any channel active?
        channel_ptr = channel;
        OCR1A += channel->ticks;
        // turn channels on first
#if DIMMER_USE_INLINE_ASM
        // enables 8 active channels in less than 0.125µs
        // channels that share a port turn on at the same time, having all channels on one port eliminates any delay
        // yellow = PORTD, pink = PORTB, blue = PORTC
        // https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/turn_on_inline_asm.png
        cli();
        DIMMER_CHANNELS_SET_ENABLE_MASK(enable_channel_mask);
        sei();
#else
        // the delay between turning on a channel is ~2µs @ 16MHz for 2 active channels (or 16µs for 8 active channels)
        // during testing with 8MHz and 8 channels, the ZC was missed by up to 180µs (~12V for 120V@60Hz) while
        // the inline assembler version was turning on between 0 and 1.7V (up to ~20µs)
        // yellow = channel#0, pink = channel#1, blue = channel#7
        // https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/turn_on_default.png
        do {
            enableChannel(channel->channel);
            channel++;
        } while(channel->ticks);
#endif

        FOR_CHANNELS(i) {
            if (!dimmer_level(i)) {
                disableChannel(i);
            }
        }
    }
    else {
        // all channels off
        FOR_CHANNELS(i) {
            disableChannel(i);
        }
        _endHalfwave();
    }
}

// uint32_t __counter;
// uint32_t __trigger;
// uint16_t __diff;

void Dimmer::_dimmingCycle(uint16_t startOCR1A)
{
    sei();
    // channel = current channel
    // channel_ptr = next channel
    auto channel = channel_ptr++;
    for(;;) {
        disableChannel(channel->channel);    // turn off current channel

#if DEBUG_FAULTS
        channel->_OCR1A = OCR1A;
#endif
        auto &frame = debugStats.getFrame();
        frame.channelTicks[channel->channel] = OCR1A;

        if (channel_ptr->ticks == 0 || channel_ptr->ticks == 0xffff) {
            _endHalfwave();

            // for(dimmer_channel_id_t i = 0; ordered_channels[i].ticks; i++) {
            //     auto channel = ordered_channels[i].channel;
            //     int32_t tmp = ordered_channels[i]._OCR1A - (int32_t)_startOCR1A;
            //     if (tmp < 0) {
            //         tmp += 0x10000;
            //     }
            //     uint16_t ticks = tmp;
            //     if (round(ticks / 2000.0) != round(ordered_channels[i].ticks / 2000.0)) { // compare if ticks and OCR1A roughly match
            //         Serial_printf("\nnum=%u,ch=%d,ticks=%d,OCR1A=%u\n", i, channel, ordered_channels[i].ticks, ticks);
            //         Serial_printf("c32=%lu,t32=%lu\n", __counter,__trigger);
            //         Serial_printf("c=%u,t=%u,d=%u\n", (uint16_t)__counter,(uint16_t)__trigger,__diff);
            //         _fault("invalid ticks");
            //     }
            // }
            break;
        }
        else if (channel_ptr->ticks > channel->ticks) {
            // next channel has a different time slot, re-schedule
            uint16_t diff = channel_ptr->ticks - channel->ticks; // add the difference

            ATOMIC_BLOCK(ATOMIC_FORCEON) {

                // setting OCR1A close to the previous compare interrupt is a bit tricky
                uint32_t counter = TCNT1;
                // we cannot use TIFR1/TOV1 since interrupts were enabled before
                if (startOCR1A > (uint16_t)counter) { // overflow occured
                    counter += (1UL << 16);
                }
                startOCR1A += diff;
                int16_t distance = startOCR1A - counter; // calculate distance between TCNT1 and next OCR1A
                if (distance < DIMMER_EXTRA_TICKS) { // if it is getting close, add extra ticks to avoid missing the interrupt
                    startOCR1A += (DIMMER_EXTRA_TICKS - distance); // DIMMER_EXTRA_TICKS has to cover the clock cycles from reading TCNT1 to setting OCR1A
                }
                OCR1A = startOCR1A; // OCR1A must be >= (TCNT1 + 1) at this point to get triggered

#if DEBUG_FAULTS
                _dcOCR1A = OCR1A;
#endif
                // __trigger = OCR1A;
                // __counter = counter;
                // __diff=distance;

            }
            break;
        }
        channel = channel_ptr;
        channel_ptr++;
    }
}

void Dimmer::_endHalfwave()
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
#if DEBUG_FAULTS
        _endCounter++;
#endif
        // dimming cycle complete, wait for next halfwave
        _state = StateEnum::NEXT_HALFWAVE;

        auto &frame = debugStats.getFrame();
        frame.endTicks = OCR1A;

        // set to next halfwave
        OCR1A = _startOCR1A + _halfwaveTicks;
        frame.nextTicks = OCR1A;
        _unlockCompareA();
    }
}

#if DEBUG_FAULTS

void Dimmer::_fault(const char *msg)
{
    uint16_t _TCNT1 = TCNT1;
    uint16_t _OCR1A = OCR1A;
    uint16_t _OCR1B = OCR1B;
    uint16_t __prevOCR1B = _prevOCR1B;
    uint16_t __startOCR1A = _startOCR1A;
    uint16_t __dcOCR1A = _dcOCR1A;
    uint8_t _TIMSK1 = TIMSK1;
    uint8_t _TIFR1 = TIFR1;
    uint8_t __state = (uint8_t)_state;
    uint8_t __intFlags = _intFlags;
    uint8_t _channel_number = (channel_ptr - ordered_channels);
    uint8_t channels[DIMMER_CHANNELS];
    FOR_CHANNELS(i) {
        channels[i] = digitalRead(dimmer_pins[i]);
    }
    end();
    Serial.println(msg);
    Serial_printf("TCNT1=%u,OCR1A=%u(%u),OCR1B=%u,", _TCNT1, _OCR1A, _OCR1A - DIMMER_COMPARE_B_EXTRA_TICKS, _OCR1B);
    Serial_printf("prevOCR1B=%u,dcOCR1A=%u,startOCR1A=%u,", __prevOCR1B, __dcOCR1A, __startOCR1A);
    Serial_printf("OCIE1A=%u,OCIE1B=%u,", !!(_TIMSK1 & _BV(OCIE1A)), !!(_TIMSK1 & _BV(OCIE1B)));
    Serial_printf("IFZCI=%u,IFOCA=%u,IFOCB=%u,", !!(__intFlags & _BV(_IFZCI)), !!(__intFlags & _BV(_IFOCA)), !!(__intFlags & _BV(_IFOCB)));
    Serial_printf("OCF1A=%u,OCF1B=%u\n", !!(_TIFR1 & _BV(OCF1A)), !!(_TIFR1 & _BV(OCF1B)));
    Serial_printf("state=%u,channel=%u,hw=%u\n", __state, _channel_number, _halfwaveTicks);
    for(dimmer_channel_id_t i = 0; ordered_channels[i].ticks; i++) {
        auto channel = ordered_channels[i].channel;
        Serial_printf("num=%u,ch=%d,ticks=%d,OCR1A=%u,pin=%u\n", i, channel, ordered_channels[i].ticks, ordered_channels[i]._OCR1A, channels[channel]);
    }
}

#endif

