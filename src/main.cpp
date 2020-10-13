/**
 * Author: sascha_lammers@gmx.de
 */

// 1-8 Channel Dimmer with I2C interface

#include <Arduino.h>
#include "i2c_slave.h"
#include "helpers.h"
#include "dimmer.h"
#include <EEPROM.h>
#include <crc16.h>

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

config_t config;
uint16_t eeprom_position = 0;
unsigned long eeprom_write_timer = -EEPROM_REPEATED_WRITE_DELAY;

void reset_config()
{
    dimmer_init_register_mem();
    dimmer_config.max_temp = 75;
    dimmer_config.bits.restore_level = true;
    dimmer_config.bits.report_metrics = true;
    dimmer_config.fade_in_time = 7.5;
    dimmer_config.temp_check_interval = 2;
    dimmer_config.zero_crossing_delay_ticks = Dimmer::Timer<2>::microsToTicks(DIMMER_ZC_DELAY_US);
    dimmer_config.minimum_on_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_ON_TIME_US);
    dimmer_config.minimum_off_time_ticks = Dimmer::Timer<1>::microsToTicks(DIMMER_MIN_OFF_TIME_US);
    dimmer_config.internal_1_1v_ref = Dimmer::kVRef;
    dimmer_config.report_metrics_max_interval = 5;
#ifdef INTERNAL_TEMP_OFS
    dimmer_config.int_temp_offset = INTERNAL_TEMP_OFS;
#endif
    dimmer_config.range_begin = Dimmer::Level::min;
    dimmer_config.range_end = Dimmer::Level::max;

    dimmer_copy_config_to(config.cfg);
}

unsigned long get_eeprom_num_writes(unsigned long cycle, uint16_t position)
{
    return ((EEPROM.length() / sizeof(config_t)) * (cycle - 1)) + (position / sizeof(config_t));
}

// initialize EEPROM and wear leveling
void init_eeprom()
{
    config = {};
    reset_config();

    EEPROM.begin();
    config.eeprom_cycle = 1;
    eeprom_position = 0;
    _D(5, debug_printf("init eeprom cycle=%ld, position %d\n", (long)config.eeprom_cycle, (int)eeprom_position));

    for(uint16_t i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
    }
    config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg));
    EEPROM.put(eeprom_position, config);
    EEPROM.end();
}

void read_config()
{
    uint16_t pos = 0;
    uint32_t cycle, max_cycle = 0;

    eeprom_position = 0;

    // find last configuration
    // the first byte is the cycle, which increases by one once the last position has been written
    while((pos + sizeof(config_t)) < EEPROM.length()) {
        EEPROM.get(pos, cycle);
        _D(5, debug_printf("eeprom cycle %ld position %d id\n", cycle, pos));
        if (cycle >= max_cycle) {
            eeprom_position = pos; // last position with highest cycle number is the config written last
            max_cycle = cycle;
        }
        pos += sizeof(config_t);
    }
    EEPROM.get(eeprom_position, config);
    EEPROM.end();

    auto crc = crc16_update(&config.cfg, sizeof(config.cfg));

    constexpr uint16_t crcEmptyConfig = constexpr_crc16_update(REP_NUL_256X, sizeof(config.cfg));

    if (config.crc16 != crc || config.crc16 == crcEmptyConfig) {
        init_eeprom();
        _D(5, debug_print_memory(&config.cfg, sizeof(config.cfg)));
    }
    else {
        dimmer_copy_config_from(config.cfg);
        _D(5, debug_print_memory(&config.cfg, sizeof(config.cfg)));
        Serial.printf_P(PSTR("+REM=EEPROMR,c=%lu,p=%u,n=%lu,crc=%04x=%04x\n"), (unsigned long)max_cycle, eeprom_position, get_eeprom_num_writes(max_cycle, eeprom_position), config.crc16, crc);
    }

}

