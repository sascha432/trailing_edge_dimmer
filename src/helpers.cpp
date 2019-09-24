/**
 * Author: sascha_lammers@gmx.de
 */

#include <avr/boot.h>
#include "helpers.h"

// returns number of digits without trailing zeros after determining max. precision
int count_decimals(double value, uint8_t max_precision, uint8_t max_decimals) {
    auto precision = max_precision;
    auto number = abs(value);
    if (number < 1) {
        while ((number = (number * 10)) < 1 && precision < max_decimals) { // increase precision for decimals
            precision++;
        }
    }
    else {
        while ((number = (number / 10)) > 1 && precision > 1) { // reduce precision for decimals
            precision--;
        }
    }
    char format[8];
    snprintf_P(format, sizeof(format), PSTR("%%.%uf"), precision);
    char buf[32];
    auto len = snprintf(buf, sizeof(buf), format, value);
    char *ptr;
    if (len < (int)sizeof(buf) && (ptr = strchr(buf, '.'))) {
        ptr++;
        char *endPtr = ptr + strlen(ptr);
        while(--endPtr > ptr && *endPtr == '0') { // remove trailing zeros
            *endPtr = 0;
            precision--;
        }
    }
    else {
        precision = max_decimals; // buffer to small
    }
    return precision;
}

int Serial_print_float(double value, uint8_t max_precision, uint8_t max_decimals) {
    return Serial.print(value, count_decimals(value, max_precision, max_decimals));
}


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

/*
ATmega1280      1e9703
ATmega1281      1e9704
ATmega1284P     1e9705
ATmega1284      1e9706
ATmega128A      1e9702
ATmega128RFA1   1ea701
ATmega128       1e9702
ATmega162       1e9404
ATmega164A      1e940f
ATmega164PA     1e940a
ATmega164P      1e940a
ATmega165A      1e9410
ATmega165PA     1e9407
ATmega165P      1e9407
ATmega168A      1e9406
ATmega168PA     1e940b
ATmega168P      1e940b
ATmega168       1e9406
ATmega169A      1e9411
ATmega169PA     1e9405
ATmega169P      1e9405
ATmega16A       1e9403
ATmega16HVB     1e940d
ATmega16M1      1e9484
ATmega16U2      1e9489
ATmega16U4      1e9488
ATmega16        1e9403
ATmega2560      1e9801
ATmega2561      1e9802
ATmega324A      1e9515
ATmega324PA     1e9511
ATmega324P      1e9508
ATmega3250A     1e9506
ATmega3250PA    1e950e
ATmega3250P     1e950e
ATmega3250      1e9506
ATmega325A      1e9505
ATmega325PA     1e950d
ATmega325P      1e950d
ATmega325       1e9505
ATmega328P      1e950f
ATmega328       1e9514
ATmega3290A     1e9504
ATmega3290PA    1e950c
ATmega3290P     1e950c
ATmega3290      1e9504
ATmega329A      1e9503
ATmega329PA     1e950b
ATmega329P      1e950b
ATmega329       1e9503
ATmega32A       1e9502
ATmega32C1      1e9586
ATmega32HVB     1e9510
ATmega32M1      1e9584
ATmega32U2      1e958a
ATmega32U4      1e9587
ATmega32        1e9502
ATmega48A       1e9205
ATmega48PA      1e920a
ATmega48P       1e920a
ATmega48        1e9205
ATmega640       1e9608
ATmega644A      1e9609
ATmega644PA     1e960a
ATmega644P      1e960a
ATmega644       1e9609
ATmega6450A     1e9606
ATmega6450P     1e960e
ATmega6450      1e9606
ATmega645A      1e9605
ATmega645P      1e960D
ATmega645       1e9605
ATmega6490A     1e9604
ATmega6490P     1e960C
ATmega6490      1e9604
ATmega649A      1e9603
ATmega649P      1e960b
ATmega649       1e9603
ATmega64A       1e9602
ATmega64C1      1e9686
ATmega64M1      1e9684
ATmega64        1e9602
ATmega8515      1e9306
ATmega8535      1e9308
ATmega88A       1e930a
ATmega88PA      1e930f
ATmega88P       1e930f
ATmega88        1e930a
ATmega8A        1e9307
ATmega8U2       1e9389
ATmega8         1e9307
*/

uint8_t *get_signature(uint8_t *sig) {
    auto ptr = sig;
    *ptr++ = boot_signature_byte_get(0);
    *ptr++ = boot_signature_byte_get(2);
    *ptr++ = boot_signature_byte_get(4);
    return sig;
}

unique_ptr<uint8_t> get_mcu_type(char *&mcu, uint8_t *&sig, uint8_t *&fuses) {
    const size_t mcu_size = 17;
    auto buffer = new uint8_t[3 + 3 + mcu_size + 1];
    auto ptr = buffer;

    sig = ptr;
    ptr = get_signature(ptr) + 3;

    fuses = ptr;
    *ptr++ = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
    *ptr++ = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
    *ptr++ = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);

    mcu = reinterpret_cast<char *>(ptr);
    *mcu = 0;
    *(mcu + mcu_size) = 0;

    if (sig[0] == 0x1e) {
        if (sig[1] == 0x93) {
            switch(sig[2]) {
                case 0x0a:
                    strncpy_P(mcu, PSTR("ATmega88"), mcu_size);
                    break;
                case 0x0f:
                    strncpy_P(mcu, PSTR("ATmega88P"), mcu_size);
                    break;
            }
        }
        else if (sig[1] == 0x95) {
            switch(sig[2]) {
                case 0x02:
                    strncpy_P(mcu, PSTR("ATmega32"), mcu_size);
                    break;
                case 0x0f:
                    strncpy_P(mcu, PSTR("ATmega328P"), mcu_size);
                    break;
                case 0x14:
                    strncpy_P(mcu, PSTR("ATmega328-PU"), mcu_size);
                    break;
                case 0x16:
                    strncpy_P(mcu, PSTR("ATmega328PB"), mcu_size);
                    break;
            }
        }
    }

    return unique_ptr<uint8_t>(buffer);
}

#if DEBUG
uint8_t _debug_level = DEBUG_LEVEL;

void debug_print_millis() {
    Serial_printf_P(PSTR("+DBG%05lu: "), millis());
}

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
