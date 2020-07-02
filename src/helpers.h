/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <float.h>
#include <HardwareSerial.h>
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
#define debug_printf_P(...)     { debug_print_millis(); Serial_printf_P(__VA_ARGS__); }
#define debug_printf(...)       { debug_print_millis(); Serial_printf(__VA_ARGS__); }
#else
#define DEBUG_LEVEL   0
#define _D(...) ;
#define debug_printf_P(...)
#define debug_printf(...)
#endif

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

typedef struct {
    uint8_t sig[3];
    uint8_t fuses[3];
    char name[17];
} MCUInfo_t;

uint8_t *get_signature(uint8_t *sig);
void get_mcu_type(MCUInfo_t &info);

// println + flush
void Serial_println(const char *str);
void Serial_println(const __FlashStringHelper *str);

int Serial_printf(const char *format, ...);
int Serial_printf_P(PGM_P format, ...);
bool Serial_readLine(String &input, bool allowEmpty);
int Serial_print_float(double value, uint8_t max_precision = FLT_DIG, uint8_t max_decimals = 8);
int count_decimals(double value, uint8_t max_precision = FLT_DIG, uint8_t max_decimals = 8);

template <typename T>
inline void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
};
