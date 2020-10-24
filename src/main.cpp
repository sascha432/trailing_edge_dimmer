/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include <crc16.h>
#include "dimmer.h"
#include "sensor.h"
#include "i2c_slave.h"
#include "config.h"
#include "helpers.h"
#include "measure_frequency.h"

// size reduction
//23704 - 2.1.3
//23492 - helpers.cpp / get_signature
//Flash: [=======   ]  73.5% (used 22570 bytes from 30720,22824
// lash: [========  ]  76.2% (used 23416 bytes from 30720 byt
//ash: [========  ]  76.2% (used 23398 bytes from 30720 bytes)
//ash: [========  ]  76.8% (used 23588 bytes from 30720 byte
//Flash: [========  ]  76.6% (used 23530 bytes from 30720 byte
//Flash: [========  ]  76.6% (used 23518 bytes from 30720 bytes)
//Flash: [=======   ]  73.1% (used 22468 bytes from 30720 bytes)
// Flash: [=======   ]  73.2% (used 22480 bytes from 30720 bytes
// frequency detection and continue without zc signal
// Flash: [========  ]  78.7% (used 24168 bytes from 30720 bytes)
// lash: [========  ]  78.7% (used 24188 bytes from 30720 bytes
// 29888

void rem() {
    Serial.print(F("+REM="));
}

#if HIDE_DIMMER_INFO == 0

void display_dimmer_info() {

    rem();
    Serial.println(F("MOSFET Dimmer " DIMMER_VERSION " " __DATE__ " " __TIME__ " " DIMMER_INFO));
    Serial.flush();

    rem();
    MCUInfo_t mcu;
    get_mcu_type(mcu);

    Serial.printf_P(PSTR("sig=%02x-%02x-%02x,fuses=l:%02x,h:%02x,e:%02x"), mcu.sig[0], mcu.sig[1], mcu.sig[2], mcu.fuses[0], mcu.fuses[1], mcu.fuses[2]);
    if (mcu.name) {
        Serial.printf_P(PSTR(",MCU=%S"), mcu.name);
    }
    Serial.printf_P(PSTR("@%uMhz\n"), (unsigned)(F_CPU / 1000000UL));
    Serial.flush();

    rem();
    Serial.printf_P(PSTR("options=EEPROM=%lu,"), conf.getEEPROMWriteCount());
#if HAVE_NTC
    Serial.printf_P(PSTR("NTC=A%u,"), NTC_PIN - A0);
#endif
#if HAVE_READ_INT_TEMP
    Serial.print(F("int.temp,"));
#endif
#if HAVE_READ_VCC
    Serial.print(F("VCC,"));
#endif
#if HAVE_FADE_COMPLETION_EVENT
    Serial.print(F("fading_events=1,"));
#endif
#if SERIAL_I2C_BRDIGE
    Serial.print(F("proto=UART,"));
#else
    Serial.print(F("proto=I2C,"));
#endif
    Serial.printf_P(PSTR("addr=%02x,mode=%c,"),
        DIMMER_I2C_ADDRESS,
        (dimmer_config.bits.leading_edge ? 'L' : 'T')
    );
    Serial.printf_P(PSTR("timer1=%u/%.2f,lvls=" _STRINGIFY(DIMMER_MAX_LEVEL) ",pins="), Dimmer::Timer<1>::prescaler, Dimmer::Timer<1>::ticksPerMicrosecond);
    for(auto pin: Dimmer::Channel::pins) {
        Serial.print(pin);
        Serial.print(',');
    }
    Serial.printf_P(PSTR("range=%d-%d\n"), dimmer_config.range_begin, dimmer_config.get_range_end());
    Serial.flush();

    rem();
    Serial.printf_P(PSTR("values=restore=%u,f=%.3fHz,vref11=%.3f,"), dimmer_config.bits.restore_level, dimmer._get_frequency(), (float)dimmer_config.internal_vref11);
#if HAVE_NTC
    Serial.printf_P(PSTR("NTC=%.2f/%+.2f,"), get_ntc_temperature(), (float)dimmer_config.ntc_temp_offset);
#endif
#if HAVE_READ_INT_TEMP
    Serial.printf_P(PSTR("int.temp=%.2f/%+.2f,"), get_internal_temperature(), (float)dimmer_config.int_temp_offset);
#endif
    Serial.printf_P(PSTR("max.temp=%u,metrics=%u,"), dimmer_config.max_temp, REPORT_METRICS_INTERVAL(dimmer_config.report_metrics_interval));
#if HAVE_READ_VCC
    Serial.printf_P(PSTR("VCC=%.3f,"), read_vcc() / 1000.0);
#endif
    Serial.printf_P(PSTR("min.on-time=%u,min.off=%u,ZC-delay=%u,"),
        dimmer_config.minimum_on_time_ticks,
        dimmer_config.minimum_off_time_ticks,
        dimmer_config.zero_crossing_delay_ticks
    );
    Serial.printf_P(PSTR("sw.on-time=%u/%u\n"),
        dimmer_config.switch_on_minimum_ticks,
        dimmer_config.switch_on_count
    );
    Serial.flush();
}

