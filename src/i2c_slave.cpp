/**
 * Author: sascha_lammers@gmx.de
 */

#include "i2c_slave.h"
#include "helpers.h"
#include "cubic_interpolation.h"
#include <EEPROM.h>

register_mem_union_t register_mem;

void fade(dimmer_channel_id_t channel, dimmer_level_t from, dimmer_level_t to, float time)
{
    _D(5, debug_printf_P(PSTR("fade %d: %d to %d, time %f\n"), channel, from, to, time));
    if (channel == -1) {
        FOR_CHANNELS(i) {
            dimmer.setFade(i, from, to, time);
        }
    } else {
        dimmer.setFade(channel, from, to, time);
    }
}

void set_level(dimmer_channel_id_t channel, dimmer_level_t level)
{
    _D(5, debug_printf_P(PSTR("set level %d: %d\n"), channel, level));
    if (channel == -1) {
        FOR_CHANNELS(i) {
            dimmer.setLevel(i, level);
        }
    } else {
        dimmer.setLevel(channel, level);
    }
}

void print_zcdelay()
{
    Serial_printf_P(PSTR("+REM=zcdelay=%d\n"), register_mem.data.cfg.zero_crossing_delay_ticks);
}

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
    _D(5, debug_printf_P(PSTR("I2C write @ 0x%02x = %u (0x%02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR , data&0xff, data&0xff));
    register_mem.data.address++;
}

uint8_t i2c_read_from_register()
{
    auto data = register_mem.raw[validate_register_address()];
    _D(5, debug_printf_P(PSTR("I2C read @ 0x%02x = %u (0x%02x)\n"), validate_register_address() + DIMMER_REGISTER_START_ADDR, data&0xff, data&0xff));
    register_mem.data.address++;
    return data;
}

void i2c_slave_set_register_address(int length, uint8_t address, int8_t read_length)
{
    register_mem.data.cmd.read_length += read_length;
    register_mem.data.address = (length <= 1) ? address : DIMMER_REGISTER_ADDRESS;
    _D(5, debug_printf_P(PSTR("I2C auto set register address 0x%02x, read length %d\n"), register_mem.data.address, read_length));
}

void _dimmer_i2c_on_receive(int length)
{
    register_mem.data.address = DIMMER_REGISTER_ADDRESS;
    register_mem.data.cmd.status = DIMMER_COMMAND_STATUS_OK;
    register_mem.data.cmd.read_length = 0;
    while(length-- > 0) {
        auto addr = register_mem.data.address;
        _D(5, debug_printf_P(PSTR("I2C write, register address 0x%02x, data left %d\n"), addr, length));
        i2c_write_to_register(Wire.read());
        if (addr == DIMMER_REGISTER_ADDRESS) {
            register_mem.data.address--;
            _D(5, debug_printf_P(PSTR("I2C set register address = 0x%02x\n"), register_mem.data.address));
        }
        else if (addr == DIMMER_REGISTER_READ_LENGTH) {
            register_mem.data.address = DIMMER_REGISTER_ADDRESS;
        }
        else if (addr == DIMMER_REGISTER_COMMAND) {
            _D(5, debug_printf_P(PSTR("I2C command = 0x%02x\n"), register_mem.data.cmd.command));
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
                case DIMMER_COMMAND_FADE:
                    _D(5, Serial_printf_P(PSTR("I2C fade from=%d, to=%d, channel=%d, fade_time=%f\n"), register_mem.data.from_level, register_mem.data.to_level, register_mem.data.channel, register_mem.data.time));
                    fade(register_mem.data.channel, register_mem.data.from_level, register_mem.data.to_level, register_mem.data.time); // 0-655 seconds in 10ms steps
                    break;
                case DIMMER_COMMAND_READ_NTC:
                    // store NAN in register if not available or if the data is requested before the scheduled call has finished
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
                    register_mem.data.temp = dimmer.getFrequency();
                    _D(5, debug_printf_P(PSTR("I2C get AC frequency=%.3f\n"), register_mem.data.temp));
                    i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                    break;
                case DIMMER_COMMAND_WRITE_EEPROM:
                    write_config();
                    break;
                case DIMMER_COMMAND_FORCE_WRITE_EEPROM:
                    _write_config(true);
                    break;
                case DIMMER_COMMAND_RESTORE_FS:
                    reset_config();
                    init_eeprom();
                    break;
                case DIMMER_COMMAND_READ_TIMINGS:
                    if (length-- > 0) {
                        uint8_t timing = (uint8_t)Wire.read();
                        switch(timing) {
                            case DIMMER_TIMINGS_TMR1_TICKS_PER_US:
                                register_mem.data.temp = DIMMER_TMR1_TICKS_PER_US;
                                break;
                            case DIMMER_TIMINGS_TMR2_TICKS_PER_US:
                                register_mem.data.temp = 0;
                                break;
                            case DIMMER_TIMINGS_ZC_DELAY_IN_US:
                                register_mem.data.temp = DIMMER_TICKS_TO_US(register_mem.data.cfg.zero_crossing_delay_ticks, DIMMER_TMR1_TICKS_PER_US);
                                break;
                            case DIMMER_TIMINGS_MIN_ON_TIME_IN_US:
                                register_mem.data.temp = DIMMER_TICKS_TO_US(register_mem.data.cfg.min_on_ticks, DIMMER_TMR1_TICKS_PER_US);
                                break;
                            case DIMMER_TIMINGS_MAX_ON_TIME_IN_US:
                                register_mem.data.temp = DIMMER_TICKS_TO_US(register_mem.data.cfg.max_on_ticks, DIMMER_TMR1_TICKS_PER_US);
                                break;
                            default:
                                timing = 0;
                                break;
                        }
                        if (timing) {
                            i2c_slave_set_register_address(length, DIMMER_REGISTER_TEMP, sizeof(register_mem.data.temp));
                            _D(5, debug_printf_P(PSTR("I2C get timing 0x%02x=%s\n"), timing, String(register_mem.data.temp, 5).c_str()));
                        }
                    }
                    break;

                case DIMMER_COMMAND_PRINT_INFO:
                    display_dimmer_info();
                    break;

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

#if DIMMER_CUBIC_INTERPOLATION
                case DIMMER_COMMAND_PRINT_CUBIC_INT:
                    {
                        uint8_t channel = 0xff;
                        if (length-- > 0) {
                            channel = Wire.read();
                        }
                        if (channel < DIMMER_CHANNELS) {
                            cubicInterpolation.printTable(channel);
                        }
                        else {
                            FOR_CHANNELS(i) {
                                cubicInterpolation.printTable(i);
                            }
                        }
                    }
                    break;

                case DIMMER_COMMAND_GET_CUBIC_INT:
                    if (length > (int)sizeof(dimmer_get_cubic_int_header_t)) {
                        dimmer_get_cubic_int_header_t header;
                        length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&header), sizeof(header));

                        uint8_t count = length;
                        if (count % 3 == 0) {
                            count /= 3;
                            if (count && count <= DIMMER_CUBIC_INT_TABLE_SIZE) {
                                double x_values[DIMMER_CUBIC_INT_TABLE_SIZE];
                                for(uint8_t i = 0; i < count; i++) {
                                    x_values[i] = Wire.read();
                                    length--;
                                }
                                double y_values[DIMMER_CUBIC_INT_TABLE_SIZE];
                                for(uint8_t i = 0; i < count; i++) {
                                    dimmer_level_t value;
                                    length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
                                    y_values[i] = value;
                                }
                                header.level_count = min(11, header.level_count);
                                cubicInterpolation.getInterpolatedLevels(cubicInterpolation.getRegisterMemPtr(), header.level_count, header.start_level, header.step_size, count, x_values, y_values);
                                i2c_slave_set_register_address(length, DIMMER_REGISTER_CHANNELS_START, header.level_count * sizeof(dimmer_level_t));
                            }
                        }

                    }
                    break;

#endif

                case DIMMER_COMMAND_SET_ZC:
                    if (length-- >= 4) {
                        float temp = 0;
                        length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&temp), sizeof(temp));
                        register_mem.data.cfg.zero_crossing_delay_ticks = microsecondsToClockCycles(temp) / DIMMER_TIMER1_PRESCALER;
                    }
                    else if (length-- >= 2) {
                        length -= Wire.readBytes(reinterpret_cast<uint8_t *>(&register_mem.data.cfg.zero_crossing_delay_ticks), sizeof(register_mem.data.cfg.zero_crossing_delay_ticks));
                    }
                    print_zcdelay();
                    break;
                case DIMMER_COMMAND_ZC_DECREASE:
                    register_mem.data.cfg.zero_crossing_delay_ticks--;
                    print_zcdelay();
                    break;
                case DIMMER_COMMAND_ZC_INCREASE:
                    register_mem.data.cfg.zero_crossing_delay_ticks++;
                    print_zcdelay();
                    break;

#if 0
                // FOR CALIBRATION
                // undocumented, for calibration and testing
                case 0x80:
                    register_mem.data.cfg.internal_1_1v_ref += 0.001f;
                    Serial_printf_P(PSTR("+REM=ref11=%.4f\n"), register_mem.data.cfg.internal_1_1v_ref);
                    break;
                case 0x81:
                    register_mem.data.cfg.internal_1_1v_ref -= 0.001f;
                    Serial_printf_P(PSTR("+REM=ref11=%.4f\n"), register_mem.data.cfg.internal_1_1v_ref);
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
#if 0
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
#endif
#endif

                case DIMMER_COMMAND_FORCE_TEMP_CHECK:
                    next_temp_check = 0;
                    break;

                case DIMMER_COMMAND_DUMP_CFG: {
                        Serial_printf_P(PSTR("+REM=+I2CT=%02X%02X"), DIMMER_I2C_ADDRESS, DIMMER_REGISTER_CONFIG_OFS);
                        for(uint8_t i = DIMMER_REGISTER_CONFIG_OFS; i < DIMMER_REGISTER_CONFIG_OFS + DIMMER_REGISTER_CONFIG_SZ; i++) {
                            Serial_printf_P(PSTR("%02X"), register_mem.raw[i - DIMMER_REGISTER_START_ADDR]);
                        }
                        Serial.println();
                    }
                    break;
                case DIMMER_COMMAND_SIMULATE_ZC: {
                        uint8_t seconds = 1;
                        if (length-- > 0) {
                            seconds = Wire.read();
                        }
                        float freq = dimmer.getFrequency();
                        uint8_t freq_byte = round(freq);
                        uint32_t _delay = (1000000UL / 2) / freq;
                        for (uint8_t second = 0; second < seconds; second++) {
#if DIMMER_SIMULATE_ZC
                            Serial_printf_P(PSTR("zc second %u\n"), second + 1);
#endif
                            for(uint8_t i = 0; i < freq_byte; i++) {
                                dimmer._zcHandler(TCNT1);
                                delayMicroseconds(_delay);
                            }
                        }
                    }
                    break;

                case DIMMER_COMMAND_DUMP_MEM:
                    for(uint8_t addr = DIMMER_REGISTER_START_ADDR; addr < DIMMER_REGISTER_END_ADDR; addr++) {
                        auto ptr = register_mem.raw + addr - DIMMER_REGISTER_START_ADDR;
                        uint8_t data = *ptr;
                        Serial_printf_P(PSTR("[%02x]: 0x%02x (%u)\n"), addr, data, data);
                    }
                    break;
            }
        }
    }
}

