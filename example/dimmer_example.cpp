/**
 * Author: sascha_lammers@gmx.de
 */

/*

Sample code to control the dimmer

The dimmer needs a zero crossing signal, which is provided on pin D3 (and needs to be connect to D3 on the dimmer)

LEDs can be connected to PIN 6, 8, 9 and 10 of the dimmer (with a 1K resistor), to test the MOSFET signal

I2C: Connect SDA (A4) and SCL (A5) to the dimmer
Serial Bridge: Connect TX to D8 and RX to D9, recommended baud rate is 9600 or 19200 for SoftwareSerial

Keys

'q': select channel 0
'w': select channel 1
'e': select channel 2
'r': select channel 3
'A': select all channels

'p': read channels
'P': increase frequency signal
'K': enable zc timings output
'k': disable zc timings output

'0': set level for current channel to 0
',': set level to max
'1': fade to 0%
'2': fade to 12.5%
...
'9': fade to 100%
'-': decrease level
'+': increase level

't': read temperature and vcc
'f': read AC frequency
'E': read errors
'l': display timings
'm': modify timings
'R': set 1.1v reference

'O': wdt reset

's': write EEPROM
'F': reset configuration to factory default


*/

#include <Arduino.h>
#if SERIAL_I2C_BRDIGE
#include <SoftwareSerial.h>
#include "SerialTwoWire.h"
#else
#include <Wire.h>
#endif
#include "../src/helpers.h"
#include "../src/dimmer_protocol.h"
#include "../src/dimmer_reg_mem.h"

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE 115200
#endif

#if SERIAL_I2C_BRDIGE
SoftwareSerial Serial2(8, 9);
SerialTwoWire Wire(Serial2);
#endif

#define DIMMER_CHANNELS     4

// simulation of zero crossing signal
#define ZC_PIN              3

#if ZC_PIN
ISR(TIMER1_COMPA_vect) {
    digitalWrite(ZC_PIN, HIGH);
}

ISR(TIMER1_COMPB_vect) {
    digitalWrite(ZC_PIN, LOW);
    TCNT1 = 0;
    if (rand() % 1000 == 0) {
        // simulate misfire
        for(ulong i = 0; i < rand() % 200; i++) {
            i = i * 1.0;
        }
        digitalWrite(ZC_PIN, HIGH);
        for(ulong i = 0; i < 10; i++) {
            i = i * 1.0;
        }
        digitalWrite(ZC_PIN, LOW);
    }
}
#endif

unsigned long poll_channels[DIMMER_CHANNELS];

void setup() {

    memset(&poll_channels, 0, sizeof(poll_channels));

#if ZC_PIN
    digitalWrite(ZC_PIN, LOW);
    pinMode(ZC_PIN, OUTPUT);
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
    TCCR1A = 0;
    TCCR1B = (1 << CS12); // prescaler 256 = 16us
    // TCCR1B = ((1 << CS11) | (1 << CS10)); // prescaler 64
    // TCCR1B = (1 << CS11); // prescaler 8 = 0.5us
    TCNT1 = 0;
    OCR1A = F_CPU / 256 / 120;                          // 120Hz
    // OCR1B = OCR1A + 12;                                 // 192us
    OCR1B = OCR1A + 3;                                  // 48us

    // OCR1B = OCR1A + 12; //(F_CPU / 256 / (1e6 / 200));
#endif

    Serial.begin(DEFAULT_BAUD_RATE);
    Serial.print(F("Dimmer control example @ "));
    Serial_printf_P(PSTR("0x%02x\n"), DIMMER_I2C_ADDRESS);

#if SERIAL_I2C_BRDIGE
    Serial2.begin(DEFAULT_BAUD_RATE);

    // set read handler
    Wire.onReadSerial([](){
        Wire._serialEvent();
    });

#endif

    // receive incoming data as slave
    Wire.begin(DIMMER_I2C_ADDRESS + 1);
    Wire.onReceive([](int length) {
        // Serial_printf_P(PSTR("Wire.onReceive(): length %u, type %#02x\n"), length, Wire.peek());
        switch((uint8_t)Wire.read()) {
            case DIMMER_METRICS_REPORT:
                if (length >= (int)sizeof(dimmer_metrics_t)) {
                    dimmer_metrics_t metrics;
                    Wire.readBytes(reinterpret_cast<uint8_t *>(&metrics), sizeof(metrics));
                    Serial_printf_P(PSTR("Temperature %.2f°C NTC %.2f°C "), metrics.internal_temp, metrics.ntc_temp);
                    Serial_printf_P(PSTR("VCC %.3fV AC frequency %.2f Hz\n"), metrics.vcc / 1000.0, metrics.frequency);
                }
                break;
            case DIMMER_TEMPERATURE_ALERT:
                if (length == 3) {
                    uint8_t temperature = Wire.read();
                    uint8_t tempThreshold = Wire.read();
                    Serial_printf_P(PSTR("Temperature alarm: %u > %u\n"), temperature, tempThreshold);
                }
                break;
            case DIMMER_FADING_COMPLETE: {
                    int8_t channel;
                    int16_t level;
                    const int len = sizeof(channel) + sizeof(level);
                    Serial.print(F("Fading complete: "));
                    while(length >= len) {
                        channel = (int8_t)Wire.read();
                        Wire.readBytes(reinterpret_cast<uint8_t *>(&level), sizeof(level));
                        Serial_printf_P(PSTR("[%d]: %d "), channel, level);
                        length -= len;
                        poll_channels[channel] = 0;
                    }
                    Serial.println();
                }
                break;
            case DIMMER_EEPROM_WRITTEN: {
                    if (length >= sizeof(dimmer_eeprom_written_t)) {
                        dimmer_eeprom_written_t eeprom;
                        Wire.readBytes(reinterpret_cast<uint8_t *>(&eeprom), sizeof(eeprom));
                        Serial_printf_P(PSTR("EEPROM written: cycle %lu, position %u, bytes written %u\n"), (unsigned long)eeprom.write_cycle, eeprom.write_position, eeprom.bytes_written);
                    }
                }
                break;
        }
    });

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_FORCE_TEMP_CHECK);
    Wire.endTransmission();
}

