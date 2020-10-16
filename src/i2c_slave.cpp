/**
 * Author: sascha_lammers@gmx.de
 */

#include "i2c_slave.h"
#include "helpers.h"
#include "dimmer.h"

register_mem_union_t register_mem;
extern dimmer_scheduled_calls_t dimmer_scheduled_calls;

uint8_t validate_register_address()
{
    uint8_t offset = register_mem.data.address - DIMMER_REGISTER_START_ADDR;
    if (offset < (uint8_t)sizeof(register_mem_t)) {
        return offset;
    }
    return DIMMER_REGISTER_ADDRESS;
}

void i2c_write_to_register(uint8_t data)
{
    register_mem.raw[validate_register_address()] = data;
    _D(5, debug_printf("I2C write @ %#02x = %u (%#02x)\n", validate_register_address() + DIMMER_REGISTER_START_ADDR , data&0xff, data&0xff));
    register_mem.data.address++;
}

uint8_t i2c_read_from_register()
{
    auto data = register_mem.raw[validate_register_address()];
    _D(5, debug_printf("I2C read @ %#02x = %u (%#02x)\n", validate_register_address() + DIMMER_REGISTER_START_ADDR, data&0xff, data&0xff));
    register_mem.data.address++;
    return data;
}

void i2c_slave_set_register_address(int length, uint8_t address, int8_t read_length)
{
    register_mem.data.cmd.read_length += read_length;
    if (length <= 1) { // no more data available
        register_mem.data.address = address;
    } else {
        register_mem.data.address = DIMMER_REGISTER_ADDRESS;
    }
    _D(5, debug_printf("I2C auto set register address %#02x, read length %d\n", register_mem.data.address, read_length));
}

