/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#ifndef __attribute__packed__
#define __attribute__packed__           __attribute__((packed))
#endif

template<typename _Type, uint32_t _Offset, uint8_t _Shift>
struct __attribute__((__packed__)) ShiftedFloat {
    static constexpr uint32_t offset = _Offset;
    static constexpr uint8_t shift = _Shift;

    static float toFloat(_Type value) {
        union {
            uint32_t _i;
            float _f;
        } tmp = { ((value << shift) + offset) };
        return tmp._f;
    }
    static _Type fromFloat(float f) {
        return (*reinterpret_cast<uint32_t *>(&f) - offset) >> shift;
    }

    ShiftedFloat() = default;
    ShiftedFloat(_Type v) : _value(v) {}
    ShiftedFloat(float f) : _value(fromFloat(f)) {}

    ShiftedFloat &operator=(float f) {
        _value = fromFloat(f);
        return *this;
    }

    ShiftedFloat &operator=(_Type value) {
        _value = value;
        return *this;
    }

    ShiftedFloat &operator=(int value) {
        _value = value;
        return *this;
    }

    ShiftedFloat &operator=(long value) {
        _value = value;
        return *this;
    }

    operator float() const {
        return toFloat(_value);
    }

    operator _Type() const {
        return _value;
    }

    _Type _value;
};
template<typename _Type, uint32_t _Multiplier, uint32_t _Divider = 1>
struct __attribute__((__packed__)) FixedPointFloat {

    static constexpr float multiplier = _Multiplier / (float)_Divider;
    static constexpr float inverted_multiplier = 1.0f / multiplier; // avoid any float divison
    static constexpr float rounding = 1.0f / multiplier / 1.9999999f;

    static float toFloat(_Type value) {
        return value * inverted_multiplier;
    }
    static _Type fromFloat(float f) {
        return (f + rounding) * multiplier;
    }

    FixedPointFloat() = default;
    FixedPointFloat(_Type v) : _value(v) {}
    FixedPointFloat(float f) : _value(fromFloat(f)) {}

    FixedPointFloat &operator=(float f) {
        _value = fromFloat(f);
        return *this;
    }

    FixedPointFloat &operator=(int value) {
        _value = static_cast<_Type>(value);
        return *this;
    }

    FixedPointFloat &operator=(unsigned value) {
        _value = static_cast<_Type>(value);
        return *this;
    }

    FixedPointFloat &operator=(long value) {
        _value = static_cast<_Type>(value);
        return *this;
    }

    FixedPointFloat &operator=(unsigned long value) {
        _value = static_cast<_Type>(value);
        return *this;
    }

    operator bool() const {
        return _value != 0;
    }

    operator float() const {
        return toFloat(_value);
    }

    operator _Type() const {
        return _value;
    }

    operator int() const {
        return _value;
    }

    _Type _value;
};

using internal_vref11_t = ShiftedFloat<int8_t, 0x3f8ccccd, 12>; // -128=1.037500, 0=1.100000, 127=1.162012, precision=0.000488 (~0.5mV)
using fadetime_t = FixedPointFloat<uint16_t, 100, 1>; // 0.0 to 1310.699951, precision=0.02 (20ms)
using temp_ofs_t = FixedPointFloat<int8_t, 4, 1>; // -32.0 to 31.75, precision=0.25 (1/4th°C)

typedef struct __attribute__((__packed__)) {
    uint8_t command;
    int8_t read_length;
    int8_t status;
} register_mem_command_t;

typedef struct {
    uint8_t restore_level: 1;
    uint8_t leading_edge: 1;
    uint8_t over_temperature_alert_triggered: 1;
    uint8_t ___reserved: 5;
} config_options_t;

#define REPORT_METRICS_INTERVAL(value)             (value)
#define REPORT_METRICS_INTERVAL_MILLIS(value)      (value * 1000UL)

// tmp = '0=disabled, '
// for i in range(1, 8):
//     tmp += "%u=%usec, " % (i, (1 << i))
// print(tmp)


