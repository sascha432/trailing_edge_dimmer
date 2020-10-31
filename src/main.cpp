/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include <util/atomic.h>
#include <crc16.h>
#include "dimmer.h"
#include "sensor.h"
#include "i2c_slave.h"
#include "config.h"
#include "helpers.h"
#include "measure_frequency.h"
#include "adc.h"

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
// 23868
//30268
//30294

Queues queues;

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
    Serial.printf_P(PSTR("int.temp=%.2f/ofs=%u/gain=%u,"), get_internal_temperature(), dimmer_config.internal_temp_calibration.ts_offset, dimmer_config.internal_temp_calibration.ts_gain);
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

void setup() {

    uint8_t buf[3];
    is_Atmega328PB = memcmp_P(get_signature(buf), PSTR("\x1e\x95\x16"), 3) == 0;

//     	#define TSOFFSET		5
// #define TSGAIN			7

// T_offset = boot_signature_byte_get( TSOFFSET ) ;
// 	T_gain = boot_signature_byte_get( TSGAIN ) ;
// 	T_mult = 32768U / T_gain ;


//     	temp = AdcTotal ;
// 						temp -= 298 ;
// 						temp += T_offset ;
// 						temp *= T_mult ;
// 						temp >>= 8 ;
// 						temp += 25 ;
// 						Temperature = temp ;

    Serial.begin(DEFAULT_BAUD_RATE);
    // delay(1000);
    // for(uint8_t i = 0; i < 0x1f; i++) {
    //     auto tmp = boot_signature_byte_get(i);
    //     Serial.printf("%02x(%u) ", tmp,tmp);
    // }
    // Serial.println();

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

#if HAVE_FADE_COMPLETION_EVENT

void Dimmer::DimmerBase::send_fading_completion_events() {

    FadingCompletionEvent_t buffer[Dimmer::Channel::size()];
    FadingCompletionEvent_t *ptr = buffer;

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        DIMMER_CHANNEL_LOOP(i) {
            if (dimmer.fading_completed[i] != Dimmer::Level::invalid) {
                *ptr++ = { i, dimmer.fading_completed[i] };
                dimmer.fading_completed[i] = Dimmer::Level::invalid;
            }
        }
    }

    if (ptr != buffer) {
        // _D(5, debug_printf("sending fading completion event for %u channel(s)\n", ptr - buffer));

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_EVENT_FADING_COMPLETE);
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
        DIMMER_CHANNEL_LOOP(i) {
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

            // read all values once before starting the dimmer
            cli();
            _adc.begin();
            _adc.setPosition(0);
            _adc.restart();
            sei();
            uint32_t endTime = millis() + 250;
            while(millis() < endTime) {
                if (_adc.canScheduleNext()) {
                    _adc.next();
                    if (_adc.getPosition() == _adc.getMaxPosition()) {
                        break;
                    }
                }
            }
            _D(5, debug_printf("adc init time=%d count=%u\n", (int)(250 - (endTime - millis())), _adc.getPosition()));
            _D(5, _adc.dump());

            dimmer.begin();
            restore_level();


#if HIDE_DIMMER_INFO == 0
            ATOMIC_BLOCK(ATOMIC_FORCEON) {
                queues.scheduled_calls.print_info = true;
            }
#endif
        }
        return;
    }

    if (_adc.canScheduleNext()) {
        _adc.next();
    }


    // create non-volatile copy for read operations
    // reduces code size by ~30-40 byte
    cli();
    dimmer_scheduled_calls_nv_t tmp_scheduled_calls(queues.scheduled_calls);
    sei();

#if HIDE_DIMMER_INFO == 0
    if (tmp_scheduled_calls.print_info) {
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            queues.scheduled_calls.print_info = false;
        }
        display_dimmer_info();
    }
#endif

    uint24_t millis24 = (millis() >> 8);

#if HAVE_POTI
    {
        auto level = read_poti();
        if (abs(level - poti_level) >= max(1, (Dimmer::Level::max >> 10)) || (level == 0 && poti_level != 0)) {     // = ~0.1% steps
            if (level > Dimmer::Level::max) {
                level = Dimmer::Level::max;
            }
            if (poti_level != level) {
                poti_level = level;
                dimmer.set_channel_level(POTI_CHANNEL, level);
            }
        }

    }
#endif

    if (tmp_scheduled_calls.report_error) {
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            queues.scheduled_calls.report_error = false;
        }

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_EVENT_FREQUENCY_WARNING);
        Wire.write(0xff);
        Wire.write(reinterpret_cast<const uint8_t *>(&register_mem.data.errors), sizeof(register_mem.data.errors));
        Wire.endTransmission();
        _D(5, debug_printf("Report error\n"));
    }

