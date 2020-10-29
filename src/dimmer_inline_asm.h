// AUTO GENERATED FILE - DO NOT MODIFY
// MCU: ATmega328P
// port=PORTB mask=0x02 pin=1 mask=b00000010/0x02
// port=PORTD mask=0x40 pin=6 mask=b01000000/0x40

#pragma once
#include <avr/io.h>

// all ports are read first, modified and written back to minimize the delay between toggling different ports (3 cycles, 187.5ns per port @16MHz)

#define DIMMER_SFR_ENABLE_ALL_CHANNELS() { uint8_t tmp[2] = { (uint8_t)(PORTB | 0x02), (uint8_t)(PORTD | 0x40) }; PORTB = tmp[0]; PORTD = tmp[1]; }
#define DIMMER_SFR_DISABLE_ALL_CHANNELS() { uint8_t tmp[2] = { (uint8_t)(PORTB & ~0x02), (uint8_t)(PORTD & ~0x40) }; PORTB = tmp[0]; PORTD = tmp[1]; }
#define DIMMER_SFR_CHANNELS_SET_BITS(mask) { uint8_t tmp[2] = { (uint8_t)(PORTB | mask[0]), (uint8_t)(PORTD | mask[1]) }; PORTB = tmp[0]; PORTD = tmp[1]; }
#define DIMMER_SFR_CHANNELS_CLR_BITS(mask) { uint8_t tmp[2] = { (uint8_t)(PORTB & ~mask[0]), (uint8_t)(PORTD & ~mask[1]) }; PORTB = tmp[0]; PORTD = tmp[1]; }

#define DIMMER_SFR_CHANNELS_ENABLE(channel) switch(channel) { default: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (1)); break; case 1: asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6)); }
#define DIMMER_SFR_CHANNELS_DISABLE(channel) switch(channel) { default: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTB)), "I" (1)); break; case 1: asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6)); }

// verify signature during compliation
static constexpr uint8_t kInlineAssemblerSignature[] = { 0x1e, 0x95, 0x0f, 0x09, 0x06 }; // MCU ATmega328P (1e-95-0f)

