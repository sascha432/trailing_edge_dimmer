/**
 * Author: sascha_lammers@gmx.de
 */

#include "dimmer.h"
#include "i2c_slave.h"
#include "helpers.h"
#include "cubic_interpolation.h"

void print_zcofs()
{
    Serial_printf_P(PSTR("+REM=zcofs=%d\n"), register_mem.data.cfg.zc_offset_ticks);
}

register_mem_union_t register_mem;

class RegisterMemory {
private:
    static constexpr register_mem_union_t &_mem = register_mem;
    static constexpr uint8_t *_start = &_mem.raw[0];
    static constexpr uint8_t *_end = &_mem.raw[sizeof(_mem.raw)];

public:
    class AddressPointer {
    public:
        AddressPointer() : _pointer(&_address) {}

        AddressPointer &operator=(uint8_t address) {
            _address = address;
            _pointer = &_mem.raw[address];
            return *this;
        }

        AddressPointer &operator=(void *pointer) {
            _pointer = reinterpret_cast<uint8_t *>(pointer);
            _address = _pointer - _start;
            return *this;
        }

        AddressPointer &operator++() {
            _pointer++;
            _address++;
            return *this;
        }

        AddressPointer operator++(int) {
            auto tmp = *this;
            _pointer++;
            _address++;
            return tmp;
        }

        operator uint8_t *() {
            return _pointer;
        }

        uint8_t &operator*() {
            return *_pointer;
        }

        bool isInvalid() const {
            return _address >= DIMMER_REGISTER_MEM_SIZE;
            //return _pointer >= _end || _pointer < _start;
        }

        bool isValid() const {
            return _address < DIMMER_REGISTER_MEM_SIZE;
        }

    private:
        static constexpr uint8_t &_address = _mem.data.address;
        uint8_t *_pointer;
    };

    RegisterMemory() {
        _mem = {};
        _mem.data.info = { DIMMER_VERSION_WORD, DIMMER_MAX_LEVELS, DIMMER_CHANNELS };
        _mem.data.channel.from_level = -1;
    }

    void onReceive(int8_t length);
    void onRequest();

private:
    void setResponse(int8_t length, uint8_t address, uint8_t readLength);

    template<class T>
    void setResponse(int8_t length, T &address) {
        _mem.data.cmd.read_length += sizeof(address);
        _pointer = (length <= 1) ? (void *)&address : (void *)&_mem.data.address;
    }

    uint8_t write(uint8_t data);
    uint8_t read();

private:
    AddressPointer _pointer;
};

RegisterMemory regMem;


void RegisterMemory::setResponse(int8_t length, uint8_t address, uint8_t readLength)
{
    Serial_printf("+REM=setResponse(%d, %u/0x%02x, %d)\n", length, address, address, readLength);
    _mem.data.cmd.read_length += readLength;
    _pointer = (length <= 1) ? address : DIMMER_REGISTER_ADDRESS;
}

uint8_t RegisterMemory::write(uint8_t data)
{
    *_pointer++ = data;
    return data;
}

uint8_t RegisterMemory::read()
{
    return *_pointer++;
}

