/**
 * Author: sascha_lammers@gmx.de
 */

/*

Sample code for dimmer library
Controls the dimmer via keyboard over the serial interface


Setup PINs and interrupts

    dimmer_setup();

Set level of a channel

    void dimmer_set_level(uint8_t channel, int16_t level);

Fade from current level to new level. The specified time is fading from 0-100% if absolute_time is set to false.
Any fading operation in progress is aborted.

    void dimmer_fade(uint8_t channel, int16_t to_level, float time_in_seconds, bool absolute_time = false);

Minimal program

    void setup() {
        dimmer_setup();
    }

    void loop() {
        // use dimmer_set_level() or dimmer_fade()
    }


*/

#include <Arduino.h>
#include "helpers.h"
#include "dimmer.h"

void setup() {

    Serial.begin(115200);
    dimmer_setup();
}

uint8_t selected_channel = 0;
uint8_t read_input_type = 0;
float fade_time = 5;
String line;

void loop() {

    if (Serial.available()) {

        if (read_input_type) {

            if (SerialEx.readLine(line, true)) {
                long l;
                float f;
                switch(read_input_type) {
                    case 1:
                        l = line.toInt();
                        if (l >= 0 && l < DIMMER_MAX_LEVEL) {
                            selected_channel = l;
                            SerialEx.printf_P(PSTR("Channel %u selected\n"), (unsigned)selected_channel);
                        } else {
                            Serial.println(F("Invalid channel"));
                        }

                        break;
                    case 2:
                        f = line.toFloat();
                        if (f != 0) {
                            dimmer_set_lcf(f);
                            SerialEx.printf_P(PSTR("LCF set to %s div %s\n"), float_to_str(dimmer.linear_correction_factor), float_to_str(dimmer.linear_correction_factor_div));
                        }
                        break;
                    case 3:
                        f = line.toFloat();
                        if (f != 0) {
                            fade_time = f;
                            SerialEx.printf_P(PSTR("Fade time set to %s\n"), float_to_str(fade_time));
                        }
                        break;
                }
                read_input_type = 0;
            }


        } else {
            uint8_t input;
            switch(input = Serial.read()) {

                case 'q':
                    selected_channel = 0;
                    SerialEx.printf_P(PSTR("Channel %u selected\n"), (unsigned)selected_channel);
                    break;
                case 'w':
                    selected_channel = 1;
                    SerialEx.printf_P(PSTR("Channel %u selected\n"), (unsigned)selected_channel);
                    break;
                case 'e':
                    selected_channel = 2;
                    SerialEx.printf_P(PSTR("Channel %u selected\n"), (unsigned)selected_channel);
                    break;
                case 'r':
                    selected_channel = 3;
                    SerialEx.printf_P(PSTR("Channel %u selected\n"), (unsigned)selected_channel);
                    break;

                case 'c':
                case 'C':
                    SerialEx.printf_P(PSTR("Enter channel '0' - '%u': "), (unsigned)(DIMMER_CHANNELS - 1));
                    SerialEx.flush();
                    line = String();
                    read_input_type = 1;
                    break;
                case 'l':
                    SerialEx.printf_P(PSTR("Enter linear correction factor (%s): "), float_to_str(dimmer.linear_correction_factor));
                    SerialEx.flush();
                    line = String();
                    read_input_type = 2;
                    break;

                case 'f':
                    SerialEx.printf_P(PSTR("Enter fade time (%s): "), float_to_str(fade_time));
                    SerialEx.flush();
                    line = String();
                    read_input_type = 3;
                    break;

                // case 's':
                //     Serial.println(F("Simulating single zero crossing interrupt..."));
                //     dimmer_zc_interrupt_handler();
                //     break;

                // dim single steps
                case '+':
                    dimmer_set_level(selected_channel, dimmer_get_level(selected_channel) + 1);
                    break;
                case '-':
                    dimmer_set_level(selected_channel, dimmer_get_level(selected_channel) - 1);
                    break;

                // dim in 1% steps
                case '*':
                    dimmer_set_level(selected_channel, dimmer_get_level(selected_channel) + max(1, DIMMER_MAX_LEVEL / 100));
                    break;
                case '/':
                    dimmer_set_level(selected_channel, dimmer_get_level(selected_channel) - max(1, DIMMER_MAX_LEVEL / 100));
                    break;

                // set 0% / 100%
                case '0':
                    dimmer_set_level(selected_channel, 0);
                    break;
                case ',':
                    dimmer_set_level(selected_channel, DIMMER_MAX_LEVEL);
                    break;

                // 0-100% fadein/out "fade_time" seconds
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    dimmer_fade(selected_channel, (input - '1') * 0.125 * DIMMER_MAX_LEVEL, fade_time);
                    break;

                default:
                    break;
            }
        }
    }

    delay(1);
}
