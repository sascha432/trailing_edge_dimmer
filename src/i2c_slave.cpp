/**
 * Author: sascha_lammers@gmx.de
 */

#include "i2c_slave.h"
#include "helpers.h"
#include "dimmer.h"
#include "measure_frequency.h"
#include "main.h"

register_mem_union_t register_mem;

inline uint8_t validate_register_address()
{
    uint8_t offset = register_mem.data.address - DIMMER_REGISTER_START_ADDR;
    if (offset < (uint8_t)sizeof(register_mem_t)) {
        return offset;
    }
    return DIMMER_REGISTER_ADDRESS - DIMMER_REGISTER_START_ADDR;
}

void i2c_write_to_register(uint8_t data)
{
    register_mem.raw[validate_register_address()] = data;
    _D(5, debug_printf("I2C write to %#02x: %#02x (%u, %d)\n", validate_register_address() + DIMMER_REGISTER_START_ADDR , data, data, (int8_t)data));
    register_mem.data.address++;
}

uint8_t i2c_read_from_register()
{
    auto data = register_mem.raw[validate_register_address()];
    _D(5, debug_printf("I2C read from %#02x: %#02x (%u, %d)\n", validate_register_address() + DIMMER_REGISTER_START_ADDR, data, data, (int8_t)data));
    register_mem.data.address++;
    return data;
}

void i2c_slave_set_register_address(int length, uint8_t address, int8_t read_length)
{
    register_mem.data.cmd.read_length += read_length;
    register_mem.data.address = (length <= 1) ? /* no more data available */ address : DIMMER_REGISTER_ADDRESS;
    _D(5, debug_printf("I2C auto addr=%#02x read_len=%d\n", register_mem.data.address, read_length));
}

uint8_t Wire_read_uint8_t(int &length, uint8_t default_value)
{
    if (length-- > 0) {
        return Wire.read();
    }
    return default_value;
}

void _dimmer_i2c_on_receive(int length)
{
    register_mem.data.address = DIMMER_REGISTER_ADDRESS;
    register_mem.data.cmd.status = DIMMER_COMMAND_STATUS_OK;
    register_mem.data.cmd.read_length = 0;
    while(length-- > 0) {
        auto addr = register_mem.data.address;
        _D(5, debug_printf("I2C addr=%#02x data=%02x left=%d\n", addr, Wire.peek(), length));
        i2c_write_to_register(Wire.read());
        if (addr == DIMMER_REGISTER_ADDRESS) {
            register_mem.data.address--;
            _D(5, debug_printf("I2C set addr=%#02x\n", register_mem.data.address));

            // legacy version request
            //
            // +i2ct=17,8a,02,b9
            // +i2cr=17,07
            //
            // older versions will respond with 2 byte for the version and the rest filled with 0xff
            if (length == 0 && register_mem.data.address == 0xb9 && register_mem.data.cmd.read_length == 2) {
                _D(5, debug_printf("I2C version request\n"));
                register_mem.data.ram.v.version._word = Dimmer::Version::kVersion;
                register_mem.data.ram.v.info = { Dimmer::Level::max, Dimmer::Channel::kSize, DIMMER_REGISTER_OPTIONS, sizeof(register_mem.data.cfg) };
                register_mem.data.cmd.read_length = 0;
                i2c_slave_set_register_address(0, DIMMER_REGISTER_RAM, sizeof(register_mem.data.ram.v));
            }
        }
        else if (addr == DIMMER_REGISTER_READ_LENGTH) {
            register_mem.data.address = DIMMER_REGISTER_ADDRESS;
        }
        else if (addr == DIMMER_REGISTER_COMMAND) {
            _D(5, debug_printf("I2C cmd=%#02x\n", register_mem.data.cmd.command));
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
                        i2c_slave_set_register_address(0, DIMMER_REGISTER_CH0_LEVEL + (start * sizeof(register_mem.data.channels.level[0])), numChannels * sizeof(register_mem.data.channels.level[0]));
                    }
                    break;
                case DIMMER_COMMAND_SET_LEVEL:
                    _D(5, debug_printf("I2C set=%d ch=%d\n", register_mem.data.to_level, register_mem.data.channel));
                    dimmer.set_level(register_mem.data.channel, register_mem.data.to_level);
                    break;
                case DIMMER_COMMAND_FADE:
                    _D(5, debug_printf("I2C fade from=%d to=%d ch=%d t=%f\n", register_mem.data.from_level, register_mem.data.to_level, register_mem.data.channel, register_mem.data.time));
                    dimmer.fade_from_to(register_mem.data.channel, register_mem.data.from_level, register_mem.data.to_level, register_mem.data.time);
                    break;
                case DIMMER_COMMAND_READ_NTC:
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_NTC_TEMP, sizeof(register_mem.data.metrics.ntc_temp));
                    break;
                case DIMMER_COMMAND_READ_INT_TEMP:
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_INT_TEMP, sizeof(register_mem.data.metrics.int_temp));
                    break;
                case DIMMER_COMMAND_READ_VCC:
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_VCC, sizeof(register_mem.data.metrics.vcc));
                    break;
                case DIMMER_COMMAND_READ_AC_FREQUENCY:
                    _D(5, debug_printf("I2C get frequency=%.3f\n", register_mem.data.metrics.frequency));
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_FREQUENCY, sizeof(register_mem.data.metrics.frequency));
                    break;

                case DIMMER_COMMAND_GET_TIMER_TICKS:
                    register_mem.data.ram.timers = { Dimmer::Timer<1>::ticksPerMicrosecond };
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_RAM, sizeof(register_mem.data.ram.timers));
                    break;