void RegisterMemory::onReceive(int8_t length)
{
    Serial_printf("+REM=onReceive len=%u\n", length);
    _pointer = DIMMER_REGISTER_ADDRESS;
    _mem.data.cmd.read_length = 0;
    while(length-- > 0) {
        Serial_printf("+REM=address=%u 0x%02x data=%u 0x%02x len=%u\n", _mem.data.address, _mem.data.address, Wire.peek(), Wire.peek(), length);
        switch(_mem.data.address) {
            case DIMMER_REGISTER_ADDRESS:
                _pointer = Wire.read();
                break;
            case DIMMER_REGISTER_CMD_READ_LENGTH:
                write(Wire.read());
                _pointer = DIMMER_REGISTER_ADDRESS;
                break;
            case DIMMER_REGISTER_COMMAND:
                switch(write(Wire.read())) {
                    case DIMMER_COMMAND_READ_CHANNELS:
                        {
                            uint8_t channels = 0x80;
                            if (length-- > 0) {
                                channels = Wire.read();
                            }
                            setResponse(length, DIMMER_REGISTER_CHANNELS_LEVEL(channels & 0x0f), ((channels >> 4) << 1));
                        }
                        break;
                case DIMMER_COMMAND_SET_LEVEL:
                    dimmer.setLevel(_mem.data.channel.channel, _mem.data.channel.to_level);
                    break;
                case DIMMER_COMMAND_FADE:
                    dimmer.setFade(_mem.data.channel.channel, _mem.data.channel.from_level, _mem.data.channel.to_level, _mem.data.channel.time);
                    break;
                case DIMMER_COMMAND_READ_TEMPERATURE:
                    _mem.data.metrics.temperature = NAN;
#if HAVE_NTC
                    dimmer_scheduled_calls.readNTCTemp = true;
#endif
                    // setResponse(length, DIMMER_REGISTER_METRICS_TEMPERATURE, sizeof(_mem.data.metrics.temperature));
                    setResponse(length, _mem.data.metrics.temperature);
                    break;
                case DIMMER_COMMAND_READ_TEMPERATURE2:
                    _mem.data.metrics.temperature2 = NAN;
#if HAVE_READ_INT_TEMP
                    dimmer_scheduled_calls.readIntTemp = true;
#endif
                    setResponse(length, _mem.data.metrics.temperature2);
                    break;
                case DIMMER_COMMAND_READ_VCC:
                    _mem.data.metrics.vcc = 0;
#if HAVE_READ_VCC
                    dimmer_scheduled_calls.readVCC = true;
#endif
                    setResponse(length, _mem.data.metrics.vcc);
                    break;
                case DIMMER_COMMAND_READ_FREQUENCY:
                    _mem.data.metrics.frequency = dimmer.getFrequency();
                    setResponse(length, _mem.data.metrics.frequency);
                    break;
                case DIMMER_COMMAND_WRITE_SETTINGS:
                    write_config();
                    break;
                case DIMMER_COMMAND_WRITE_EEPROM:
                    config.writeConfiguration();
                    break;
                case DIMMER_COMMAND_RESTORE_FACTORY:
                    config.restoreFactorySettings();
                    break;
                case DIMMER_COMMAND_PRINT_INFO:
                    display_dimmer_info();
                    break;

#if HAVE_PRINT_METRICS
                case DIMMER_COMMAND_PRINT_METRICS:
                    print_metrics_timeout = 0;
                    if (length-- > 0 && Wire.read() == 0) {
                        dimmer_scheduled_calls.printMetrics = false;
                    }
                    else {
                        dimmer_scheduled_calls.printMetrics = true;
                    }
                    break;
#endif

#if DIMMER_CUBIC_INTERPOLATION
                case DIMMER_COMMAND_PRINT_CUBIC_INT:
                    {
                        uint8_t channel = 0xff;
                        uint8_t stepSize = 64;
                        if (length-- > 0) {
                            channel = Wire.read();
                            if (length-- > 0) {
                                stepSize = Wire.read();
                            }
                        }
                        if (channel < DIMMER_CHANNELS) {
                            cubicInterpolation.printTable(channel, stepSize);
                        }
                        else {
                            FOR_CHANNELS(i) {
                                cubicInterpolation.printTable(i, stepSize);
                            }
                        }
                    }
                    break;

                case DIMMER_COMMAND_GET_CUBIC_INT:
                    if (length > (int8_t)sizeof(dimmer_get_cubic_int_header_t)) {
                        dimmer_get_cubic_int_header_t header;
                        length -= Wire_read(header);

                        uint8_t count = length;
                        if (count % 3 == 0) {
                            count /= 3;
                            if (count && count <= DIMMER_CUBIC_INT_DATA_POINTS) {
                                double x_values[DIMMER_CUBIC_INT_DATA_POINTS];
                                for(uint8_t i = 0; i < count; i++) {
                                    x_values[i] = Wire.read();
                                    length--;
                                }
                                double y_values[DIMMER_CUBIC_INT_DATA_POINTS];
                                for(uint8_t i = 0; i < count; i++) {
                                    dimmer_level_t value;
                                    length -= Wire_read(value);
                                    y_values[i] = value;
                                }
                                header.level_count = min(sizeof(_mem.data.cubic_int) / sizeof(dimmer_level_t), header.level_count);
                                cubicInterpolation.getInterpolatedLevels(_mem.data.cubic_int.levels, header.level_count, header.start_level, header.step_size, count, x_values, y_values);
                                setResponse(length, DIMMER_REGISTER_CUBIC_INT_LEVELS(0), header.level_count * sizeof(dimmer_level_t));
                            }
                        }
                    }
                    break;

                case DIMMER_COMMAND_WRITE_CUBIC_INT:
                    if (length-- > 0) {
                        uint8_t channel = Wire.read();
                        if (channel <  DIMMER_CHANNELS) {
                            cubicInterpolation.copyFromConfig(_mem.data.cubic_int, channel);
                        }
                    }
                    break;

                case DIMMER_COMMAND_READ_CUBIC_INT:
                    if (length-- > 0) {
                        uint8_t channel = Wire.read();
                        if (channel < DIMMER_CHANNELS) {
                            cubicInterpolation.copyToConfig(_mem.data.cubic_int, channel);
                            setResponse(length, _mem.data.cubic_int);
                        }
                    }
                    break;

#endif

                case DIMMER_COMMAND_SET_ZC_OFS:
                    if (length-- >= 4) {
                        float temp = 0;
                        length -= Wire_read(temp);
                        _mem.data.cfg.zc_offset_ticks = microsecondsToClockCycles(temp) / DIMMER_TIMER1_PRESCALER;
                    }
                    else if (length-- >= 2) {
                        length -= Wire_read(_mem.data.cfg.zc_offset_ticks);
                    }
                    print_zcofs();
                    break;

#if DEBUG_STATISTICS
                case 0x80:
                    debugStats.print(Serial);
                    break;
#endif

                case DIMMER_COMMAND_FORCE_TEMP_CHECK:
                    next_temp_check = 0;
                    break;

#if DIMMER_SIMULATE_ZC
                case DIMMER_COMMAND_SIMULATE_ZC: {
                        uint8_t seconds = 1;
                        if (length-- > 0) {
                            seconds = Wire.read();
                        }
                        float freq = dimmer.getFrequency();
                        uint8_t freq_byte = round(freq);
                        uint32_t _delay = (1000000UL / 2) / freq;
                        for (uint8_t second = 0; second < seconds; second++) {
                            Serial_printf_P(PSTR("zc second %u\n"), second + 1);
                            for(uint8_t i = 0; i < freq_byte; i++) {
                                dimmer._zcHandler(TCNT1);
                                delayMicroseconds(_delay);
                            }
                        }
                    }
                    break;
#endif

                }
                break;
            default:
                write(Wire.read());
                break;
        }
        if (_pointer.isInvalid()) {
            break;
        }
    }
}

