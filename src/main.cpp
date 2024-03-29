/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include <util/atomic.h>
#include <avr/io.h>
#include <crc16.h>
#include "dimmer.h"
#include "sensor.h"
#include "i2c_slave.h"
#include "config.h"
#include "helpers.h"
#include "measure_frequency.h"
#include "adc.h"

Queues queues;

void remln(const __FlashStringHelper *str)
{
    rem();
    Serial.println(str);
    Serial.flush();
}

#if HIDE_DIMMER_INFO == 0

void display_dimmer_info()
{
    remln(F("MOSFET Dimmer " DIMMER_VERSION " " __DATE__ " " __TIME__ " " DIMMER_INFO));

    rem();
    MCUInfo_t mcu;
    get_mcu_type(mcu);

    Serial.printf_P(PSTR("sig=%02x-%02x-%02x,fuses=l:%02x,h:%02x,e:%02x"), mcu.sig[0], mcu.sig[1], mcu.sig[2], mcu.fuses[0], mcu.fuses[1], mcu.fuses[2]);
    if (mcu.name) {
        Serial.print(F(",MCU="));
        Serial.print(mcu.name);
    }
    Serial.println(F("@" _STRINGIFY(F_CPU_MHZ) "Mhz" __GNUC_STR__));
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
    #if SERIAL_I2C_BRIDGE
        Serial.print(F("proto=UART,"));
    #else
        Serial.print(F("proto=I2C,"));
    #endif
    Serial.printf_P(PSTR("addr=%02x,mode=%c,"), DIMMER_I2C_ADDRESS, (register_mem.data.cfg.bits.leading_edge ? 'L' : 'T'));
    Serial.printf_P(PSTR("timer1=%u/%.2f,lvls=" _STRINGIFY(DIMMER_MAX_LEVEL) ",pins="), Dimmer::Timer<1>::prescaler, Dimmer::Timer<1>::ticksPerMicrosecond);
    for(auto pin: Dimmer::Channel::pins) {
        Serial.print(pin);
        Serial.print(',');
    }
    #if DIMMER_CUBIC_INTERPOLATION
        Serial.printf_P(PSTR("cubic=%u,"), register_mem.data.cfg.bits.cubic_interpolation);
    #endif
    Serial.printf_P(PSTR("range=%d-%d\n"), register_mem.data.cfg.range_begin, register_mem.data.cfg.get_range_end());
    Serial.flush();

    rem();
    Serial.printf_P(PSTR("values=restore=%u,f=%.3fHz,vref11=%.3f,"), register_mem.data.cfg.bits.restore_level, dimmer._get_frequency(), static_cast<float>(register_mem.data.cfg.internal_vref11));
    #if HAVE_NTC
        Serial.printf_P(PSTR("NTC=%.2f/%+.2f,"), get_ntc_temperature(), static_cast<float>(register_mem.data.cfg.ntc_temp_cal_offset));
    #endif
    #if HAVE_READ_INT_TEMP
        Serial.printf_P(PSTR("int.temp=%d/ofs=%u/gain=%u,"),
            get_internal_temperature(),
            register_mem.data.cfg.internal_temp_calibration.ts_offset,
            register_mem.data.cfg.internal_temp_calibration.ts_gain
        );
    #endif
    Serial.printf_P(PSTR("max.temp=%u,metrics=%u"), register_mem.data.cfg.max_temp, REPORT_METRICS_INTERVAL(register_mem.data.cfg.report_metrics_interval));
    #if HAVE_READ_VCC
        Serial.print(F(",VCC="));
        auto vcc = read_vcc();
        if (vcc == 0xffff || vcc == 0) {
            Serial.print('/');
        }
        else {
            Serial.printf_P(PSTR("%.3f"), vcc / 1000.0);
        }
    #endif
    Serial.printf_P(PSTR(",min.on-time=%u,min.off=%u,ZC=%u\n"),
        register_mem.data.cfg.minimum_on_time_ticks,
        register_mem.data.cfg.minimum_off_time_ticks,
        register_mem.data.cfg.zero_crossing_delay_ticks
    );
    Serial.flush();
}

#endif