#if HIDE_DIMMER_INFO == 0
                case DIMMER_COMMAND_PRINT_INFO:
                    display_dimmer_info();
                    break;
#endif

#if HAVE_PRINT_METRICS
                case DIMMER_COMMAND_PRINT_METRICS:
                    queues.print_metrics.timer = 0;
                    queues.print_metrics.interval = Wire_read_uint8_t(length, 0);
                    break;
#endif

                case DIMMER_COMMAND_SET_MODE:
                    if (length-- > 0) {
                        dimmer.set_mode((Wire.read() == 1) ? Dimmer::ModeType::LEADING_EDGE : Dimmer::ModeType::TRAILING_EDGE);
                    }
                    break;

                case DIMMER_COMMAND_PRINT_CONFIG: { // print command to restore parameters
                        Serial.printf_P(PSTR("+REM=v%04x,i2ct=%02x%02x"), Dimmer::Version::kVersion, DIMMER_I2C_ADDRESS, DIMMER_REGISTER_OPTIONS);
                        for(const auto data: Dimmer::RegisterMemory::config()) {
                            Serial.printf_P(PSTR("%02x"), data);
                        }
                        Serial.println();
                    } break;

                case DIMMER_COMMAND_RESTORE_FS:
                    conf.restoreFactory();
                    break;

                case DIMMER_COMMAND_WRITE_EEPROM:
                    if (Wire_read_uint8_t(length, 0) == DIMMER_COMMAND_WRITE_CONFIG) {
                        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                            queues.scheduled_calls.eeprom_update_config = true;
                        }
                    }
                    conf.scheduleWriteConfig();
                    break;

                case DIMMER_COMMAND_WRITE_EEPROM_NOW:
                    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                        if (Wire_read_uint8_t(length, 0) == DIMMER_COMMAND_WRITE_CONFIG) {
                            queues.scheduled_calls.eeprom_update_config = true;
                        }
                        queues.scheduled_calls.write_eeprom = false;
                    }
                    conf._writeConfig(true);
                    break;

                case DIMMER_COMMAND_FORCE_TEMP_CHECK:
                    queues.check_temperature.timer = 0;
                    queues.report_metrics.timer = 0;
                    break;