dimmer_scheduled_calls_t dimmer_scheduled_calls;
uint32_t metrics_next_event;

void setup() {

    uint8_t buf[3];
    is_Atmega328PB = memcmp_P(get_signature(buf), PSTR("\x1e\x95\x16"), 3) == 0;

    Serial.begin(DEFAULT_BAUD_RATE);

#if SERIAL_I2C_BRDIGE && DEBUG
    _debug_level = 9;
#endif

#if HIDE_DIMMER_INFO == 0
    rem();
    Serial.println(F("BOOT"));
    Serial.flush();
#endif

    dimmer_i2c_slave_setup();
    conf.readConfig();

#if HAVE_POTI
    pinMode(POTI_PIN, INPUT);
#endif
#if HAVE_NTC
    pinMode(NTC_PIN, INPUT);
#endif
    pinMode(ZC_SIGNAL_PIN, INPUT);

    register_mem.data.errors = {};

    start_measure_frequency();
    _D(5, debug_printf("exiting setup\n"));
}

uint32_t next_temp_check;

#if HAVE_PRINT_METRICS

uint32_t print_metrics_timeout;
uint16_t print_metrics_interval;

#endif

#if HAVE_FADE_COMPLETION_EVENT

uint32_t next_fading_event_check;

void Dimmer::DimmerBase::send_fading_completion_events() {

    FadingCompletionEvent_t buffer[Dimmer::Channel::size()];
    FadingCompletionEvent_t *ptr = buffer;

    cli();
    for(Channel::type i = 0; i < Dimmer::Channel::size(); i++) {
        if (dimmer.fading_completed[i] != Dimmer::Level::invalid) {
            *ptr++ = { i, dimmer.fading_completed[i] };
            dimmer.fading_completed[i] = Dimmer::Level::invalid;
        }
    }
    sei();

    if (ptr != buffer) {
        _D(5, debug_printf("sending fading completion event for %u channel(s)\n", ptr - buffer));

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_FADING_COMPLETE);
        Wire.write(reinterpret_cast<const uint8_t *>(buffer), (reinterpret_cast<const uint8_t *>(ptr) - reinterpret_cast<const uint8_t *>(buffer)));
        Wire.endTransmission();
    }

}

#endif

#if HAVE_POTI
uint16_t poti_level = 0;
#endif

void restore_level()
{
    if (dimmer_config.bits.restore_level) {
        // restore levels from EEPROM configuration
        for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size(); i++) {
            _D(5, debug_printf("restoring ch=%u level=%u time=%f\n", i, conf.level(i), dimmer_config.fade_in_time));
            if (conf.level(i) && dimmer_config.fade_in_time) {
                dimmer.fade_channel_to(i, conf.level(i), dimmer_config.fade_in_time);
            }
        }
    }
}

void loop()
{
    // run in main loop that the I2C slave is responding
    if (frequency_measurement) {
        if (run_frequency_measurement()) {
            dimmer.begin();
            restore_level();
#if HIDE_DIMMER_INFO == 0
            dimmer_scheduled_calls.print_info = true;
#endif
        }
        return;
    }


#if HIDE_DIMMER_INFO == 0
    if (dimmer_scheduled_calls.print_info) {
        dimmer_scheduled_calls.print_info = false;
        display_dimmer_info();
    }
#endif

#if HAVE_POTI
    {
        auto level = read_poti();
        if (abs(level - poti_level) >= max(1, (Dimmer::Level::max / 256))) { // ~0.39% steps
            if (level < (int32_t)Dimmer::Level::min) {
                level = Dimmer::Level::min;
            }
            else if (level > Dimmer::Level::max) {
                level = Dimmer::Level::max;
            }
            if (poti_level != level) {
                poti_level = level;
                dimmer.set_channel_level(POTI_CHANNEL, level);
            }
        }

    }
#endif

#if HAVE_READ_VCC
    if (dimmer_scheduled_calls.read_vcc) {
        dimmer_scheduled_calls.read_vcc = false;
        register_mem.data.vcc = read_vcc();
        _D(5, debug_printf("Scheduled: read vcc=%u\n", register_mem.data.vcc));
    }
#endif
#if HAVE_READ_INT_TEMP
    if (dimmer_scheduled_calls.read_int_temp) {
        dimmer_scheduled_calls.read_int_temp = false;
        register_mem.data.temp = get_internal_temperature();
        _D(5, debug_printf("Scheduled: read int. temp=%.3f\n", register_mem.data.temp));
    }
#endif
#if HAVE_NTC
    if (dimmer_scheduled_calls.read_ntc_temp) {
        dimmer_scheduled_calls.read_ntc_temp = false;
        register_mem.data.temp = get_ntc_temperature();
        _D(5, debug_printf("Scheduled: read ntc=%.3f\n", register_mem.data.temp));
    }
#endif

    if (dimmer_scheduled_calls.report_error) {
        dimmer_scheduled_calls.report_error = false;

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_FREQUENCY_WARNING);
        Wire.write(0xff);
        Wire.write(reinterpret_cast<const uint8_t *>(&register_mem.data.errors), sizeof(register_mem.data.errors));
        Wire.endTransmission();
        _D(5, debug_printf("Report error\n"));
    }