int selected_channel = 0;

int endTransmission(uint8_t stop = true) {
    auto result = Wire.endTransmission(stop);
    if (result) {
        Serial_printf_P(PSTR("endTransmission() returned %d\n"), result);
    }
    return result;
}

void set_channel(int channel) {
    selected_channel = channel;
    Serial_printf_P(PSTR("Channel %u selected\n"), channel);
}

void print_channels() {

    int16_t levels[DIMMER_CHANNELS];

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_CHANNELS);
    Wire.write(DIMMER_CHANNELS << 4);
    if (endTransmission() == 0 && Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(levels)) == sizeof(levels)) {
        Wire.readBytes(reinterpret_cast<uint8_t *>(&levels), sizeof(levels));

        for(int8_t i = 0; i < DIMMER_CHANNELS; i++) {
            Serial_printf_P(PSTR("Channel %u: %d\n"), i, levels[i]);
        }
    }

}

int get_level(int channel) {
    if (channel == -1 || channel == 0xff) {
        return 0;
    }

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_CHANNELS);
    Wire.write((1 << 4) | channel);
    if (endTransmission() == 0) {
        auto result = Wire.requestFrom(DIMMER_I2C_ADDRESS, 2);
        if (result == 2) {
            return (uint8_t)Wire.read() | ((uint8_t)Wire.read() << 8);
        } else {
            Serial_printf_P(PSTR("requestFrom() returned %d\n"), result);
        }
    }
    return -1;
}

void set_level(int channel, int newLevel) {

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_CHANNEL);
    Wire.write((uint8_t)channel);
    uint16_t level = 0;
    if (newLevel >= 0) {
        level = (uint16_t)newLevel;
    }
    Wire.write(reinterpret_cast<const uint8_t *>(&level), sizeof(level));
    if (endTransmission(false) == 0) {

        // start new transmission to move to command
        Wire.beginTransmission(DIMMER_I2C_ADDRESS);
        Wire.write(DIMMER_REGISTER_COMMAND);
        Wire.write(DIMMER_COMMAND_SET_LEVEL);
        if (endTransmission() == 0) {
            Serial_printf_P(PSTR("Set level %d for channel %d\n"), get_level(channel), channel);
        }
    }

}

void write_eeprom() {
    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_WRITE_EEPROM);
    endTransmission();
}

unsigned long poll_channels_interval = 0;

void check_poll_channels() {
    if (millis() > poll_channels_interval) {
        for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
            if (poll_channels[i]) {
                if (millis() > poll_channels[i]) {
                    poll_channels[i] = 0;
                } else {
                    Serial_printf_P(PSTR("[%d]: %d\n"), i, get_level(i));
                }
            }
        }
        poll_channels_interval = millis() + 250;
    }
}

