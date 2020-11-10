/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifndef UINT24_MAX
#define UINT24_MAX ((uint32_t)16777216)
#endif

#ifndef INT24_MAX
#define INT24_MAX ((int32_t)8388607)
#endif

#ifndef INT24_MIN
#define INT24_MIN ((int32_t)-8388608)
#endif

#if __GNUC__
#define __attribute_always_inline__         __attribute__((always_inline))
#define __attribute_packed__                __attribute__((__packed__))
#else
#define __attribute_always_inline__
#define __attribute_packed__
#endif

// NOTE: the custom uint24_t implementation is used for intellisense since it does not support the avr-gcc 24bit integer extension

#if HAVE_UINT24 == 1 && !defined(__INTELLISENSE__)

using uint24_t = __uint24;
using int24_t = __int24;

// equivalent of uint24_t value = lo | (uint24_t)uint16_value << 16;
inline __attribute_always_inline__ static uint24_t __uint24_from_ui16_ui8(const uint16_t hi, const uint8_t lo) {
    return lo | static_cast<uint24_t>(hi) << 16;
}

// equivalent of uint24_t value = uint32_value >> 8;
inline __attribute_always_inline__ static uint24_t __uint24_from_shr8_ui32(const uint32_t value) {
    return value >> 8;
}

#else

class uint24_t;
class int24_t;

// equivalent of uint24_t value = lo | (uint24_t)uint16_value << 16;
static uint24_t __uint24_from_ui16_ui8(const uint16_t hi, const uint8_t lo);

// equivalent of uint24_t value = uint32_value >> 8;
static uint24_t __uint24_from_shr8_ui32(const uint32_t value);

#warning uint24_t/int24_t is experimental/not tested
#warning set HAVE_UINT24=1 to use avr-gccs native __int24/__uint24 type

#if _MSC_VER
#pragma pack(push, 1)
#endif

class __attribute_packed__ uint24_t
{
public:
    static constexpr size_t bits = 24;
    static constexpr size_t size = 3;

    typedef union __attribute_packed__ {
        uint8_t ui8;
        int8_t i8;
        uint16_t ui16;
        int16_t i16;
        uint32_t ui24 : 24;
        int32_t i24 : 24;
    } int_union_t;

    uint24_t() = default;
    explicit uint24_t(uint8_t lo, uint8_t mid, uint8_t hi) : _lo(lo), _mid(mid), _hi(hi) {}

    explicit uint24_t(uint8_t value) : _lo(static_cast<uint8_t>(value)), _mid(0), _hi(0) {}
    explicit uint24_t(uint16_t value) :
        _lo(static_cast<uint8_t>(value)),
        _mid(static_cast<uint8_t>(value >> 8)),
        _hi(0) {}
    uint24_t(uint32_t value) :
        _lo(static_cast<uint8_t>(value)),
        _mid(static_cast<uint8_t>(static_cast<uint16_t>(value) >> 8)),
        _hi(static_cast<uint8_t>(static_cast<uint32_t>(value) >> 16))
    {}

    // delegating constructors
    explicit uint24_t(int8_t value) __attribute_always_inline__ : uint24_t(static_cast<uint8_t>(value)) {}
    explicit uint24_t(char value) __attribute_always_inline__ : uint24_t(static_cast<uint8_t>(value)) {}
    explicit uint24_t(int16_t value) __attribute_always_inline__ : uint24_t(static_cast<uint16_t>(value)) {}
    explicit uint24_t(int32_t value) __attribute_always_inline__ : uint24_t(static_cast<uint32_t>(value)) {}
    explicit uint24_t(uint64_t value) __attribute_always_inline__ : uint24_t(static_cast<uint32_t>(value)) {}
    explicit uint24_t(int64_t value) __attribute_always_inline__ : uint24_t(static_cast<uint32_t>(value)) {}

    // equivalent of (hi << 8) | lo
    uint24_t(uint16_t hi, uint8_t lo) : _lo(lo), _mid(static_cast<uint8_t>(hi)), _hi(hi >> 8) {}

    // equivalent of (hi << 16) | lo
    uint24_t(uint8_t hi, uint16_t lo) : _lo(static_cast<uint8_t>(lo)), _mid(lo >> 8), _hi(hi) {}

