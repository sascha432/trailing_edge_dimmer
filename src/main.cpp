/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include <EEPROM.h>
#include <crc16.h>
#include "dimmer.h"
#include "sensor.h"
#include "i2c_slave.h"
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

static constexpr uint16_t kInvalidPosition = ~0;

EEPROM_config_t config;
uint16_t eeprom_position;
unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;

void reset_config()
{
    dimmer_init_register_mem();
    dimmer_config.max_temp = 75;
    dimmer_config.bits.restore_level = DIMMER_RESTORE_LEVEL;
    dimmer_config.bits.leading_edge = (DIMMER_TRAILING_EDGE == 0);
    dimmer_config.fade_in_time = 4.5f;
    dimmer_config.zero_crossing_delay_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_ZC_DELAY_US);
    dimmer_config.minimum_on_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_ON_TIME_US);
    dimmer_config.minimum_off_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_OFF_TIME_US);
#ifdef INTERNAL_TEMP_OFS
    dimmer_config.int_temp_offset = INTERNAL_TEMP_OFS;
#endif
    dimmer_config.range_begin = Dimmer::Level::min;
    dimmer_config.range_end = Dimmer::Level::max;
    dimmer_config.report_metrics_interval = 2;

    dimmer_copy_config_to(config.cfg);
}

unsigned long get_eeprom_num_writes(unsigned long cycle, uint16_t position)
{
    return (kEEPROMMaxCopies * (cycle - 1)) + (position / sizeof(EEPROM_config_t));
}


void init_eeprom()
{
    // initialize EEPROM and wear leveling
    // invalidates cycle number and crc only
    EEPROM_config_header_t header = { 0, ~0U };
    uint16_t pos = sizeof(EEPROM_config_t);
    while((pos + sizeof(EEPROM_config_t)) <= EEPROM.length()) {
        EEPROM.put(pos, header);
        pos += sizeof(EEPROM_config_t);
    }

    // create first valid configuration
    eeprom_position = 0;
    config = {};
    config.eeprom_cycle = 1;
    reset_config();
    config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg));
    EEPROM.put(0, config);
    _D(5, debug_printf("init eeprom cycle=%lu pos=%u crc=%04x\n", (unsigned long)config.eeprom_cycle, (unsigned)eeprom_position, config.crc16));
    Serial.println(F("+REM=EEPROMR,init"));
}

void read_config()
{
    uint16_t pos = 0;
    uint32_t max_cycle = 0;
    EEPROM_config_t temp_config;

    eeprom_position = kInvalidPosition;

    // read entire eeprom and check which entries are valid
    // if the most recent configuration cannot be read, the previous one is used

    _D(5, debug_printf("reading eeprom "));
#if DEBUG
    char type;
    uint32_t start = micros();
#endif
    while((pos + sizeof(temp_config)) <= EEPROM.length()) {
        EEPROM.get(pos, temp_config);
        auto crc = crc16_update(&temp_config.cfg, sizeof(temp_config.cfg));
        if (crc == temp_config.crc16) {
            // valid configuration
            if (temp_config.eeprom_cycle >= max_cycle) {
                // if cycle is equal or greater max_cycle, the configuration is more recent
                // remember max_cycle, positition and copy data
                max_cycle = temp_config.eeprom_cycle;
                eeprom_position = pos;
                config = temp_config;
#if DEBUG
                type = 'N'; // new
#endif
            }
#if DEBUG
            else {
                type = 'O'; // old
            }
#endif
        }
#if DEBUG
        else {
            type = 'E'; // error
        }
        _D(5, Serial.printf_P(PSTR("%lu:%u<%c> "), temp_config.eeprom_cycle, pos, type));
#endif
        pos += sizeof(config);
    }
    _D(5, Serial.printf_P(PSTR("max_cycle=%ld pos=%d time=%lu\n"), max_cycle, eeprom_position, micros() - start));

    if (eeprom_position == kInvalidPosition) { // no valid entries found
        init_eeprom();
        _D(5, debug_print_memory(&config.cfg, sizeof(config.cfg)));
        return;
    }

    dimmer_copy_config_from(config.cfg);
    _D(5, debug_print_memory(&config.cfg, sizeof(config.cfg)));
    Serial.printf_P(PSTR("+REM=EEPROMR,c=%lu,p=%u,n=%lu,crc=%04x\n"), (unsigned long)max_cycle, eeprom_position, get_eeprom_num_writes(max_cycle, eeprom_position), config.crc16);
}