void _write_config(bool force, bool update_regmem_cfg)
{
    config_t temp_config;
    dimmer_eeprom_written_t event;

    if (update_regmem_cfg) {
        dimmer_copy_config_to(config.cfg);
    }

    memcpy(&config.level, &register_mem.data.level, sizeof(config.level));
    config.crc16 = crc16_update(&config.cfg, sizeof(config.cfg));

    EEPROM.begin();
    EEPROM.get(eeprom_position, temp_config);

    _D(5, debug_printf("_write_config force=%u reg_mem=%u memcmp=%d\n", force, update_regmem_cfg, memcmp(&config, &temp_config, sizeof(config))));

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
    EEPROM.end();
    dimmer_scheduled_calls.write_eeprom = false;

    event.write_cycle = config.eeprom_cycle;
    event.write_position = eeprom_position;

    _D(5, debug_printf("eeprom written event: cycle %lu, pos %u, written %u\n", (unsigned long)event.write_cycle, event.write_position, event.bytes_written));
    Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
    Wire.write(DIMMER_EEPROM_WRITTEN);
    Wire.write(reinterpret_cast<const uint8_t *>(&event), sizeof(event));
    Wire.endTransmission();

    Serial.printf_P(PSTR("+REM=EEPROMW,c=%lu,p=%u,n=%lu,w=%u,crc=%04x\n"), (unsigned long)event.write_cycle, eeprom_position, get_eeprom_num_writes(event.write_cycle, eeprom_position), event.bytes_written, config.crc16);
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

#if HAVE_READ_INT_TEMP

bool is_Atmega328PB;

// https://playground.arduino.cc/Main/InternalTemperatureSensor/
float get_internal_temperature()
{
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);
    uint16_t sum = 0;
    for (uint8_t i = 0; i < 25; i++) {
        delay(1);
        if (i == 15) { // start after 15ms
            sum = 0;
        }
        ADCSRA |= _BV(ADSC);
        while (bit_is_set(ADCSRA, ADSC)) ;
        sum += ADCW;
    }
    return (((sum / 10.0) - (is_Atmega328PB ? 247.0f : 324.31f)) / 1.22f) + (float)(dimmer_config.int_temp_offset / 4.0f);
}

#endif

#if HAVE_READ_VCC

#if HAVE_EXT_VCC

uint16_t read_vcc()
{
    analogReference(INTERNAL);
    analogRead(VCC_PIN);
    uint32_t sum = 0;
    for(uint8_t i = 0; i < 25; i++) {
        delay(1);
        if (i == 15) { // start after 15ms
            sum = 0;
        }
        sum += analogRead(VCC_PIN);
    }

    // Vout = (Vs * R2) / (R1 + R2)
    // ((ADCValue / 1024) * (Vref * 1000)) / N = (Vs * R2) / (R1 + R2)
    // Vs=((125*ADCValue*R2+125*ADCValue*R1)*Vref)/(128*N*R2)

    // R1=12K
    // R2=3K
    // N=10
    // ((ADCValue / 1024) * (Vref * 1000)) / N = (Vs * 3000) / (12000 + 3000)
    // Vs=(625*ADCValue*Vref)/(128*N)

    return (625UL * sum * dimmer_config.internal_1_1v_ref) / 1280U;
}

#else
#define read_vcc()      read_vcc_int()

#endif

// read VCC in mV
uint16_t read_vcc_int()
{
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); // analogReference(DEFAULT) = AVCC with external capacitor at AREF pin
    uint16_t sum = 0;
    for (uint8_t i = 0; i < 20; i++) {
        delay(1);
        if (i == 10) { // start after 10ms
            sum = 0;
        }
        ADCSRA |= _BV(ADSC);
        while (bit_is_set(ADCSRA, ADSC));
        sum += ADCW;
    }
    return (10UL * 1000UL * 1024UL) * dimmer_config.internal_1_1v_ref / (float)sum;
}

#endif


#if HAVE_NTC

uint16_t read_ntc_value(uint8_t num)
{
    uint32_t value = analogRead(NTC_PIN);
    for(uint8_t i = 1; i < num; i++) {
        delay(1);
        value += analogRead(NTC_PIN);
    }
    return value / num;
}

float convert_to_celsius(uint16_t value)
{
    float steinhart;
    steinhart = 1023 / (float)value - 1;
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
    return convert_to_celsius(read_ntc_value(5)) + (float)(dimmer_config.ntc_temp_offset / 4.0f);
#endif
}

