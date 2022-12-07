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
                            numChannels = Wire.read();
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
                        #if DIMMER_CUBIC_INTERPOLATION
                            cubicInterpolation.printConfig();
                        #endif
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

                case DIMMER_COMMAND_INCR_ZC_DELAY:
                    register_mem.data.cfg.zero_crossing_delay_ticks += Wire_read_uint8_t(length, 1);
                    Serial.printf_P(PSTR("+REM=zc=%u,0x%04x\n"), register_mem.data.cfg.zero_crossing_delay_ticks, register_mem.data.cfg.zero_crossing_delay_ticks);
                    break;
                case DIMMER_COMMAND_DECR_ZC_DELAY:
                    register_mem.data.cfg.zero_crossing_delay_ticks -= Wire_read_uint8_t(length, 1);
                    Serial.printf_P(PSTR("+REM=zc=%u,0x%04x\n"), register_mem.data.cfg.zero_crossing_delay_ticks, register_mem.data.cfg.zero_crossing_delay_ticks);
                    break;
                case DIMMER_COMMAND_SET_ZC_DELAY:
                    if (length-- >= static_cast<int>(sizeof(register_mem.data.cfg.zero_crossing_delay_ticks))) {
                        Wire.readBytes(reinterpret_cast<uint8_t *>(&register_mem.data.cfg.zero_crossing_delay_ticks), sizeof(register_mem.data.cfg.zero_crossing_delay_ticks));
                    }
                    Serial.printf_P(PSTR("+REM=zc=%u,0x%04x\n"), register_mem.data.cfg.zero_crossing_delay_ticks, register_mem.data.cfg.zero_crossing_delay_ticks);
                    break;

                #if DEBUG_COMMANDS
                    case DIMMER_COMMAND_MEASURE_FREQ: {
                            _D(5, debug_printf("measuring...\n"));
                            Serial.println(F("+REM=freq"));
                            dimmer.end();
                            delay(500);
                            FrequencyMeasurement::run();
                        }
                        break;

                    case DIMMER_COMMAND_INIT_EEPROM:
                        conf.initEEPROM();
                        break;

                    case DIMMER_COMMAND_INCR_HW_TICKS:
                        dimmer.halfwave_ticks += Wire_read_uint8_t(length, 1);
                        Serial.printf_P(PSTR("+REM=ticks=%d\n"), dimmer.halfwave_ticks);
                        break;
                    case DIMMER_COMMAND_DECR_HW_TICKS:
                        dimmer.halfwave_ticks -= Wire_read_uint8_t(length, 1);
                        Serial.printf_P(PSTR("+REM=ticks=%d\n"), dimmer.halfwave_ticks);
                        break;

                    case DIMMER_COMMAND_DUMP_CHANNELS: {
                            decltype(dimmer.ordered_channels) tmp;
                            decltype(dimmer.levels_buffer) tmp2;
                            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                                memcpy(tmp, dimmer.ordered_channels, sizeof(tmp));
                                memcpy(tmp2, dimmer.levels_buffer, sizeof(tmp2));
                            }
                            Serial.print(F("+REM="));
                            if (tmp[0].ticks) {
                                for(Dimmer::Channel::type i = 0; tmp[i].ticks; i++) {
                                    Serial.printf_P(PSTR("%u=%u(%u) "), tmp[i].channel, tmp[i].ticks, tmp2[tmp[i].channel]);
                                }
                                Serial.println();
                            }
                            else {
                                Serial.println(F("No channels active"));
                            }
                            DIMMER_CHANNEL_LOOP(i) {
                                Serial.printf_P(PSTR("+REM=ch=%u,l=%u/%u\n"), i, tmp2[i], dimmer._get_level(i));
                            }
                        }
                        break;
                    case DIMMER_COMMAND_DUMP_MEM: {
                            Serial.print(F("+REM="));
                            auto ptr = Dimmer::RegisterMemory::raw::begin();
                            for(uint8_t addr = DIMMER_REGISTER_START_ADDR; addr < DIMMER_REGISTER_END_ADDR; addr++, ptr++) {
                                //Serial.printf_P(PSTR("+REM=[%02x]: %u (%#02x)\n"), addr, *ptr, *ptr);
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

                #if DIMMER_CUBIC_INTERPOLATION

                    #if HAVE_CUBIC_INT_TEST_PERFORMANCE
                        case DIMMER_COMMAND_CUBIC_INT_TEST_PERF: {
                                uint8_t levels[DIMMER_CHANNEL_COUNT];
                                auto ptr = levels;
                                // turn all channels off
                                DIMMER_CHANNEL_LOOP(channel) {
                                    *ptr++ = dimmer._get_level(channel);
                                    dimmer.set_level(channel, 0);
                                }
                                DIMMER_CHANNEL_LOOP(channel2) {
                                    cubicInterpolation.testPerformance(channel2);
                                }
                                ptr = levels;
                                DIMMER_CHANNEL_LOOP(channel3) {
                                    dimmer.set_level(channel3, *ptr++);
                                }
                            }
                            break;
                    #endif

                    #if HAVE_CUBIC_INT_PRINT_TABLE
                        case DIMMER_COMMAND_PRINT_CUBIC_INT: {
                                uint8_t channel = Wire_read_uint8_t(length, 0xff);
                                uint8_t stepSize = Wire_read_uint8_t(length, 127);
                                if (channel < DIMMER_CHANNEL_COUNT) {
                                    cubicInterpolation.printTable(channel, stepSize);
                                }
                                else {
                                    DIMMER_CHANNEL_LOOP(i) {
                                        cubicInterpolation.printTable(i, stepSize);
                                    }
                                }
                            }
                            break;
                    #endif

                    #if HAVE_CUBIC_INT_GET_TABLE
                        case DIMMER_COMMAND_GET_CUBIC_INT:
                            if (length > (int8_t)sizeof(dimmer_get_cubic_int_header_t)) {
                                dimmer_get_cubic_int_header_t header;
                                length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&header), sizeof(header));

                                // start:uint16_t,num_level:uint8_t(1-8),step_size:uint8_t,x values:uint8[],y values:uint8_t[]
                                uint8_t count = length;
                                if (count % 2 == 0) {
                                    count /= 2;
                                    if (count && count <= DIMMER_CUBIC_INT_DATA_POINTS) {
                                        CubicInterpolation::xyValueType x_values[DIMMER_CUBIC_INT_DATA_POINTS * 2] = {};
                                        CubicInterpolation::xyValueType *y_values = &x_values[DIMMER_CUBIC_INT_DATA_POINTS];
                                        length -= Wire.readBytes(reinterpret_cast<uint8_t *>(x_values), count);
                                        length -= Wire.readBytes(reinterpret_cast<uint8_t *>(y_values), count);
                                        uint8_t size = cubicInterpolation.getInterpolatedLevels(
                                            register_mem.data.ram.cubic_int.levels,
                                            &register_mem.data.ram.cubic_int.levels[DIMMER_CUBIC_INT_DATA_POINTS],
                                            header.start_level,
                                            header.level_count,
                                            header.step_size,
                                            count,
                                            x_values,
                                            y_values
                                        );
                                        i2c_slave_set_register_address(length, DIMMER_REGISTER_CUBIC_INT_OFS, size);
                                    }
                                }
                            }
                            break;
                    #endif

                    case DIMMER_COMMAND_WRITE_CUBIC_INT: {
                            uint8_t channel = Wire_read_uint8_t(length, 0xff);
                            if (channel < DIMMER_CHANNEL_COUNT) {
                                ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                                    register_mem.data.ram.cubic_int = {};
                                    if (length > 0) {
                                        auto size = std::min<uint8_t>(DIMMER_CUBIC_INT_DATA_POINTS * 2, length);
                                        _D(5, debug_printf("write_cubic_int %u\n", length));
                                        if (Wire.readBytes(reinterpret_cast<uint8_t *>(&register_mem.data.ram.cubic_int.points), size) == size) {
                                            cubicInterpolation.getChannel(channel).createFromConfig(register_mem.data.ram.cubic_int);
                                        }
                                    }
                                    else {
                                        _D(5, debug_printf("write_cubic_int clear\n"));
                                        cubicInterpolation.getChannel(channel).createFromConfig(register_mem.data.ram.cubic_int);
                                    }
                                    // check if there is any data
                                    dimmer_config.bits.cubic_interpolation = false;
                                    DIMMER_CHANNEL_LOOP(channel) {
                                        _D(5, debug_printf("write_cubic_int channel=%u size=%u\n"), channel, cubicInterpolation.getChannel(channel).size());
                                        if (cubicInterpolation.getChannel(channel).size()) {
                                            dimmer_config.bits.cubic_interpolation = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;

                    case DIMMER_COMMAND_READ_CUBIC_INT: {
                            uint8_t channel = Wire_read_uint8_t(length, 0xff);
                            if (channel < DIMMER_CHANNEL_COUNT) {
                                cubicInterpolation.getChannel(channel).copyToConfig(register_mem.data.ram.cubic_int);
                                _D(5, debug_printf("read_cubic_int\n"));
                                i2c_slave_set_register_address(length, DIMMER_REGISTER_CUBIC_INT_OFS, sizeof(register_mem.data.ram.cubic_int));
                            }
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
