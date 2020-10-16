/**
 * Author: sascha_lammers@gmx.de
 */

#include <Arduino.h>
#include "dimmer_reg_mem.h"
#include "dimmer_protocol.h"


void setup()
{
    Serial.begin(DEFAULT_BAUD_RATE);
    delay(500);
    Serial.println(F("Starting..."));
    delay(5000);
    Serial.println(F("Make sure to run ./scripts/read_def.py before, to update the print_def.h"));
    Serial.println();
}

void loop() {
    #include "./print_def.h"
    delay(60000);
}
