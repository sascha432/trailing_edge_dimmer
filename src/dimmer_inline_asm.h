// AUTO GENERATED FILE - DO NOT MODIFY
// MCU: ATmega328P
// zero crossing pin=PIND mask=0x08/b00001000
// port=PORTD mask=0x04 pin=2 mask=b00000100/0x04
// port=PORTD mask=0x10 pin=4 mask=b00010000/0x10
// port=PORTD mask=0x20 pin=5 mask=b00100000/0x20
// port=PORTD mask=0x40 pin=6 mask=b01000000/0x40
// port=PORTB mask=0x01 pin=0 mask=b00000001/0x01
// port=PORTB mask=0x02 pin=1 mask=b00000010/0x02
// port=PORTB mask=0x04 pin=2 mask=b00000100/0x04
// port=PORTB mask=0x08 pin=3 mask=b00001000/0x08
// port=PORTB mask=0x10 pin=4 mask=b00010000/0x10
// port=PORTB mask=0x20 pin=5 mask=b00100000/0x20
// port=PORTC mask=0x01 pin=0 mask=b00000001/0x01
// port=PORTC mask=0x02 pin=1 mask=b00000010/0x02
// port=PORTC mask=0x04 pin=2 mask=b00000100/0x04
// port=PORTC mask=0x08 pin=3 mask=b00001000/0x08
// port=PORTC mask=0x10 pin=4 mask=b00010000/0x10
// port=PORTC mask=0x20 pin=5 mask=b00100000/0x20

#pragma once
#include <avr/io.h>

#define DIMMER_SFR_ZC_STATE (PIND & 0x08)
#define DIMMER_SFR_ZC_IS_SET asm volatile ("sbis %0, %1" :: "I" ( _SFR_IO_ADDR(PIND)), "I" (3));
#define DIMMER_SFR_ZC_IS_CLR asm volatile ("sbic %0, %1" :: "I" ( _SFR_IO_ADDR(PIND)), "I" (3));
#define DIMMER_SFR_ZC_JMP_IF_SET(label) DIMMER_SFR_ZC_IS_CLR asm volatile("rjmp " # label);
#define DIMMER_SFR_ZC_JMP_IF_CLR(label) DIMMER_SFR_ZC_IS_SET asm volatile("rjmp " # label);

// all ports are read first, modified and written back to minimize the delay between toggling different ports (3 cycles, 187.5ns per port @16MHz)

