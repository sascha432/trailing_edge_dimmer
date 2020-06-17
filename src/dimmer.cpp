/**
 * Author: sascha_lammers@gmx.de
 */

#include <util/atomic.h>
#include "helpers.h"
#include "dimmer.h"
#include "i2c_slave.h"
#include "cubic_interpolation.h"

Dimmer dimmer;

#if DEBUG_COMPARE_B_PIN
volatile uint8_t *pinCmpBAddr;
uint8_t pinCmpBMask;
#endif

Dimmer::Dimmer() : dimmer_t(), _halfwaveTicks(0), _cycleCounter(0), _state(StateEnum::MEASURE), _intFlags(0)
{
#if DEBUG_COMPARE_B_PIN
    pinMode(DEBUG_COMPARE_B_PIN, OUTPUT);
    pinCmpBMask = digitalPinToBitMask(DEBUG_COMPARE_B_PIN);
    pinCmpBAddr = portOutputRegister(digitalPinToPort(DEBUG_COMPARE_B_PIN));
#endif

    FOR_CHANNELS(i) {
	    _pinsMask[i] = digitalPinToBitMask(dimmer_pins[i]);
	    _pinsAddr[i] = portOutputRegister(digitalPinToPort(dimmer_pins[i]));
        _D(5, Serial_printf_P(PSTR("Channel %u, pin %u, address %02x, mask %02x\n"), i, dimmer_pins[i], dimmer_pins_addr[i], dimmer_pins_mask[i]));
    }

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
    if (_halfwaveTicks) {
        return (F_CPU / DIMMER_TIMER1_PRESCALER / 2) / (float)_halfwaveTicks;
    }
    return NAN;
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

            Serial_printf_P(PSTR("measure %lu hw %u zcmt %lu\n"), (long)ticks, _halfwaveTicks, (long)clockCyclesToMicroseconds(_halfwaveTicks * (94UL * DIMMER_TIMER1_PRESCALER)) / 100);//TODO debug remove

#if DIMMER_ZC_FILTER
            _zcIntMinTime = clockCyclesToMicroseconds(_halfwaveTicks * (94UL * DIMMER_TIMER1_PRESCALER)) / 100;
#endif
        }
        _cycleCounter++;
    }
}

uint32_t Dimmer::getTicks(uint16_t counter)
{
    cli();
    uint32_t result = _ticks;
    _ticks = -(int32_t)counter;
    sei();
    result += counter;
    return result;
}

ISR(TIMER1_OVF_vect)
{
    dimmer._overflow();
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

    cli();
    detachInterrupt(digitalPinToInterrupt(ZC_SIGNAL_PIN));

    FOR_CHANNELS(i) {
        disableChannel(i);
        pinMode(dimmer_pins[i], INPUT);
    }
    _state = StateEnum::STOPPED;
    disableTimer1();
    sei();
}

void Dimmer::enableChannel(dimmer_channel_id_t channel)
{
    *_pinsAddr[channel] |= _pinsMask[channel];
}

void Dimmer::disableChannel(dimmer_channel_id_t channel)
{
    *_pinsAddr[channel] &= ~_pinsMask[channel];
}

uint16_t Dimmer::getChannel(dimmer_level_t level) const
{
    uint16_t ticks = (level * (uint32_t)_halfwaveTicks) / DIMMER_MAX_LEVELS;
    // TODO optimize code, precalculate min_on_level max_on_level
    if (ticks < dimmer_config.min_on_ticks) {
        return dimmer_config.min_on_ticks;
    }
    uint16_t max = _halfwaveTicks - dimmer_config.max_on_ticks;
    if (ticks >= max) {
        return 0xffff;
    }
    return ticks;
}

