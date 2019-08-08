/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"

#if DEBUG
uint8_t _debug_level = DEBUG_LEVEL;
PrintExEx SerialEx = Serial;

void PrintExEx::printf_P(PGM_P format, ...) {
    char buf[64];
    size_t len;
    va_list arg;
    va_start(arg, format);
    if ((len = vsnprintf_P(buf, sizeof(buf), format, arg)) == sizeof(buf)) {
        char *ptr = (char *)malloc(len + 2);
        if (ptr) {
            vsnprintf_P(ptr, len, format, arg);
            SerialEx.print(ptr);
            free(ptr);
        }
    } else {
        SerialEx.print(buf);
    }
    va_end(arg);
}

void PrintExEx::vprintf(const char *format, ...) {
    char buf[64];
    size_t len;
    va_list arg;
    va_start(arg, format);
    if ((len = vsnprintf(buf, sizeof(buf), format, arg)) == sizeof(buf)) {
        char *ptr = (char *)malloc(len + 2);
        if (ptr) {
            vsnprintf(ptr, len, format, arg);
            print(ptr);
            free(ptr);
        }
    } else {
        print(buf);
    }
    va_end(arg);
}

PrintExEx::PrintExEx(Stream &stream) : PrintEx(stream), _stream(stream) {
}

PrintExEx::~PrintExEx() {
}

bool PrintExEx::readLine(String &input, bool allowEmpty) {
    int ch;
    while (_stream.available()) {
        ch = _stream.read();
        if (ch == '\b') {
            input.remove(-1, 1);
            print(F("\b \b"));
        }
        else if (ch == '+') {
            input = "+";
            return true;
         } else if (ch == '-') {
            input = "-";
            return true;
        } else if (ch == 27) {
            write('\r');
            repeat(' ', input.length() + 1);
            write('\r');
            input = String();
        }
        else if (ch == '\r' || ch == -1) {
        }
        else if (ch == '\n') {
            if (input.length() != 0 || allowEmpty) { // ignore empty lines
                if (_stream.available() && _stream.peek() == '\r') { // CRLF, CR should already be gone...
                    _stream.read();
                }
                input += '\n';
                println();
                return true;
            } else {
                if (allowEmpty ) {
                    return true;
                }
            }
        } else {
            input += (char)ch;
        }
    }
    return false;
}

#endif
