/**
 * Author: sascha_lammers@gmx.de
 */

#include <avr/wdt.h>
#include "i2c_slave.h"
#include "helpers.h"

register_mem_union_t register_mem;

#if DIMMER_USE_FADING

void fade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time) {
    _D(5, debug_printf_P(PSTR("fade %d: %d to %d, time %f\n"), channel, from, to, time));
    if (channel == -1) {
        for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
            fade(i, from, to, time);
        }
    } else {
        dimmer_set_fade(channel, from, to, time);
    }
}

#endif

void set_level(dimmer_channel_id_t channel, dimmer_level_t level) {
    _D(5, debug_printf_P(PSTR("set level %d: %d\n"), channel, level));
    if (channel == -1) {
        for(dimmer_channel_id_t i = 0; i < DIMMER_CHANNELS; i++) {
            dimmer_set_level(i, level);
        }
    } else {
        dimmer_set_level(channel, level);
    }
}

#if DEBUG
void dump_macros() {
#if 0
    char str[100];

    #define DUMP_MACRO(name) { memset(str, 32, sizeof(str)); strcpy_P(str, ({static const char __c[] PROGMEM = {#name}; &__c[0];}))[strlen(str)] = 32; str[35] = 0; Serial.printf("#define %s ", str); Serial.printf("0x%02x\n", name); }

    DUMP_MACRO(DIMMER_REGISTER_FROM_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CHANNEL);
    DUMP_MACRO(DIMMER_REGISTER_TO_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_TIME);
    DUMP_MACRO(DIMMER_REGISTER_COMMAND);
    DUMP_MACRO(DIMMER_REGISTER_READ_LENGTH);
    DUMP_MACRO(DIMMER_REGISTER_COMMAND_STATUS);
    DUMP_MACRO(DIMMER_REGISTER_CH0_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CH1_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CH2_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CH3_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CH4_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CH5_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CH6_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_CH7_LEVEL);
    DUMP_MACRO(DIMMER_REGISTER_TEMP);
    DUMP_MACRO(DIMMER_REGISTER_VCC);
    DUMP_MACRO(DIMMER_REGISTER_OPTIONS);
    DUMP_MACRO(DIMMER_REGISTER_MAX_TEMP);
    DUMP_MACRO(DIMMER_REGISTER_FADE_IN_TIME);
    DUMP_MACRO(DIMMER_REGISTER_TEMP_CHECK_INT);
    DUMP_MACRO(DIMMER_REGISTER_LC_FACTOR);
    DUMP_MACRO(DIMMER_REGISTER_ZC_DELAY_TICKS);
    DUMP_MACRO(DIMMER_REGISTER_MIN_ON_TIME_TICKS);
    DUMP_MACRO(DIMMER_REGISTER_ADJ_HALFWAVE_TICKS);
    DUMP_MACRO(DIMMER_REGISTER_ADDRESS);
    DUMP_MACRO(DIMMER_REGISTER_END_ADDR);
#endif
}
#endif

uint8_t validate_register_address() {
    uint8_t offset = register_mem.data.address - DIMMER_REGISTER_START_ADDR;
    if (offset < (uint8_t)sizeof(register_mem_t)) {
        return offset;
    }
    return DIMMER_REGISTER_ADDRESS;
}

