/**
 * Author: sascha_lammers@gmx.de
 */

#include <Arduino.h>
#include "dimmer_def.h"
#include "dimmer_protocol.h"
#include "dimmer_reg_mem.h"


void setup()
{
    Serial.begin(DEFAULT_BAUD_RATE);
    delay(500);
    Serial.println(F("Starting..."));
    Serial.println(F("Copy output to ./src/dimmer_protocol_const.h"));
    delay(5000);
    Serial.println();
}

void loop() {
    #include "./print_def.h"
    delay(60000);
}