void RegisterMemory::onRequest()
{
    Serial_printf("+REM=onRequest ptr=%p end=%p len=%u\n", _pointer, _end, _mem.data.cmd.read_length);
    while(_mem.data.cmd.read_length-- && _pointer.isValid()) {
        Wire.write(*_pointer++);
    }
    _mem.data.cmd.read_length = 0;
}


// uint8_t validate_register_address()
// {
//     uint8_t offset = register_mem.data.address - DIMMER_REGISTER_START_ADDR;
//     if (offset < (uint8_t)sizeof(register_mem_t)) {
//         return offset;
//     }
//     return DIMMER_REGISTER_ADDRESS;
// }

// void i2c_write_to_register(uint8_t data)
// {
//     register_mem.raw[validate_register_address()] = data;
//     _D(5, debug_printf_P(PSTR("I2C write @ 0x%02x = %u (0x%02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR , data&0xff, data&0xff));
//     register_mem.data.address++;
// }

// uint8_t i2c_read_from_register()
// {
//     auto data = register_mem.raw[validate_register_address()];
//     _D(5, debug_printf_P(PSTR("I2C read @ 0x%02x = %u (0x%02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR, data&0xff, data&0xff));
//     register_mem.data.address++;
//     return data;
// }

// void i2c_slave_set_register_address(int length, uint8_t address, int8_t read_length)
// {
//     register_mem.data.cmd.read_length += read_length;
//     register_mem.data.address = (length <= 1) ? address : DIMMER_REGISTER_ADDRESS;
//     _D(5, debug_printf_P(PSTR("I2C auto set register address 0x%02x, read length %d\n"), register_mem.data.address, read_length));
// }