void _dimmer_i2c_on_receive(int length)
{
    register_mem.data.address = DIMMER_REGISTER_ADDRESS;
    register_mem.data.cmd.status = DIMMER_COMMAND_STATUS_OK;
    register_mem.data.cmd.read_length = 0;
    while(length-- > 0) {
        auto addr = register_mem.data.address;
        _D(5, debug_printf("I2C write, register address %#02x, data left %d\n", addr, length));
        i2c_write_to_register(Wire.read());
        if (addr == DIMMER_REGISTER_ADDRESS) {
            register_mem.data.address--;
            _D(5, debug_printf("I2C set register address = %#02x\n", register_mem.data.address));

            // legacy version request
            //
            // +i2ct=17,8a,02,b9
            // +i2cr=17,02
            if (length == 0 && register_mem.data.address == DIMMER_REGISTER_VERSION && register_mem.data.cmd.read_length == 2) {
                _D(5, debug_printf("I2C version request\n"));
                register_mem.data.vcc = Dimmer::Version::kVersion;
                register_mem.data.address = DIMMER_REGISTER_VCC;
            }
        }
        else if (addr == DIMMER_REGISTER_READ_LENGTH) {
            register_mem.data.address = DIMMER_REGISTER_ADDRESS;
        }
        else if (addr == DIMMER_REGISTER_COMMAND) {
            _D(5, debug_printf("I2C command = %#02x\n", register_mem.data.cmd.command));
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
                        _D(5, debug_printf("I2C read channels %u:%u\n", start, Dimmer::Channel::size));
                        i2c_slave_set_register_address(0, DIMMER_REGISTER_CH0_LEVEL + (start * sizeof(register_mem.data.level[0])), numChannels * sizeof(register_mem.data.level[0]));
                    }
                    break;
                case DIMMER_COMMAND_SET_LEVEL:
                    _D(5, debug_printf("I2C set level cmd=%d, channel=%d\n", register_mem.data.to_level, register_mem.data.channel));
                    dimmer.set_level(register_mem.data.channel, register_mem.data.to_level);
                    break;
                case DIMMER_COMMAND_FADE:
                    _D(5, debug_printf("I2C fade cmd from=%d, to=%d, channel=%d, fade_time=%f\n", register_mem.data.from_level, register_mem.data.to_level, register_mem.data.channel, register_mem.data.time));
                    dimmer.fade_from_to(register_mem.data.channel, register_mem.data.from_level, register_mem.data.to_level, register_mem.data.time);
                    break;
                case DIMMER_COMMAND_READ_NTC:
                    register_mem.data.temp = NAN;
#if HAVE_NTC
                    dimmer_scheduled_calls.read_ntc_temp = true;
#endif
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
                case DIMMER_COMMAND_READ_INT_TEMP:
                    register_mem.data.temp = NAN;
#if HAVE_READ_INT_TEMP
                    dimmer_scheduled_calls.read_int_temp = true;
#endif
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
                case DIMMER_COMMAND_READ_VCC:
                    register_mem.data.vcc = 0;
#if HAVE_READ_VCC
                    dimmer_scheduled_calls.read_vcc = true;
#endif
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_VCC, sizeof(register_mem.data.vcc));
                    break;
                case DIMMER_COMMAND_READ_AC_FREQUENCY:
                    register_mem.data.temp = dimmer._get_frequency();
                    _D(5, debug_printf("I2C get AC frequency=%.3f\n", register_mem.data.temp));
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
                case DIMMER_COMMAND_WRITE_EEPROM:
                    write_config();
                    break;
                case DIMMER_COMMAND_RESTORE_FS:
                    init_eeprom();
                    break;
                case DIMMER_COMMAND_GET_TIMER_TICKS:
                    // if (length-- > 0) {
                    //     switch(Wire.read()) {
                    //         case 1:
                    //             register_mem.data.temp = Dimmer::Timer<1>::ticksPerMicrosecond;
                    //             break;
                    //         case 2:
                    //             register_mem.data.temp = Dimmer::Timer<2>::ticksPerMicrosecond;
                    //             break;
                    //         default:
                    //             register_mem.data.temp = NAN;
                    //             break;
                    //     }
                    //     i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    // }
                    register_mem.data.temp = Dimmer::Timer<1>::ticksPerMicrosecond;
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;

#if HIDE_DIMMER_INFO == 0
                case DIMMER_COMMAND_PRINT_INFO:
                    display_dimmer_info();
                    break;
#endif

#if HAVE_PRINT_METRICS
                case DIMMER_COMMAND_PRINT_METRICS:
                    print_metrics_timeout = 0;
                    if (length-- > 0) {
                        print_metrics_interval = Wire.read() * 100;
                    } else {
                        print_metrics_interval = 0;
                    }
                    break;
#endif

                case DIMMER_COMMAND_SET_MODE:
                    if (length-- > 0) {
                        dimmer.set_mode((Wire.read() == 1) ? Dimmer::ModeType::LEADING_EDGE : Dimmer::ModeType::TRAILING_EDGE);
                    }
                    break;

                case DIMMER_COMMAND_PRINT_CONFIG: { // print command to restore parameters
                        auto ptr = reinterpret_cast<uint8_t *>(&register_mem.data.cfg);
                        Serial.printf_P(PSTR("+REM=v%02x,i2ct=%02x%02x"), Dimmer::Version::kVersion, DIMMER_I2C_ADDRESS, DIMMER_REGISTER_OPTIONS);
                        for(uint8_t i = DIMMER_REGISTER_OPTIONS; i < DIMMER_REGISTER_OPTIONS + sizeof(register_mem.data.cfg); i++) {
                            Serial.printf_P(PSTR("%02x"), *ptr++);
                        }
                        Serial.println();
                    } break;

                case DIMMER_COMMAND_WRITE_CFG_NOW:
                    _write_config(true, true);
                    break;

                case DIMMER_COMMAND_WRITE_EEPROM_NOW:
                    _write_config(true, false);
                    break;

#if DEBUG_COMMANDS
                case DIMMER_COMMAND_INCR_ZC_DELAY:
                    if (length > 0) {
                        length--;
                        register_mem.data.cfg.zero_crossing_delay_ticks += Wire.read();
                    }
                    else {
                        register_mem.data.cfg.zero_crossing_delay_ticks++;
                    }
                    goto print_zcdelay;
                case DIMMER_COMMAND_DECR_ZC_DELAY:
                    if (length > 0) {
                        length--;
                        register_mem.data.cfg.zero_crossing_delay_ticks -= Wire.read();
                    }
                    else {
                        register_mem.data.cfg.zero_crossing_delay_ticks--;
                    }
                    goto print_zcdelay;
                case DIMMER_COMMAND_SET_ZC_DELAY:
                    if (length-- >= (int)sizeof(register_mem.data.cfg.zero_crossing_delay_ticks)) {
                        Wire.readBytes(reinterpret_cast<uint8_t *>(&register_mem.data.cfg.zero_crossing_delay_ticks), sizeof(register_mem.data.cfg.zero_crossing_delay_ticks));
                    }
                    print_zcdelay:
                    Serial.printf_P(PSTR("+REM=zcdelay=%u,0x%04x\n"), register_mem.data.cfg.zero_crossing_delay_ticks, register_mem.data.cfg.zero_crossing_delay_ticks);
                    break;
                case DIMMER_COMMAND_INCR_HW_TICKS:
                    if (length > 0) {
                        length--;
                        dimmer.halfwave_ticks += Wire.read();
                    }
                    goto print_ticks;
                case DIMMER_COMMAND_DECR_HW_TICKS:
                    if (length > 0) {
                        length--;
                        dimmer.halfwave_ticks -= Wire.read();
                    }
                    print_ticks:
                    Serial.printf_P(PSTR("+REM=ticks=%d\n"), dimmer.halfwave_ticks);
                    break;

                case DIMMER_COMMAND_DUMP_CHANNELS: {
                        auto &tmp = dimmer.ordered_channels;
                        Serial.print(F("+REM="));
                        if (tmp[0].ticks) {
                            for(Dimmer::Channel::type i = 0; tmp[i].ticks; i++) {
                                Serial.printf_P(PSTR("%u=%u(%u) "), tmp[i].channel, tmp[i].ticks, dimmer._get_level(tmp[i].channel));
                            }
                            Serial.println();
                        }
                        else {
                            Serial.println(F("No channels active"));
                        }
                    }
                    break;
                case DIMMER_COMMAND_DUMP_MEM: {
                        auto ptr = register_mem.raw;
                        for(uint8_t addr = DIMMER_REGISTER_START_ADDR; addr < DIMMER_REGISTER_END_ADDR; addr++, ptr++) {
                            Serial.printf_P(PSTR("+REM=[%02x]: %u (%#02x)\n"), addr, *ptr, *ptr);
                        }
                    } break;
#endif

#if USE_TEMPERATURE_CHECK
                case DIMMER_COMMAND_FORCE_TEMP_CHECK:
                    next_temp_check = 0;
                    metrics_next_event = 0;
                    break;
#endif

            }
        }
    }
}


