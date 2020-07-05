/**
 * Author: sascha_lammers@gmx.de
 */

#include "dimmer.h"
#include "i2c_slave.h"
#include "helpers.h"
#include "cubic_interpolation.h"

register_mem_union_t register_mem;
RegisterMemory regMem;


RegisterMemory::AddressPointer::AddressPointer() : _pointer(&_address)
{
}

RegisterMemory::AddressPointer &RegisterMemory::AddressPointer::operator=(uint8_t address)
{
    _address = address;
    _pointer = &_mem.raw[address];
    return *this;
}

RegisterMemory::AddressPointer &RegisterMemory::AddressPointer::operator=(void *pointer)
{
    _pointer = reinterpret_cast<uint8_t *>(pointer);
    _address = _pointer - _start;
    return *this;
}

RegisterMemory::AddressPointer &RegisterMemory::AddressPointer::operator++()
{
    _pointer++;
    _address++;
    return *this;
}

RegisterMemory::AddressPointer RegisterMemory::AddressPointer::operator++(int)
{
    auto tmp = *this;
    _pointer++;
    _address++;
    return tmp;
}

RegisterMemory::AddressPointer::operator uint8_t() const
{
    return _address;
}

RegisterMemory::AddressPointer::operator uint8_t *()
{
    return _pointer;
}

uint8_t &RegisterMemory::AddressPointer::operator*()
{
    return *_pointer;
}

bool RegisterMemory::AddressPointer::isInvalid() const
{
    return _address >= DIMMER_REGISTER_MEM_SIZE;
    //return _pointer >= _end || _pointer < _start;
}

bool RegisterMemory::AddressPointer::isValid() const
{
    return _address < DIMMER_REGISTER_MEM_SIZE;
}


RegisterMemory::RegisterMemory()
{
    _mem = {};
    _mem.data.info = {
            DIMMER_VERSION_WORD,
            DIMMER_MAX_LEVELS,
            DIMMER_CHANNELS,
            kRegisterMemInfoOptionsBitValue
    };
    _mem.data.channel.from_level = -1;
}


