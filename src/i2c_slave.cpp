/**
 * Author: sascha_lammers@gmx.de
 */

#include "i2c_slave.h"
#include "helpers.h"

register_mem_union_t register_mem;

#if DIMMER_USE_FADING

void fade(int8_t channel, int16_t from, int16_t to, float time) {
    _D(5, SerialEx.printf_P(PSTR("fade %d: %d to %d, time %f\n"), channel, from, to, time));
    if (channel == -1) {
        for(int8_t i = 0; i < DIMMER_CHANNELS; i++) {
            fade(i, from, to, time);
        }
    } else {
        dimmer_set_fade(channel, from, to, time);
    }
}

#endif

void set_level(int8_t channel, int16_t level) {
    _D(5, SerialEx.printf_P(PSTR("set level %d: %d\n"), channel, level));
    if (channel == -1) {
        for(int8_t i = 0; i < DIMMER_CHANNELS; i++) {
            dimmer_set_level(i, level);
        }
    } else {
        dimmer_set_level(channel, level);
    }
}

#if DEBUG
void dump_macros() {
    char str[100];

    #define DUMP_MACRO(name) { memset(str, 32, sizeof(str)); strcpy_P(str, ({static const char __c[] PROGMEM = {#name}; &__c[0];}))[strlen(str)] = 32; str[35] = 0; SerialEx.printf("#define %s ", str); SerialEx.printf("0x%02x\n", name); }

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
    DUMP_MACRO(DIMMER_REGISTER_ADDRESS);
    DUMP_MACRO(DIMMER_REGISTER_END_ADDR);
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
    _D(5, SerialEx.printf_P(PSTR("I2C write @ %#02x = %u (%#02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR , data&0xff, data&0xff));
    register_mem.data.address++;
}

uint8_t i2c_read_from_register() {
    auto data = register_mem.raw[validate_register_address()];
    _D(5, SerialEx.printf_P(PSTR("I2C read @ %#02x = %u (%#02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR, data&0xff, data&0xff));
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
    _D(5, SerialEx.printf_P(PSTR("I2C auto set register address %#02x, read length %d\n"), register_mem.data.address, read_length));
}

void _dimmer_i2c_on_receive(int length) {
    register_mem.data.address = DIMMER_REGISTER_ADDRESS;
    register_mem.data.cmd.status = DIMMER_COMMAND_STATUS_OK;
    register_mem.data.cmd.read_length = 0;
    while(length-- > 0) {
        auto addr = register_mem.data.address;
        _D(5, SerialEx.printf_P(PSTR("I2C write, register address %#02x, data left %d\n"), addr, length));
        i2c_write_to_register(Wire.read());
        if (addr == DIMMER_REGISTER_ADDRESS) {
            register_mem.data.address--;
            _D(5, SerialEx.printf_P(PSTR("I2C set register address = %#02x\n"), register_mem.data.address));
        } 
        else if (addr == DIMMER_REGISTER_READ_LENGTH) {
            register_mem.data.address = DIMMER_REGISTER_ADDRESS;
        } 
#if DIMMER_USE_LINEAR_CORRECTION
        else if (addr == DIMMER_REGISTER_LC_FACTOR + sizeof(register_mem.data.cfg.linear_correction_factor) - 1) {
            _D(5, SerialEx.printf_P(PSTR("I2C set LCF = %s\n"), float_to_str(register_mem.data.cfg.linear_correction_factor)));
            dimmer_set_lcf(register_mem.data.cfg.linear_correction_factor);
        }
#endif
        else if (addr == DIMMER_REGISTER_COMMAND) {
            _D(5, SerialEx.printf_P(PSTR("I2C command = %#02x\n"), register_mem.data.cmd.command));
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
                        _D(5, SerialEx.printf_P(PSTR("I2C read channels %u:%u\n"), start, numChannels));
                        i2c_slave_set_register_address(0, DIMMER_REGISTER_CH0_LEVEL + (start * sizeof(register_mem.data.level[0])), numChannels * sizeof(register_mem.data.level[0]));
                    }
                    break;
                case DIMMER_COMMAND_SET_LEVEL:
                    _D(5, SerialEx.printf_P(PSTR("I2C set level=%d, channel=%d\n"), register_mem.data.to_level, register_mem.data.channel));
                    set_level(register_mem.data.channel, register_mem.data.to_level);
                    break;
#if DIMMER_USE_FADING
                case DIMMER_COMMAND_FADE:
                    _D(5, SerialEx.printf_P(PSTR("I2C fade from=%d, to=%d, channel=%d, fade_time=%f\n"), register_mem.data.from_level, register_mem.data.to_level, register_mem.data.channel, register_mem.data.time));
                    fade(register_mem.data.channel, register_mem.data.from_level, register_mem.data.to_level, register_mem.data.time); // 0-655 seconds in 10ms steps
                    break;
#endif
#if HAVE_NTC
                case DIMMER_COMMAND_READ_NTC:
                    register_mem.data.temp = convert_to_celsius(read_ntc_value());
                    _D(5, SerialEx.printf_P(PSTR("I2C read ntc=%s\n"), float_to_str(register_mem.data.temp)));
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
#endif
#if HAVE_READ_INT_TEMP
                case DIMMER_COMMAND_READ_INT_TEMP:
                    register_mem.data.temp = get_internal_temperature();
                    _D(5, SerialEx.printf_P(PSTR("I2C read int. temp=%s\n"), float_to_str(register_mem.data.temp)));
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
#endif
#if HAVE_READ_VCC
                case DIMMER_COMMAND_READ_VCC:
                    register_mem.data.vcc = read_vcc();
                    _D(5, SerialEx.printf_P(PSTR("I2C read vcc=%u\n"), register_mem.data.vcc));
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_VCC, sizeof(register_mem.data.vcc));
                    break;
#endif
#if USE_EEPROM
                case DIMMER_COMMAND_WRITE_EEPROM:
                    write_config();
                    break;
#endif                    
                case DIMMER_COMMAND_RESTORE_FS:
                    reset_config();
                    init_eeprom();
                    _write_config();
                    break;
#if DEBUG
                case DIMMER_COMMAND_DUMP_MEM:
                    for(uint8_t addr = DIMMER_REGISTER_START_ADDR; addr < DIMMER_REGISTER_END_ADDR; addr++) {
                        auto ptr = register_mem.raw + addr - DIMMER_REGISTER_START_ADDR;
                        uint8_t data = *ptr;
                        SerialEx.printf_P(PSTR("[%02x]: %u (%#02x)\n"), addr, data, data);
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
    _D(9, SerialEx.printf_P(PSTR("I2C slave onRequest: %#02x, length %u\n"), register_mem.data.address, register_mem.data.cmd.read_length));
    auto ptr = register_mem.raw + register_mem.data.address - DIMMER_REGISTER_START_ADDR;
    while(register_mem.data.cmd.read_length-- && ptr < DIMMER_REGISTER_MEM_END_PTR) {
        Wire.write(*ptr++);
    }
    register_mem.data.cmd.read_length = 0;
}

void dimmer_i2c_slave_setup() {

    _D(5, SerialEx.printf_P(PSTR("I2C slave address: %#02x\n"), DIMMER_I2C_ADDRESS));

    memset(&register_mem, 0, sizeof(register_mem));
    register_mem.data.from_level = -1;

    Wire.begin(DIMMER_I2C_ADDRESS);
    Wire.onReceive(_dimmer_i2c_on_receive);
    Wire.onRequest(_dimmer_i2c_on_request);

#if DEBUG
    dump_macros();
#endif    

}