void Dimmer::_zcHandler(uint16_t counter)
{
#if 1 //DEBUG
    static volatile uint8_t count = 0;
    if (_intFlags & _BV(_IFZCI)) {
        count++;
        sei();
        Serial_printf("zcl %u st %u ws %u\n", count, (int)_state, _intFlags & _BV(_IFCAB));
        if (count > 100) {
            end();
        }
        return;
    }
    count = 0;
#else
    if (_zcLocked) {
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
    // lock ZC interrupt
    _intFlags |= _BV(_IFZCI);
    sei();

    if (_state == StateEnum::MEASURE) { // wait until the measurement has been completed
        addEvent(counter);
        cli();
        // unlock ZC interrupt
        _intFlags &= ~_BV(_IFZCI);
        sei();
    }
    else {

        uint16_t endTicks = _halfwaveTicks + counter;
        endTicks += dimmer_config.zero_crossing_delay_ticks; // add zero crossing delay
        endTicks -= DIMMER_COMPARE_B_EXTRA_TICKS;

        // if the frequency increases, compare B might not be executed yet
        // this also waits until compare A has been called to intialize the halfwave
        while (_intFlags & _IFCAB) {
        }

        cli();
        // lock compare A/B interrupt
        _intFlags |= _BV(_IFCAB);
        OCR1B = endTicks;
        // clear interrupt B flag and enable interrupt
        TIFR1 |= _BV(OCF1B);
        TIMSK1 |= _BV(OCIE1B);
        sei();

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
        cli();
        // unlock ZC interrupt
        _intFlags &= ~_BV(_IFZCI);
        sei();

        _D(10, Serial.println(F("ZC int")));
        dimmer_apply_fading();
    }
}

void Dimmer::_compareA()
{
    switch(_state) {
        case StateEnum::START_HALFWAVE:
            // sync compare A/B and zero crossing interrupt
            // _intFlags &= ~_BV(_IFCAB);
            _state = StateEnum::HALFWAVE;
            sei();
            _startHalfwave();
            break;
        case StateEnum::HALFWAVE:
            sei();
            _dimmingCycle();
            break;
        default:
#if DEBUG_FAULTS
            _fault("compare A invalid state");
#endif
            break;
    }
}

void Dimmer::_compareB()
{
#if DEBUG_COMPARE_B_PIN
    *pinCmpBAddr = *pinCmpBAddr ^ pinCmpBMask;
#endif
#if DEBUG_FAULTS
    if (_state == StateEnum::HALFWAVE) {
        _fault("compare B during dimming cycle"); // good change that _dimmingCycle did not finish if dcOCR1A==OCR1A
        return;
    }
    else if (TIMSK1 & _BV(OCIE1A)) {
        _fault("compare A still active"); // most likely it was skipped due to insufficient time between compare B and A interrupt (DIMMER_COMPARE_B_EXTRA_TICKS)
        return;
    }
    _prevOCR1B = OCR1B;
#endif
    _state = StateEnum::START_HALFWAVE;
    // point OCR1A to the beginning of the halfwave
    OCR1A = OCR1B + DIMMER_COMPARE_B_EXTRA_TICKS;
    // clear compare A interrupt flag
    TIFR1 |= _BV(OCF1A);
    // disable compare B, enable compare A interrupt
    TIMSK1 = (TIMSK1 & ~_BV(OCIE1B)) | _BV(OCIE1A);
    // copy double buffer
    memcpy(&ordered_channels, &ordered_channels_buffer, sizeof(ordered_channels));
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
    auto channel = &ordered_channels[0];
    if (channel->ticks) { // any channel active?
        channel_ptr = 0;
        OCR1A += channel->ticks;
#if DEBUG_FAULTS
        if (channel->ticks < (128 / DIMMER_TIMER1_PRESCALER)) {
            _fault("ticks less than 128 / DIMMER_TIMER1_PRESCALER");
            return;
        }
#endif
        // turn channels on first
        // the delay between turning on a channel is ~2µs @ 16MHz (or 16µs between channel 0 and 7, having 8 channels and all of them enabled)
        for(; channel->ticks; channel++) {
            enableChannel(channel->channel);
        }
        // for(i = 0; ordered_channels[i].ticks; i++) {
        //     enableChannel(ordered_channels[i].channel);
        // }

        FOR_CHANNELS(i) {
            if (!dimmer_level(i)) {
                disableChannel(i);
            }
        }
        // _state = StateEnum::HALFWAVE;
        // sei();
    }
    else {
        // all channels off
        FOR_CHANNELS(i) {
            disableChannel(i);
        }
        _endHalfwave();
    }
}

void Dimmer::_dimmingCycle()
{
    uint16_t startOCR1A = OCR1A;
    dimmer_channel_t *channel = &ordered_channels[channel_ptr++];
    dimmer_channel_t *next_channel = &ordered_channels[channel_ptr];
    for(;;) {
        disableChannel(channel->channel);    // turn off current channel
#if DEBUG_FAULTS
        channel->_OCR1A = OCR1A;
#endif

        if (next_channel->ticks == 0 || next_channel->ticks == 0xffff) {
            _endHalfwave();
            break;
        }
        else if (next_channel->ticks > channel->ticks) {
            // next channel has a different time slot, re-schedule
            // add the difference
            uint16_t diff = next_channel->ticks - channel->ticks;
#define DEBUG_OVERFLOW 1
#if DEBUG_OVERFLOW
            bool ovf = false;
            uint16_t cnt2, cnt1;
#endif

            ATOMIC_BLOCK(ATOMIC_FORCEON) {
                // setting OCR1A close to the previous compare interrupt is a bit tricky
                // we cannot use TIFR1/TOV1 since interrupts were enabled before
                // it adds up to 2µs @ 16MHz if the levels are too close
                OCR1A += diff;
                uint16_t cnt = (32 / DIMMER_TIMER1_PRESCALER) + TCNT1;
                if (cnt < startOCR1A) { // overflow within the next 32 cpu cycles
                    OCR1A = max(OCR1A, (0x10000UL + (32 / DIMMER_TIMER1_PRESCALER)) + TCNT1);
#if DEBUG_OVERFLOW
                    cnt2 = TCNT1;
                    cnt1 = cnt;
                    ovf = true;
#endif
                }
                else {
                    // add 16 extra cycles
                    OCR1A = max(OCR1A, (16 / DIMMER_TIMER1_PRESCALER) + TCNT1);
                }
#if DEBUG_FAULTS
                uint16_t tmp = TCNT1;
                // next_channel->_OCR1A = OCR1A;
                _dcOCR1A = OCR1A;
                if (tmp >= OCR1A) {
                    // if compare A has not been triggered we missed TCNT1
                    if ((TIFR1 & _BV(OCF1A)) == 0) {
#if DEBUG_OVERFLOW
                        if (ovf) {
                            Serial_printf("dc ovf %u %u %u %u\n", startOCR1A, cnt1, OCR1A, cnt2);
                        }
#endif
                        _fault("OCR1A missed");
                    }
                }
#endif
            }
#if DEBUG_OVERFLOW && 0
            if (ovf) {
                Serial_printf("dc ovf %u %u %u %u\n", startOCR1A, cnt1, OCR1A, cnt2);
            }
#endif
            break;
        }
        channel = next_channel;
        channel_ptr++;
        next_channel = &ordered_channels[channel_ptr];
    }
}

void Dimmer::_endHalfwave()
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        // sync compare A/B and zero crossing interrupt
        _intFlags &= ~_BV(_IFCAB);
        // dimming cycle complete, wait for next halfwave
        _state = StateEnum::NEXT_HALFWAVE;
        // clear compare A interrupt flag
        TIFR1 |= _BV(OCF1A);
        // disable compare A interrupt
        TIMSK1 &= ~_BV(OCIE1A);
    }
}