void RegisterMemory::setResponse(int8_t length, uint8_t address, uint8_t readLength)
{
    // Serial.printf("+REM=setResponse(%d, %u/0x%02x, %d)\n", length, address, address, readLength);
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
    // Serial.printf("+REM=onReceive len=%u\n", length);
    _pointer = DIMMER_REGISTER_ADDRESS;
    _mem.data.cmd.read_length = 0;
    if (length == 3 && Wire.peek() == 0x8a) { // version 2.x
        Wire.read();
        if (Wire.read() == 2 && Wire.read() == 0xb9) {
            setResponse(0, DIMMER_REGISTER_INFO_VERSION, 2);
        }
        return;
    }
    while(length-- > 0) {
        // Serial.printf("+REM=address=%u 0x%02x data=%u 0x%02x len=%u\n", _mem.data.address, _mem.data.address, Wire.peek(), Wire.peek(), length);
        switch(_mem.data.address) {
            // set pointer to address in data
            case DIMMER_REGISTER_ADDRESS:
                _pointer = Wire.read();
                break;
            // set read length for requestFrom() and set pointer to address
            case DIMMER_REGISTER_CMD_READ_LENGTH:
                write(Wire.read());
                _pointer = DIMMER_REGISTER_ADDRESS;
                break;
            // process command
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
                case DIMMER_COMMAND_READ_FREQUENCY:
                    setResponse(length, _mem.data.metrics.frequency);
                    break;
                case DIMMER_COMMAND_READ_TEMPERATURE:
                    setResponse(length, _mem.data.metrics.temperature);
                    break;
                case DIMMER_COMMAND_READ_TEMPERATURE2:
                    setResponse(length, _mem.data.metrics.temperature2);
                    break;
                case DIMMER_COMMAND_READ_VCC:
                    setResponse(length, _mem.data.metrics.vcc);
                    break;
                case DIMMER_COMMAND_READ_METRICS:
                    setResponse(length, _mem.data.metrics);
                    break;
                case DIMMER_COMMAND_WRITE_SETTINGS:
                    config.scheduleWriteSettings();
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
                    print_metrics_enabled = !(length-- > 0 && Wire.read() == 0);
                    break;
#endif

#if DIMMER_CUBIC_INTERPOLATION

#if HAVE_CUBIC_INT_TEST_PERFORMANCE
                case DIMMER_COMMAND_CUBIC_INT_TEST_PERF:
                    FOR_CHANNELS(i) {
                        cubicInterpolation.testPerformance(i);
                    }
                    break;
#endif

#if HAVE_CUBIC_INT_PRINT_TABLE
                case DIMMER_COMMAND_PRINT_CUBIC_INT:
                    {
                        uint8_t channel = 0xff;
                        uint8_t stepSize = 127;
                        if (length-- > 0) {
                            channel = Wire.read();
                            if (length-- > 0) {
                                stepSize = Wire.read();
                            }
                        }
                        if (Dimmer::isChannelValid(channel)) {
                            cubicInterpolation.printTable(channel, stepSize);
                        }
                        else {
                            FOR_CHANNELS(i) {
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
                        length -= Wire_read(header);

                        // start:uint16_t,num_level:uint8_t(1-8),step_size:uint8_t,x values:uint8[],y values:uint8_t[]

                        uint8_t count = length;
                        if (count % 2 == 0) {
                            count /= 2;
                            if (count && count <= Dimmer::kCubicIntMaxDataPoints) {
                                CubicInterpolation::xyValueType x_values[Dimmer::kCubicIntMaxDataPoints * 2];
                                CubicInterpolation::xyValueType *y_values = &x_values[Dimmer::kCubicIntMaxDataPoints];
                                memset(x_values, 0, sizeof(x_values));
                                length -= Wire.readBytes(reinterpret_cast<uint8_t *>(x_values), count);
                                length -= Wire.readBytes(reinterpret_cast<uint8_t *>(y_values), count);
                                uint8_t size = cubicInterpolation.getInterpolatedLevels(
                                    _mem.data.cubic_int.levels,
                                    &_mem.data.cubic_int.levels[sizeof(_mem.data.cubic_int.levels) / sizeof(*_mem.data.cubic_int.levels)],
                                    header.start_level,
                                    header.level_count,
                                    header.step_size,
                                    count,
                                    x_values,
                                    y_values
                                );
                                setResponse(length, DIMMER_REGISTER_CUBIC_INT_LEVELS(0), size);
                            }
                        }
                    }
                    break;
#endif

                case DIMMER_COMMAND_WRITE_CUBIC_INT:
                    if (length-- > 0) {
                        uint8_t channel = Wire.read();
                        if (Dimmer::isChannelValid(channel)) {
                            cubicInterpolation.copyFromConfig(_mem.data.cubic_int, channel);
                        }
                    }
                    break;

                case DIMMER_COMMAND_READ_CUBIC_INT:
                    if (length-- > 0) {
                        uint8_t channel = Wire.read();
                        if (Dimmer::isChannelValid(channel)) {
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
                    break;

#if DEBUG_STATISTICS
                case 0x80:
                    debugStats.print(Serial);
                    break;
#endif

                case DIMMER_COMMAND_FORCE_TEMP_CHECK:
                    update_metrics_timer = 0;
                    break;

            }
            break;

            // not a special register, write to register memory
            default:
                write(Wire.read());
                break;
        }
        if (_pointer.isInvalid()) {
            DEBUG_INVALID_I2C_ADDRESS((uint8_t)_pointer);
            break;
        }
    }
}

void RegisterMemory::onRequest()
{
    // Serial.printf("+REM=onRequest ptr=%p end=%p len=%u\n", _pointer, _end, _mem.data.cmd.read_length);
    while(_mem.data.cmd.read_length-- && _pointer.isValid()) {
        Wire.write(*_pointer++);
    }
    _mem.data.cmd.read_length = 0;
}

void RegisterMemory::begin()
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
