/**
 * Author: sascha_lammers@gmx.de
 */

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

#if 0
    // generate defines for inline assembler
    for(int j = 0; j < 8; j++) {
        for(int i = 0; i < 16; i++) {
            Serial_printf_P(PSTR("#if xBI_CHANNEL%u==%u\n"), j, i);
            Serial.flush();
            Serial_printf_P(PSTR("    #define xBI_ARGS_CHANNEL%u \"0x%02x,%d\"\n"), j, portOutputRegister(digitalPinToPort(i)) - __SFR_OFFSET, _BV2B(digitalPinToBitMask(i)));
            Serial.flush();
            Serial.println(F("#endif"));
            Serial.flush();
        }
    }
#endif

#if !HAVE_ASM_CHANNELS
    FOR_CHANNELS(i) {
	    _pinsMask[i] = digitalPinToBitMask(dimmer_pins[i]);
	    _pinsAddr[i] = portOutputRegister(digitalPinToPort(dimmer_pins[i]));
        _D(5,
            {
                Serial_printf_P(PSTR("Channel %u, pin %u, address %02x, mask %02x\n"), i, dimmer_pins[i], _pinsAddr[i], _pinsMask[i]);
                Serial.flush();
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

#if !HAVE_ASM_CHANNELS

void Dimmer::enableChannel(dimmer_channel_id_t channel)
{
    *_pinsAddr[channel] |= _pinsMask[channel];
}

void Dimmer::disableChannel(dimmer_channel_id_t channel)
{
    *_pinsAddr[channel] &= ~_pinsMask[channel];
}
#endif

uint16_t Dimmer::getChannel(dimmer_level_t level) const
{
    uint16_t ticks = (level * (uint32_t)_halfwaveTicks) / DIMMER_MAX_LEVELS;
    if (ticks < dimmer_config.min_on_ticks) {
        return dimmer_config.min_on_ticks;
    }
    uint16_t max = _halfwaveTicks - dimmer_config.max_on_ticks;
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
    if (_intFlags & _BV(_IFZCI)) {
        if (++count > 200) {
            _fault("ZC locked 200 times");
        }
        return;
    }
    count = 0;
#else
    if (_intFlags & _BV(_IFZCI)) {
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
    // lock ZC interrupt before allowing interrupts
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
        // uint16_t counter = 0;
        while (_intFlags & _BV(_IFCAB)) {
            // counter++;
        }
        // if (counter > 10) {
        //     Serial.println(counter);
        // }

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
        _applyFading();
    }
}

void Dimmer::_compareA()
{
    switch(_state) {
        case StateEnum::START_HALFWAVE:
            // // sync compare A/B and zero crossing interrupt
            _intFlags &= ~_BV(_IFCAB);
            _state = StateEnum::HALFWAVE;
            sei();
            _startHalfwave();
            break;
        case StateEnum::HALFWAVE:
            _dimmingCycle(OCR1A);
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
// #if DEBUG_COMPARE_B_PIN
//     *pinCmpBAddr = *pinCmpBAddr ^ pinCmpBMask;
// #endif
    // compare A still active
    if (_intFlags & _BV(_IFOCA)) {
        // disable compare B
        TIMSK1 &= ~_BV(OCIE1B);
        sei();
        *pinCmpBAddr |= pinCmpBMask;
        delayMicroseconds(10);
        *pinCmpBAddr &= ~pinCmpBMask;
        Serial_printf("skipB %u %u\n", OCR1A, OCR1B + DIMMER_COMPARE_B_EXTRA_TICKS);
        _fault("compare A active");

// +REM=zcdelay=-20
// skipB 52710 52153
// compare A active
// TCNT1=53182,OCR1A=62907(62843),OCR1B=3219,prevOCR1B=35423,dcOCR1A=62907,OCIE1A=1,OCIE1B=1,IFZCI=0,IFCAB=1,OCF1A=0,OCF1B=0
// state=3,channel_number=3
// num=0,ch=0,ticks=4068,OCR1A=52099,pin=0
// num=1,ch=1,ticks=4679,OCR1A=52710,pin=0
// num=2,ch=3,ticks=4681,OCR1A=52735,pin=0
// num=3,ch=2,ticks=14853,OCR1A=0,pin=1
        return;
    }
#if DEBUG_FAULTS
    if (_state == StateEnum::START_HALFWAVE) {
        _fault("compare B during start");
        return;
    }
    else if (_state == StateEnum::HALFWAVE) {
        _fault("compare B during dimming cycle");
        return;
    }
    else if (TIMSK1 & _BV(OCIE1A)) {
        _fault("compare A still active"); // most likely it was skipped due to insufficient time between compare B and A interrupt (DIMMER_COMPARE_B_EXTRA_TICKS)
        return;
    }
    _prevOCR1B = OCR1B;
#endif
    _state = StateEnum::START_HALFWAVE;
    // set compare A active
    _intFlags |= _BV(_IFOCA);
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
    auto channel = ordered_channels;
    if (channel->ticks) { // any channel active?
        channel_ptr = channel;
        OCR1A += channel->ticks;
        // turn channels on first
        // the delay between turning on a channel is ~2µs @ 16MHz for 2 active channels (or 6.45µs for 4 active channels)
        // using inline assembler reduces the delay to 1.25µs (or 3.6µs for 4 active channels)
        do {
            enableChannel(channel->channel);
            channel++;
        } while(channel->ticks);

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
            //         Serial.flush();
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
            // _intFlags &= ~_BV(_IFCAB);
        // mark compare A as done
        _intFlags &= ~_BV(_IFOCA);
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
    uint8_t _channel_number = (channel_ptr - ordered_channels);
    uint8_t channels[DIMMER_CHANNELS];
    FOR_CHANNELS(i) {
        channels[i] = digitalRead(dimmer_pins[i]);
    }
    end();
    Serial.println(msg);
    Serial_printf("TCNT1=%u,OCR1A=%u(%u),OCR1B=%u,", _TCNT1, _OCR1A, _OCR1A - DIMMER_COMPARE_B_EXTRA_TICKS, _OCR1B);
    Serial_printf("prevOCR1B=%u,dcOCR1A=%u,", __prevOCR1B, __dcOCR1A);
    Serial_printf("OCIE1A=%u,OCIE1B=%u,IFZCI=%u,IFCAB=%u,", !!(_TIMSK1 & _BV(OCIE1A)), !!(_TIMSK1 & _BV(OCIE1B)), !!(__intFlags & _BV(_IFZCI)), !!(__intFlags & _BV(_IFCAB)));
    Serial_printf("OCF1A=%u,OCF1B=%u\n", !!(_TIFR1 & _BV(OCF1A)), !!(_TIFR1 & _BV(OCF1B)));
    Serial_printf("state=%u,channel_number=%u\n", __state, _channel_number);
    for(dimmer_channel_id_t i = 0; ordered_channels[i].ticks; i++) {
        auto channel = ordered_channels[i].channel;
        Serial_printf("num=%u,ch=%d,ticks=%d,OCR1A=%u,pin=%u\n", i, channel, ordered_channels[i].ticks, ordered_channels[i]._OCR1A, channels[channel]);
    }
}

#endif
