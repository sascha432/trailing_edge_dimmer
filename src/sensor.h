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

uint16_t read_vcc_int();
uint16_t read_vcc();

#elif HAVE_READ_VCC

uint16_t read_vcc_int();
#define read_vcc()                          read_vcc_int()

#endif

#if HAVE_NTC
float get_ntc_temperature();
#endif

#if HAVE_POTI
extern uint16_t raw_poti_value;
int32_t read_poti();
#endif