// void _dimmer_i2c_on_receive(int length)
// {
//     register_mem.data.address = DIMMER_REGISTER_ADDRESS;
//     register_mem.data.cmd.status = DIMMER_COMMAND_STATUS_OK;
//     register_mem.data.cmd.read_length = 0;
//     while(length-- > 0) {
//         auto addr = register_mem.data.address; // store a copy of the address in case the next write access changes it
//         _D(5, debug_printf_P(PSTR("I2C write, register address 0x%02x, data left %d\n"), addr, length));
//         i2c_write_to_register(Wire.read());
//         if (addr == DIMMER_REGISTER_ADDRESS) {
//             register_mem.data.address--;
//             _D(5, debug_printf_P(PSTR("I2C set register address = 0x%02x\n"), register_mem.data.address));
//         }
//         else if (addr == DIMMER_REGISTER_READ_LENGTH) {
//             register_mem.data.address = DIMMER_REGISTER_ADDRESS;
//         }
//         else if (addr == DIMMER_REGISTER_COMMAND) {
//             _D(5, debug_printf_P(PSTR("I2C command = 0x%02x\n"), register_mem.data.cmd.command));
//             switch(register_mem.data.cmd.command) {
//                 case DIMMER_COMMAND_READ_CHANNELS:
//                     {
//                         uint8_t numChannels = 8;
//                         uint8_t start = 0;
//                         if (length-- > 0) {
//                             numChannels = (uint8_t)Wire.read();
//                             start = numChannels & 0x0f;
//                             numChannels >>= 4;
//                         }
//                         _D(5, debug_printf_P(PSTR("I2C read channels %u:%u\n"), start, numChannels));
//                         i2c_slave_set_register_address(0, DIMMER_REGISTER_CH0_LEVEL + (start * sizeof(register_mem.data.channels.level[0])), numChannels * sizeof(register_mem.data.channels.level[0]));
//                     }
//                     break;
//                 case DIMMER_COMMAND_SET_LEVEL:
//                     _D(5, debug_printf_P(PSTR("I2C set level=%d, channel=%d\n"), register_mem.data.channel.to_level, register_mem.data.channel.channel));
//                     dimmer.setLevel(register_mem.data.channel.channel, register_mem.data.channel.to_level);
//                     break;
//                 case DIMMER_COMMAND_FADE:
//                     _D(5, Serial_printf_P(PSTR("I2C fade from=%d, to=%d, channel=%d, fade_time=%f\n"), register_mem.data.channel.from_level, register_mem.data.channel.to_level, register_mem.data.channel.channel, register_mem.data.channel.time));
//                     dimmer.setFade(register_mem.data.channel.channel, register_mem.data.channel.from_level, register_mem.data.channel.to_level, register_mem.data.channel.time); // 0-655 seconds in 10ms steps
//                     break;
//                 case DIMMER_COMMAND_READ_NTC:
//                     // store NAN in register if not available or if the data is requested before the scheduled call has finished
//                     register_mem.data.metrics.temperature = NAN;
// #if HAVE_NTC
//                     dimmer_scheduled_calls.readNTCTemp = true;
// #endif
//                     i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.metrics.temperature));
//                     break;
//                 case DIMMER_COMMAND_READ_INT_TEMP:
//                     register_mem.data.metrics.temperature2 = NAN;
// #if HAVE_READ_INT_TEMP
//                     dimmer_scheduled_calls.readIntTemp = true;
// #endif
//                     i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.metrics.temperature2));
//                     break;
//                 case DIMMER_COMMAND_READ_VCC:
//                     register_mem.data.metrics.vcc = 0;
// #if HAVE_READ_VCC
//                     dimmer_scheduled_calls.readVCC = true;
// #endif
//                     i2c_slave_set_register_address(length, DIMMER_REGISTER_VCC, sizeof(register_mem.data.metrics.vcc));
//                     break;
//                 case DIMMER_COMMAND_READ_AC_FREQUENCY:
//                     register_mem.data.metrics.frequency = dimmer.getFrequency();
//                     _D(5, debug_printf_P(PSTR("I2C get AC frequency=%.3f\n"), register_mem.data.metrics.frequency));
//                     i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.metrics.frequency));
//                     break;
//                 case DIMMER_COMMAND_WRITE_EEPROM:
//                     write_config();
//                     break;
//                 case DIMMER_COMMAND_WRITE_EEPROM_CFG:
//                     config.writeConfiguration();
//                     break;
//                 case DIMMER_COMMAND_RESTORE_FS: {
//                         config.eraseEEPROM();
//                         ConfigStorage::Settings settings;
//                         config.read(settings); // read() restores the factory settings after erasing the EEPROM
//                     }
//                     break;
//                 case DIMMER_COMMAND_PRINT_INFO:
//                     display_dimmer_info();
//                     break;