#if DEBUG_FAULTS

void Dimmer::_fault(const char *msg)
{
    uint16_t _TCNT1 = TCNT1;
    uint16_t _OCR1A = OCR1A;
    uint16_t _OCR1B = OCR1B;
    uint16_t __prevOCR1B = _prevOCR1B;
    uint16_t __dcOCR1A = _dcOCR1A;
    uint8_t _TIMSK1 = TIMSK1;
    uint8_t _TIFR1 = TIFR1;
    uint8_t __state = (uint8_t)_state;
    uint8_t __intFlags = _intFlags;
    uint8_t _channel_ptr = channel_ptr;
    uint8_t channels[DIMMER_CHANNELS];
    FOR_CHANNELS(i) {
        channels[i] = !!(*_pinsAddr[i] & _pinsMask[i]);
    }
    end();
    Serial.println(msg);
    Serial_printf("TCNT1=%u,OCR1A=%u(%u),OCR1B=%u,", _TCNT1, _OCR1A, _OCR1A - DIMMER_COMPARE_B_EXTRA_TICKS, _OCR1B);
    Serial_printf("prevOCR1B=%u,dcOCR1A=%u,", __prevOCR1B, __dcOCR1A);
    Serial_printf("OCIE1A=%u,OCIE1B=%u,IFZCI=%u,IFCAB=%u,", _TIMSK1 & _BV(OCIE1A), _TIMSK1 & _BV(OCIE1B), __intFlags & _BV(_IFZCI), __intFlags & _BV(_IFCAB));
    Serial_printf("OCF1A=%u,OCF1B=%u\n", _TIFR1 & _BV(OCF1A), _TIFR1 & _BV(OCF1B));
    Serial_printf("state=%u,channel_ptr=%u\n", __state, _channel_ptr);
    for(dimmer_channel_id_t i = 0; ordered_channels[i].ticks; i++) {
        auto channel = ordered_channels[i].channel;
        Serial_printf("num=%u,ch=%d,ticks=%d,OCR1A=%u,pin=%u\n", i, channel, ordered_channels[i].ticks, ordered_channels[i]._OCR1A, channels[channel]);
    }
}

#endif