void _write_config(bool force)
{
    EEPROM_config_t temp_config;
    dimmer_eeprom_written_t event = {};

    if (dimmer_scheduled_calls.eeprom_update_config) {
        event.config_updated = true;
        dimmer_copy_config_to(config.cfg);
    }

    memcpy(&config.level, &register_mem.data.level, sizeof(config.level));
    config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg));

    EEPROM.get(eeprom_position, temp_config);

    _D(5, debug_printf("_write_config force=%u reg_mem=%u memcmp=%d\n", force, event.config_updated, memcmp(&config, &temp_config, sizeof(config))));

    if (force || memcmp(&config, &temp_config, sizeof(config))) {
        _D(5, debug_printf("old eeprom write cycle %lu, position %u, ", (unsigned long)config.eeprom_cycle, eeprom_position));
        eeprom_position += sizeof(config);
        if (eeprom_position + sizeof(config) >= EEPROM.length()) { // end reached, start from beginning and increase cycle counter
            eeprom_position = 0;
            config.eeprom_cycle++;
            config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg)); // recalculate CRC
        }
        _D(5, debug_printf("new cycle %lu, position %u\n", (unsigned long)config.eeprom_cycle, eeprom_position));
        EEPROM.put(eeprom_position, config);
        eeprom_write_timer = millis();
        event.bytes_written = sizeof(config);
    }
    else {
        _D(5, debug_printf("configuration didn't change, skipping write cycle\n"));
        eeprom_write_timer = millis();
        event.bytes_written = 0;
    }
    dimmer_scheduled_calls.write_eeprom = false;
    dimmer_scheduled_calls.eeprom_update_config = false;

    event.write_cycle = config.eeprom_cycle;
    event.write_position = eeprom_position;

    _D(5, debug_printf("eeprom written event: cycle %lu, pos %u, written %u\n", (unsigned long)event.write_cycle, event.write_position, event.bytes_written));
    Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
    Wire.write(DIMMER_EEPROM_WRITTEN);
    Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
    Wire.endTransmission();

    Serial.printf_P(PSTR("+REM=EEPROMW,c=%lu,p=%u,n=%lu,w=%u,f=%u,crc=%04x\n"),
        (unsigned long)event.write_cycle,
        eeprom_position,
        get_eeprom_num_writes(event.write_cycle, eeprom_position),
        event.bytes_written,
        event.flags,
        config.crc16
    );
}

void write_config()
{
    long lastWrite = millis() - eeprom_write_timer;
    if (!dimmer_scheduled_calls.write_eeprom) { // no write scheduled
        _D(5, debug_printf("scheduling eeprom write cycle, last write %d seconds ago\n", (int)(lastWrite / 1000UL)));
        eeprom_write_timer = millis() + ((lastWrite > EEPROM_REPEATED_WRITE_DELAY) ? EEPROM_WRITE_DELAY : EEPROM_REPEATED_WRITE_DELAY);
        dimmer_scheduled_calls.write_eeprom = true;
    } else {
        _D(5, debug_printf("eeprom write cycle already scheduled in %d seconds\n", (int)(lastWrite / -1000L)));
    }
}

void restore_level()
{
    if (dimmer_config.bits.restore_level) {
        for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size; i++) {
            _D(5, debug_printf("restoring ch=%u level=%u time=%f\n", i, config.level[i], dimmer_config.fade_in_time));
            if (config.level[i] && dimmer_config.fade_in_time) {
                dimmer.fade_channel_to(i, config.level[i], dimmer_config.fade_in_time);
            }
        }
    }
}