    // equivalent of (hi << 8) | lo
    uint24_t(uint8_t hi, uint8_t lo) : _lo(lo), _mid(hi), _hi(0) {}

    explicit operator uint64_t() const {
        return _union_cref().ui24;
    }

    explicit operator int64_t() const {
        return _union_cref().ui24;
    }

    operator uint32_t() const {
        return _union_cref().ui24; // -O2 24358
        //return static_cast<uint32_t>(_lo | (static_cast<uint16_t>(_mid) << 8) | (static_cast<uint32_t>(_hi) << 16)); // -O2 24424
        // return static_cast<uint32_t>(_lo | (static_cast<uint32_t>(_hi16) << 8)); // -O2 24592
    }

    explicit operator int32_t() const __attribute_always_inline__ {
        return static_cast<uint32_t>(*this);
    }

    explicit operator uint16_t() const {
        return _union_cref().ui16; // -O2 24330
        // return _lo || (static_cast<uint16_t>(_mid) << 8); // -O2 24352
    }

    explicit operator int16_t() const __attribute_always_inline__ {
        return static_cast<uint16_t>(*this);
    }

    explicit operator uint8_t() const __attribute_always_inline__ {
        return _lo;
    }

    explicit operator int8_t() const __attribute_always_inline__ {
        return _lo;
    }

    explicit operator char() const __attribute_always_inline__ {
        return _lo;
    }

    uint24_t &operator=(const uint64_t value) __attribute_always_inline__ {
        *this = static_cast<const uint32_t>(value);
        return *this;
    }

    uint24_t &operator=(const uint32_t value) {
        // _union_ref().ui24 = value;               // -O2 24318
        _lo = static_cast<uint8_t>(value);          // -O2 24306
        _mid = static_cast<uint16_t>(value) >> 8;
        _hi = static_cast<uint8_t>(value >> 16);
        return *this;
    }

    uint24_t &operator=(const uint24_t value) {
        _lo = value._lo;
        _mid = value._mid;
        _hi = value._hi;
        return *this;
    }

    uint24_t &operator=(const uint16_t value) {
        _lo = static_cast<uint8_t>(value);
        _mid = value >> 8;
        _hi = 0;
        return *this;
    }

    uint24_t &operator=(const int16_t value) {
        _lo = static_cast<uint8_t>(value);
        _mid = value >> 8;
        _hi = static_cast<uint8_t>(value >= 0 ? 0 : 0xff);
        return *this;
    }

    uint24_t &operator=(const uint8_t value) {
        _lo = value;
        _mid = 0;
        _hi = 0;
        return *this;
    }

    uint24_t &operator=(const int8_t value) {
        _lo = static_cast<uint8_t>(value);
        _mid = static_cast<uint8_t>(value >= 0 ? 0 : 0xff);
        _hi = _mid;
        return *this;
    }

    uint24_t &operator=(const char value) {
        return this->operator=(static_cast<int8_t>(value));
    }

public:
    template<typename _T>
    uint24_t &operator-=(_T value) {
        _union_ref().ui24 -= value;
        return *this;
    }

    template<typename _T>
    uint24_t &operator+=(_T value) {
        _union_ref().ui24 -= value;
        return *this;
    }

    template<typename _T>
    uint24_t &operator*=(_T value) {
        _union_ref().ui24 *= value;
        return *this;
    }

    template<typename _T>
    uint24_t &operator/=(_T value) {
        _union_ref().ui24 /= value;
        return *this;
    }

    template<typename _T>
    uint24_t &operator|=(_T value) {
        _union_ref().ui24 |= value;
        return *this;
    }

    template<typename _T>
    uint24_t &operator&=(_T value) {
        _union_ref().ui24 |= value;
        return *this;
    }

    template<typename _T>
    uint24_t &operator^=(_T value) {
        _union_ref().ui24 ^= value;
        return *this;
    }

    template<typename _T>
    uint24_t &operator%=(_T value) {
        _union_ref().ui24 %= value;
        return *this;
    }

    uint24_t &operator<<=(uint8_t value) {
        _union_ref().ui24 <<= static_cast<uint8_t>(value);
        return *this;
    }

    uint24_t &operator>>=(uint8_t value) {
        _union_ref().ui24 >>= value;
        return *this;
    }

    template<typename _T>
    uint24_t operator+(_T value) const {
        return _union_cref().ui24 + value;
    }