// #if HAVE_PRINT_METRICS
//                 case DIMMER_COMMAND_PRINT_METRICS:
//                     print_metrics_timeout = 0;
//                     if (length-- > 0 && Wire.read() == 0) {
//                         dimmer_scheduled_calls.printMetrics = false;
//                     }
//                     else {
//                         dimmer_scheduled_calls.printMetrics = true;
//                     }
//                     break;
// #endif

// #if DIMMER_CUBIC_INTERPOLATION
//                 case DIMMER_COMMAND_PRINT_CUBIC_INT:
//                     {
//                         uint8_t channel = 0xff;
//                         uint8_t stepSize = 1;
//                         if (length-- > 0) {
//                             channel = Wire.read();
//                             if (length-- > 0) {
//                                 stepSize = Wire.read();
//                             }
//                         }
//                         if (channel < DIMMER_CHANNELS) {
//                             cubicInterpolation.printTable(channel, stepSize);
//                         }
//                         else {
//                             FOR_CHANNELS(i) {
//                                 cubicInterpolation.printTable(i, stepSize);
//                             }
//                         }
//                     }
//                     break;

//                 case DIMMER_COMMAND_GET_CUBIC_INT:
//                     if (length > (int)sizeof(dimmer_get_cubic_int_header_t)) {
//                         dimmer_get_cubic_int_header_t header;
//                         length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&header), sizeof(header));

//                         uint8_t count = length;
//                         if (count % 3 == 0) {
//                             count /= 3;
//                             if (count && count <= DIMMER_CUBIC_INT_TABLE_SIZE) {
//                                 double x_values[DIMMER_CUBIC_INT_TABLE_SIZE];
//                                 for(uint8_t i = 0; i < count; i++) {
//                                     x_values[i] = Wire.read();
//                                     length--;
//                                 }
//                                 double y_values[DIMMER_CUBIC_INT_TABLE_SIZE];
//                                 for(uint8_t i = 0; i < count; i++) {
//                                     dimmer_level_t value;
//                                     length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
//                                     y_values[i] = value;
//                                 }
//                                 header.level_count = min(sizeof(register_mem.data.cubic_int) / sizeof(dimmer_level_t), header.level_count);
//                                 cubicInterpolation.getInterpolatedLevels(register_mem.data.cubic_int.levels, header.level_count, header.start_level, header.step_size, count, x_values, y_values);
//                                 i2c_slave_set_register_address(length, DIMMER_REGISTER_CUBIC_INT, header.level_count * sizeof(dimmer_level_t));
//                             }
//                         }