void _dimmer_i2c_on_request()
{
    _D(9, debug_printf_P(PSTR("I2C slave onRequest: 0x%02x, length %u\n"), register_mem.data.address, register_mem.data.cmd.read_length));
    auto ptr = &register_mem.raw[register_mem.data.address - DIMMER_REGISTER_START_ADDR];
    while(register_mem.data.cmd.read_length-- && ptr < DIMMER_REGISTER_MEM_END_PTR) {
        Wire.write(*ptr++);
    }
    register_mem.data.cmd.read_length = 0;
}

void dimmer_i2c_slave_setup()
{
    _D(5, debug_printf_P(PSTR("I2C slave address: 0x%02x\n"), DIMMER_I2C_ADDRESS));

    register_mem = {};
    register_mem.data.from_level = -1;

    Wire.begin(DIMMER_I2C_ADDRESS);
    Wire.onReceive(_dimmer_i2c_on_receive);
    Wire.onRequest(_dimmer_i2c_on_request);
}

config_t::config_t() : cfg(register_mem.data.cfg)
{
    clear();
}

void config_t::clear()
{
    eeprom_cycle = 0;
    crc16 = 0;
    bzero(level, sizeof(level));
}

void config_t::read(size_t position)
{
    EEPROM.get(position, eeprom_cycle);
    position += sizeof(eeprom_cycle);
    EEPROM.get(position, crc16);
    position += sizeof(crc16);
    EEPROM.get(position, level);
    position += sizeof(level);
    EEPROM.get(position, register_mem.data.cfg);
}