#if HAVE_PRINT_METRICS

    if (queues.print_metrics.timer && millis24 >= queues.print_metrics.timer) {
        queues.print_metrics.timer = millis24 + queues.print_metrics.interval;
        rem();
        #if HAVE_NTC
            Serial.printf_P(PSTR("NTC=%.3f,"), get_ntc_temperature());
        #endif
        #if HAVE_READ_INT_TEMP
            Serial.printf_P(PSTR("int.temp=%.3f,"), get_internal_temperature());
        #endif
        #if HAVE_READ_VCC || HAVE_EXT_VCC
            Serial.printf_P(PSTR("VCC=%u,"), read_vcc());
        #endif
        #if HAVE_POTI
            Serial.printf_P(PSTR("poti=%u,"), _adc.getValue(ADCHandler::kPosPoti) >> 6);
        #endif
        // Serial.printf_P(PSTR("hw=%u,diff=%d,"), dimmer.halfwave_ticks, (int)dimmer.zc_diff_ticks);
        // Serial.printf_P(PSTR("frq=%.3f,mode=%c,lvl="), dimmer._get_frequency(), (dimmer_config.bits.leading_edge) ? 'L' : 'T');
        Serial.printf_P(PSTR("hw=%u,diff=%d,frq=%.3f,mode=%c,lvl="), dimmer.halfwave_ticks, (int)dimmer.zc_diff_ticks, dimmer._get_frequency(), (dimmer_config.bits.leading_edge) ? 'L' : 'T');
        DIMMER_CHANNEL_LOOP(i) {
            Serial.printf_P(PSTR("%d,"), register_mem.data.level[i]);
        }
        Serial.printf_P(PSTR("hf=%u,ticks="), (unsigned)dimmer._get_ticks_per_halfwave());
        DIMMER_CHANNEL_LOOP(j) {
            Serial.print(dimmer._get_ticks(j, register_mem.data.level[j]));
            if (j < Dimmer::Channel::max) {
                Serial.print(',');
            }
        }
        Serial.println();
        Serial.flush();
#if DEBUG
         _adc.dump();
#endif
    }
#endif

    if (tmp_scheduled_calls.send_channel_state) {
        cli();
        dimmer_channel_state_event_t event = { dimmer.channel_state };
        queues.scheduled_calls.send_channel_state = false;
        sei();

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_EVENT_CHANNEL_ON_OFF);
        Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
        Wire.endTransmission();
    }

#if HAVE_FADE_COMPLETION_EVENT
    if (tmp_scheduled_calls.send_fading_events) {
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            queues.scheduled_calls.send_fading_events = false;
            queues.fading_completed_events.timer = Queues::kFadingCompletedEventTimerOverFlows;
        }
    }
    if (queues.fading_completed_events.timer == 0) {
        // we can set the high byte to 0xff (= -256) to disable the timer if the value is 0 without locking interrupts
        reinterpret_cast<uint8_t *>(&queues.fading_completed_events.timer)[1] = 0xff;
        dimmer.send_fading_completion_events();
    }
#endif

    if (tmp_scheduled_calls.write_eeprom && conf.isEEPROMWriteTimerExpired()) {
        conf._writeConfig(false);
    }

    if (tmp_scheduled_calls.sync_event) {
        cli();
        auto event = dimmer.sync_event;
        if (event.sync) {
            dimmer.sync_event = {}; // clear data
        }
        else {
            dimmer.sync_event.lost = false; // keep data for sync event
        }
        queues.scheduled_calls.sync_event = false;
        sei();

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_EVENT_SYNC_EVENT);
        Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
        Wire.endTransmission();

        Serial.printf_P(PSTR("+REM=lost=%u,sync=%u,cnt=%u,c=%ld,t=%.1fus\n"), event.lost, event.sync, event.halfwave_counter, event.sync_difference_cycles * Dimmer::Timer<1>::prescaler, event.sync_difference_cycles / Dimmer::Timer<1>::ticksPerMicrosecond);
    }

    if (queues.check_temperature.timer == 0) {
        _adc.stop();
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            queues.check_temperature.timer = Queues::kTemperatureCheckTimerOverflows;
        }

#if HAVE_NTC

        int current_temp = (register_mem.data.ntc_temp = get_ntc_temperature());
#if HAVE_READ_INT_TEMP
        current_temp = max(current_temp, (int16_t)(register_mem.data.int_temp = get_internal_temperature()));
#endif

#elif HAVE_READ_INT_TEMP

        int current_temp = (register_mem.data.int_temp = get_internal_temperature());

#else

#error No temperature sensor available

#endif

        if (dimmer_config.max_temp && current_temp > (int)dimmer_config.max_temp) {
            _D(5, debug_printf("OVER TEMPERATURE PROTECTION temp=%d\n", current_temp));

            dimmer.fade_from_to(Dimmer::Channel::any, Dimmer::Level::current, Dimmer::Level::off, 10);
            dimmer_config.bits.over_temperature_alert_triggered = 1;
            conf.scheduleWriteConfig();
            Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
            Wire.write(DIMMER_EVENT_TEMPERATURE_ALERT);
            Wire.write((uint8_t)current_temp);
            Wire.write(dimmer_config.max_temp);
            Wire.endTransmission();
        }

        if (dimmer_config.report_metrics_interval && millis24 >= queues.report_metrics.timer) {
            queues.report_metrics.timer = millis24 + REPORT_METRICS_INTERVAL_MILLIS24(dimmer_config.report_metrics_interval);
            dimmer_metrics_t event = {
                (uint8_t)current_temp,
                read_vcc(),
                dimmer._get_frequency(),
                register_mem.data.ntc_temp,
                register_mem.data.int_temp
            };
            Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
            Wire.write(DIMMER_EVENT_METRICS_REPORT);
            Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
            Wire.endTransmission();
        }

        // restart reading adc values
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            _adc.setPosition(0);
            _adc.restart();
        }
    }
#endif
}
