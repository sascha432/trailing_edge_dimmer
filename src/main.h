/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <util/atomic.h>
#include "dimmer.h"
#include "i2c_slave.h"
#if SERIAL_I2C_BRDIGE
#include "SerialTwoWire.h"
#else
#include <Wire.h>
#endif

#if DIMMER_I2C_SLAVE && DIMMER_CHANNELS > 8
#error I2C is limited to 8 channels
#endif

#ifndef SERIAL_I2C_BRDIGE
#define SERIAL_I2C_BRDIGE                       0
#endif

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE                       115200
#endif

#ifndef HAVE_NTC
#define HAVE_NTC                                1
#endif

#ifndef HAVE_READ_VCC
#define HAVE_READ_VCC                           1
#endif

#ifndef INTERNAL_VREF_1_1V
// after calibration VCC readings are pretty accurate, +-2-3mV
// default for cfg.internal_1_1v_ref
#define INTERNAL_VREF_1_1V                      1.1
#endif

#ifndef HAVE_READ_INT_TEMP
#define HAVE_READ_INT_TEMP                      1
#endif

// NTC pin
#ifndef NTC_PIN
#define NTC_PIN                                 A1
#endif

// beta coefficient
#ifndef NTC_BETA_COEFF
#define NTC_BETA_COEFF                          3950
#endif
// resistor in series with the NTC
#ifndef NTC_SERIES_RESISTANCE
#define NTC_SERIES_RESISTANCE                   3300
#endif
// ntc resistance @ 25°C
#ifndef NTC_NOMINAL_RESISTANCE
#define NTC_NOMINAL_RESISTANCE                  10000
#endif

#ifndef NTC_NOMINAL_TEMP
#define NTC_NOMINAL_TEMP                        25
#endif

#define SERIAL_INPUT_BUFFER_MAX_LENGTH          64
#define SERIAL_MAX_ARGUMENTS                    10

#ifndef HAVE_PRINT_METRICS
#define HAVE_PRINT_METRICS                      1
#endif

// delay in milliseconds before metrics are printed again
#ifndef PRINT_METRICS_REPEAT
#define PRINT_METRICS_REPEAT                    5000
#endif
// write EEPROM after a delay in milliseconds
#define EEPROM_WRITE_DELAY                      500
// if writing is requested multiple times within this period, increase delay to the same time
#define EEPROM_REPEATED_WRITE_DELAY             1000

// size with old eeprom lib 28258

void rem(); // print "+REM="
void write_config();


class dimmer_scheduled_calls_t {
public:
    dimmer_scheduled_calls_t() = default;
    struct {
        uint8_t readVCC: 1;
        uint8_t readIntTemp: 1;
        uint8_t readNTCTemp: 1;
        uint8_t writeEEPROM: 1;
        uint8_t printMetrics: 1;
        uint8_t fadingCompleted: 1;
    };
};

//  // bitset
//  typedef enum : dimmer_scheduled_calls_t {
//     TYPE_NONE =             0,
//     READ_VCC =              0x01,
//     READ_INT_TEMP =         0x02,
//     READ_NTC_TEMP =         0x04,
//     EEPROM_WRITE =          0x08,
//     PRINT_METRICS =         0x10,
// } dimmer_scheduled_calls_enum_t;

extern unsigned long next_temp_check;

#if HAVE_PRINT_METRICS
extern unsigned long print_metrics_timeout;
#endif

extern dimmer_scheduled_calls_t dimmer_scheduled_calls;

template<class T>
uint8_t Wire_read(T &data) {
    return Wire.readBytes(reinterpret_cast<uint8_t *>(&data), sizeof(data));
}

template<class T>
uint8_t Wire_write(T &data) {
    return Wire.write(reinterpret_cast<const uint8_t *>(&data), sizeof(data));
}

#if HAVE_READ_INT_TEMP
float get_internal_temperature();
#endif

void display_dimmer_info();

#if HAVE_READ_VCC
uint16_t read_vcc();
#endif

#if HAVE_NTC
float get_ntc_temperature();
#endif