void fade(int channel, uint16_t toLevel, float time) {

    Serial_printf_P(PSTR("Fading channel %u to %u in %.2f seconds\n"), channel, toLevel, time);

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_CHANNEL);
    Wire.write(channel);
    Wire.write(reinterpret_cast<const uint8_t *>(&toLevel), sizeof(toLevel));
    Wire.write(reinterpret_cast<const uint8_t *>(&time), sizeof(time));
    Wire.write(DIMMER_COMMAND_FADE);
    if (endTransmission() == 0) {
        unsigned long endPolling = millis() + (time * 1000) + 300;
        if (channel == -1 || channel == 0xff) {
            uint8_t count = DIMMER_CHANNELS - 1;
            do {
                poll_channels[count] = endPolling;
            } while(count--);
        } else {
            poll_channels[channel] = endPolling;
        }
    }
}

void read_timing(uint8_t timing, const String &name) {
    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_TIMINGS);
    Wire.write(timing);
    if (endTransmission() == 0 && Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(float)) == sizeof(float)) {
        float value = -1;
        Wire.readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
        Serial.print(name);
        Serial_printf_P(PSTR("% 5.4f\n"), value);
    }
}

void read_errors() {
    register_mem_errors_t errors;
    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_READ_LENGTH);
    Wire.write(sizeof(errors));
    Wire.write(DIMMER_REGISTER_ERR_FREQ_LOW);
    if (endTransmission() == 0 && Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(errors)) == sizeof(errors)) {
        Wire.readBytes(reinterpret_cast<uint8_t *>(&errors), sizeof(errors));
        Serial_printf_P(PSTR("frequency low %u, frequency high %u, zc misfire %u\n"), errors.frequency_low, errors.frequency_high, errors.zc_misfire);
    }
}