#endif

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
#if USE_TEMPERATURE_CHECK
    Serial.print(F("Temp.Chk,"));
#endif
#if HAVE_READ_VCC
    Serial.print(F("VCC,"));
#endif
    Serial.printf_P(PSTR("ACFrq=%u,"), DIMMER_AC_FREQUENCY);
#if SERIAL_I2C_BRDIGE
    Serial.print(F("Pr=UART,"));
#else
    Serial.print(F("Pr=I2C,"));
#endif
#if HAVE_FADE_COMPLETION_EVENT
    Serial.print(F("CE=1,"));
#endif
    Serial.printf_P(PSTR("Addr=%02x,Pre=%u/%u,"),
        DIMMER_I2C_ADDRESS,
        DIMMER_TIMER1_PRESCALER, DIMMER_TIMER2_PRESCALER
    );
    Serial.printf_P(PSTR("Ticks=%.2f/%.2f"), Dimmer::Timer<1>::ticksPerMicrosecond, Dimmer::Timer<2>::ticksPerMicrosecond);
    Serial.printf_P(PSTR(",Lvls=%u,P="), DIMMER_MAX_LEVEL);
    for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size; i++) {
        Serial.print((int)Dimmer::Channel::pins[i]);
        Serial.print(',');
    }
    Serial.printf_P(PSTR("Range=%d-%d\n"), dimmer_config.range_begin, dimmer_config.range_end);
    Serial.flush();

    rem();
    Serial.print(F("values="));
    Serial.printf_P(PSTR("Restore=%u,ACFrq=%.3f,vref11=%.3f"), dimmer_config.bits.restore_level, dimmer._get_frequency(), dimmer_config.internal_1_1v_ref);
    Serial.print(',');
#if HAVE_NTC
    Serial.printf_P(PSTR("NTC=%.2f"), get_ntc_temperature());
    #if USE_TEMPERATURE_CHECK
        Serial.printf_P(PSTR("/%+u"), dimmer_config.ntc_temp_offset);
    #endif
    Serial.print(',');
#endif
#if HAVE_READ_INT_TEMP
    Serial.printf_P(PSTR("Int.Temp=%.2f"), get_internal_temperature());
    #if USE_TEMPERATURE_CHECK
        Serial.printf_P(PSTR("/%+u"), dimmer_config.int_temp_offset);
    #endif
    Serial.print(',');
#endif
#if USE_TEMPERATURE_CHECK
    Serial.printf_P(PSTR("max.tmp=%u/%us,metrics=%u,"), dimmer_config.max_temp, dimmer_config.temp_check_interval, dimmer_config.report_metrics_max_interval);
#endif
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

unsigned long frequency_wait_timeout;

dimmer_scheduled_calls_t dimmer_scheduled_calls = {};
unsigned long metrics_next_event = 0;

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
    dimmer.begin();

#if HAVE_NTC
    pinMode(NTC_PIN, INPUT);
#endif

    restore_level();

#if HIDE_DIMMER_INFO == 0
    // run main loop till the frequency is available
    frequency_wait_timeout = millis() + min(550, FREQUENCY_TEST_DURATION);
    dimmer_scheduled_calls.print_info = true;

#endif
    _D(5, debug_printf("exiting setup\n"));
}

#if USE_TEMPERATURE_CHECK

unsigned long next_temp_check = 0;

#endif

#if HAVE_PRINT_METRICS

unsigned long print_metrics_timeout;

#endif

#if ZC_MAX_TIMINGS

unsigned long print_zc_timings = 0;

#endif

#if HAVE_FADE_COMPLETION_EVENT

unsigned long next_fading_event_check = 0;

