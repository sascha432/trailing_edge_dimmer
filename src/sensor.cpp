/**
 * Author: sascha_lammers@gmx.de
 */

#include "sensor.h"
#include "adc.h"

#if HAVE_READ_INT_TEMP

// LSB are the ADC readings for 3 given temperatures
// those are different for the type of MCU

// avr_temp_ofs_gain.py can be used to find TS_GAIN and TS_OFFSET for different calibration points (Temperature/LSB)
// it is recommended to calibrate each chip at 20 and 55 °C to get a precision of +-2°C

// ATmega328PB
// T°C 	    -40 	+25 	+105
// LSB 	    205 	270 	350
// T = ((ADC - 247) * 1.0) / 1.22 + 32
// the closest values for
// T = ((ADC - (273 + 100 - TS_OFFSET)) * 128) / TS_GAIN + 25
// are
// TS_GAIN = 156, TS_OFFSET = 112

// ATmega328P
// T 		-40 	+25 	+125
// LSB		269		352		480
// T = ((ADC - (273 + 100 - TS_OFFSET)) * 128) / TS_GAIN + 25
// TS_GAIN = 164 TS_OFFSET = 21

int16_t get_internal_temperature()
{
    return ((((_adc.getIntTempValue() >> ADCHandler::kAveragePrecisionBits) - (273 + 100 - dimmer_config.internal_temp_calibration.ts_offset)) * 128) / dimmer_config.internal_temp_calibration.ts_gain) + 25;
}

#if __AVR_ATmega328P__ && MCU_IS_ATMEGA328PB == 0

#include <avr/boot.h>

internal_temp_calibration_t atmega328p_read_ts_values()
{
    internal_temp_calibration_t values;
    constexpr uint16_t TS_GAIN = 0x0005;
    constexpr uint16_t TS_OFFSET = 0x0007;
    loop_until_bit_is_clear(SPMCSR, SPMEN);
    SPMCSR |= (_BV(SIGRD)|_BV(SPMEN));
    asm(
        "lpm %0, Z\n"
        : "=r" (values.ts_gain)
        : "z" (TS_GAIN)
    );
    loop_until_bit_is_clear(SPMCSR, SPMEN);
    SPMCSR |= (_BV(SIGRD)|_BV(SPMEN));
    asm(
        "lpm %0, Z\n"
        : "=r" (values.ts_offset)
        : "z" (TS_OFFSET)
    );
    return values;

    // Source: http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
    // LDI R30,LOW(TS_GAIN)
    // LDI R31,HIGH (TS_GAIN)
    // RCALL Read_signature_row
    // MOV R17,R16; Save R16 result
    // LDI R30,LOW(TS_OFFSET)
    // LDI R31,HIGH (TS_OFFSET)
    // RCALL Read_signature_row
    // ; R16 holds TS_OFFSET and R17 holds TS_GAIN
    // Read_signature_row:
    // IN R16,SPMCSR; Wait for SPMEN ready
    // SBRC R16,SPMEN; Exit loop here when SPMCSR is free
    // RJMP Read_signature_row
    // LDI R16,((1<<SIGRD)|(1<<SPMEN)); We need to set SIGRD and SPMEN together
    // OUT SPMCSR,R16; and execute the LPM within 3 cycles
    // LPM R16,Z
    // RET
}

#endif

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


    register_mem.data.metrics.vcc = (625U * _adc.getValue(ADCHandler::kPosVCC) * (float)dimmer_config.internal_vref11) / 8192U;
    return register_mem.data.metrics.vcc;
}

#elif HAVE_READ_VCC

#if 1

// read VCC in mV (faster version with rounding error every 11th millivolt)
uint16_t read_vcc()
{
    static_assert(internal_vref11_t::shift == 12 && internal_vref11_t::offset == 0x3f8ccccd, "values do not match");
    register_mem.data.metrics.vcc = (72090000UL + dimmer_config.internal_vref11._value * 31982) / _adc.getVCCValue();
    return register_mem.data.metrics.vcc;
}

#else

// read VCC in mV
uint16_t read_vcc()
{
    register_mem.data.metrics.vcc = (uint32_t)(((1024UL * 1000) << ADCHandler::kAveragePrecisionBits) * (float)dimmer_config.internal_vref11) / _adc.getValue(ADCHandler::kPosVCC);
    return register_mem.data.metrics.vcc;
}

#endif

#endif

#if HAVE_POTI

uint16_t read_poti()
{
    constexpr uint16_t dead_zone = 50 << 6;
    constexpr uint16_t max_value = (1023U << ADCHandler::kAveragePrecisionBits) - (dead_zone * 2) + (1 << ADCHandler::kAveragePrecisionBits);
    auto value = _adc.getPotiValue();
    if (value <= dead_zone) {
        return 0;
    }
    return (((uint32_t)(value - dead_zone)) * Dimmer::Level::max) / max_value;
}

#endif

#if HAVE_NTC

float convert_to_celsius(uint16_t value)
{
    float steinhart = ((1023U << ADCHandler::kAveragePrecisionBits) / (float)value) - 1;
    steinhart *= NTC_SERIES_RESISTANCE / (float)NTC_NOMINAL_RESISTANCE;
    steinhart = log(steinhart);
    steinhart /= NTC_BETA_COEFF;
    steinhart += 1.0 / (NTC_NOMINAL_TEMP + 273.15);
    steinhart = 1.0 / steinhart;
    return steinhart - 273.15;
}

float get_ntc_temperature()
{
    #ifdef FAKE_NTC_VALUE
        return FAKE_NTC_VALUE + (float)dimmer_config.ntc_temp_cal_offset;
    #else
        return convert_to_celsius(_adc.getNTCValue()) + (float)dimmer_config.ntc_temp_cal_offset;
    #endif
}

#endif
