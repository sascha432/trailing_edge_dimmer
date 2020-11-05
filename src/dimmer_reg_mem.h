/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <math.h>

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
        union {
            float _f;
            uint32_t _i;
        } tmp = { f };
        return (tmp._i - offset) >> shift;
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

template<typename _Type, uint32_t _Multiplier, uint32_t _Divider = 1, _Type _NANValue = ~0>
struct __attribute__((__packed__)) FixedPointFloat {

    static constexpr float multiplier = _Multiplier / (float)_Divider;
    static constexpr float inverted_multiplier = 1.0f / multiplier; // avoid any float divison
    // static constexpr float rounding = 1.0f / multiplier / 1.9999999f;

    static float toFloat(_Type value) {
        if (value == _NANValue) {
            return NAN;
        }
        return value * inverted_multiplier;
    }
    static _Type fromFloat(float f) {
        if (::isnan(f)) {
            return _NANValue;
        }
        return static_cast<_Type>(lround(f * multiplier));
        //29686 = same code size
        // if (f < 0.0f) {
        //     return (f - rounding) * multiplier;
        // }
        // return (f + rounding) * multiplier;
    }

    FixedPointFloat() = default;
    FixedPointFloat(_Type v) : _value(v) {}
    FixedPointFloat(float f) : _value(fromFloat(f)) {}

    bool isnan() const {
        return _value == _NANValue;
    }

    FixedPointFloat &operator=(const char[]) {
        _value = _NANValue;
        return *this;
    }

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
        return _value != 0 && _value != _NANValue;
    }

    operator float() const {
        if (_value == _NANValue) {
            return NAN;
        }
        return toFloat(_value);
    }

    operator _Type() const {
        return _value;
    }

    explicit operator int() const {
        return _value;
    }

    template<typename _Cast>
    _Cast cast() const {
        return static_cast<_Cast>(_value);
    }

    template<typename _Cast>
    bool is_negative() const {
        return static_cast<_Cast>(_value) < 0;
    }

    template<typename _Cast>
    bool is_positive() const {
        return static_cast<_Cast>(_value) >= 0;
    }

    _Type _value;
};

#if HAVE_UINT24 == 1

using uint24_t = __uint24;
using int24_t = __int24;

static constexpr size_t sizeof_uint24_t = 3; //sizeof(uint24_t);
static constexpr size_t sizeof_int24_t = 3; //sizeof(int24_t);

static_assert(sizeof_uint24_t == sizeof(uint24_t), "check size");
static_assert(sizeof_int24_t == sizeof(int24_t), "check size");

#else

template<size_t _Bits, typename _Type>
struct __attribute__((__packed__,aligned(1))) custom_int_t {
    using type = custom_int_t<_Bits, _Type>;
    using underlying_type = _Type;

    static constexpr size_t bits = _Bits;
    static constexpr size_t size = (_Bits + 7) / 8;

    custom_int_t() = default;
    custom_int_t(const _Type value) : _value(value) {}

    operator _Type() const {
        return _value;
    }
    custom_int_t &operator==(const _Type value) const {
        _value = value;
        return *this;
    }

    union __attribute__((__packed__)) {
        struct __attribute__((__packed__)) {
            uint8_t _bytes[size];
        };
        struct __attribute__((__packed__)) {
            _Type _value: _Bits;
        };
    };
};

using uint24_t = custom_int_t<24, uint32_t>;
using int24_t = custom_int_t<24, int32_t>;

static constexpr size_t sizeof_uint24_t = uint24_t::size;
static constexpr size_t sizeof_int24_t = int24_t::size;

static_assert(sizeof(uint24_t) == uint24_t::size, "check struct");
static_assert(sizeof(int24_t) == int24_t::size, "check struct");

#endif

using internal_vref11_t = ShiftedFloat<int8_t, 0x3f8ccccd, 12>; // -127=1.0370212, 0=1.100000, 127=1.162012, precision=0.000488 (~0.5mV)
using temp_ofs_t = FixedPointFloat<int8_t, 4, 1>; // -31.75 to 31.75, precision=0.25 (1/4th°C)

typedef struct __attribute__((__packed__)) {
    uint8_t command;
    int8_t read_length;
    int8_t status;
} register_mem_command_t;

typedef struct __attribute__((__packed__)) {
    uint8_t restore_level: 1;
    uint8_t leading_edge: 1;
    uint8_t over_temperature_alert_triggered: 1;
    uint8_t negative_zc_delay: 1;                            // currently not implemented: zc delay = halfwave length - zcdelay, effectively making zc delay negative
    uint8_t ___reserved: 4;
} config_options_t;

#define REPORT_METRICS_INTERVAL(value)             (value)
#define REPORT_METRICS_INTERVAL_MILLIS(value)      (value * 1000UL)
#define REPORT_METRICS_INTERVAL_MILLIS24(value)    (value << 2)

// tmp = '0=disabled, '
// for i in range(1, 8):
//     tmp += "%u=%usec, " % (i, (1 << i))
// print(tmp)