void setup()
{
    Serial.begin(DEFAULT_BAUD_RATE);

    #if SERIAL_I2C_BRIDGE && DEBUG
        _debug_level = 9;
    #endif

    #if HIDE_DIMMER_INFO == 0
        remln(F("BOOT"));
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

    FrequencyMeasurement::run();
    _D(5, debug_printf("exiting setup\n"));
}

#if HAVE_FADE_COMPLETION_EVENT

    void Dimmer::DimmerBase::send_fading_completion_events()
    {
        FadingCompletionEvent buffer[Channel::size()];
        auto ptr = buffer;

        DIMMER_CHANNEL_LOOP(i) {
            if (dimmer.fading_completed[i] != Level::invalid) {
                *ptr++ = { i, dimmer.fading_completed[i] };
                dimmer.fading_completed[i] = Level::invalid;
            }
        }
        sei();

        if (ptr != buffer) {
            // _D(5, debug_printf("sending fading completion event for %u channel(s)\n", ptr - buffer));
            DimmerEvent<DIMMER_EVENT_FADING_COMPLETE>::send(buffer, static_cast<uint8_t>(reinterpret_cast<const uint8_t *>(ptr) - reinterpret_cast<const uint8_t *>(buffer)));
        }
    }

#endif

#if HAVE_POTI
uint16_t poti_level = 0;
#endif

void restore_level()
{
    if (register_mem.data.cfg.bits.restore_level) {
        // restore levels from EEPROM configuration
        DIMMER_CHANNEL_LOOP(i) {
            _D(5, debug_printf("restoring ch=%u level=%u time=%f\n", i, conf.level(i), register_mem.data.cfg.fade_in_time));
            if (conf.level(i) && register_mem.data.cfg.fade_in_time) {
                dimmer.fade_channel_to(i, conf.level(i), register_mem.data.cfg.fade_in_time);
            }
        }
    }
}

