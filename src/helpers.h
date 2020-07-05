/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <stdio.h>
#include "helpers.h"

#if DEBUG
extern uint8_t _debug_level;
void debug_print_millis();

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL   _D_INFO
#endif
#define _D_ALWAYS     0
#define _D_ERROR      1
#define _D_WARNING    2
#define _D_NOTICE     3
#define _D_INFO       5
#define _D_DEBUG      10
#define _D(level, ...)          { if (_debug_level >= level) { __VA_ARGS__; }; }
#define debug_printf_P(...)     { debug_print_millis(); Serial.printf_P(__VA_ARGS__); }
#define debug_printf(...)       { debug_print_millis(); Serial.printf(__VA_ARGS__); }
#else
#define DEBUG_LEVEL   0
#define _D(...) ;
#define debug_printf_P(...)
#define debug_printf(...)
#endif

#ifndef DEBUG_REPORT_ERRORS
#define DEBUG_REPORT_ERRORS                                 0
#endif

#if DEBUG_REPORT_ERRORS

extern const char PSTR_debug_error_alloc[] PROGMEM;
extern const char PSTR_debug_i2c_invalid_address[] PROGMEM;

void debug_report_error(PGM_P format, ...);

#define DEBUG_VALIDATE_ALLOC(ptr, size)                     if (!ptr) { debug_report_error(PSTR_debug_error_alloc, size); }
#define DEBUG_INVALID_I2C_ADDRESS(addr)                     debug_report_error(PSTR_debug_i2c_invalid_address, addr)
#else
#define DEBUG_VALIDATE_ALLOC(...)                           ;
#define DEBUG_INVALID_I2C_ADDRESS(...)                      ;
#define
#endif

namespace std {

    template <class T>
    struct remove_pointer {
        using type = T;

    };

    template <class T>
    struct remove_pointer<T *> {
        using type = T;
    };

    template <class T>
    struct remove_pointer<T * const> {
        using type = T;
    };

};


template <class T>
class unique_ptr {
public:
    typedef T* T_ptr_t;

    constexpr unique_ptr() : _ptr(nullptr) {
    }
    constexpr unique_ptr(nullptr_t) : _ptr(nullptr) {
    }
    explicit unique_ptr(T_ptr_t ptr) : _ptr(ptr) {
    }
    ~unique_ptr() {
        _delete();
    }
    inline unique_ptr &operator=(nullptr_t) {
        reset(nullptr);
        return *this;
    }
    inline T_ptr_t operator *() const {
        return _ptr;
    }
    inline T_ptr_t operator ->() const {
        return _ptr;
    }
    inline operator bool() const {
        return _ptr != nullptr;
    }
    inline T_ptr_t get() const {
        return _ptr;
    }
    inline void reset(nullptr_t = nullptr) {
        _delete();
    }
    void reset(T_ptr_t ptr) {
        _delete();
        _ptr = ptr;
    }
    T_ptr_t release() {
        auto ptr = _ptr;
        _ptr = nullptr;
        return ptr;
    }
    void swap(T_ptr_t &ptr) {
        auto tmp_ptr = ptr;
        ptr = _ptr;
        _ptr = tmp_ptr;
    }
private:
    void _delete() {
        if (_ptr) {
            delete _ptr;
            _ptr = nullptr;
        }
    }
    T_ptr_t _ptr;
};

// reverse _BV(), convert mask to bit, designed for a single bit and returns 0xff if multiple or none are set
#define _BV2B(mask)             bitValue2Bit(mask)

uint8_t bitValue2Bit(uint8_t mask);

#ifndef FPSTR
#define FPSTR(str)                              reinterpret_cast<const __FlashStringHelper *>(PSTR(str))
#endif

typedef struct {
    uint8_t sig[3];
    uint8_t fuses[3];
    const __FlashStringHelper *name;
} MCUInfo_t;

uint8_t *get_signature(uint8_t *sig);
void get_mcu_type(MCUInfo_t &info);

unsigned int stackAvailable();
int freeMemory();


// framework-arduino-avr\cores\arduino\Print.h
// add
// class Print {
//...
// private:
//     typedef int (* vsnprint_t)(char *, size_t, const char *, va_list ap);
//     size_t __printf(vsnprint_t func, const char *format, va_list arg);
// public:
//     size_t printf(const char *format, ...);
//     size_t printf_P(PGM_P format, ...);
// };

template <typename T>
inline void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
};