#define DIMMER_SFR_ENABLE_ALL_CHANNELS() { uint8_t tmp[16] = { (uint8_t)(PORTD | 0x74), (uint8_t)(PORTD | 0x74), (uint8_t)(PORTD | 0x74), (uint8_t)(PORTD | 0x74), (uint8_t)(PORTB | 0x3f), (uint8_t)(PORTB | 0x3f), (uint8_t)(PORTB | 0x3f), (uint8_t)(PORTB | 0x3f), (uint8_t)(PORTB | 0x3f), (uint8_t)(PORTB | 0x3f), (uint8_t)(PORTC | 0x3f), (uint8_t)(PORTC | 0x3f), (uint8_t)(PORTC | 0x3f), (uint8_t)(PORTC | 0x3f), (uint8_t)(PORTC | 0x3f), (uint8_t)(PORTC | 0x3f) }; PORTD = tmp[0]; PORTD = tmp[1]; PORTD = tmp[2]; PORTD = tmp[3]; PORTB = tmp[4]; PORTB = tmp[5]; PORTB = tmp[6]; PORTB = tmp[7]; PORTB = tmp[8]; PORTB = tmp[9]; PORTC = tmp[10]; PORTC = tmp[11]; PORTC = tmp[12]; PORTC = tmp[13]; PORTC = tmp[14]; PORTC = tmp[15]; }
#define DIMMER_SFR_DISABLE_ALL_CHANNELS() { uint8_t tmp[16] = { (uint8_t)(PORTD & ~0x74), (uint8_t)(PORTD & ~0x74), (uint8_t)(PORTD & ~0x74), (uint8_t)(PORTD & ~0x74), (uint8_t)(PORTB & ~0x3f), (uint8_t)(PORTB & ~0x3f), (uint8_t)(PORTB & ~0x3f), (uint8_t)(PORTB & ~0x3f), (uint8_t)(PORTB & ~0x3f), (uint8_t)(PORTB & ~0x3f), (uint8_t)(PORTC & ~0x3f), (uint8_t)(PORTC & ~0x3f), (uint8_t)(PORTC & ~0x3f), (uint8_t)(PORTC & ~0x3f), (uint8_t)(PORTC & ~0x3f), (uint8_t)(PORTC & ~0x3f) }; PORTD = tmp[0]; PORTD = tmp[1]; PORTD = tmp[2]; PORTD = tmp[3]; PORTB = tmp[4]; PORTB = tmp[5]; PORTB = tmp[6]; PORTB = tmp[7]; PORTB = tmp[8]; PORTB = tmp[9]; PORTC = tmp[10]; PORTC = tmp[11]; PORTC = tmp[12]; PORTC = tmp[13]; PORTC = tmp[14]; PORTC = tmp[15]; }
#define DIMMER_SFR_CHANNELS_SET_BITS(mask) { uint8_t tmp[16] = { (uint8_t)(PORTD | mask[0]), (uint8_t)(PORTD | mask[1]), (uint8_t)(PORTD | mask[2]), (uint8_t)(PORTD | mask[3]), (uint8_t)(PORTB | mask[4]), (uint8_t)(PORTB | mask[5]), (uint8_t)(PORTB | mask[6]), (uint8_t)(PORTB | mask[7]), (uint8_t)(PORTB | mask[8]), (uint8_t)(PORTB | mask[9]), (uint8_t)(PORTC | mask[10]), (uint8_t)(PORTC | mask[11]), (uint8_t)(PORTC | mask[12]), (uint8_t)(PORTC | mask[13]), (uint8_t)(PORTC | mask[14]), (uint8_t)(PORTC | mask[15]) }; PORTD = tmp[0]; PORTD = tmp[1]; PORTD = tmp[2]; PORTD = tmp[3]; PORTB = tmp[4]; PORTB = tmp[5]; PORTB = tmp[6]; PORTB = tmp[7]; PORTB = tmp[8]; PORTB = tmp[9]; PORTC = tmp[10]; PORTC = tmp[11]; PORTC = tmp[12]; PORTC = tmp[13]; PORTC = tmp[14]; PORTC = tmp[15]; }
#define DIMMER_SFR_CHANNELS_CLR_BITS(mask) { uint8_t tmp[16] = { (uint8_t)(PORTD & ~mask[0]), (uint8_t)(PORTD & ~mask[1]), (uint8_t)(PORTD & ~mask[2]), (uint8_t)(PORTD & ~mask[3]), (uint8_t)(PORTB & ~mask[4]), (uint8_t)(PORTB & ~mask[5]), (uint8_t)(PORTB & ~mask[6]), (uint8_t)(PORTB & ~mask[7]), (uint8_t)(PORTB & ~mask[8]), (uint8_t)(PORTB & ~mask[9]), (uint8_t)(PORTC & ~mask[10]), (uint8_t)(PORTC & ~mask[11]), (uint8_t)(PORTC & ~mask[12]), (uint8_t)(PORTC & ~mask[13]), (uint8_t)(PORTC & ~mask[14]), (uint8_t)(PORTC & ~mask[15]) }; PORTD = tmp[0]; PORTD = tmp[1]; PORTD = tmp[2]; PORTD = tmp[3]; PORTB = tmp[4]; PORTB = tmp[5]; PORTB = tmp[6]; PORTB = tmp[7]; PORTB = tmp[8]; PORTB = tmp[9]; PORTC = tmp[10]; PORTC = tmp[11]; PORTC = tmp[12]; PORTC = tmp[13]; PORTC = tmp[14]; PORTC = tmp[15]; }

#define DIMMER_SFR_CHANNELS_ENABLE(channel) switch(channel) { default: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (2)); break; case 1: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (4)); break; case 2: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (5)); break; case 3: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6)); break; case 4: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (0)); break; case 5: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (1)); break; case 6: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (2)); break; case 7: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (3)); break; case 8: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (4)); break; case 9: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (5)); break; case 10: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (0)); break; case 11: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (1)); break; case 12: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (2)); break; case 13: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (3)); break; case 14: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (4)); break; case 15: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (5)); }
#define DIMMER_SFR_CHANNELS_DISABLE(channel) switch(channel) { default: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (2)); break; case 1: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (4)); break; case 2: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (5)); break; case 3: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6)); break; case 4: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (0)); break; case 5: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (1)); break; case 6: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (2)); break; case 7: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (3)); break; case 8: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (4)); break; case 9: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (5)); break; case 10: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (0)); break; case 11: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (1)); break; case 12: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (2)); break; case 13: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (3)); break; case 14: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (4)); break; case 15: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTC)), "I" (5)); }

// verify signature during compilation
static constexpr uint8_t kInlineAssemblerSignature[] = { 0x1e, 0x95, 0x0f, 0x02, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13 }; // MCU ATmega328P (1e-95-0f)