void i2c_write_to_register(uint8_t data) {
    register_mem.raw[validate_register_address()] = data;
    _D(5, debug_printf_P(PSTR("I2C write @ %#02x = %u (%#02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR , data&0xff, data&0xff));
    register_mem.data.address++;
}

uint8_t i2c_read_from_register() {
    auto data = register_mem.raw[validate_register_address()];
    _D(5, debug_printf_P(PSTR("I2C read @ %#02x = %u (%#02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR, data&0xff, data&0xff));
    register_mem.data.address++;
    return data;
}

void i2c_slave_set_register_address(int length, uint8_t address, int8_t read_length) {
    register_mem.data.cmd.read_length += read_length;
    if (length <= 1) { // no more data available
        register_mem.data.address = address;
    } else {
        register_mem.data.address = DIMMER_REGISTER_ADDRESS;
    }
    _D(5, debug_printf_P(PSTR("I2C auto set register address %#02x, read length %d\n"), register_mem.data.address, read_length));
}

void _dimmer_i2c_on_receive(int length) {
    register_mem.data.address = DIMMER_REGISTER_ADDRESS;
    register_mem.data.cmd.status = DIMMER_COMMAND_STATUS_OK;
    register_mem.data.cmd.read_length = 0;
    while(length-- > 0) {
        auto addr = register_mem.data.address;
        _D(5, debug_printf_P(PSTR("I2C write, register address %#02x, data left %d\n"), addr, length));
        i2c_write_to_register(Wire.read());
        if (addr == DIMMER_REGISTER_ADDRESS) {
            register_mem.data.address--;
            _D(5, debug_printf_P(PSTR("I2C set register address = %#02x\n"), register_mem.data.address));
        }
        else if (addr == DIMMER_REGISTER_READ_LENGTH) {
            register_mem.data.address = DIMMER_REGISTER_ADDRESS;
        }
#if DIMMER_USE_LINEAR_CORRECTION
        else if (addr == DIMMER_REGISTER_LC_FACTOR + sizeof(register_mem.data.cfg.linear_correction_factor) - 1) {
            _D(5, debug_printf_P(PSTR("I2C set LCF = %.5f\n"), register_mem.data.cfg.linear_correction_factor));
            dimmer_set_lcf(register_mem.data.cfg.linear_correction_factor);
        }
#endif
        else if (addr == DIMMER_REGISTER_COMMAND) {
            _D(5, debug_printf_P(PSTR("I2C command = %#02x\n"), register_mem.data.cmd.command));
            switch(register_mem.data.cmd.command) {
                case DIMMER_COMMAND_READ_CHANNELS:
                    {
                        uint8_t numChannels = 8;
                        uint8_t start = 0;
                        if (length-- > 0) {
                            numChannels = (uint8_t)Wire.read();
                            start = numChannels & 0x0f;
                            numChannels >>= 4;
                        }
                        _D(5, debug_printf_P(PSTR("I2C read channels %u:%u\n"), start, numChannels));
                        i2c_slave_set_register_address(0, DIMMER_REGISTER_CH0_LEVEL + (start * sizeof(register_mem.data.level[0])), numChannels * sizeof(register_mem.data.level[0]));
                    }
                    break;
                case DIMMER_COMMAND_SET_LEVEL:
                    _D(5, debug_printf_P(PSTR("I2C set level=%d, channel=%d\n"), register_mem.data.to_level, register_mem.data.channel));
                    set_level(register_mem.data.channel, register_mem.data.to_level);
                    break;
#if DIMMER_USE_FADING
                case DIMMER_COMMAND_FADE:
                    _D(5, debug_printf_P(PSTR("I2C fade from=%d, to=%d, channel=%d, fade_time=%f\n"), register_mem.data.from_level, register_mem.data.to_level, register_mem.data.channel, register_mem.data.time));
                    fade(register_mem.data.channel, register_mem.data.from_level, register_mem.data.to_level, register_mem.data.time); // 0-655 seconds in 10ms steps
                    break;
#endif
                case DIMMER_COMMAND_READ_NTC:
                    register_mem.data.temp = NAN;
#if HAVE_NTC
                    dimmer_schedule_call(READ_NTC_TEMP);
#endif
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
                case DIMMER_COMMAND_READ_INT_TEMP:
                    register_mem.data.temp = NAN;
#if HAVE_READ_INT_TEMP
                    dimmer_schedule_call(READ_INT_TEMP);
#endif
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
                case DIMMER_COMMAND_READ_VCC:
                    register_mem.data.vcc = 0;
#if HAVE_READ_VCC
                    dimmer_schedule_call(READ_VCC);
#endif
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_VCC, sizeof(register_mem.data.vcc));
                    break;
                case DIMMER_COMMAND_READ_AC_FREQUENCY:
#if FREQUENCY_TEST_DURATION
                    register_mem.data.temp = dimmer_get_frequency();
#else
                    register_mem.data.temp = NAN;
#endif
                    _D(5, debug_printf_P(PSTR("I2C get AC frequency=%.3f\n"), register_mem.data.temp));
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
#if USE_EEPROM
                case DIMMER_COMMAND_WRITE_EEPROM:
                    write_config();
                    break;
#endif
                case DIMMER_COMMAND_RESTORE_FS:
                    reset_config();
#if USE_EEPROM
                    init_eeprom();
                    _write_config();
#endif
                    break;
                case DIMMER_COMMAND_READ_TIMINGS:
                    if (length-- > 0) {
                        uint8_t timing = (uint8_t)Wire.read();
                        switch(timing) {
                            case DIMMER_TIMINGS_TMR1_TICKS_PER_US:
                                register_mem.data.temp = DIMMER_TMR1_TICKS_PER_US;
                                break;
                            case DIMMER_TIMINGS_TMR2_TICKS_PER_US:
                                register_mem.data.temp = DIMMER_TMR2_TICKS_PER_US;
                                break;
                            case DIMMER_TIMINGS_ZC_DELAY_IN_US:
                                register_mem.data.temp = DIMMER_TICKS_TO_US(register_mem.data.cfg.zero_crossing_delay_ticks, DIMMER_TMR2_TICKS_PER_US);
                                break;
                            case DIMMER_TIMINGS_MIN_ON_TIME_IN_US:
                                register_mem.data.temp = DIMMER_TICKS_TO_US(register_mem.data.cfg.minimum_on_time_ticks, DIMMER_TMR1_TICKS_PER_US);
                                break;
                            case DIMMER_TIMINGS_ADJ_HW_TIME_IN_US:
                                register_mem.data.temp = DIMMER_TICKS_TO_US(register_mem.data.cfg.adjust_halfwave_time_ticks, DIMMER_TMR1_TICKS_PER_US);
                                break;
                            default:
                                timing = 0;
                                break;
                        }
                        if (timing) {
                            i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                            _D(5, debug_printf_P(PSTR("I2C get timing %#02x=%s\n"), timing, String(register_mem.data.temp, 5).c_str()));
                        }
                    }
                    break;

#if HIDE_DIMMER_INFO == 0
                case DIMMER_COMMAND_PRINT_INFO:
                    display_dimmer_info();
                    break;
#endif

#if HAVE_PRINT_METRICS
                case DIMMER_COMMAND_PRINT_METRICS:
                    print_metrics_timeout = 0;
                    if (length-- > 0 && Wire.read() == 0) {

                        dimmer_remove_scheduled_call(PRINT_METRICS);
                    }
                    else {
                        dimmer_schedule_call(PRINT_METRICS);
                    }
                    break;
#endif

                case DIMMER_COMMAND_RESET:
                    wdt_reset();
                    break;

#if ZC_MAX_TIMINGS
                case DIMMER_COMMAND_ZC_TIMINGS_OUTPUT:
                    zc_timings_output = (length-- > 0 && Wire.read() != 0);
                    zc_timings_counter = 0;
                    break;
#endif

#if 1
                // undocumented, for calibration and testing
                case 0x80:
                    register_mem.data.cfg.internal_1_1v_ref += 0.001f;
                    Serial_printf_P(PSTR("+REM=ref11=%.4f\n"), register_mem.data.cfg.internal_1_1v_ref);
                    break;
                case 0x81:
                    register_mem.data.cfg.internal_1_1v_ref -= 0.001f;
                    Serial_printf_P(PSTR("+REM=ref11=%.4f\n"), register_mem.data.cfg.internal_1_1v_ref);
                    break;
                case 0x82:
                    register_mem.data.cfg.zero_crossing_delay_ticks++;
                    Serial_printf_P(PSTR("+REM=zcdelay=%u\n"), register_mem.data.cfg.zero_crossing_delay_ticks);
                    break;
                case 0x83:
                    register_mem.data.cfg.zero_crossing_delay_ticks--;
                    Serial_printf_P(PSTR("+REM=zcdelay=%u\n"), register_mem.data.cfg.zero_crossing_delay_ticks);
                    break;
                case 0x84:
                    register_mem.data.cfg.int_temp_offset++;
                    Serial_printf_P(PSTR("+REM=tmpofs=%d\n"), register_mem.data.cfg.int_temp_offset);
                    break;
                case 0x85:
                    register_mem.data.cfg.int_temp_offset--;
                    Serial_printf_P(PSTR("+REM=tmpofs=%d\n"), register_mem.data.cfg.int_temp_offset);
                    break;
                case 0x86:
                    register_mem.data.cfg.ntc_temp_offset++;
                    Serial_printf_P(PSTR("+REM=ntctmpofs=%d\n"), register_mem.data.cfg.ntc_temp_offset);
                    break;
                case 0x87:
                    register_mem.data.cfg.ntc_temp_offset--;
                    Serial_printf_P(PSTR("+REM=ntctmpofs=%d\n"), register_mem.data.cfg.ntc_temp_offset);
                    break;
                case 0x88:
                    register_mem.data.cfg.linear_correction_factor += 0.001f;
                    Serial_printf_P(PSTR("+REM=LCF=%.4f\n"), register_mem.data.cfg.linear_correction_factor);
                    break;
                case 0x89:
                    register_mem.data.cfg.linear_correction_factor -= 0.001f;
                    Serial_printf_P(PSTR("+REM=LCF=%.4f\n"), register_mem.data.cfg.linear_correction_factor);
                    break;
                case 0x90: { // toggle pins on/off
                        if (length-- > 1) {
                            dimmer_timer_remove();

                            auto port_ptr = unique_ptr<volatile uint8_t *>(new volatile uint8_t *[length]);
                            auto pins_ptr = unique_ptr<uint8_t>(new uint8_t[length]);
                            auto mask_ptr = unique_ptr<uint8_t>(new uint8_t[length]);

                            auto port = port_ptr.get();
                            auto pins = pins_ptr.get();
                            auto mask = mask_ptr.get();
                            auto time = (unsigned long)((uint8_t)Wire.read());
                            if (time > 100) {
                                time -= 100;
                                time *= 10;
                            }
                            uint8_t count = 0;
                            Serial_printf_P(PSTR("+REM=time=%lu,pins="), time);
                            time *= 1000UL;
                            while(length-- > 0) {
                                auto pin = (uint8_t)Wire.read();
                                pinMode(pin, OUTPUT);
                                pins[count] = pin;
                                port[count] = portOutputRegister(digitalPinToPort(pin));
                                mask[count] = digitalPinToBitMask(pin);;
                                Serial.print((unsigned)pin);
                                if (length > 0) {
                                    Serial.print(',');
                                }
                                count++;
                            }
                            Serial.println();
                            auto timeout = millis() + 30e3;

                            while(millis() < timeout) {
                                for(uint8_t state = 0; state < 2; state++) {
                                    auto end = micros() + time;
                                    for(uint8_t i = 0; i < count; i++) {
                                        if (state) {
                                            *port[i] |= mask[i];
                                        }
                                        else {
                                            *port[i] &= ~mask[i];
                                        }
                                    }
                                    Serial.print('\b');
                                    Serial.print(state ? '+' : '-');
                                    while(micros() < end) {
                                    }
                                }
                            }
                            Serial.println(F("+REM=done"));

                            for(uint8_t i = 0; i < count; i++) {
                                pinMode(pins[i], INPUT);
                                *port[i] &= ~mask[i];
                            }
                            // delete port;
                            // delete pins;
                            // delete mask;

                            dimmer_timer_setup();
                        }
                    }
                    break;
                case 0x91: { // print command to restore parameters
                        Serial_printf_P(PSTR("+REM=i2ct=%02x%02x"), DIMMER_I2C_ADDRESS, DIMMER_REGISTER_OPTIONS);
                        for(uint8_t i = DIMMER_REGISTER_OPTIONS; i < DIMMER_REGISTER_VERSION; i++) {
                            Serial_printf_P(PSTR("%02x"), register_mem.raw[i - DIMMER_REGISTER_START_ADDR]);
                        }
                        Serial.println();
                    } break;
#endif

#if USE_TEMPERATURE_CHECK
                case DIMMER_COMMAND_FORCE_TEMP_CHECK:
                    next_temp_check = 0;
                    break;
#endif

#if DEBUG
                case DIMMER_COMMAND_DUMP_MEM:
                    for(uint8_t addr = DIMMER_REGISTER_START_ADDR; addr < DIMMER_REGISTER_END_ADDR; addr++) {
                        auto ptr = register_mem.raw + addr - DIMMER_REGISTER_START_ADDR;
                        uint8_t data = *ptr;
                        Serial_printf_P(PSTR("[%02x]: %u (%#02x)\n"), addr, data, data);
                    }
                    break;
                case DIMMER_COMMAND_DUMP_MACROS:
                    dump_macros();
                    break;
#endif
            }
        }
    }
}


#define DIMMER_REGISTER_MEM_END_PTR         &register_mem.raw[sizeof(register_mem_t)]

void _dimmer_i2c_on_request() {
    _D(9, debug_printf_P(PSTR("I2C slave onRequest: %#02x, length %u\n"), register_mem.data.address, register_mem.data.cmd.read_length));
    auto ptr = &register_mem.raw[register_mem.data.address - DIMMER_REGISTER_START_ADDR];
    while(register_mem.data.cmd.read_length-- && ptr < DIMMER_REGISTER_MEM_END_PTR) {
        Wire.write(*ptr++);
    }
    register_mem.data.cmd.read_length = 0;
}

void dimmer_i2c_slave_setup() {

    _D(5, debug_printf_P(PSTR("I2C slave address: %#02x\n"), DIMMER_I2C_ADDRESS));

    memset(&register_mem, 0, sizeof(register_mem));
    register_mem.data.from_level = -1;

    Wire.begin(DIMMER_I2C_ADDRESS);
    Wire.onReceive(_dimmer_i2c_on_receive);
    Wire.onRequest(_dimmer_i2c_on_request);

#if DEBUG
    dump_macros();
#endif

}
