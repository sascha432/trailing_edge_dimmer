/**
 * Author: sascha_lammers@gmx.de
 */

#include "dimmer.h"

#if HAVE_READ_INT_TEMP

float get_internal_temperature();

#if __AVR_ATmega328P__ && MCU_IS_ATMEGA328PB == 0

internal_temp_calibration_t atmega328p_read_ts_values();

#endif

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
