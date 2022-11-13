// AUTO GENERATED FILE - DO NOT MODIFY
// MCU: ATmega328P
// zero crossing pin=PIND mask=0x08/b00001000
// port=PORTD mask=0x40 pin=6 mask=b01000000/0x40
// port=PORTB mask=0x01 pin=0 mask=b00000001/0x01
// port=PORTB mask=0x02 pin=1 mask=b00000010/0x02
// port=PORTB mask=0x04 pin=2 mask=b00000100/0x04

#pragma once
#include <avr/io.h>

#define DIMMER_SFR_ZC_STATE (PIND & 0x08)
#define DIMMER_SFR_ZC_IS_SET asm volatile ("sbis %0, %1" :: "I" ( _SFR_IO_ADDR(PIND)), "I" (3));
#define DIMMER_SFR_ZC_IS_CLR asm volatile ("sbic %0, %1" :: "I" ( _SFR_IO_ADDR(PIND)), "I" (3));
#define DIMMER_SFR_ZC_JMP_IF_SET(label) DIMMER_SFR_ZC_IS_CLR asm volatile("rjmp " # label);
#define DIMMER_SFR_ZC_JMP_IF_CLR(label) DIMMER_SFR_ZC_IS_SET asm volatile("rjmp " # label);

// all ports are read first, modified and written back to minimize the delay between toggling different ports (3 cycles, 187.5ns per port @16MHz)

#define DIMMER_SFR_ENABLE_ALL_CHANNELS() { uint8_t tmp[4] = { (uint8_t)(PORTD | 0x40), (uint8_t)(PORTB | 0x07), (uint8_t)(PORTB | 0x07), (uint8_t)(PORTB | 0x07) }; PORTD = tmp[0]; PORTB = tmp[1]; PORTB = tmp[2]; PORTB = tmp[3]; }
#define DIMMER_SFR_DISABLE_ALL_CHANNELS() { uint8_t tmp[4] = { (uint8_t)(PORTD & ~0x40), (uint8_t)(PORTB & ~0x07), (uint8_t)(PORTB & ~0x07), (uint8_t)(PORTB & ~0x07) }; PORTD = tmp[0]; PORTB = tmp[1]; PORTB = tmp[2]; PORTB = tmp[3]; }
#define DIMMER_SFR_CHANNELS_SET_BITS(mask) { uint8_t tmp[4] = { (uint8_t)(PORTD | mask[0]), (uint8_t)(PORTB | mask[1]), (uint8_t)(PORTB | mask[2]), (uint8_t)(PORTB | mask[3]) }; PORTD = tmp[0]; PORTB = tmp[1]; PORTB = tmp[2]; PORTB = tmp[3]; }
#define DIMMER_SFR_CHANNELS_CLR_BITS(mask) { uint8_t tmp[4] = { (uint8_t)(PORTD & ~mask[0]), (uint8_t)(PORTB & ~mask[1]), (uint8_t)(PORTB & ~mask[2]), (uint8_t)(PORTB & ~mask[3]) }; PORTD = tmp[0]; PORTB = tmp[1]; PORTB = tmp[2]; PORTB = tmp[3]; }

#define DIMMER_SFR_CHANNELS_ENABLE(channel) switch(channel) { default: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6)); break; case 1: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (0)); break; case 2: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (1)); break; case 3: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (2)); }
#define DIMMER_SFR_CHANNELS_DISABLE(channel) switch(channel) { default: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6)); break; case 1: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (0)); break; case 2: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (1)); break; case 3: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (2)); }

// verify signature during compilation
static constexpr uint8_t kInlineAssemblerSignature[] = { 0x1e, 0x95, 0x0f, 0x06, 0x08, 0x09, 0x0a }; // MCU ATmega328P (1e-95-0f)