#if DEBUG_COMMANDS
                case DIMMER_COMMAND_MEASURE_FREQ: {
                        _D(5, debug_printf("measuring...\n"));
                        Serial.println(F("+REM=freq"));
                        dimmer.end();
                        delay(500);
                        start_measure_frequency();
                    }
                    break;

                case DIMMER_COMMAND_INIT_EEPROM:
                    conf.initEEPROM();
                    break;

                case DIMMER_COMMAND_INCR_ZC_DELAY:
                    register_mem.data.cfg.zero_crossing_delay_ticks += Wire_read_uint8_t(length, 1);
                    goto print_zcdelay;
                case DIMMER_COMMAND_DECR_ZC_DELAY:
                    register_mem.data.cfg.zero_crossing_delay_ticks -= Wire_read_uint8_t(length, 1);
                    goto print_zcdelay;
                case DIMMER_COMMAND_SET_ZC_DELAY:
                    if (length-- >= (int)sizeof(register_mem.data.cfg.zero_crossing_delay_ticks)) {
                        Wire.readBytes(reinterpret_cast<uint8_t *>(&register_mem.data.cfg.zero_crossing_delay_ticks), sizeof(register_mem.data.cfg.zero_crossing_delay_ticks));
                    }
                    print_zcdelay:
                    Serial.printf_P(PSTR("+REM=zcdelay=%u,0x%04x\n"), register_mem.data.cfg.zero_crossing_delay_ticks, register_mem.data.cfg.zero_crossing_delay_ticks);
                    break;
                case DIMMER_COMMAND_INCR_HW_TICKS:
                    dimmer.halfwave_ticks += Wire_read_uint8_t(length, 1);
                    goto print_ticks;
                case DIMMER_COMMAND_DECR_HW_TICKS:
                    dimmer.halfwave_ticks -= Wire_read_uint8_t(length, 1);
                    print_ticks:
                    Serial.printf_P(PSTR("+REM=ticks=%d\n"), dimmer.halfwave_ticks);
                    break;

#if HAVE_DISABLE_ZC_SYNC
                case DIMMER_COMMAND_SET_ZC_SYNC: {
                        if (length == 0) {
                            dimmer.zc_sync_disabled = !dimmer.zc_sync_disabled;
                        }
                        else {
                            dimmer.zc_sync_disabled = Wire_read_uint8_t(length, 0);
                        }
                        Serial.printf_P(PSTR("+REM=sync=%u\n"), !dimmer.zc_sync_disabled);
                    }
                    break;
#endif

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
                        Serial.print(F("+REM="));
                        auto ptr = Dimmer::RegisterMemory::raw::begin();
                        for(uint8_t addr = DIMMER_REGISTER_START_ADDR; addr < DIMMER_REGISTER_END_ADDR; addr++, ptr++) {
                            //1Serial.printf_P(PSTR("+REM=[%02x]: %u (%#02x)\n"), addr, *ptr, *ptr);
                            if (addr % 4 == 0) {
                                Serial.printf_P(PSTR("[%02x]"), addr);
                            }
                            Serial.printf_P(PSTR("%02x"), *ptr);
                            if (addr % 16 == 15) {
                                Serial.print(F("\n+REM="));
                            }
                            else if (addr % 4 == 3) {
                                Serial.print(' ');
                            }
                        }
                        Serial.println();
                    }
                    break;
#endif
            }
        }
    }
}


void _dimmer_i2c_on_request()
{
#if DEBUG
    auto tmp = register_mem.data.cmd.read_length;
#endif
    Dimmer::RegisterMemory::request data(register_mem.data.address, register_mem.data.cmd.read_length);
    _D(5, debug_printf("I2C on_request addr=%#02x len=%u avail=%u\n", register_mem.data.address, tmp, data.size()));
    Wire.write(data.data(), data.size());
}

void dimmer_i2c_slave_setup()
{
    _D(5, debug_printf("I2C slave address=%#02x\n", DIMMER_I2C_ADDRESS));

    conf.initRegisterMem();

    Wire.begin(DIMMER_I2C_ADDRESS);
    Wire.onReceive(_dimmer_i2c_on_receive);
    Wire.onRequest(_dimmer_i2c_on_request);
}
