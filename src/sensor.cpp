/**
 * Author: sascha_lammers@gmx.de
 */

#include "sensor.h"
#include "adc.h"

#if HAVE_READ_INT_TEMP

bool is_Atmega328PB;

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
float get_internal_temperature()
{
    // return (((sum / 10.0) - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (float)dimmer_config.int_temp_offset;

    return (((_adc.getValue(ADCHandler::kPosIntTemp) / 64.0) - (is_Atmega328PB ? 247.0 : 324.31)) / 1.22);
    //TODO
    //dimmer_config.internal_temp_calibration.ts_gain
     //+ (float)dimmer_config.internal_temp_calibration;
}

#endif

#if HAVE_EXT_VCC

uint16_t read_vcc()
{
    // ADCValue = ADC readings * 64 (0-65472)
    // Vs = (((125 * R2) * ADCValue + (125 * R1) * ADCValue) * Vref) / (128 * 64 * R2)
    // for
    // R1=12K
    // R2=3K
    // N=64
    // ((ADCValue / 1024) * (Vref * 1000)) / N = (Vs * 3000) / (12000 + 3000)
    // Vs = (625 * ADCValue * Vref) / (128 * N)
    // Vs = (625 * ADCValue * Vref) / 8192


    return (625U * _adc.getValue(ADCHandler::kPosVCC) * (float)dimmer_config.internal_vref11) / 8192U;
}

#elif HAVE_READ_VCC

// read VCC in mV
uint16_t read_vcc()
{
    return (uint32_t)(((1024UL * 1000) << ADCHandler::kLeftShift) * (float)dimmer_config.internal_vref11) / _adc.getValue(ADCHandler::kPosVCC);
}

#endif

#if HAVE_POTI

uint16_t read_poti()
{
    constexpr uint16_t dead_zone = 50 << 6;
    constexpr uint16_t max_value = (1023U << ADCHandler::kLeftShift) - (dead_zone * 2) + (1 << ADCHandler::kLeftShift);
    auto value = _adc.getValue(ADCHandler::kPosPoti);
    if (value <= dead_zone) {
        return 0;
    }
    return (((uint32_t)(value - dead_zone)) * Dimmer::Level::max) / max_value;
}

#endif

#if HAVE_NTC

float convert_to_celsius(uint16_t value)
{
    // constexpr float kResistorFactor = NTC_SERIES_RESISTANCE / (float)NTC_NOMINAL_RESISTANCE;
    // constexpr float kNominalValue = 1.0 / (NTC_NOMINAL_TEMP + 273.15);
    // constexpr float kBetaCoEff = NTC_BETA_COEFF;
    float steinhart;
    // steinhart = 1023 / (float)value - 1;
    // steinhart = (((1023U << 6) / value) - 1) * kRFactor
    // steinhart = (((1023U << 6) / value) - 1) * kRFactor;
    steinhart = (1023 / (value / 64.0)) - 1;
    //steinhart = ((1023U << ADCHandler::kLeftShift) / value) - 1;
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
    return FAKE_NTC_VALUE + (float)dimmer_config.ntc_temp_offset;
#else
    return convert_to_celsius(_adc.getValue(ADCHandler::kPosNTC)) + (float)dimmer_config.ntc_temp_offset;
#endif
}

#endif
