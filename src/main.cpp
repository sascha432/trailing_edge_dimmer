/**
 * Author: sascha_lammers@gmx.de
 */

// 4 Channel Dimmer with Serial Interface

#include <Arduino.h>
#include "helpers.h"
#include "dimmer.h"

/*

Changelog

    Moved to CHANGELOG.md


Serial protocol

    Each command is confirmed with '\n'. The response can be a single or multple lines.

    Set channel

        ch=<channel>

        channel is 0 based, 'a' for all

        Response: ch=<new channel>

    Set level for current channel(s)

        set=<level>

        Response (per channel): ch=<channel>,lvl=<new level>

    Fade to level

        fade=<from level>,<to level>,<time in seconds>[,<channel>[,<channel>],...]

        from level = -1: use current level
        if no channel is specified, it is using the selected channel(s)

        Response (one line per channel): fade,ch=<channel>,from=<old level>,lvl=<target level>,time=<time tom reach target in seconds>


    Get level for all channels

        get

        Response (one line for each channel): ch=<channel>,lvl=<level>

    Show dimmer info

        info

    Read NTC temperature

        temp

        Response (°C):

        temp=<xxx.xx>

        If the interal temperature sensor is enabled

        temp=<xxx.xx>,int_temp=<xxx.xx>

    Show configuration parameter

        cfg=<number>

    Set configuration parameter

        cfg=<number>,<value>

    Read configuration from EEPROM

        read

        Response: read=ok

    Write configuration to EEPROM

        write

        Response: write=ok,cycle=<write counter>

    Reset configuration

        reset

        Response: reset=ok


Slim version only:

    Set channel

        c<channel>      -1 = all

    Set level

        s<value>        0-max level

    Fade to level

        f<value>        0-max level

    Set fade time for subsequent fade commands

        F<value>        in milliseconds, default 5000

    Read NTC

        t



*/

#if SLIM_VERSION

// slim version that fits into 8kb flash

#define USE_EEPROM                              0
#define USE_TEMPERATURE_CHECK                   0
#define USE_NTC                                 1
#define USE_INTERAL_TEMP_SENSOR                 0
#define USE_I2C_SLAVE                           0

#else

// regular version

#ifndef USE_EEPROM
#define USE_EEPROM                              1
#endif

#ifndef INTERNAL_VREF_1_1V
#define INTERNAL_VREF_1_1V                      1.1
#endif


#ifndef USE_TEMPERATURE_CHECK
#define USE_TEMPERATURE_CHECK                   1
#endif

#ifndef USE_NTC
#define USE_NTC                                 1
#endif

#ifndef USE_INTERAL_TEMP_SENSOR
#define USE_INTERAL_TEMP_SENSOR                 1
#endif

#ifndef USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN
#define USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN    0
#endif

#ifndef USE_I2C_SLAVE // not implemented yet
#define USE_I2C_SLAVE                           1
#endif

#endif

#if USE_EEPROM
#include <EEPROM.h>
#endif

#ifndef DEFAULT_BAUD_RATE
#define DEFAULT_BAUD_RATE                       115200
#endif

#define NTC_PIN                                 A1

#define SERIAL_INPUT_BUFFER_MAX_LENGTH          64
#define SERIAL_MAX_ARGUMENTS                    10

#if USE_EEPROM

#define CONFIG_ID                               0xc33e166c5e7c6571
#define EEPROM_WRITE_DELAY                      1000
#define EEPROM_REPEATED_WRITE_DELAY             30000

struct config_t {
    uint32_t eeprom_cycle;
    uint32_t baud;
    uint16_t fadein_time;
    uint8_t max_temp;
    uint8_t temp_check_interval;
    uint8_t restore_level:1;
    uint8_t report_temp:1;
    uint8_t command_prefix:1;
    int16_t level[DIMMER_CHANNELS];
};

config_t config;
uint16_t eeprom_position = sizeof(uint64_t);
unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;
bool eeprom_write_scheduled = false;

#define CONFIG_BAUD config.baud

void reset_config() {
    memset(&config, 0, sizeof(config));
    config.baud = DEFAULT_BAUD_RATE;
    config.max_temp = 65;
    config.temp_check_interval = 30;
    config.restore_level = true;
    config.report_temp = true;
    config.fadein_time = 7500;
}

