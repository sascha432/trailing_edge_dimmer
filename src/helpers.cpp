/**
 * Author: sascha_lammers@gmx.de
 */

#include "helpers.h"

int Serial_printf(const char *format, ...) {
    char buf[64];
    char *temp = buf;
    va_list arg;
    va_start(arg, format);
    int len = vsnprintf(buf, sizeof(buf), format, arg);
    if (len >= (int)sizeof(buf) - 1) {
        temp = (char *)malloc(len + 2);
        if (!temp) {
            return 0;
        }
        len = vsnprintf(temp, len, format, arg);
    }
    if (len > 0) {
        Serial.write(reinterpret_cast<const char *>(temp), len);
    }
    if (temp != buf) {
        free(temp);
    }
    va_end(arg);
    return len;
}

int Serial_printf_P(PGM_P format, ...) {
    char buf[64];
    char *temp = buf;
    va_list arg;
    va_start(arg, format);
    int len = vsnprintf_P(buf, sizeof(buf), format, arg);
    if (len >= (int)sizeof(buf) - 1) {
        temp = (char *)malloc(len + 2);
        if (!temp) {
            return 0;
        }
        len = vsnprintf_P(temp, len, format, arg);
    }
    if (len > 0) {
        Serial.write(reinterpret_cast<const char *>(temp), len);
    }
    if (temp != buf) {
        free(temp);
    }
    va_end(arg);
    return len;
}

bool Serial_readLine(String &input, bool allowEmpty) {
    int ch;
    while (Serial.available()) {
        ch = Serial.read();
        if (ch == '\b') {
            input.remove(-1, 1);
            Serial.print(F("\b \b"));
        }
        else if (ch == '+') {
            input = "+";
            return true;
         } else if (ch == '-') {
            input = "-";
            return true;
        } else if (ch == 27) {
            Serial.write('\r');
            size_t count = input.length() + 1;
            while(count--) {
                Serial.write(' ');
            }
            Serial.write('\r');
            input = String();
        }
        else if (ch == '\r' || ch == -1) {
        }
        else if (ch == '\n') {
            if (input.length() != 0 || allowEmpty) { // ignore empty lines
                if (Serial.available() && Serial.peek() == '\r') { // CRLF, CR should already be gone...
                    Serial.read();
                }
                input += '\n';
                Serial.println();
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


#if DEBUG
uint8_t _debug_level = DEBUG_LEVEL;


// PrintExEx SerialEx = Serial;

// void PrintExEx::printf_P(PGM_P format, ...) {
// }

// void PrintExEx::vprintf(const char *format, ...) {
//     char buf[64];
//     size_t len;
//     va_list arg;
//     va_start(arg, format);
//     if ((len = vsnprintf(buf, sizeof(buf), format, arg)) == sizeof(buf)) {
//         char *ptr = (char *)malloc(len + 2);
//         if (ptr) {
//             vsnprintf(ptr, len, format, arg);
//             print(ptr);
//             free(ptr);
//         }
//     } else {
//         print(buf);
//     }
//     va_end(arg);
// }

// PrintExEx::PrintExEx(Stream &stream) : PrintEx(stream), _stream(stream) {
// }

// PrintExEx::~PrintExEx() {
// }

#endif
