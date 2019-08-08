/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <HardwareSerial.h>
#include <PrintEx.h>
#include "helpers.h"

#if DEBUG
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL   _D_INFO
#endif
#define _D_ALWAYS     0
#define _D_ERROR      1
#define _D_WARNING    2
#define _D_NOTICE     3
#define _D_INFO       5
#define _D_DEBUG      10
#define _D(level, ...) { if (_debug_level >= level) { __VA_ARGS__; }; }
#else
#define DEBUG_LEVEL   0
#define _D(...) ;
#endif

typedef unsigned long ulong;

#define STR(s)                  _STR(s)
#define _STR(s)                 #s

#define float_to_str(value)             (String(value).c_str())

#if DEBUG

class PrintExEx : public PrintEx {
public:
    PrintExEx(Stream &stream);
    virtual ~PrintExEx();

    bool readLine(String &input, bool allowEmpty = false);;

    String floatToString(double n, uint8_t prec, int8_t width);

    void printf_P(PGM_P format, ...);
    void vprintf(const char *format, ...);

private:
  Stream &_stream;
};

extern PrintExEx SerialEx;
extern uint8_t _debug_level;
#endif