void loop()
{
    // run in main loop that the I2C slave is responding
    if (measure) {
        if (FrequencyMeasurement::run()) {

            #if DIMMER_USE_ADC_INTERRUPT
                // read all values once before starting the dimmer
                ATOMIC_BLOCK(ATOMIC_FORCEON) {
                    _adc.begin();
                    _adc.setPosition(0);
                    _adc.restart();
                }
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
            #endif

            dimmer.begin();

            register_mem.data.metrics.int_temp = get_internal_temperature();
            register_mem.data.metrics.ntc_temp = get_ntc_temperature();
            /*register_mem.data.metrics.vcc = */read_vcc();

            // send restart event
            Dimmer::DimmerEvent<DIMMER_EVENT_RESTART>::send(register_mem.data.metrics);
            restore_level();

            #if HIDE_DIMMER_INFO == 0
                ATOMIC_BLOCK(ATOMIC_FORCEON) {
                    queues.scheduled_calls.print_info = true;
                }
            #endif
        }
        return;
    }

    #if DIMMER_USE_ADC_INTERRUPT
        if (_adc.canScheduleNext()) {
            ::delay(1);
            _adc.next();
        }
    #endif

    #if DIMMER_USE_QUEUE_LEVELS
        // apply level changes that have been received by i2c
        for(uint8_t i = 0; i < Dimmer::Channel::size(); i++) {
            #if SERIAL_I2C_BRIDGE
                // levels are only changed in SerialEvent, once at the end of each main loop
                auto &level = queues.levels[i];
            #else
                cli();
                auto level = queues.levels[i];
                queues.levels[i].type = dimmer_scheduled_levels_t::SetType::NONE;
                sei();
            #endif
            switch(level.type) {
                case dimmer_scheduled_levels_t::SetType::SET:
                    dimmer.set_channel_level(i, level.to);
                    #if SERIAL_I2C_BRIDGE
                        level.type = dimmer_scheduled_levels_t::SetType::NONE;
                    #endif
                    break;
                case dimmer_scheduled_levels_t::SetType::FADE:
                    dimmer.fade_channel_from_to(i, level.from, level.to, level.time);
                    #if SERIAL_I2C_BRIDGE
                        level.type = dimmer_scheduled_levels_t::SetType::NONE;
                    #endif
                    break;
                case dimmer_scheduled_levels_t::SetType::NONE:
                    break;
            }
        }
    #endif

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

    auto millis24 = __uint24_from_shr8_ui32(millis());

    #if HAVE_POTI
        {
            auto level = read_poti();
            if (abs(level - poti_level) >= std::max<int>(1, (Dimmer::Level::max >> 10)) || (level == 0 && poti_level != 0)) {     // = ~0.1% steps
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
        Dimmer::DimmerEvent<DIMMER_EVENT_FREQUENCY_WARNING>::send(0xff, register_mem.data.errors);
        _D(5, debug_printf("Report error\n"));
    }

    #if HAVE_PRINT_METRICS

        if (queues.print_metrics.interval && millis24 >= queues.print_metrics.timer) {
            queues.print_metrics.timer = millis24 + queues.print_metrics.interval;
            rem();
            #if HAVE_NTC
                Serial.printf_P(PSTR("NTC=%.2f°C(%.1f),"), get_ntc_temperature(), _adc.getNTC_ADCValueAsFloat());
            #endif
            #if HAVE_READ_INT_TEMP
                Serial.printf_P(PSTR("int.temp=%d°C(%.1f),"), get_internal_temperature(), _adc.getIntTemp_ADCValueAsFloat());
            #endif
            #if HAVE_READ_VCC || HAVE_EXT_VCC
                Serial.printf_P(PSTR("VCC=%umV (%.1f),"), read_vcc(), _adc.getVCC_ADCValueAsFloat());
            #endif
            #if HAVE_POTI
                Serial.printf_P(PSTR("poti=%.1f,"), _adc.getPoti_ADCValueAsFloat());
            #endif
            // Serial.printf_P(PSTR("hw=%u,diff=%d,"), dimmer.halfwave_ticks, (int)dimmer.zc_diff_ticks);
            // Serial.printf_P(PSTR("frq=%.3f,mode=%c,lvl="), dimmer._get_frequency(), (register_mem.data.cfg.bits.leading_edge) ? 'L' : 'T');
            Serial.printf_P(PSTR("hw=%u,diff=%d,frq=%.3f,mode=%c,lvl="), dimmer.halfwave_ticks, (int)dimmer.zc_diff_ticks, dimmer._get_frequency(), (register_mem.data.cfg.bits.leading_edge) ? 'L' : 'T');
            DIMMER_CHANNEL_LOOP(i) {
                Serial.printf_P(PSTR("%d,"), register_mem.data.channels.level[i]);
            }
            Serial.printf_P(PSTR("hf=%u,ticks="), (unsigned)dimmer._get_ticks_per_halfwave());
            DIMMER_CHANNEL_LOOP(j) {
                Serial.print(dimmer._get_ticks(j, register_mem.data.channels.level[j]));
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

        Dimmer::DimmerEvent<DIMMER_EVENT_CHANNEL_ON_OFF>::send(event);
    }

    #if HAVE_FADE_COMPLETION_EVENT
        if (tmp_scheduled_calls.send_fading_events) {
            cli();
            // wait for timer to collect multiple fading events within 100ms
            if (queues.fading_completed_events.timer == 0) {
                queues.scheduled_calls.send_fading_events = false;
                queues.fading_completed_events.disableTimer(); // disable timer until new events are added
                dimmer.send_fading_completion_events(); // calls sei()
            }
            sei();
        }
    #endif

    if (tmp_scheduled_calls.write_eeprom && conf.isEEPROMWriteTimerExpired()) {
        conf._writeConfig(false);
    }

    #if ENABLE_ZC_PREDICTION
        if (tmp_scheduled_calls.sync_event) {
            Dimmer::DimmerEvent<DIMMER_EVENT_SYNC_EVENT>::send(dimmer.sync_event);

            Serial.printf_P(PSTR("+REM=lost,invalid=%u,time=%u,restarting\n"), dimmer.sync_event.invalid_signals, dimmer.sync_event.halfwave_micros);

            // start new measurement
            FrequencyMeasurement::run();
            return;
        }
    #endif

    if (queues.check_temperature.timer == 0) {
        #if DIMMER_USE_ADC_INTERRUPT
            _adc.stop();
        #endif
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            queues.check_temperature.timer = Queues::kTemperatureCheckTimerOverflows;
        }
        #if ENABLE_ZC_PREDICTION
            dimmer.set_halfwave_ticks(dimmer.halfwave_ticks_integral);
        #endif

        int16_t current_temp;
        enable_serial_read_during_delay();
        #if HAVE_NTC
            
            register_mem.data.metrics.ntc_temp = get_ntc_temperature();
            if (!isnan(register_mem.data.metrics.ntc_temp)) {
                current_temp = register_mem.data.metrics.ntc_temp;
            }
            #if HAVE_READ_INT_TEMP
                register_mem.data.metrics.int_temp = get_internal_temperature();
                if (!isnan(register_mem.data.metrics.int_temp)) {
                    current_temp = std::max(current_temp, register_mem.data.metrics.int_temp);
                }
            #endif

        #elif HAVE_READ_INT_TEMP

            register_mem.data.metrics.int_temp = get_internal_temperature();
            current_temp = isnan(register_mem.data.metrics.int_temp) ? 0 : register_mem.data.metrics.int_temp;

        #else

            #error No temperature sensor available

        #endif
        disable_serial_read_during_delay();

        if (register_mem.data.cfg.max_temp && current_temp > static_cast<int16_t>(register_mem.data.cfg.max_temp)) {

            if (millis24 >= queues.check_temperature.report_next) {

                _D(5, debug_printf("OVER TEMPERATURE PROTECTION temp=%d\n", current_temp));
                queues.check_temperature.report_next = millis24 + (30000U >> 8); // next alert in 30 seconds

                if (!register_mem.data.cfg.bits.over_temperature_alert_triggered) {
                    register_mem.data.cfg.bits.over_temperature_alert_triggered = 1;
                    conf.scheduleWriteConfig();
                }

                dimmer.set_level(Dimmer::Channel::any, Dimmer::Level::off);

                Dimmer::DimmerEvent<DIMMER_EVENT_TEMPERATURE_ALERT>::send(dimmer_over_temperature_event_t{ static_cast<uint8_t>(current_temp), register_mem.data.cfg.max_temp });
            }

        }

        if (register_mem.data.cfg.report_metrics_interval && millis24 >= queues.report_metrics.timer) {
            queues.report_metrics.timer = millis24 + REPORT_METRICS_INTERVAL_MILLIS24(register_mem.data.cfg.report_metrics_interval);
            enable_serial_read_during_delay();
            register_mem.data.metrics.int_temp = get_internal_temperature();
            register_mem.data.metrics.ntc_temp = get_ntc_temperature();
            /*register_mem.data.metrics.vcc = */read_vcc();
            disable_serial_read_during_delay();
            Dimmer::DimmerEvent<DIMMER_EVENT_METRICS_REPORT>::send(static_cast<uint8_t>(current_temp), register_mem.data.metrics);

            #if DEBUG_ZC_PREDICTION
                // display the zc prediction values
                Serial.flush();
                Serial.printf_P(PSTR("+REM=zc=%u,n=%u,v=%u,p=%u,s=%u,i=%u\n"), dimmer.debug_pred.zc_signals, dimmer.debug_pred.next_cycle, dimmer.debug_pred.valid_signals, dimmer.debug_pred.pred_signals, dimmer.debug_pred.start_halfwave, dimmer.debug_pred.invalid_signals);
                Serial.flush();
                Serial.print(F("+REM="));
                for(uint8_t i = 0; i < dimmer.kTimeStorage; i++) {
                    long tmp = dimmer.debug_pred.times[i];
                    Serial.print(tmp);
                    Serial.print(',');
                }
                Serial.print(dimmer.halfwave_ticks_integral, 1);
                Serial.print(',');
                Serial.print(dimmer._get_frequency(), 4);
                Serial.print(',');
                Serial.println((F_CPU / 2) / dimmer.halfwave_ticks_integral, 4);
                Serial.flush();
            #endif
        }

        #if DIMMER_USE_ADC_INTERRUPT
            // restart reading adc values
            ATOMIC_BLOCK(ATOMIC_FORCEON) {
                _adc.setPosition(0);
                _adc.restart();
            }
        #endif
    }
}