typedef struct __attribute__((__packed__)) {
    union __attribute__((__packed__)) {
        config_options_t bits;
        uint8_t options;
    };
    uint8_t max_temp;
    float fade_in_time;
    uint16_t zero_crossing_delay_ticks;
    uint16_t minimum_on_time_ticks;
    uint16_t minimum_off_time_ticks;
    int16_t range_begin;
    int16_t range_end;
    internal_vref11_t internal_vref11;
    temp_ofs_t int_temp_offset;
    temp_ofs_t ntc_temp_offset;
    uint8_t report_metrics_interval;        // in seconds, 0=disabled
    int8_t halfwave_adjust_cycles;          // correction for measured time in clock cycles
    uint16_t switch_on_minimum_ticks;       // "minimum_on_time_ticks" after "switching on"
    uint8_t switch_on_count;                // number of half cycles before changing to minimum_on_time_ticks
} register_mem_cfg_t;

typedef struct __attribute__((__packed__)) {
    uint8_t frequency_low;
    uint8_t frequency_high;
    uint8_t zc_misfire;
} register_mem_errors_t;

typedef struct __attribute__((__packed__)) {
    int16_t from_level;
    int8_t channel;
    int16_t to_level;
    float time;
    register_mem_command_t cmd;
    uint16_t level[8];
    union {
        float temp;
        uint32_t temp_dword;
        uint16_t temp_words[2];
        uint8_t temp_bytes[4];
    };
    union {
        uint16_t vcc;
        uint8_t vcc_bytes[2];
    };
    register_mem_cfg_t cfg;
    register_mem_errors_t errors;
    uint8_t address;
} register_mem_t;

typedef union __attribute__((__packed__)) {
    register_mem_t data;
    uint8_t raw[sizeof(register_mem_t)];
} register_mem_union_t;

typedef struct __attribute__((__packed__)) {
    uint8_t temp_check_value;
    uint16_t vcc;
    float frequency;
    float ntc_temp;
    float internal_temp;
} dimmer_metrics_t;

static_assert(sizeof(dimmer_metrics_t) == 15, "check struct");

typedef struct __attribute__((__packed__)) {
    uint8_t current_temp;
    uint8_t max_temp;
} dimmer_over_temperature_event_t;

static_assert(sizeof(dimmer_over_temperature_event_t) == 2, "check struct");

typedef struct __attribute__((__packed__)) {
    uint32_t write_cycle;
    uint16_t write_position;
    uint8_t bytes_written;      // might be 0 if the data has not been changed
    union {
        uint8_t flags;
        struct {
            uint8_t config_updated: 1;
            uint8_t __reserved: 7;
        };
    };
} dimmer_eeprom_written_t;

static_assert(sizeof(dimmer_eeprom_written_t) == 8, "check struct");

typedef struct __attribute__((__packed__)) {
    uint8_t channel;
    uint16_t level;
} dimmer_fading_complete_event_t;

static_assert(sizeof(dimmer_fading_complete_event_t) == 3, "check struct");

typedef struct __attribute__((__packed__)) {
    uint8_t channel_state;
} dimmer_channel_state_event_t;

static_assert(sizeof(dimmer_channel_state_event_t) == 1, "check struct");


static constexpr uint16_t dimmer_version_to_uint16(const uint8_t major, const uint8_t minor, const uint8_t revision) {
    return (major << 10) | ((minor & 0x1f) << 5) | (revision & 0x1f);
}

extern register_mem_union_t register_mem;

namespace Dimmer  {

    namespace RegisterMemory {

        struct raw {
            static constexpr uint8_t *begin() {
                return register_mem.raw;
            }
            static constexpr uint8_t *end() {
                return register_mem.raw + sizeof(register_mem_t);
            }
            static uint8_t *fromAddress(uint8_t address) {
                return register_mem.raw + (address - DIMMER_REGISTER_START_ADDR);
            }
        };

        struct request {
            request(const uint8_t address, int8_t &length) :
                _iterator(raw::fromAddress(address)),
                _length(length)
            {
                length = 0;
            }

            operator bool() const {
                return _length > 0 && _iterator < raw::end();
            }

            request &operator++() {
                _length--;
                return *this;
            }

            uint8_t operator*() const {
                return *_iterator;
            }

            const uint8_t *data() const {
                return _iterator;
            }

            size_t size() const {
                int8_t tmp = (raw::end() - _iterator);
                if (tmp > _length) {
                    return _length;
                }
                return tmp;
            }

            uint8_t *_iterator;
            int8_t _length;
        };

        struct config {
            constexpr config() {}

            constexpr uint8_t *begin() const {
                return register_mem.raw + offsetof(register_mem_t, cfg);
            }
            constexpr uint8_t *end() const {
                return begin() + sizeof(register_mem_cfg_t);
            }
            constexpr size_t size() const {
                return sizeof(register_mem_cfg_t);
            }
        };

    }
}
