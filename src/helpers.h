/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <HardwareSerial.h>
#include "helpers.h"

#if DEBUG
extern uint8_t _debug_level;

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

int Serial_printf(const char *format, ...);
int Serial_printf_P(PGM_P format, ...);
bool Serial_readLine(String &input, bool allowEmpty);

typedef unsigned long ulong;

#define STR(s)                  _STR(s)
#define _STR(s)                 #s