typedef struct __attribute__((__packed__)) {
    uint8_t ts_offset;
    uint8_t ts_gain;
} internal_temp_calibration_t;

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
    uint16_t range_begin;
    uint16_t range_divider;
    internal_vref11_t internal_vref11;
    internal_temp_calibration_t internal_temp_calibration;
    temp_ofs_t ntc_temp_cal_offset;
    uint8_t report_metrics_interval;        // in seconds, 0=disabled
    int8_t halfwave_adjust_cycles;          // correction for measured time in clock cycles
    uint16_t switch_on_minimum_ticks;       // "minimum_on_time_ticks" after "switching on"
    uint8_t switch_on_count;                // number of half cycles before changing to minimum_on_time_ticks

    uint16_t get_range_end() const {
        if (range_divider == 0) {
            return DIMMER_MAX_LEVEL;
        }
        return ((uint32_t)DIMMER_MAX_LEVEL * DIMMER_MAX_LEVEL) / (range_divider - range_begin);
    }
    void set_range_end(uint16_t range_end) {
        if (!range_end) {
            range_begin = 0;
            range_divider = 0;
        }
        else if (range_end == DIMMER_MAX_LEVEL) {
            range_divider = range_begin ? range_begin : 0;
        }
        else {
            range_divider = (((uint32_t)DIMMER_MAX_LEVEL * DIMMER_MAX_LEVEL) / range_end) + range_begin;
        }
    }
} register_mem_cfg_t;

typedef struct __attribute__((__packed__)) {
    uint8_t frequency_low;
    uint8_t frequency_high;
    uint8_t zc_misfire;
} register_mem_errors_t;

typedef struct __attribute__((__packed__)) {
        uint16_t max_levels;
        uint8_t channel_count;
        uint8_t cfg_start_address;
        uint8_t length;
} dimmer_config_info_t;

static_assert(sizeof(dimmer_config_info_t) == 5, "check struct");

typedef struct __attribute__((__packed__)) {
    float timer1_ticks_per_us;
} dimmer_timers_t;

typedef struct __attribute__((__packed__)) dimmer_version_t {
    union __attribute__((__packed__)) {
        uint16_t _word;
        struct __attribute__((__packed__)) {
            uint16_t revision: 5;
            uint16_t minor: 5;
            uint16_t major: 5;
            uint16_t __reserved: 1;
        };
    };
    operator uint16_t() const {
        return _word;
    }
    operator bool() const {
        return _word != 0;
    }
} dimmer_version_t;

static constexpr uint16_t dimmer_version_to_uint16(const uint8_t major, const uint8_t minor, const uint8_t revision) {
    return ((major & 0x1f) << 10) | ((minor & 0x1f) << 5) | (revision & 0x1f);
}

static_assert(sizeof(dimmer_version_t) == 2, "check struct");

typedef struct __attribute__((__packed__)) {
    dimmer_version_t version;
    dimmer_config_info_t info;
} dimmer_version_info_t;

typedef union __attribute__((__packed__)) {
    dimmer_timers_t timers;
    dimmer_version_info_t v;
    uint64_t qword[2];
    uint32_t dwords[4];
    float floats[4];
    uint16_t words[8];
    uint8_t bytes[16];
} register_mem_ram_t;

typedef struct __attribute__((__packed__)) {
    int16_t from_level;
    int8_t channel;
    int16_t to_level;
    float time;
    register_mem_command_t cmd;
    uint16_t level[8];
    register_mem_cfg_t cfg;
    register_mem_errors_t errors;
    float frequency;
    int16_t int_temp;
    float ntc_temp;
    uint16_t vcc;
    register_mem_ram_t ram;
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
    int16_t internal_temp;
} dimmer_metrics_t;

static_assert(sizeof(dimmer_metrics_t) == 13, "check struct");

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
    union {
        uint8_t channel_state;
        struct {
            uint8_t channel0: 1;
            uint8_t channel1: 1;
            uint8_t channel2: 1;
            uint8_t channel3: 1;
            uint8_t channel4: 1;
            uint8_t channel5: 1;
            uint8_t channel6: 1;
            uint8_t channel7: 1;
        };
    };
} dimmer_channel_state_event_t;

static_assert(sizeof(dimmer_channel_state_event_t) == 1, "check struct");

typedef struct __attribute__((__packed__)) {
    uint8_t lost: 1;
    uint8_t sync: 1;
    uint8_t __reserved: 2;
    int32_t sync_difference_cycles: 28;
    uint16_t halfwave_counter;
} dimmer_sync_event_t;

static_assert(sizeof(dimmer_sync_event_t) == 6, "check struct");

extern register_mem_union_t register_mem;

typedef struct __attribute__((__packed__)) dimmer_command_fade_t {
    int16_t from_level;
    int8_t channel;
    int16_t to_level;
    float time;
    uint8_t command;

    dimmer_command_fade_t(uint8_t p_channel, int16_t p_from_level, int16_t p_to_level, float time) :
        from_level(p_from_level),
        channel(p_channel),
        to_level(p_to_level),
        time(time),
        command(DIMMER_COMMAND_FADE)
    {}

    static uint8_t address() {
        return DIMMER_REGISTER_FROM_LEVEL;
    }

} dimmer_command_fade_t;

static_assert(sizeof(dimmer_command_fade_t) == 10, "check struct");

namespace Dimmer  {

    static constexpr const uint8_t kRequestVersion[] = { 0x8a, 0x02, 0xb9 };

    namespace RegisterMemory {

        struct raw {
            static constexpr uint8_t size() {
                return sizeof(register_mem_t);
            }
            static constexpr uint8_t *begin() {
                return register_mem.raw;
            }
            static constexpr uint8_t *end() {
                return register_mem.raw + size();
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
                if (_length < 0) {
                    _length = 0;
                }
                else  {
                    int8_t tmp = (raw::end() - _iterator);
                    if ((uint8_t)tmp >= raw::size()) {
                        _length = 0;
                    }
                    else if (_length > tmp)  {
                        _length = tmp;
                    }
                }
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
                return _length;
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
