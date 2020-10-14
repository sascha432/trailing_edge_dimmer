/**
 * Author: sascha_lammers@gmx.de
 */

#include "sensor.h"

#if HAVE_READ_INT_TEMP

bool is_Atmega328PB;

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
float get_internal_temperature()
{
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    uint16_t sum = 0;
    for (uint8_t i = 0; i < 25; i++) {
        delay(1);
        if (i == 15) { // start after 15ms
            sum = 0;
        }
        ADCSRA |= _BV(ADSC);
        while (bit_is_set(ADCSRA, ADSC)) ;
        sum += ADCW;
    }
    return (((sum / 10.0) - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (float)(dimmer_config.int_temp_offset / 4.0f);
}

#endif

#if HAVE_READ_VCC

#if HAVE_EXT_VCC

uint16_t read_vcc()
{
    analogReference(INTERNAL);
    analogRead(VCC_PIN);
    uint32_t sum = 0;
    for(uint8_t i = 0; i < 25; i++) {
        delay(1);
        if (i == 15) { // start after 15ms
            sum = 0;
        }
        sum += analogRead(VCC_PIN);
    }

    // Vout = (Vs * R2) / (R1 + R2)
    // ((ADCValue / 1024) * (Vref * 1000)) / N = (Vs * R2) / (R1 + R2)
    // Vs=((125*ADCValue*R2+125*ADCValue*R1)*Vref)/(128*N*R2)

    // R1=12K
    // R2=3K
    // N=10
    // ((ADCValue / 1024) * (Vref * 1000)) / N = (Vs * 3000) / (12000 + 3000)
    // Vs=(625*ADCValue*Vref)/(128*N)

    return (625UL * sum * dimmer_config.internal_1_1v_ref) / 1280U;
}

#endif

// read VCC in mV
uint16_t read_vcc_int()
{
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); // analogReference(DEFAULT) = AVCC with external capacitor at AREF pin
    uint16_t sum = 0;
    for (uint8_t i = 0; i < 20; i++) {
        delay(1);
        if (i == 10) { // start after 10ms
            sum = 0;
        }
        ADCSRA |= _BV(ADSC);
        while (bit_is_set(ADCSRA, ADSC));
        sum += ADCW;
    }
    return (10UL * 1000UL * 1024UL) * dimmer_config.internal_1_1v_ref / (float)sum;
}

#endif

#if HAVE_POTI

uint16_t raw_poti_value;
static int32_t poti_value;
static unsigned long poti_read_timer = 0;

int32_t read_poti()
{
    if (millis() < poti_read_timer) {
        return poti_value;
    }
    poti_read_timer = millis() + 100;

    analogReference(DEFAULT);
    raw_poti_value = 0;
    for(uint8_t i = 0; i < 5; i++) {
        delay(1);
        raw_poti_value += analogRead(POTI_PIN);
    }
    raw_poti_value /= 5;

    static constexpr uint8_t dead_zone = 50;
    return (poti_value = (((int32_t)(raw_poti_value) - dead_zone) * Dimmer::Level::max) / (1024 - (dead_zone * 2)));
}

#endif

#if HAVE_NTC

uint16_t read_ntc_value()
{
    analogReference(DEFAULT);
    uint16_t value = analogRead(NTC_PIN);
    for(uint8_t i = 1; i < 5; i++) {
        delay(1);
        value += analogRead(NTC_PIN);
    }
    return value / 5;
}

float convert_to_celsius(uint16_t value)
{
    float steinhart;
    steinhart = 1023 / (float)value - 1;
    steinhart *= NTC_SERIES_RESISTANCE;
    steinhart /= NTC_NOMINAL_RESISTANCE;
    steinhart = log(steinhart);
    steinhart /= NTC_BETA_COEFF;
    steinhart += 1.0 / (NTC_NOMINAL_TEMP + 273.15);
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    return steinhart;
}

float get_ntc_temperature()
{
#ifdef FAKE_NTC_VALUE
    return FAKE_NTC_VALUE;
#else
    return convert_to_celsius(read_ntc_value()) + (float)(dimmer_config.ntc_temp_offset / 4.0f);
#endif
}

#endif