    template<typename _T>
    uint24_t operator-(_T value) const {
        return _union_cref().ui24 - value;
    }

    template<typename _T>
    uint32_t operator*(_T value) const {
        return __uint32() * value;
    }

    template<typename _T>
    uint24_t operator/(_T value) const {
        return _union_cref().ui24 / value;
    }

    template<typename _T>
    uint24_t operator<<(_T value) const {
        return _union_cref().ui24 << value;
    }

    template<typename _T>
    uint24_t operator>>(_T value) const {
        return _union_cref().ui24 >> value;
    }

public:
    uint64_t __uint64() const __attribute_always_inline__ {
        return static_cast<uint64_t>(*this);
    }

    uint32_t __uint32() const __attribute_always_inline__ {
        return static_cast<uint32_t>(*this);
    }

    uint16_t __uint16() const __attribute_always_inline__ {
        return static_cast<uint16_t>(*this);
    }

    uint8_t __uint8() const __attribute_always_inline__ {
        return static_cast<uint8_t>(*this);
    }

protected:
    const void *_ptr() const __attribute_always_inline__ {
        return static_cast<const void *>(&_lo);
    }
    void *_ptr() __attribute_always_inline__ {
        return static_cast<void *>(&_lo);
    }
    const int_union_t &_union_cref() const __attribute_always_inline__ {
        return *reinterpret_cast<const int_union_t *>(_ptr());
    }
    int_union_t &_union_ref() __attribute_always_inline__ {
        return *reinterpret_cast<int_union_t *>(_ptr());
    }

protected:
    uint8_t _lo;
    uint8_t _mid;
    uint8_t _hi;
};

class __attribute_packed__ int24_t: public uint24_t
{
public:
    using uint24_t::uint24_t;
    using uint24_t::operator=;
    using uint24_t::operator uint8_t;
    using uint24_t::operator int8_t;
    using uint24_t::operator char;
    using uint24_t::operator uint16_t;
    using uint24_t::operator int16_t;

    int24_t() = default;
    int24_t(int32_t value) __attribute_always_inline__ : uint24_t(static_cast<uint32_t>(value)) {}

    explicit operator uint32_t() const {
        if (_hi & 0x80) {
            return uint24_t::operator uint32_t() | static_cast<uint32_t>(0xff000000);
        }
        return uint24_t::operator uint32_t();
        //return static_cast<uint32_t>(_lo | (static_cast<uint16_t>(_mid) << 8) | (static_cast<uint32_t>(_hi) << 16) | (_hi & 0x80 ? (uint32_t)0xff000000 : 0));
    }

    operator int32_t() const __attribute_always_inline__ {
        return static_cast<uint32_t>(*this);
    }

    explicit operator uint64_t() const {
        register uint32_t tmp = uint24_t::operator uint32_t();
        if (_hi & 0x80) {
            return tmp | static_cast<uint64_t>(0xffffffffff000000);
        }
        return tmp;
        //return static_cast<uint64_t>(_lo | (static_cast<uint16_t>(_mid) << 8) | (static_cast<uint32_t>(_hi) << 16) | (_hi & 0x80 ? (uint64_t)0xffffffffff000000 : 0));
    }

    explicit operator int64_t() const __attribute_always_inline__ {
        return static_cast<uint64_t>(*this);
    }

public:
    int64_t ___int64() const __attribute_always_inline__ {
        return static_cast<int64_t>(*this);
    }

    int32_t ___int32() const __attribute_always_inline__ {
        return static_cast<int32_t>(*this);
    }

    int16_t ___int16() const __attribute_always_inline__ {
        return static_cast<int16_t>(*this);
    }

    int8_t ___int8() const __attribute_always_inline__ {
        return static_cast<int8_t>(*this);
    }
};

static_assert(sizeof(uint24_t) == 3 && sizeof(int24_t) == 3, "something went wrong");

inline __attribute_always_inline__ static uint24_t __uint24_from_ui16_ui8(const uint16_t hi, const uint8_t lo) {
    return uint24_t(hi, lo);
}

inline __attribute_always_inline__ static uint24_t __uint24_from_shr8_ui32(const uint32_t value) {
    return uint24_t(value >> 8, value >> 16, value >> 24);
}

#if _MSC_VER
#pragma pack(pop)
#endif

#endif