// initialize EEPROM and wear leveling
void init_eeprom() {
    uint64_t config_id = CONFIG_ID;

    EEPROM.begin();
    config.eeprom_cycle = 1;
    eeprom_position = sizeof(uint64_t);
    _D(5, SerialEx.printf_P(PSTR("init eeprom cycle=%ld, position %d\n"), (long)config.eeprom_cycle, (int)eeprom_position));

    for(uint16_t i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
    }
    EEPROM.put(0, config_id);
    EEPROM.put(eeprom_position, config);
    EEPROM.end();
}

void read_config() {
    uint64_t config_id;

    EEPROM.begin();
    EEPROM.get(0, config_id);
    if (config_id != CONFIG_ID) {
        EEPROM.end();
        reset_config();
        init_eeprom();
    } else {
        uint16_t pos = sizeof(uint64_t);
        uint32_t cycle, max_cycle = 0;

        // find last configuration
        while(pos < EEPROM.length()) {
            EEPROM.get(pos, cycle);
            _D(5, SerialEx.printf_P(PSTR("eeprom cycle %ld position %d\n"), cycle, pos));
            if (cycle > max_cycle) {
                eeprom_position = pos;
                max_cycle = cycle;
            }
            pos += sizeof(config_t);
        }
        EEPROM.get(eeprom_position, config);
        EEPROM.end();
        _D(5, SerialEx.printf_P(PSTR("read_config, eeprom cycle %ld, position %d\n"), (long)max_cycle, (int)eeprom_position));
    }
}

void _write_config() {
    config_t temp_config;

    EEPROM.begin();
    EEPROM.get(eeprom_position, temp_config);
    if (memcmp(&config, &temp_config, sizeof(config)) != 0) {
        _D(5, SerialEx.printf_P(PSTR("old eeprom write cycle %ld, position %d, "), (long)config.eeprom_cycle, (int)eeprom_position));
        config.eeprom_cycle++;
        eeprom_position += sizeof(config_t);
        if (eeprom_position + sizeof(config_t) >= EEPROM.length()) { // end reached, start from beginning
            eeprom_position = sizeof(uint64_t);
        }
        _D(5, SerialEx.printf_P(PSTR("new cycle %ld, position %d\n"), (long)config.eeprom_cycle, (int)eeprom_position));
        EEPROM.put(eeprom_position, config);
        eeprom_write_timer = millis();
    } else {
        _D(5, SerialEx.printf_P(PSTR("configuration didn't change, skipping write cycle\n")));
        eeprom_write_timer = millis();
    }
    EEPROM.end();
}

void write_config() {
    if (!eeprom_write_scheduled) { // no write scheduled
        long since = millis() - eeprom_write_timer;
        _D(5, SerialEx.printf_P(PSTR("scheduling eeprom write cycle, last write %d seconds ago\n"), (int)(since / 1000)));
        eeprom_write_timer = millis() + ((since > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
        eeprom_write_scheduled = true;
    } else {
        _D(5, SerialEx.printf_P(PSTR("eeprom write cycle already scheduled in %d seconds\n"), (int)((eeprom_write_timer - millis()) / 1000)));
    }
}

#else

#define CONFIG_BAUD DEFAULT_BAUD_RATE

#define read_config()
#define write_config()
#define reset_config()

#endif

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
double get_interal_temperature(void) {
  unsigned int wADC;
  double t;

  // The internal temperature has to be used
  // with the internal reference of 1.1V.
  // Channel 8 can not be selected with
  // the analogRead function yet.

  // Set the internal reference and mux.
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA, ADSC)) ;

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;

  // The returned temperature is in degrees Celsius.
  return (t);
}

// read VCC in mV
int16_t read_vcc() {
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(20);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC)) ;
  return (uint32_t)(5000 * (INTERNAL_VREF_1_1V / 5) * 1024) / ADCW;
}

uint16_t read_ntc_value(uint8_t num = 5) {
    uint32_t value = 0;
    for(uint8_t i = 0; i < num; i++) {
        value += analogRead(NTC_PIN);
        delay(1);
    }
    return value / num;
}

