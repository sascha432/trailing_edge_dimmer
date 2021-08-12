// AUTO GENERATED FILE - DO NOT MODIFY
// MCU: ATmega328P
// port=PORTD mask=0x40 pin=6 mask=b01000000/0x40

#pragma once
#include <avr/io.h>

// all ports are read first, modified and written back to minimize the delay between toggling different ports (3 cycles, 187.5ns per port @16MHz)

#define DIMMER_SFR_ENABLE_ALL_CHANNELS() { PORTD |= 0x40; }
#define DIMMER_SFR_DISABLE_ALL_CHANNELS() { PORTD &= ~0x40; }
#define DIMMER_SFR_CHANNELS_SET_BITS(mask) { PORTD |= mask; }
#define DIMMER_SFR_CHANNELS_CLR_BITS(mask) { PORTD &= ~mask; }

#define DIMMER_SFR_CHANNELS_ENABLE(channel) asm volatile ("sbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6))
#define DIMMER_SFR_CHANNELS_DISABLE(channel) asm volatile ("cbi %0, %1" :: "I" ( _SFR_IO_ADDR(PORTD)), "I" (6))

// verify signature during compliation
static constexpr uint8_t kInlineAssemblerSignature[] = { 0x1e, 0x95, 0x0f, 0x06 }; // MCU ATmega328P (1e-95-0f)