//                     }
//                     break;

//                 case DIMMER_COMMAND_WRITE_CUBIC_INT_CFG:
//                     if (length-- > 0) {
//                         uint8_t channel = Wire.read();
//                         if (channel <  DIMMER_CHANNELS) {
//                             cubicInterpolation.copyFromConfig(register_mem.data.cubic_int, channel);
//                         }
//                     }
//                     break;

//                 case DIMMER_COMMAND_READ_CUBIC_INT_CFG:
//                     if (length-- > 0) {
//                         uint8_t channel = Wire.read();
//                         if (channel < DIMMER_CHANNELS) {
//                             cubicInterpolation.copyToConfig(register_mem.data.cubic_int, channel);
//                             i2c_slave_set_register_address(length, DIMMER_REGISTER_CUBIC_INT, sizeof(register_mem.data.cubic_int));
//                         }
//                     }
//                     break;

// #endif

//                 case DIMMER_COMMAND_SET_ZC:
//                     if (length-- >= 4) {
//                         float temp = 0;
//                         length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&temp), sizeof(temp));
//                         register_mem.data.cfg.zc_offset_ticks = microsecondsToClockCycles(temp) / DIMMER_TIMER1_PRESCALER;
//                     }
//                     else if (length-- >= 2) {
//                         length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&register_mem.data.cfg.zc_offset_ticks), sizeof(register_mem.data.cfg.zc_offset_ticks));
//                     }
//                     print_zcofs();
//                     break;

// #if DEBUG_STATISTICS
//                 case 0x80:
//                     debugStats.print(Serial);
//                     break;
// #endif

//                 case DIMMER_COMMAND_FORCE_TEMP_CHECK:
//                     next_temp_check = 0;
//                     break;

//                 case DIMMER_COMMAND_DUMP_CFG: {
//                         Serial_printf_P(PSTR("+REM=+I2CT=%02X%02X"), DIMMER_I2C_ADDRESS, DIMMER_REGISTER_CONFIG_OFS);
//                         for(uint8_t i = DIMMER_REGISTER_CONFIG_OFS; i < DIMMER_REGISTER_CONFIG_OFS + DIMMER_REGISTER_CONFIG_SZ; i++) {
//                             Serial_printf_P(PSTR("%02X"), register_mem.raw[i - DIMMER_REGISTER_START_ADDR]);
//                         }
//                         Serial.println();
//                     }
//                     break;
// #if DIMMER_SIMULATE_ZC
//                 case DIMMER_COMMAND_SIMULATE_ZC: {
//                         uint8_t seconds = 1;
//                         if (length-- > 0) {
//                             seconds = Wire.read();
//                         }
//                         float freq = dimmer.getFrequency();
//                         uint8_t freq_byte = round(freq);
//                         uint32_t _delay = (1000000UL / 2) / freq;
//                         for (uint8_t second = 0; second < seconds; second++) {
//                             Serial_printf_P(PSTR("zc second %u\n"), second + 1);
//                             for(uint8_t i = 0; i < freq_byte; i++) {
//                                 dimmer._zcHandler(TCNT1);
//                                 delayMicroseconds(_delay);
//                             }
//                         }
//                     }
//                     break;
// #endif
//             }
//         }
//     }
// }

void dimmer_i2c_slave_setup()
{
    _D(5, debug_printf_P(PSTR("I2C slave address: 0x%02x\n"), DIMMER_I2C_ADDRESS));

    Wire.begin(DIMMER_I2C_ADDRESS);
    Wire.onReceive([](int length) {
        regMem.onReceive(length);
    });
    Wire.onRequest([]() {
        regMem.onRequest();
    });
}
