/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"
#include "sensors.h"

#if HAVE_NTC

static uint16_t read_ntc_value()
{
    uint16_t value = analogRead(NTC_PIN);
    delay(1);
    return (value + analogRead(NTC_PIN)) / 2;
}

static float convert_to_celsius(uint16_t value)
{
    float steinhart;
    steinhart = (1023 / (float)value) - 1;
    steinhart *= NTC_SERIES_RESISTANCE;
    steinhart /= NTC_NOMINAL_RESISTANCE;
    steinhart = log(steinhart);
    steinhart /= NTC_BETA_COEFF;
    steinhart += 1.0 / (NTC_NOMINAL_TEMP + 273.15);
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    return steinhart;
}

#endif

uint16_t Sensors::readVCCmV()
{
    return readVCC() * 1000;
}

float Sensors::readVCC()
{
#if HAVE_READ_VCC

    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(40);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return 1024.0 * register_mem.data.cfg.vref11 / (float)ADCW;

#else

    return 0;

#endif
}

float Sensors::readTemperature()
{
#ifdef FAKE_NTC_VALUE

    return FAKE_NTC_VALUE;

#elif HAVE_NTC

    return convert_to_celsius(read_ntc_value()) + (register_mem.data.cfg.temperature_offset / DIMMER_TEMP_OFFSET_DIVIDER);

#else

    return NAN;

#endif

}

#if HAVE_READ_INT_TEMP
bool is_Atmega328PB = false; // runtime variable since the bootloader reports Atmega328P
#endif

float Sensors::readTemperature2()
{
#if HAVE_READ_INT_TEMP

    // https://playground.arduino.cc/Main/InternalTemperatureSensor/

    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    delay(40); // 20 was not enough. It takes quite a while when switching from reading VCC to temp.
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    // TODO verify calculation, it is way off for a couple of chips
    return ((ADCW - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (register_mem.data.cfg.temperature2_offset / DIMMER_TEMP_OFFSET_DIVIDER);

#else

    return NAN;

#endif
}