#if HAVE_PRINT_METRICS
    if (print_metrics_interval && millis() >= print_metrics_timeout) {
        print_metrics_timeout = millis() + print_metrics_interval;
        rem();
        #if HAVE_NTC
            Serial.printf_P(PSTR("NTC=%.3f,"), get_ntc_temperature());
        #endif
        #if HAVE_READ_INT_TEMP
            Serial.printf_P(PSTR("int.temp=%.3f,"), get_internal_temperature());
        #endif
        #if HAVE_EXT_VCC
            Serial.printf_P(PSTR("VCC=%u,VCCi=%u,"), read_vcc(), read_vcc_int());
        #elif HAVE_READ_VCC
            Serial.printf_P(PSTR("VCC=%u,"), read_vcc());
        #endif
        #if HAVE_POTI
            Serial.printf_P(PSTR("poti=%u,"), raw_poti_value);
        #endif
        // Serial.printf_P(PSTR("hw=%u,diff=%d,"), dimmer.halfwave_ticks, (int)dimmer.zc_diff_ticks);
        // Serial.printf_P(PSTR("frq=%.3f,mode=%c,lvl="), dimmer._get_frequency(), (dimmer_config.bits.leading_edge) ? 'L' : 'T');
        Serial.printf_P(PSTR("hw=%u,diff=%d,frq=%.3f,mode=%c,lvl="), dimmer.halfwave_ticks, (int)dimmer.zc_diff_ticks, dimmer._get_frequency(), (dimmer_config.bits.leading_edge) ? 'L' : 'T');
        for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size(); i++) {
            Serial.printf_P(PSTR("%d,"), register_mem.data.level[i]);
        }
        Serial.printf_P(PSTR("hf=%u,ticks="), (unsigned)dimmer._get_ticks_per_halfwave());
        for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size(); i++) {
            Serial.print(dimmer._get_ticks(i, register_mem.data.level[i]));
            if (i < Dimmer::Channel::max) {
                Serial.print(',');
            }
        }
        Serial.println();
        Serial.flush();
    }
#endif

    cli();
    if (dimmer_scheduled_calls.send_channel_state) {
        dimmer_channel_state_event_t event = { dimmer.channel_state };
        dimmer_scheduled_calls.send_channel_state = false;
        sei();

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_CHANNEL_ON_OFF);
        Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
        Wire.endTransmission();
    }
    else {
        sei();
    }

#if HAVE_FADE_COMPLETION_EVENT
    if (dimmer_scheduled_calls.send_fading_events) {
        dimmer_scheduled_calls.send_fading_events = false;
        next_fading_event_check = millis() + 50; // delay sending events to send them in batches
    }
    if (next_fading_event_check && millis() >= next_fading_event_check) {
        next_fading_event_check = 0;
        dimmer.send_fading_completion_events();
    }
#endif

    if (dimmer_scheduled_calls.write_eeprom && conf.isEEPROMWriteTimerExpired()) {
        conf._writeConfig(false);
    }

    if (millis() >= next_temp_check) {

        int current_temp;
#if HAVE_NTC
        float ntc_temp = get_ntc_temperature();
        current_temp = ntc_temp;
        if (ntc_temp < 0) {
            current_temp = 0;
        }
#endif
#if HAVE_READ_INT_TEMP
        float int_temp = get_internal_temperature();
        current_temp = max(current_temp, (int)int_temp);
#endif
        next_temp_check = millis() + DIMMER_TEMPERATURE_CHECK_INTERVAL;
        if (dimmer_config.max_temp && current_temp > (int)dimmer_config.max_temp) {
            _D(5, debug_printf("OVER TEMPERATURE PROTECTION temp=%d\n", current_temp));
            dimmer.fade_from_to(Dimmer::Channel::any, Dimmer::Level::current, Dimmer::Level::off, 10);
            dimmer_config.bits.over_temperature_alert_triggered = 1;
            conf.scheduleWriteConfig();
            Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
            Wire.write(DIMMER_TEMPERATURE_ALERT);
            Wire.write((uint8_t)current_temp);
            Wire.write(dimmer_config.max_temp);
            Wire.endTransmission();
        }

        if (dimmer_config.report_metrics_interval && millis() >= metrics_next_event) {
            metrics_next_event = millis() + REPORT_METRICS_INTERVAL_MILLIS(dimmer_config.report_metrics_interval);
            dimmer_metrics_t event = {
                (uint8_t)current_temp,
#if HAVE_READ_VCC
                read_vcc(),
#else
                0,
#endif
                dimmer._get_frequency(),
#if HAVE_READ_INT_TEMP
                ntc_temp,
#else
                NAN,
#endif
#if HAVE_NTC
                int_temp,
#else
                NAN
#endif
            };
            Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
            Wire.write(DIMMER_METRICS_REPORT);
            Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
            Wire.endTransmission();
        }
    }
#endif
}