void loop() {

#if SERIAL_I2C_BRDIGE
    Wire._serialEvent();
#endif

    check_poll_channels();

    if (Serial.available()) {

        int level;
        int step = 10;

        auto input = Serial.read();
        switch(input) {
            case 'K':
                Serial.println(F("Enabling ZC timings output..."));
                Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                Wire.write(DIMMER_REGISTER_COMMAND);
                Wire.write(DIMMER_COMMAND_ZC_TIMINGS_OUTPUT);
                Wire.write(1);
                endTransmission();
                break;
            case 'k':
                Serial.println(F("Disabling ZC timings output..."));
                Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                Wire.write(DIMMER_REGISTER_COMMAND);
                Wire.write(DIMMER_COMMAND_ZC_TIMINGS_OUTPUT);
                Wire.write(0);
                endTransmission();
                break;
            case 'O':
                Serial.println(F("Sending reset..."));
                Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                Wire.write(DIMMER_REGISTER_COMMAND);
                Wire.write(DIMMER_COMMAND_RESET);
                endTransmission();
                break;
            case 'P': {
                    OCR1A--;
                    OCR1B = OCR1A + 3;
                    Serial_printf_P(PSTR("AC Frequency %.2f Hz (%u)\n"), F_CPU / 256.0 / (float)OCR1A / 2, OCR1A);
                }
                break;
            case 'E':
                read_errors();
                break;
            case 't': {
                    float int_temp = NAN;
                    float ntc_temp = NAN;
                    uint16_t vcc = 0;
                    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                    Wire.write(DIMMER_REGISTER_COMMAND);
                    Wire.write(DIMMER_COMMAND_READ_VCC);
                    Wire.write(DIMMER_REGISTER_COMMAND);
                    Wire.write(DIMMER_COMMAND_READ_INT_TEMP);
                    const int len = sizeof(float) + sizeof(uint16_t);
                    if (endTransmission() == 0) {
                        delay(250); // 100 if not in debug mode
                        if (Wire.requestFrom(DIMMER_I2C_ADDRESS, len) == len) {
                            Wire.readBytes(reinterpret_cast<uint8_t *>(&int_temp), sizeof(int_temp));
                            Wire.readBytes(reinterpret_cast<uint8_t *>(&vcc), sizeof(vcc));
                        }
                    }
                    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                    Wire.write(DIMMER_REGISTER_COMMAND);
                    Wire.write(DIMMER_COMMAND_READ_NTC);
                    const int len2 = sizeof(float);
                    if (endTransmission() == 0) {
                        delay(250); // 20 if not in debug mode
                        if (Wire.requestFrom(DIMMER_I2C_ADDRESS, len2) == len2) {
                            Wire.readBytes(reinterpret_cast<uint8_t *>(&ntc_temp), sizeof(ntc_temp));
                        }
                    }
                    Serial_printf_P(PSTR("VCC: %.3f Internal temperature: %.2f°C NTC: %.2f°C\n"), vcc / 1000.0, int_temp, ntc_temp);
                } break;

            case 'f':
                Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                Wire.write(DIMMER_REGISTER_COMMAND);
                Wire.write(DIMMER_COMMAND_READ_AC_FREQUENCY);
                if (endTransmission() == 0 && Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(float)) == sizeof(float)) {
                    float value;
                    Wire.readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
                    Serial.print(F("AC Frequency: "));
                    Serial.println(value, 3);
                }
                break;

            case 'R': {
                    Serial.print(F("Enter voltage [empty=abort]: "));
                    String input = String();
                    while(!Serial_readLine(input, true)) {
                    }
                    if (input.length()) {
                        auto value = input.toFloat();
                        if (!isnan(value) && value != 0) {
                            Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                            Wire.write(DIMMER_REGISTER_INT_1_1V_REF);
                            Wire.write(reinterpret_cast<const uint8_t *>(&value), sizeof(value));
                            if (endTransmission() == 0) {
                                Serial_printf_P(PSTR("Written %.6f\n"), value);
                            }
                        }
                    }
                }
                break;

            case 'm': {
                    Serial.print(F("1 - DIMMER_TIMINGS_ZC_DELAY_IN_US\n2 - DIMMER_TIMINGS_MIN_ON_TIME_IN_US\n3 - DIMMER_TIMINGS_ADJ_HW_TIME_IN_US\n\nSelect [empty=abort]: "));
                    String input = String();
                    while(!Serial_readLine(input, true)) {
                    }
                    int num = input.toInt();
                    if (num >= 1 && num <= 3) {
                        Serial.print(F("Enter ticks [empty=abort]: "));
                        input = String();
                        while(!Serial_readLine(input, true)) {
                        }
                        input.trim();
                        if (input.length()) {
                            int addr = DIMMER_REGISTER_ZC_DELAY_TICKS + num - 1;
                            int ticks = input.toInt();
                            Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                            Wire.write(addr);
                            Wire.write(ticks);
                            if (endTransmission() == 0) {
                                Serial_printf_P(PSTR("Written %u ticks to %#02x\n"), ticks, addr);
                            }
                        }
                    }
                } break;

            case 'l':
                read_timing(DIMMER_TIMINGS_TMR1_TICKS_PER_US,   F("Timer 1 ticks per us:        "));
                read_timing(DIMMER_TIMINGS_TMR2_TICKS_PER_US,   F("Timer 2 ticks per us:        "));
                read_timing(DIMMER_TIMINGS_ZC_DELAY_IN_US,      F("Zero crossing delay in us:   "));
                read_timing(DIMMER_TIMINGS_MIN_ON_TIME_IN_US,   F("Min. on time in us:          "));
                read_timing(DIMMER_TIMINGS_ADJ_HW_TIME_IN_US,   F("Adjust halfwave time in us:  "));
                break;

            case 'q':
                set_channel(0);
                break;
            case 'w':
                set_channel(1);
                break;
            case 'e':
                set_channel(2);
                break;
            case 'r':
                set_channel(3);
                break;
            case 'A':
                set_channel(0xff);
                break;

            case 'p':
                print_channels();
                break;

            case 's':
                Serial.println("Writing EEPROM");
                write_eeprom();
                break;

            // restore factory settings
            case 'F':
                Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                Wire.write(DIMMER_REGISTER_COMMAND);
                Wire.write(DIMMER_COMMAND_RESTORE_FS);
                endTransmission();
                break;

#if DEBUG
            case 'd':
                Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                Wire.write(DIMMER_REGISTER_COMMAND);
                Wire.write(DIMMER_COMMAND_DUMP_MEM);
                endTransmission();
                break;
#endif

            // set level
            case '+':
                level = get_level(selected_channel);
                if (level != -1) {
                    set_level(selected_channel, level + step);
                }
                break;
            case '-':
                level = get_level(selected_channel);
                if (level != -1) {
                    set_level(selected_channel, level - step);
                }
                break;

            // dim in 1% steps
            case '*':
                level = get_level(selected_channel);
                if (level != -1) {
                    set_level(selected_channel, level + max(1, DIMMER_MAX_LEVEL / 100));
                }
                break;
            case '/':
                level = get_level(selected_channel);
                if (level != -1) {
                    set_level(selected_channel, level - max(1, DIMMER_MAX_LEVEL / 100));
                }
                break;

            // set 0% / 100%
            case '0':
                set_level(selected_channel, 0);
                break;
            case ',':
                set_level(selected_channel, DIMMER_MAX_LEVEL);
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
                fade(selected_channel, (input - '1') * 0.125 * DIMMER_MAX_LEVEL, 5.0);
                break;
        }
    }
}