void _dimmer_i2c_on_request()
{
    static constexpr auto beginPtr = register_mem.raw - DIMMER_REGISTER_START_ADDR;
    static constexpr auto endPtr = register_mem.raw + sizeof(register_mem_t);

    _D(9, debug_printf("I2C slave onRequest: %#02x, length %u\n", register_mem.data.address, register_mem.data.cmd.read_length));
    auto ptr = beginPtr + register_mem.data.address;
    while(register_mem.data.cmd.read_length-- && ptr < endPtr) {
        Wire.write(*ptr++);
    }
    register_mem.data.cmd.read_length = 0;
}

void dimmer_init_register_mem()
{
    register_mem = {};
    register_mem.data.from_level = Dimmer::Level::invalid;
    // register_mem.data.cfg.version = Dimmer::Version::kVersion;
}

void dimmer_copy_config_to(register_mem_cfg_t &config)
{
    memcpy(&config, &register_mem.data.cfg, sizeof(config));
}

void dimmer_copy_config_from(const register_mem_cfg_t &config)
{
    memcpy(&register_mem.data.cfg, &config, sizeof(register_mem.data.cfg));
    // register_mem.data.cfg.version = Dimmer::Version::kVersion;
}

void dimmer_i2c_slave_setup()
{
    _D(5, debug_printf("I2C slave address: %#02x\n", DIMMER_I2C_ADDRESS));

    dimmer_init_register_mem() ;

    Wire.begin(DIMMER_I2C_ADDRESS);
    Wire.onReceive(_dimmer_i2c_on_receive);
    Wire.onRequest(_dimmer_i2c_on_request);
}