size_t config_t::write(size_t position)
{
    EEPROM.put(position, eeprom_cycle);
    position += sizeof(eeprom_cycle);
    EEPROM.put(position, crc16);
    position += sizeof(crc16);
    EEPROM.put(position, level);
    position += sizeof(level);
    EEPROM.put(position, register_mem.data.cfg);
    position += sizeof(register_mem.data.cfg);
    return position;
}

bool config_t::compare(size_t position)
{
    uint32_t tmp_eeprom_cycle;
    EEPROM.get(position, tmp_eeprom_cycle);
    if (tmp_eeprom_cycle != eeprom_cycle) {
        return false;
    }
    position += sizeof(tmp_eeprom_cycle);

    uint16_t tmp_crc16;
    EEPROM.get(position, tmp_crc16);
    if (tmp_crc16 != crc16) {
        return false;
    }
    position += sizeof(tmp_crc16);

    int16_t tmp_level;
    FOR_CHANNELS(i) {
        EEPROM.get(position, tmp_level);
        if (tmp_level != level[i]) {
            return false;
        }
        position += sizeof(tmp_level);
    }
    auto ptr = reinterpret_cast<const uint8_t *>(&register_mem.data.cfg);
    for(size_t i = 0; i < sizeof(register_mem.data.cfg); i++)  {
        auto data = EEPROM.read(position);
        if (*ptr++ != data) {
            return false;
        }
        position++;
    }
        return true;
}

size_t config_t::size() const
{
    return sizeof(eeprom_cycle) + sizeof(crc16) + sizeof(level) + sizeof(register_mem.data.cfg);
}
