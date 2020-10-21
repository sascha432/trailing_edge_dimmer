/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <float.h>
#include <HardwareSerial.h>
#include "helpers.h"

int assert_failed();

#if DEBUG

extern uint8_t _debug_level;

void debug_print_millis();

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL                         _D_INFO
#endif
#define _D_ALWAYS                           0
#define _D_ERROR                            1
#define _D_WARNING                          2
#define _D_NOTICE                           3
#define _D_INFO                             5
#define _D_DEBUG                            10

void __debug_print_memory(void *ptr, size_t size);
void __debug_printf(const char *format, ...);

static inline void __debug_printf_i(uint16_t interval, const char *format, ...) {
    static uint32_t counter;
    if ((millis() / interval) && (counter++ % 2 == 0)) {
        debug_print_millis();
        va_list arg;
        va_start(arg, format);
        Serial.__printf(vsnprintf_P, format, arg);
        Serial.flush();
        va_end(arg);
    }
}

#define _D(level, ...)                      { if (_debug_level >= level) { __VA_ARGS__; }; }
#define debug_printf(fmt, ...)              __debug_printf(PSTR(fmt), ##__VA_ARGS__);
#define debug_print_memory(ptr, size)       __debug_print_memory(ptr, size)
#define debug_printf_i(interval, fmt, ...)  __debug_printf_i(interval, PSTR(fmt), ##__VA_ARGS__);
#else
#define DEBUG_LEVEL   0
#define _D(...) ;
#define debug_printf(...)
#define debug_print_memory(ptr, size)
#define debug_printf_i(interval, fmt, ...)
#endif

#ifdef NDEBUG
#define _ASSERTE(cond)
#define _ASSERT_EXPR(cond, expr, ...)
#elif DEBUG
#define _ASSERTE(cond)                      ( (!(cond)) ? []{ abort(); return 1; }() : 0 )
#define _ASSERT_EXPR(cond, expr, ...)       ( (!(cond)) ? Serial.printf_P(PSTR(expr), _STRINGIFY(cond), ##__VA_ARGS__) + assert_failed() : 0 )
#else
#define _ASSERTE(cond)                      ( (!(cond)) ? assert_failed() : 0 )
#define _ASSERT_EXPR(cond, expr, ...)       ( (!(cond)) ? debug_printf(expr, _STRINGIFY(cond), ##__VA_ARGS__) + assert_failed() : 0 )
#endif



template< typename T > class unique_ptr
{
public:
    using pointer = T*;
    unique_ptr() noexcept : ptr(nullptr) {}
    unique_ptr(pointer p) : ptr(p) {}
    pointer operator->() const noexcept { return ptr; }
    T& operator[](decltype(sizeof(0)) i) const { return ptr[i]; }
    void reset(pointer p = pointer()) noexcept
    {
        delete ptr;
        ptr = p;
    }
    T& operator*() const { return *ptr; }
private:
    pointer ptr;
};

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


// framework-arduino-avr\cores\arduino\Print.h
// add
// class Print {
//...
// private:
//     friend void __debug_printf(const char *format, ...);
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


bool Serial_readLine(String &input, bool allowEmpty);

typedef unsigned long ulong;

// #define STR(s)                                  _STR(s)
// #define _STR(s)                                 #s

#define REP_NUL_2X                              "\0\0"
#define REP_NUL_4X                              REP_NUL_2X REP_NUL_2X
#define REP_NUL_8X                              REP_NUL_4X REP_NUL_4X
#define REP_NUL_16X                             REP_NUL_8X REP_NUL_8X
#define REP_NUL_32X                             REP_NUL_16X REP_NUL_16X
#define REP_NUL_64X                             REP_NUL_32X REP_NUL_32X
#define REP_NUL_256X                            REP_NUL_64X REP_NUL_64X REP_NUL_64X REP_NUL_64X

#ifndef _STRINGIFY
#define _STRINGIFY(...)                         ___STRINGIFY(__VA_ARGS__)
#endif
#define ___STRINGIFY(...)                       #__VA_ARGS__

#ifndef FPSTR
#define FPSTR(str)                              reinterpret_cast<const __FlashStringHelper *>(PSTR(str))
#endif

template<typename ..._Args>
static inline constexpr const size_t size_of(_Args&&...args) {
    return sizeof...(args);
};
