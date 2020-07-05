/**
 * Author: sascha_lammers@gmx.de
 */

#include <avr/boot.h>
#include <stddef.h>
#include "helpers.h"
#include "main.h"

extern unsigned int __heap_start;
extern void *__brkval;

unsigned int stackAvailable()
{
    unsigned int v;
    return (unsigned int)&v - (__brkval == 0 ? (unsigned int)&__heap_start : (unsigned int)__brkval);
}

struct __freelist
{
  size_t sz;
  struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

/* Calculates the size of the free list */
int freeListSize()
{
  struct __freelist* current;
  int total = 0;
  for (current = __flp; current; current = current->nx)
  {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }

  return total;
}

int freeMemory()
{
  int free_memory;
  if ((int)__brkval == 0)
  {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  }
  else
  {
    free_memory = ((int)&free_memory) - ((int)__brkval);
    free_memory += freeListSize();
  }
  return free_memory;
}

size_t Print::__printf(vsnprint_t func, const char *format, va_list arg)
{
    char buf[64];
    char *temp = buf;
    int len = func(buf, sizeof(buf), format, arg);
    if (len >= (int)sizeof(buf) - 1) {
        temp = (char *)malloc(len + 2);
        DEBUG_VALIDATE_ALLOC(temp, len + 2);
        if (!temp) {
            return 0;
        }
        len = func(temp, len, format, arg);
    }
    write(reinterpret_cast<const uint8_t *>(temp), len);
    if (temp != buf) {
        free(temp);
    }
    return len;
}

size_t Print::printf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    size_t result = __printf( vsnprintf, format, arg);
    va_end(arg);
    return result;
}

size_t Print::printf_P(PGM_P format, ...)
{
    va_list arg;
    va_start(arg, format);
    size_t result = __printf(vsnprintf_P, format, arg);
    va_end(arg);
    return result;
}

#if DEBUG_REPORT_ERRORS

const char PSTR_debug_error_alloc[] PROGMEM = "alloc failed, size %u";
const char PSTR_debug_i2c_invalid_address[] PROGMEM = "i2c invalid addr. 0x%02x";

void debug_report_error(PGM_P format, ...)
{
    char buf[64];
    va_list arg;
    va_start(arg, format);
    vsnprintf_P(buf, sizeof(buf), format, arg);
    va_end(arg);
    Serial.print(F("+REM=ERROR:"));
    Serial.println(buf);
}

#endif

uint8_t bitValue2Bit(uint8_t mask)
{
    for(uint8_t i = 0; i < 8; i++) {
        if (_BV(i) == mask) {
            return i;
        }
    }
    return 0xff;
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

uint8_t *get_signature(uint8_t *sig)
{
    auto ptr = sig;
    *ptr++ = boot_signature_byte_get(0);
    *ptr++ = boot_signature_byte_get(2);
    *ptr++ = boot_signature_byte_get(4);
    return sig;
}

extern bool is_Atmega328PB;

void get_mcu_type(MCUInfo_t &info)
{
    get_signature(info.sig);

    auto ptr = info.fuses;
    *ptr++ = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
    *ptr++ = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
    *ptr++ = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);

#if __AVR_ATmega328PB__

    info.name = FPSTR("ATmega328PB");
    setAtmega328PB(true);

#elif __AVR_ATmega328P__

    if (info.sig[2] == 0x16) {
        info.name = FPSTR("ATmega328PB");
        setAtmega328PB(true);
    }
    else {
        info.name = FPSTR("ATmega328P");
    }

#elif __AVR_ATmega2560__

    info.name = FPSTR("ATmega2560");

#else

    info.name = nullptr;
    if (info.sig[0] == 0x1e) {
        if (info.sig[1] == 0x98) {
            switch(info.sig[2]) {
                case 0x01:
                    info.name = FPSTR("ATmega2560");
                    break;
            }
        }
        else if (info.sig[1] == 0x95) {
            switch(info.sig[2]) {
                case 0x02:
                     info.name = FPSTR("ATmega32");
                     break;
                case 0x0f:
                    info.name = FPSTR("ATmega328P");
                    break;
                case 0x14:
                    info.name = FPSTR("ATmega328-PU");
                    break;
                case 0x16:
                    info.name = FPSTR("ATmega328PB");
                    setAtmega328PB(true);
                    break;
            }
        }
    }
#endif

}