float convert_to_celsius(uint16_t value) {
    float steinhart;
    steinhart = 1023 / (float)value - 1;
    steinhart *= 2200;                          // serial resistance
    steinhart /= 10000;                         // nominal resistance
    steinhart = log(steinhart);
    steinhart /= 3950;                          // beta coeff.
    steinhart += 1.0 / (25 + 273.15);           // nominal temperature
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    return steinhart;
}

void invalid_error(const __FlashStringHelper *subject) {
    Serial.print(F("err=Invalid "));
    Serial.println(subject);
}

char **split(char *line, uint8_t &count, char ch = ',') {
    static char *args[SERIAL_MAX_ARGUMENTS];
    char *str = line;
    count = 0;
    for(;;) {
        args[count++] = str;
        char *ptr = strchr(str, ch);
        if (!ptr) {
            break;
        }
        *ptr = 0;
        str = ptr + 1;
        if (count >= SERIAL_MAX_ARGUMENTS - 1) {
            break;
        }
    }
    return args;
}

void fade(int8_t channel, int16_t from, int16_t to, float time) {

    if (channel == -1) {
        for(int8_t i = 0; i < DIMMER_CHANNELS; i++) {
            fade(i, from, to, time);
        }
    } else {
        dimmer_set_fade(channel, from, to, time);
        SerialEx.printf_P(PSTR("fade,ch=%d,from=%d,lvl=%d,time=%s\n"), channel, (from == -1 ? dimmer_get_level(channel) : from), to, float_to_str(time));
    }
}

#if USE_EEPROM
void restore_level() {
    if (config.restore_level) {
        float time = config.fadein_time / 1000.0;
        for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
            fade(i, DIMMER_FADE_FROM_CURRENT_LEVEL, config.level[i], time);
        }
    }
}
#endif

void setup() {

    Serial.begin(DEFAULT_BAUD_RATE);

    read_config();

    if (CONFIG_BAUD != DEFAULT_BAUD_RATE) {
        Serial.flush();
        Serial.begin(CONFIG_BAUD);
    }

    dimmer_zc_setup();
    dimmer_timer_setup();

    pinMode(NTC_PIN, INPUT);

#if USE_EEPROM
    restore_level();
#endif
}

char serial_buffer[SERIAL_INPUT_BUFFER_MAX_LENGTH];
uint8_t serial_buffer_len = 0;

int8_t channel = -1;
#if USE_TEMPERATURE_CHECK
ulong next_temp_check;
#endif

#if SLIM_VERSION
float fade_time = 5;

void dimmer_set(uint8_t channel, int16_t value, bool fade) {
    fade ? dimmer_set_fade(channel, DIMMER_FADE_FROM_CURRENT_LEVEL, value, fade_time) : dimmer_set_level(channel, value);
}
#endif

