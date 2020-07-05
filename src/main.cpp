/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

// 29484, 29280, 29310, 29294, 29212, 29170, 29108, 29004, 29102, 28918, 29074, 29044, 29086, 29248, 29084, 28998, 29000, 28916, 28136, 27962, 27586, 27584, 27536

#include <Arduino.h>
#include "i2c_slave.h"
#include "sensors.h"
#include "helpers.h"
#include "cubic_interpolation.h"
#include <EEPROM.h>

unsigned long update_metrics_timer = 0;
unsigned long send_metrics_timer = 0;
#if HAVE_PRINT_METRICS
bool print_metrics_enabled = false;
#endif

void rem()
{
#if SERIAL_I2C_BRDIGE
    Serial.print(F("+REM="));
#endif
}

void display_dimmer_info()
{
    rem();
    Serial.println(F("MOSFET Dimmer " DIMMER_VERSION " " __DATE__ " " __TIME__ " " DIMMER_INFO));

    rem();
    MCUInfo_t mcu;
    get_mcu_type(mcu);

    Serial.printf_P(PSTR("sig=%02x-%02x-%02x,fuses=l:%02x,h:%02x,e:%02x"), mcu.sig[0], mcu.sig[1], mcu.sig[2], mcu.fuses[0], mcu.fuses[1], mcu.fuses[2]);
    if (mcu.name) {
        Serial.printf_P(PSTR(",MCU=%S"), mcu.name);
    }
    Serial.printf_P(PSTR("@%uMhz\n"), (unsigned)(F_CPU / 1000000UL));

    rem();
    Serial.print(F("options="));
    Serial.printf_P(PSTR("Factory=%u,"), register_mem.data.cfg.bits.factory_settings);
#if HAVE_NTC
    // Serial.printf_P(PSTR("NTC=A%u,"), NTC_PIN - A0);
    Serial.print(F("NTC=" _STRINGIFY(NTC_PIN) ","));
#endif
#if HAVE_READ_INT_TEMP && HAVE_READ_VCC
    Serial.print(F("IntTemp,VCC,"));
#else
#if HAVE_READ_INT_TEMP
    Serial.print(F("IntTemp,"));
#endif
#if HAVE_READ_VCC
    Serial.print(F("VCC,"));
#endif
#endif
#if DIMMER_CUBIC_INTERPOLATION
    Serial.print(F("CubicInt,"));
#endif
#if SERIAL_I2C_BRDIGE
    Serial.print(F("Pr=UART,"));
#else
    Serial.print(F("Pr=I2C,"));
#endif
#if HAVE_FADE_COMPLETION_EVENT
    Serial.print(F("CE=1,"));
#endif
    Serial.printf_P(PSTR("Addr=%02x,Pre=" _STRINGIFY(DIMMER_TIMER1_PRESCALER) ",Ticks=%.1fus,MaxLvls=" _STRINGIFY(DIMMER_MAX_LEVELS) ",GPIO/lvl="), DIMMER_I2C_ADDRESS,1 / DIMMER_T1_TICKS_PER_US);
    FOR_CHANNELS(i) {
        Serial.print((int)kDimmerPins[i]);
        Serial.print('/');
        Serial.print(dimmer_level(i));
        if (i < Dimmer::kMaxChannels - 1) {
            Serial.print(',');
        }
    }
    Serial.println();

    rem();
    Serial.printf_P(PSTR("values=Restore=%u,Frq=%.3f,Ref11=%.4f,"), register_mem.data.cfg.bits.restore_level, dimmer.getFrequency(), register_mem.data.cfg.vref11);
#if HAVE_NTC
    Serial.printf_P(PSTR("NTC=%.2f/%+.1fC,"), Sensors::readTemperature(), register_mem.data.cfg.temperature_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
#if HAVE_READ_INT_TEMP
    Serial.printf_P(PSTR("IntTemp=%.2f/%+.1fC,"), Sensors::readTemperature2(), register_mem.data.cfg.temperature2_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
    Serial.printf_P(PSTR("MaxTmp=%u,Metrics=%us,"), register_mem.data.cfg.max_temperature, register_mem.data.cfg.metrics_report_interval);
#if HAVE_READ_VCC
    Serial.printf_P(PSTR("VCC=%.3f,"), Sensors::readVCC());
#endif
#if DIMMER_CUBIC_INTERPOLATION
    Serial.print(F("CubInt="));
    cubicInterpolation.printState();
#endif
    Serial.printf_P(PSTR("MinOn/Off=%u/%.1fus,%u/%.1fus,ZC=%d/%.1fus\n"),
        register_mem.data.cfg.min_on_ticks,
        DIMMER_T1_TICKS_TO_US_FLOAT(register_mem.data.cfg.min_on_ticks),
        register_mem.data.cfg.min_off_ticks,
        DIMMER_T1_TICKS_TO_US_FLOAT(register_mem.data.cfg.min_off_ticks),
        register_mem.data.cfg.zc_offset_ticks,
        DIMMER_T1_TICKS_TO_US_FLOAT(register_mem.data.cfg.zc_offset_ticks)
    );
    rem();
    Serial.printf_P(PSTR("errors=ZCmisfire=%u,temp=%u\n"),
        register_mem.data.errors.zc_misfire,
        register_mem.data.errors.temperature
    );
}

void setup()
{
    Serial.begin(DEFAULT_BAUD_RATE);
    #if SERIAL_I2C_BRDIGE && DEBUG
    _debug_level = 9;
    #endif

    Serial.println(F("+REM=BOOT"));

#if HAVE_NTC
    pinMode(NTC_PIN, INPUT);
#endif

    regMem.begin();

    ConfigStorage::Settings settings;
    config.read(settings);
    dimmer.begin();

    delay(100);
    Serial.println(F("+REM=Measuring frequency"));
    if (dimmer.measure(1000)) {
        // dimmer.enable();
    }
    else {
        Serial.println(F("+REM=timeout"));
    }

    // copy settings and restore channel level if enabled
    settings.copyFrom();

    ATOMIC_BLOCK(ATOMIC_FORCEON) {//TODO debug remove
        dimmer.setLevel(0, 2000);
        dimmer.setLevel(1, 2300);
        dimmer.setLevel(2, 7301);
        dimmer.setLevel(3, 2301);
    }

    display_dimmer_info();
}

void loop()
{
#if DIMMER_SIGNAL_GENERATOR_JITTER
    static unsigned long signalTimer = 0;
    if (millis() >= signalTimer) {
        signalTimer = millis() + 5000;
        if (OCR2A > 140) {
            // while(TCNT2!=OCR2A-1) ;
            OCR2A--;
        }
        else {
            OCR2A = 150;
        }
    }
#endif

    dimmer.sendFadingCompletedEvents();

    cli();
    if (millis() > config._eepromWriteTimer) {
        config._eepromWriteTimer = ConfigStorage::kEEPROMTimerDisabled;
        sei();
        config.writeSettings();
    }
    sei();

    // updating metrics takes 82ms (96ms with print_metrics_enabled)
    if (millis() >= update_metrics_timer) {
#define DEBUG_MEAS_METRICS_TIME 0
#if DEBUG_MEAS_METRICS_TIME
        auto start = micros();
#endif
        update_metrics_timer = millis() + DIMMER_UPDATE_METRICS_INTERVAL;

        register_mem_metrics_t tmp = { dimmer.getFrequency(), Sensors::readTemperature(), Sensors::readTemperature2(), Sensors::readVCCmV() };
        int16_t current_temp = max((int16_t)tmp.temperature, (int16_t)tmp.temperature2); // pick highest temperature

        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            register_mem.data.metrics = tmp;
        }

        if (register_mem.data.cfg.max_temperature && current_temp > (int16_t)register_mem.data.cfg.max_temperature) {
            // max. temperature exceeded, turn all channels off
            dimmer.setFade(-1, DIMMER_FADE_FROM_CURRENT_LEVEL, 0, 10);
            // store alert and save
            register_mem.data.errors.temperature++;
            config.writeSettings();

            // send temperature alert
            Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
            Wire.write(DIMMER_MASTER_COMMAND_TEMPERATURE_ALERT);
            Wire.write(current_temp);
            Wire.write(register_mem.data.cfg.max_temperature);
            Wire.endTransmission();
        }

        if (register_mem.data.cfg.bits.report_metrics) {
            if (millis() >= send_metrics_timer) {
                // no check if metrics_report_interval is zero needed since it is limited to DIMMER_UPDATE_METRICS_INTERVAL
                send_metrics_timer = millis() + (register_mem.data.cfg.metrics_report_interval * 1000UL);

                // send metrics
                Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
                Wire.write(DIMMER_MASTER_COMMAND_METRICS_REPORT);
                Wire_write(register_mem.data.metrics);
                Wire.endTransmission();
            }
        }

#if DEBUG_MEAS_METRICS_TIME
        auto stop1 = micros();
#endif

#if HAVE_PRINT_METRICS
        if (print_metrics_enabled) {
            Serial.printf_P(PSTR("+REM=ram=%u,stack=%u\n"), freeMemory(), stackAvailable());
            Serial.printf_P(PSTR("+REM=freq=%.2fHz/%u,temp=%.2f,temp2=%.2f,VCC=%u,lvl=%u"),
                tmp.frequency,
                dimmer.getHalfWaveTicks(),
                tmp.temperature,
                tmp.temperature2,
                tmp.vcc,
                register_mem.data.channels.level[0]
            );
#if DIMMER_CHANNELS>1
            for(dimmer_channel_id_t i = 1; i < Dimmer::kMaxChannels; i++) {
                Serial.print(',');
                Serial.print(register_mem.data.channels.level[i]);
            }
#endif
            Serial.println();
            Serial.flush();
        }
#endif

#if DEBUG_MEAS_METRICS_TIME
        auto stop2 = micros();
        Serial.printf_P(PSTR("update metrics %lu %lu\n"), stop1 - start, stop2 - start);
#endif

    }
}