void Dimmer::DimmerBase::send_fading_completion_events() {

    FadingCompletionEvent_t buffer[Dimmer::Channel::size];
    FadingCompletionEvent_t *ptr = buffer;

    for(Channel::type i = 0; i < Dimmer::Channel::size; i++) {
        cli(); // dimmer.fading_completed is modified inside an interrupt and copying needs to be an atomic operation
        if (dimmer.fading_completed[i] != Dimmer::Level::invalid) {
            auto level = dimmer.fading_completed[i];
            dimmer.fading_completed[i] = Dimmer::Level::invalid;
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
        _D(5, debug_printf("sending fading completion event for %u channel(s)\n", ptr - buffer));

        Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
        Wire.write(DIMMER_FADING_COMPLETE);
        Wire.write(reinterpret_cast<const uint8_t *>(buffer), (reinterpret_cast<const uint8_t *>(ptr) - reinterpret_cast<const uint8_t *>(buffer)));
        Wire.endTransmission();
    }

}

#endif

void loop()
{
#if HIDE_DIMMER_INFO == 0
    if (dimmer_scheduled_calls.print_info && millis() >= frequency_wait_timeout) {
        dimmer_scheduled_calls.print_info = false;
        display_dimmer_info();
        register_mem.data.errors = {};
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
    if (dimmer_scheduled_calls.print_metrics && millis() >= print_metrics_timeout) {
        print_metrics_timeout = millis() + PRINT_METRICS_REPEAT;
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
        #if FREQUENCY_TEST_DURATION
            Serial.printf_P(PSTR("frq=%.3f,"), dimmer._get_frequency());
        #endif
        Serial.print(F("lvl="));
        for(Dimmer::Channel::type i = 0; i < Dimmer::Channel::size; i++) {
            Serial.print(register_mem.data.level[i]);
        }
        Serial.printf_P(PSTR(",hf=%u,ticks="), Dimmer::kTicksPerHalfWave);
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

#if HAVE_FADE_COMPLETION_EVENT
    if (millis() >= next_fading_event_check)  {
        dimmer.send_fading_completion_events();
        next_fading_event_check = millis() + 100;
    }
#endif

    if (dimmer_scheduled_calls.write_eeprom && millis() >= eeprom_write_timer) {
        _write_config();
    }

#if ZC_MAX_TIMINGS
    if (zc_timings_output && millis() >= print_zc_timings) {
        auto tmp = zc_timings[0]; // copy first timing before resetting counter
        auto counter = zc_timings_counter;
        zc_timings_counter = 0;
        print_zc_timings = millis() + 1000;
        if (counter) {
            Serial.printf_P(PSTR("+REM=ZC,%lx "), tmp);
            for(uint8_t i = 1; i < counter; i++) {
                Serial_printf("%lx ", zc_timings[i] - tmp); // use relative time to reduce output
                tmp = zc_timings[i];
            }
            Serial.println();
        }
    }
#endif

#if USE_TEMPERATURE_CHECK
    if (millis() >= next_temp_check) {

        int current_temp;
#if HAVE_NTC
        float ntc_temp = get_ntc_temperature();
        current_temp = ntc_temp;
#endif
#if HAVE_READ_INT_TEMP
        float int_temp = get_internal_temperature();
        current_temp = max(current_temp, (int)int_temp);
#endif
        next_temp_check = millis() + (dimmer_config.temp_check_interval * 1000UL);
        if (dimmer_config.max_temp && current_temp > (int)dimmer_config.max_temp) {
            dimmer.fade_from_to(Dimmer::Channel::any, Dimmer::Level::current, Dimmer::Level::off, 10);
            dimmer_config.bits.temperature_alert = 1;
            write_config();
            if (dimmer_config.bits.report_metrics) {
                Wire.beginTransmission(DIMMER_I2C_ADDRESS + 1);
                Wire.write(DIMMER_TEMPERATURE_ALERT);
                Wire.write((uint8_t)current_temp);
                Wire.write(dimmer_config.max_temp);
                Wire.endTransmission();
            }
        }

        if (dimmer_config.bits.report_metrics && millis() >= metrics_next_event) {
            metrics_next_event = millis() + (dimmer_config.report_metrics_max_interval * 1000UL);
            dimmer_metrics_t event = {
                (uint8_t)current_temp,
#if HAVE_READ_VCC
                read_vcc(),
#else
                0,
#endif
#if FREQUENCY_TEST_DURATION
                dimmer._get_frequency(),
#else
                NAN,
#endif
#if HAVE_READ_INT_TEMP
                int_temp,
#else
                NAN,
#endif
#if HAVE_NTC
                ntc_temp
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

#endif
