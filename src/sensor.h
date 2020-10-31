/**
 * Author: sascha_lammers@gmx.de
 */

#include "dimmer.h"

#if HAVE_READ_INT_TEMP

extern bool is_Atmega328PB;
#define setAtmega328PB(value)               is_Atmega328PB = value;
float get_internal_temperature();

#else

#define setAtmega328PB(value)               ;

#endif

#if HAVE_EXT_VCC

uint16_t read_vcc();

#elif HAVE_READ_VCC

uint16_t read_vcc();

#else

static inline uint16_t read_vcc() {
    return 0;
}

#endif

#if HAVE_NTC

float get_ntc_temperature();

#endif

#if HAVE_POTI

uint16_t read_poti();

#endif