void rem() {
#if SERIAL_I2C_BRDIGE
    Serial.print(F("+REM="));
#endif
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
    Serial.print(F("options="));
    Serial.printf_P(PSTR("EEPROM=%lu,"), get_eeprom_num_writes(config.eeprom_cycle, eeprom_position));
#if HAVE_NTC
    Serial.printf_P(PSTR("NTC=A%u,"), NTC_PIN - A0);
#endif
#if HAVE_READ_INT_TEMP
    Serial.print(F("Int.Temp,"));
#endif
#if HAVE_READ_VCC
    Serial.print(F("VCC,"));
#endif
    Serial.printf_P(PSTR("ACFrq=%u,"), dimmer._get_frequency());
#if SERIAL_I2C_BRDIGE
    Serial.print(F("Pr=UART,"));
#else
    Serial.print(F("Pr=I2C,"));
#endif
#if HAVE_FADE_COMPLETION_EVENT
    Serial.print(F("CE=1,"));
#endif
    Serial.printf_P(PSTR("Addr=%02x,Pre=%u/%u,Mode=%c,"),
        DIMMER_I2C_ADDRESS,
        DIMMER_TIMER1_PRESCALER, DIMMER_TIMER2_PRESCALER,
        (dimmer_config.bits.leading_edge ? 'L' : 'T')
    );
    Serial.printf_P(PSTR("Ticks=%.2f,Lvls=" _STRINGIFY(DIMMER_MAX_LEVEL) ",P="), Dimmer::Timer<1>::ticksPerMicrosecond);
    for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size; i++) {
        Serial.print((int)Dimmer::Channel::pins[i]);
        Serial.print(',');
    }
    Serial.printf_P(PSTR("Range=%d-%d\n"), dimmer_config.range_begin, dimmer_config.range_end);
    Serial.flush();

    rem();
    Serial.print(F("values="));
    Serial.printf_P(PSTR("Restore=%u,ACFrq=%.3f,vref11=%.3f"), dimmer_config.bits.restore_level, dimmer._get_frequency(), (float)dimmer_config.internal_vref11);
    Serial.print(',');
#if HAVE_NTC
    Serial.printf_P(PSTR("NTC=%.2f/%+u,"), get_ntc_temperature(), dimmer_config.ntc_temp_offset);
#endif
#if HAVE_READ_INT_TEMP
    Serial.printf_P(PSTR("Int.Temp=%.2f/%+u,"), get_internal_temperature(), dimmer_config.int_temp_offset);
#endif
    Serial.printf_P(PSTR("max.tmp=%u,metrics=%u,"), dimmer_config.max_temp, REPORT_METRICS_INTERVAL(dimmer_config.report_metrics_interval));
#if HAVE_READ_VCC
    Serial.printf_P(PSTR("VCC=%.3f,"), read_vcc() / 1000.0);
#endif
    Serial.printf_P(PSTR("Min.on=%u,Min.off=%u,ZC.delay=%u,"),
        dimmer_config.minimum_on_time_ticks,
        dimmer_config.minimum_off_time_ticks,
        dimmer_config.zero_crossing_delay_ticks
    );
    Serial.flush();
    Serial.printf_P(PSTR("Sw.On=%u/%u\n"),
        dimmer_config.switch_on_minimum_ticks,
        dimmer_config.switch_on_count
    );
    Serial.flush();
}

dimmer_scheduled_calls_t dimmer_scheduled_calls;
unsigned long metrics_next_event;

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
    read_config();

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

unsigned long next_temp_check;

#if HAVE_PRINT_METRICS

unsigned long print_metrics_timeout;
uint16_t print_metrics_interval;

#endif

#if HAVE_FADE_COMPLETION_EVENT

unsigned long next_fading_event_check;

void Dimmer::DimmerBase::send_fading_completion_events() {

    FadingCompletionEvent_t buffer[Dimmer::Channel::size];
    FadingCompletionEvent_t *ptr = buffer;

    cli();
    for(Channel::type i = 0; i < Dimmer::Channel::size; i++) {
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
        if (abs(level - poti_level) >= max(1, (Dimmer::Level::max / 100))) { // 1% steps
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
        Serial.print(F("+REM="));
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
        Serial.printf_P(PSTR("hw=%u,diff=%d,"), dimmer.halfwave_ticks, (int)dimmer.zc_diff_ticks);
        Serial.printf_P(PSTR("frq=%.3f,mode=%c,lvl="), dimmer._get_frequency(), (dimmer_config.bits.leading_edge) ? 'L' : 'T');
        for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size; i++) {
            Serial.printf_P(PSTR("%d,"), register_mem.data.level[i]);
        }
        Serial.printf_P(PSTR("hf=%u,ticks="), (unsigned)dimmer._get_ticks_per_halfwave());
        for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size; i++) {
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

    if (dimmer_scheduled_calls.write_eeprom && millis() >= eeprom_write_timer) {
        _write_config();
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
            write_config();
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
