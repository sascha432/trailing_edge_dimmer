/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include "i2c_slave.h"
#include "helpers.h"
#include "cubic_interpolation.h"
#include <EEPROM.h>

unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;

void write_config()
{
    long lastWrite = millis() - eeprom_write_timer;
    if (!dimmer_scheduled_calls.writeEEPROM) { // no write scheduled
        _D(5, debug_printf_P(PSTR("scheduling eeprom write cycle, last write %d seconds ago\n"), (int)(lastWrite / 1000UL)));
        eeprom_write_timer = millis() + ((lastWrite > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
        dimmer_scheduled_calls.writeEEPROM = true;
    }
    else {
        _D(5, debug_printf_P(PSTR("eeprom write cycle already scheduled in %d seconds\n"), (int)(lastWrite / -1000L)));
    }
}

#if HAVE_READ_INT_TEMP

bool is_Atmega328PB; // runtime variable since the bootloader reports Atmega328P

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
float get_internal_temperature()
{
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    delay(40); // 20 was not enough. It takes quite a while when switching from reading VCC to temp.
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    // TODO verify calculation, it is way off for a couple of chips
    return ((ADCW - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (float)(register_mem.data.cfg.temperature2_offset / DIMMER_TEMP_OFFSET_DIVIDER);
}

#endif

#if HAVE_READ_VCC

// read VCC in mV
uint16_t read_vcc()
{
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(40);
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA, ADSC)) ;
    return (1000.0 * 1024.0) * register_mem.data.cfg.vref11 / (float)ADCW;
}

#else

constexpr uint16_t read_vcc() {
    return 0;
}

#endif

#if HAVE_NTC

uint16_t read_ntc_value()
{
    uint16_t value = analogRead(NTC_PIN);
    delay(1);
    return (value + analogRead(NTC_PIN)) / 2;
}

float convert_to_celsius(uint16_t value)
{
    float steinhart;
    steinhart = (1023 / (float)value) - 1;
    steinhart *= NTC_SERIES_RESISTANCE;
    steinhart /= NTC_NOMINAL_RESISTANCE;
    steinhart = log(steinhart);
    steinhart /= NTC_BETA_COEFF;
    steinhart += 1.0 / (NTC_NOMINAL_TEMP + 273.15);
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    return steinhart;
}

float get_ntc_temperature()
{
#ifdef FAKE_NTC_VALUE
    return FAKE_NTC_VALUE;
#else
    return convert_to_celsius(read_ntc_value()) + (register_mem.data.cfg.temperature_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
}

#endif

#if DIMMER_I2C_SLAVE

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
    Serial_printf_P(PSTR("sig=%02x-%02x-%02x,fuses=l:%02x,h:%02x,e:%02x"), mcu.sig[0], mcu.sig[1], mcu.sig[2], mcu.fuses[0], mcu.fuses[1], mcu.fuses[2]);
    if (*mcu.name) {
        Serial_printf_P(PSTR(",MCU=%s"), mcu.name);
    }
    Serial_printf_P(PSTR("@%uMhz\n"), (unsigned)(F_CPU / 1000000UL));

    rem();
    Serial.print(F("options="));
    Serial_printf_P(PSTR("Factory=%u,"), register_mem.data.cfg.bits.factory_settings);
#if HAVE_NTC
    // Serial_printf_P(PSTR("NTC=A%u,"), NTC_PIN - A0);
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
    Serial_printf_P(PSTR("Addr=%02x,Pre=" _STRINGIFY(DIMMER_TIMER1_PRESCALER) ",Ticks=%.1fus,MaxLvls=" _STRINGIFY(DIMMER_MAX_LEVELS) ",GPIO/lvl="), DIMMER_I2C_ADDRESS,1 / DIMMER_T1_TICKS_PER_US);
    FOR_CHANNELS(i) {
        Serial.print((int)dimmer_pins[i]);
        Serial.print('/');
        Serial.print(dimmer_level(i));
        if (i < DIMMER_CHANNELS - 1) {
            Serial.print(',');
        }
    }
    Serial.println();

    rem();
    Serial_printf_P(PSTR("values=Restore=%u,Frq=%.3f,Ref11="), register_mem.data.cfg.bits.restore_level, dimmer.getFrequency());
    Serial_print_float(register_mem.data.cfg.vref11, 4, 4);
    Serial.print(',');
#if HAVE_NTC
    Serial_printf_P(PSTR("NTC=%.2f/%+.1fC,"), get_ntc_temperature(), register_mem.data.cfg.temperature_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
#if HAVE_READ_INT_TEMP
    Serial_printf_P(PSTR("IntTemp=%.2f/%+.1fC,"), get_internal_temperature(), register_mem.data.cfg.temperature2_offset / DIMMER_TEMP_OFFSET_DIVIDER);
#endif
    Serial_printf_P(PSTR("MaxTmp=%u/%us,Metrics=%us,"), register_mem.data.cfg.max_temperature, register_mem.data.cfg.temp_check_interval, register_mem.data.cfg.metrics_report_interval);
#if HAVE_READ_VCC
    Serial_printf_P(PSTR("VCC=%.3f,"), read_vcc() / 1000.0);
#endif
#if DIMMER_CUBIC_INTERPOLATION
    Serial.print(F("CubInt="));
    cubicInterpolation.printState();
#endif
    Serial_printf_P(PSTR("MinOn/Off=%u/%.1fus,%u/%.1fus,ZC=%d/%.1fus\n"),
        register_mem.data.cfg.min_on_ticks,
        DIMMER_T1_TICKS_TO_US_FLOAT(register_mem.data.cfg.min_on_ticks),
        register_mem.data.cfg.min_off_ticks,
        DIMMER_T1_TICKS_TO_US_FLOAT(register_mem.data.cfg.min_off_ticks),
        register_mem.data.cfg.zc_offset_ticks,
        DIMMER_T1_TICKS_TO_US_FLOAT(register_mem.data.cfg.zc_offset_ticks)
    );
    rem();
    Serial_printf_P(PSTR("errors=ZCmisfire=%u,temp=%u\n"),
        register_mem.data.errors.zc_misfire,
        register_mem.data.errors.temperature
    );
}

void setup()
{
#if HAVE_READ_INT_TEMP
    uint8_t buf[3];
    is_Atmega328PB = memcmp_P(get_signature(buf), PSTR("\x1e\x95\x16"), 3) == 0;
#endif

    Serial.begin(DEFAULT_BAUD_RATE);
    #if SERIAL_I2C_BRDIGE && DEBUG
    _debug_level = 9;
    #endif

    Serial_println(F("+REM=BOOT"));

#if HAVE_NTC
    pinMode(NTC_PIN, INPUT);
#endif

    dimmer_i2c_slave_setup();

    ConfigStorage::Settings settings;
    config.read(settings);
    dimmer.begin();

    delay(100);
    Serial_println(F("+REM=Measuring frequency"));
    if (dimmer.measure(1000)) {
        dimmer.enable();
    }
    else {
        Serial_println(F("+REM=timeout"));
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

dimmer_scheduled_calls_t dimmer_scheduled_calls;

unsigned long next_temp_check = 0;
unsigned long next_event_metrics_event = 0;

#if HAVE_PRINT_METRICS

unsigned long print_metrics_timeout;

#endif

#if HAVE_FADE_COMPLETION_EVENT

void send_fading_completion_events()
{
    FadingCompletionEvent_t buffer[DIMMER_CHANNELS];
    FadingCompletionEvent_t *ptr = buffer;

    FOR_CHANNELS(i) {
        cli(); // dimmer.fadingCompleted is modified inside an interrupt and copying needs to be an atomic operation
        if (dimmer.fadingCompleted[i] != INVALID_LEVEL) {
            auto level = dimmer.fadingCompleted[i];
            dimmer.fadingCompleted[i] = INVALID_LEVEL;
            sei();

            ptr->channel = i;
            ptr->level = level;
            ptr++;
        }
        else {
            sei();
        }
    }

    if (ptr != buffer) {
        _D(5, debug_printf_P(PSTR("sending fading completion event for %u channel(s)\n"), ptr - buffer));

        Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
        Wire.write(DIMMER_MASTER_COMMAND_FADING_COMPLETE);
        Wire.write(reinterpret_cast<const uint8_t *>(buffer), (reinterpret_cast<const uint8_t *>(ptr) - reinterpret_cast<const uint8_t *>(buffer)));
        Wire.endTransmission();
    }
}

#endif

void loop()
{
#if DIMMER_SIGNAL_GENERATOR_JITTER
    static unsigned long signalTimer = 0;
    if (millis() > signalTimer) {
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
#if HAVE_READ_VCC
    if (dimmer_scheduled_calls.readVCC) {
        dimmer_scheduled_calls.readVCC = false;
        register_mem.data.metrics.vcc = read_vcc();
        _D(5, debug_printf_P(PSTR("Scheduled: read vcc=%u\n"), register_mem.data.vcc));
    }
#endif
#if HAVE_READ_INT_TEMP
    if (dimmer_scheduled_calls.readIntTemp) {
        dimmer_scheduled_calls.readIntTemp = false;
        register_mem.data.metrics.temperature2 = get_internal_temperature();
        _D(5, debug_printf_P(PSTR("Scheduled: read int. temp=%.3f\n"), register_mem.data.metrics.temperature2));
    }
#endif
#if HAVE_NTC
    if (dimmer_scheduled_calls.readNTCTemp) {
        dimmer_scheduled_calls.readNTCTemp = false;
        register_mem.data.metrics.temperature = get_ntc_temperature();
        _D(5, debug_printf_P(PSTR("Scheduled: read ntc=%.3f\n"), register_mem.data.metrics.temperature));
    }
#endif

#if HAVE_PRINT_METRICS
    if (dimmer_scheduled_calls.printMetrics && millis() > print_metrics_timeout) {
        print_metrics_timeout = millis() + PRINT_METRICS_REPEAT;
        Serial.print(F("+REM="));
        #if HAVE_NTC
            Serial_printf_P(PSTR("NTC=%.3f,"), get_ntc_temperature());
        #endif
        #if HAVE_READ_INT_TEMP
            Serial_printf_P(PSTR("int.temp=%.3f,"), get_internal_temperature());
        #endif
        #if HAVE_READ_VCC
            Serial_printf_P(PSTR("VCC=%u,"), read_vcc());
        #endif
        Serial_printf_P(PSTR("frq=%.3f(%u),"), dimmer.getFrequency(), dimmer.getHalfWaveTicks());
        Serial.print(F("lvl="));
        FOR_CHANNELS(i) {
            Serial.print(register_mem.data.channels.level[i]);
            if (i < DIMMER_CHANNELS - 1) {
                Serial.print(',');
            }
        }
        Serial.println();
        Serial.flush();
    }
#endif

#if HAVE_FADE_COMPLETION_EVENT
    if (dimmer_scheduled_calls.fadingCompleted)  {
        dimmer_scheduled_calls.fadingCompleted = false;
        send_fading_completion_events();
    }
#endif

    if (dimmer_scheduled_calls.writeEEPROM && millis() > eeprom_write_timer) {
        config.writeSettings();
    }

    if (millis() > next_temp_check) {
        register_mem.data.metrics.temperature = get_ntc_temperature();
        register_mem.data.metrics.temperature2 = get_internal_temperature();

        int current_temp = max((int)register_mem.data.metrics.temperature, (int)register_mem.data.metrics.temperature2);
        next_temp_check = millis() + (register_mem.data.cfg.temp_check_interval * 1000UL);

        if (register_mem.data.cfg.max_temperature && current_temp > (int)register_mem.data.cfg.max_temperature) {
            // max. temperature exceeded, turn all channels off
            dimmer.setFade(-1, DIMMER_FADE_FROM_CURRENT_LEVEL, 0, 10);
            // store alert and save
            register_mem.data.errors.temperature++;
            write_config();

            // send temperature alert
            Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
            Wire.write(DIMMER_MASTER_COMMAND_TEMPERATURE_ALERT);
            Wire.write(current_temp);
            Wire.write(register_mem.data.cfg.max_temperature);
            Wire.endTransmission();
        }

        if (register_mem.data.cfg.bits.report_metrics) {
            if (millis() > next_event_metrics_event) {
                register_mem.data.metrics.frequency =  dimmer.getFrequency();
                register_mem.data.metrics.vcc = read_vcc();
                next_event_metrics_event = millis() + (register_mem.data.cfg.metrics_report_interval * 1000UL);

                // send metrics
                Wire.beginTransmission(DIMMER_I2C_MASTER_ADDRESS);
                Wire.write(DIMMER_MASTER_COMMAND_METRICS_REPORT);
                Wire_write(register_mem.data.metrics);
                Wire.endTransmission();
            }
        }
    }
#endif
}
