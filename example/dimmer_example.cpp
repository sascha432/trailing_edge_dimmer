/**
 * Author: sascha_lammers@gmx.de
 */

/*

Sample code to control the dimmer

The dimmer needs a zero crossing signal, which is provided on pin D3 (and needs to be connect to D3 on the dimmer)

LEDs can be connected to PIN 6, 8, 9 and 10 of the dimmer (with a 1K resistor), to test the MOSFET signal

I2C: Connect SDA (A4) and SCL (A5) to the dimmer
Serial Bridge: Connect TX to D8 and RX to D9, recommended baud rate is 9600 or 19200 for SoftwareSerial

*/

#include <Arduino.h>
#if SERIAL_I2C_BRDIGE
#include <SoftwareSerial.h>
#include "SerialTwoWire.h"
#else
#include <Wire.h>
#endif
#include <PrintEx.h>
#include "../src/dimmer_protocol.h"

PrintEx SerialEx(Serial);
#if SERIAL_I2C_BRDIGE
SoftwareSerial Serial2(8, 9);
SerialTwoWire Wire(Serial2);
#endif

// simulation of zero crossing signal
#define ZC_PIN              3

#if ZC_PIN
ISR(TIMER1_COMPA_vect) {
    digitalWrite(ZC_PIN, HIGH);
}

ISR(TIMER1_COMPB_vect) {
    digitalWrite(ZC_PIN, LOW);
    TCNT1 = 0;
}
#endif

float get_internal_temperature(void) {
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    delay(50);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return (ADCW - 324.31) / 1.22;
}

uint16_t read_vcc() {
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(50);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return ((uint32_t)(5000 * (1.1 / 5) * 1024)) / ADCW;
}

void setup() {

#if ZC_PIN
    digitalWrite(ZC_PIN, LOW);
    pinMode(ZC_PIN, OUTPUT);
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
    TCCR1A = 0; 
    TCCR1B = (1 << CS12); // prescaler 256
    TCNT1 = 0;
    OCR1A = F_CPU / 256 / 120;                          // 120Hz
    OCR1B = OCR1A + (F_CPU / 256 / (1e6 / 200));        // 200us
#endif

    Serial.begin(115200);
    Serial.print("Dimmer control example @ ");
    SerialEx.printf("0x%02x\n", DIMMER_I2C_ADDRESS);

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
        switch((uint8_t)Wire.read()) {
            case DIMMER_TEMPERATURE_REPORT: 
                if (length == 4) {
                    uint8_t temperature = Wire.read();
                    uint16_t vcc;
                    Wire.readBytes(reinterpret_cast<uint8_t *>(&vcc), sizeof(vcc));
                    SerialEx.printf("Temperature %u VCC %.3f\n", temperature, vcc / 1000.0);
                } 
                break;
            case DIMMER_TEMPERATURE_ALERT: 
                if (length == 3) {
                    uint8_t temperature = Wire.read();
                    uint8_t tempThreshold = Wire.read();
                    SerialEx.printf("Temperature alarm: %u > %u\n", temperature, tempThreshold);
                } 
                break;
        }
    });

}

int selected_channel = 0;

int endTransmission(uint8_t stop = true) {
    auto result = Wire.endTransmission(stop);
    if (result) {
        SerialEx.printf("endTransmission() returned %d\n", result);
    }
    return result;
}

void set_channel(int channel) {
    selected_channel = channel;
    SerialEx.printf("Channel %u selected\n", channel);
}

void print_channels() {

    int16_t levels[4];

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_CHANNELS);
    Wire.write(0x40);
    if (endTransmission() == 0 && Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(levels)) == sizeof(levels)) {
        Wire.readBytes(reinterpret_cast<uint8_t *>(&levels), sizeof(levels));

        for(uint8_t i = 0; i < 4; i++) {
            SerialEx.printf("Channel %u: %d\n", i, levels[i]);
        }
    }

}

int get_level(int channel) {

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_CHANNELS);
    Wire.write((1 << 4) | channel);
    if (endTransmission() == 0) {
        auto result = Wire.requestFrom(DIMMER_I2C_ADDRESS, 2);
        if (result == 2) {
            return (uint8_t)Wire.read() | ((uint8_t)Wire.read() << 8);
        } else {
            SerialEx.printf("requestFrom() returned %d\n", result);
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
            SerialEx.printf("Set level %d for channel %d\n", get_level(channel), channel);
        }
    }

}

void write_eeprom() {
    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_WRITE_EEPROM);
    endTransmission();
}

void poll_channel(int channel, int time, int delayms = 100) {
    unsigned long timeout = time + millis() + delayms * 2;
    int lastLevel = -1;
    int noChangeCounter = 0;
    while(millis() < timeout) {
        auto level = get_level(channel);
        if (level != lastLevel) {
            SerialEx.printf("Current level: %u\n", level);
            lastLevel = level;
        } else {
            if (++noChangeCounter >= 2) {
                break;
            }
        }
        delay(delayms);
    }
}

void fade(int channel, uint16_t toLevel, float time) {

    SerialEx.printf("Fading channel %u to %u in %.2f seconds\n", channel, toLevel, time);

    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_CHANNEL);
    Wire.write(channel);
    Wire.write(reinterpret_cast<const uint8_t *>(&toLevel), sizeof(toLevel));
    Wire.write(reinterpret_cast<const uint8_t *>(&time), sizeof(time));
    Wire.write(DIMMER_COMMAND_FADE);
    endTransmission();

    poll_channel(channel, time * 1000);
    Serial.println("End fade");
}

void loop() {

#if SERIAL_I2C_BRDIGE
    Wire._serialEvent();
#endif

    if (Serial.available()) {

        int level;
        int step = 10;

        auto input = Serial.read();
        switch(input) {
            case 't':
                Serial.println(get_internal_temperature());
                break;
            case 'v':
                Serial.println(read_vcc());
                break;
            case 'V':
                Wire.beginTransmission(DIMMER_I2C_ADDRESS);
                Wire.write(DIMMER_REGISTER_COMMAND);
                Wire.write(DIMMER_COMMAND_READ_VCC);
                if (endTransmission() == 0) {
                    
                }
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

            case 'p':
                print_channels();
                break;

            case 's':
                Serial.println("Writing EEPROM");
                write_eeprom();
                break;

            // restore factory settings
            case 'f':
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