void loop() {

#if USE_EEPROM
    if (eeprom_write_scheduled && (millis() > eeprom_write_timer)) {
        _write_config();
        eeprom_write_scheduled = false;
    }
#endif

#if USE_TEMPERATURE_CHECK
    if (millis() > next_temp_check) {
#if USE_INTERAL_TEMP_SENSOR_FOR_SHUTDOWN
        int current_temp = get_interal_temperature();
#else
        int current_temp = convert_to_celsius(read_ntc_value());
#endif
        next_temp_check = millis() + config.temp_check_interval * 1000;
        if (config.max_temp && current_temp > config.max_temp) {
            fade(-1, DIMMER_FADE_FROM_CURRENT_LEVEL, 0, 10);
            SerialEx.printf_P(PSTR("Temperature reached %d C, emergency shutdown\n"), current_temp);
        }
        if (config.report_temp) {
            SerialEx.printf_P(PSTR("temp=%d,vcc=%d\n"), current_temp, read_vcc());
        }
    }
#endif

    if (Serial.available()) {
        int ch = Serial.read();
#if DEBUG
        serial_buffer[serial_buffer_len] = 0;
        SerialEx.printf_P(PSTR("serial in %d buffer '%s'\n"), ch, serial_buffer);
#endif
        if (ch == '\n') {
            serial_buffer[serial_buffer_len] = 0;
#if SLIM_VERSION
            switch(serial_buffer[0]) {
#if USE_NTC
                case 't':
                    Serial.println(convert_to_celsius(read_ntc_value()));
                    break;
#endif
                case 'c':
                    channel = atoi(serial_buffer + 1);
                    //channel = (atoi(serial_buffer + 1) + 1) % (DIMMER_CHANNELS + 1) - 1;
                    break;
                case 'g':
                    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
                        Serial.print(dimmer.level[i]);
                        Serial.print(i == DIMMER_CHANNELS - 1 ? '\n' : ',');
                    }
                    break;
                case 'f':
                case 's': {
                        int value = atoi(serial_buffer + 1);
                        bool fade = serial_buffer[0] == 'f';
                        if (channel == -1) {
                            for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
                                dimmer_set(i, value, fade);
                            }
                        } else {
                            dimmer_set(channel, value, fade);
                        }
                    } break;
                case 'F':
                    fade_time = atoi(serial_buffer + 1) / 1000.0;
                    break;
            }
#else
            const char *buffer = serial_buffer;
            if (config.command_prefix == 0 || strncmp(buffer, "~$", 2) == 0) {
                if (config.command_prefix) {
                    buffer += 2;
                }
                if (strcmp(buffer, "info") == 0) {
                    Serial.println(F("version=" DIMMER_VERSION ", " DIMMER_INFO));
                    SerialEx.printf_P(PSTR("lvl=0-%d\n"), DIMMER_MAX_LEVEL);
                    SerialEx.printf_P(PSTR("ch=0-%d\n"), DIMMER_CHANNELS);
                    SerialEx.printf_P(PSTR("lcf=%s\n"), float_to_str(dimmer.linear_correction_factor));
                    SerialEx.printf_P(PSTR("vcc=%d\n"), read_vcc());
                    SerialEx.printf_P(PSTR("f_cpu=%ld\n"), F_CPU);

#if USE_TEMPERATURE_CHECK
                } else if (strcmp(buffer, "temp") == 0) {
#if USE_NTC
                    Serial.print(F("temp="));
                    Serial.print(float_to_str(convert_to_celsius(read_ntc_value())));
#endif
#if USE_INTERAL_TEMP_SENSOR
#if USE_NTC
                    Serial.print(',');
#endif
                    Serial.print(F("int_temp="));
                    Serial.print(float_to_str(get_interal_temperature()));
#endif
                    Serial.println();
#endif
#if USE_EEPROM
                } else if (strcmp(buffer, "read") == 0) {
                    read_config();
                    Serial.println(F("read=ok"));
                    restore_level();
                } else if (strcmp(buffer, "write") == 0) {
                    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
                        config.level[i] = dimmer.level[i];
                    }
                    write_config();
                    SerialEx.printf_P(PSTR("write=ok,cycle=%ld\n"), (long)config.eeprom_cycle);
                } else if (strcmp(buffer, "reset") == 0) {
                    reset_config();
                    Serial.println(F("reset=ok"));
#endif
#if DEBUG
                } else if (strcmp(buffer, "debug") == 0) {
                    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
                        SerialEx.printf_P(PSTR("debug.level[%d]=%d\n"), i, dimmer.level[i]);
                        SerialEx.printf_P(PSTR("debug.fade[%d].count=%u\n"), i, dimmer.fade[i].count);
                        SerialEx.printf_P(PSTR("debug.fade[%d].level=%s\n"), i, float_to_str(dimmer.fade[i].level));
                        SerialEx.printf_P(PSTR("debug.fade[%d].step=%s\n"), i, float_to_str(dimmer.fade[i].step));
                    }
                    for(uint8_t i = 0; dimmer.ordered_channels[i].ticks; i++) {
                        SerialEx.printf_P(PSTR("debug.ordered_channels[%d].channel=%d\n"), i, dimmer.ordered_channels[i].channel);
                        SerialEx.printf_P(PSTR("debug.ordered_channels[%d].ticks=%u\n"), i, dimmer.ordered_channels[i].ticks);
                    }
#endif
                } else if (strncmp(buffer, "cfg=", 4) == 0) {
                    int param = atoi(buffer + 4);
                    char *ptr = strchr(buffer, ',');
                    switch(param) {
                        case 1:
                            if (ptr++ && *ptr) {
                                config.baud = atol(ptr);
                            }
                            SerialEx.printf_P(PSTR("config.baud=%ld\n"), (long)config.baud);
                            break;
                        case 2:
                            if (ptr++ && *ptr) {
                                config.fadein_time = atof(ptr) * 1000.0;
                            }
                            SerialEx.printf_P(PSTR("config.fadein_time=%d\n"), config.fadein_time);
                            break;
                        case 3:
                            if (ptr++ && *ptr) {
                                config.max_temp = atoi(ptr);
                            }
                            SerialEx.printf_P(PSTR("config.max_temp=%d\n"), config.max_temp);
                            break;
                        case 4:
                            if (ptr++ && *ptr) {
                                config.restore_level = atoi(ptr);
                            }
                            SerialEx.printf_P(PSTR("config.restore_level=%d\n"), config.restore_level);
                            break;
                        case 5:
                            if (ptr++ && *ptr) {
                                config.report_temp = atoi(ptr);
                            }
                            SerialEx.printf_P(PSTR("config.report_temp=%d\n"), config.report_temp);
                            break;
                        case 6:
                            if (ptr++ && *ptr) {
                                config.temp_check_interval = atoi(ptr);
                            }
                            SerialEx.printf_P(PSTR("config.temp_check_interval=%d\n"), config.temp_check_interval);
                            break;
                        case 7:
                            if (ptr++ && *ptr) {
                                config.command_prefix = atoi(ptr);
                            }
                            SerialEx.printf_P(PSTR("config.command_prefix=%d\n"), config.command_prefix);
                            break;
                        case 32:
                            if (ptr++ && *ptr) {
                                dimmer_set_lcf(atof(ptr));
                            }
                            SerialEx.printf_P(PSTR("lcf=%s\n"), float_to_str(dimmer.linear_correction_factor));
                            break;
                        default:
                            invalid_error(F("configuration parameter"));
                            break;
                    }
                } else if (strncmp(buffer, "ch=", 3) == 0) {
                    int tmp;
                    if (strcmp(buffer, "ch=a") == 0) {
                        tmp = -1;
                    } else {
                        tmp = atoi(buffer + 3);
                    }
                    if (tmp >= -1 || tmp < DIMMER_CHANNELS) {
                        SerialEx.printf_P(PSTR("ch=%d\n"), tmp);
                        channel = tmp;
                    } else {
                        invalid_error(F("channel"));
                    }
                } else if (strcmp(buffer, "get") == 0) {
                    for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
                        SerialEx.printf_P(PSTR("ch=%d,lvl=%d\n"), i, dimmer.level[i]);
                    }
                } else if (strncmp(buffer, "set=", 4) == 0) {
                    int value = atoi(buffer + 4);
                    if (value < 0 || value > DIMMER_MAX_LEVEL) {
                        invalid_error(F("level"));
                    } else {
                        if (channel == -1) {
                            for(uint8_t i = 0; i < DIMMER_CHANNELS; i++) {
                                dimmer_set_level(i, value);
                                SerialEx.printf_P(PSTR("ch=%d,lvl=%d\n"), i, value);
                            }
                        } else {
                            dimmer_set_level(channel, value);
                            SerialEx.printf_P(PSTR("ch=%d,lvl=%d\n"), channel, value);
                        }
                    }
                } else if (strncmp(buffer, "fade=", 5) == 0) {
                    uint8_t count;
                    char **args = split((char *)&buffer[5], count);
                    if (count < 3) {
                        invalid_error(F("fade parameters"));
                    } else {
                        int from = atoi(args[0]);
                        int to = atoi(args[1]);
                        float time = atof(args[2]);
                        if (count > 3) {
                            for(uint8_t i = 3; i < count; i++) {
                                fade(atoi(args[i]), from, to, time);
                            }
                        } else {
                            fade(channel, from, to, time);
                        }
                    }
                } else {
                    Serial.print(F("invalid="));
                    Serial.println(buffer);
                }
            }
#endif
            serial_buffer_len = 0;
        } else if (ch == '\r') {
        } else if (serial_buffer_len < SERIAL_INPUT_BUFFER_MAX_LENGTH - 1) {
            serial_buffer[serial_buffer_len++] = ch;
        }
    } else {
        delay(1);
    }

}
