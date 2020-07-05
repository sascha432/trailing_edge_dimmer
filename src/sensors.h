/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>

class Sensors {
public:
    // read VCC in mV
    static uint16_t readVCCmV();
    // read VCC in V
    static float readVCC();
    // NTC
    static float readTemperature();
    // internal ATmega sensors
    static float readTemperature2();
};
