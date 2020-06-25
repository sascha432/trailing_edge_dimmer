// AUTO GENERATED FILE - DO NOT MODIFY
// MCU: ATmega328P
// Channels: D4=PORTD:4,D5=PORTD:5,D6=PORTD:6,D7=PORTD:7,D9=PORTB:1,D10=PORTB:2,D11=PORTB:3,A3=PORTC:3
#pragma once
#include <avr/io.h>

#define DIMMER_CHANNEL0_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTD)
#define DIMMER_CHANNEL0_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTD)
#define DIMMER_CHANNEL0_BIT                             4
#define DIMMER_CHANNEL0_BIT_MASK                        _BV(DIMMER_CHANNEL0_BIT)
#define DIMMER_CHANNEL0_PORT_NUMBER                     0
#define DIMMER_CHANNEL1_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTD)
#define DIMMER_CHANNEL1_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTD)
#define DIMMER_CHANNEL1_BIT                             5
#define DIMMER_CHANNEL1_BIT_MASK                        _BV(DIMMER_CHANNEL1_BIT)
#define DIMMER_CHANNEL1_PORT_NUMBER                     0
#define DIMMER_CHANNEL2_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTD)
#define DIMMER_CHANNEL2_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTD)
#define DIMMER_CHANNEL2_BIT                             6
#define DIMMER_CHANNEL2_BIT_MASK                        _BV(DIMMER_CHANNEL2_BIT)
#define DIMMER_CHANNEL2_PORT_NUMBER                     0
#define DIMMER_CHANNEL3_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTD)
#define DIMMER_CHANNEL3_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTD)
#define DIMMER_CHANNEL3_BIT                             7
#define DIMMER_CHANNEL3_BIT_MASK                        _BV(DIMMER_CHANNEL3_BIT)
#define DIMMER_CHANNEL3_PORT_NUMBER                     0
#define DIMMER_CHANNEL4_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTB)
#define DIMMER_CHANNEL4_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTB)
#define DIMMER_CHANNEL4_BIT                             1
#define DIMMER_CHANNEL4_BIT_MASK                        _BV(DIMMER_CHANNEL4_BIT)
#define DIMMER_CHANNEL4_PORT_NUMBER                     1
#define DIMMER_CHANNEL5_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTB)
#define DIMMER_CHANNEL5_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTB)
#define DIMMER_CHANNEL5_BIT                             2
#define DIMMER_CHANNEL5_BIT_MASK                        _BV(DIMMER_CHANNEL5_BIT)
#define DIMMER_CHANNEL5_PORT_NUMBER                     1
#define DIMMER_CHANNEL6_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTB)
#define DIMMER_CHANNEL6_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTB)
#define DIMMER_CHANNEL6_BIT                             3
#define DIMMER_CHANNEL6_BIT_MASK                        _BV(DIMMER_CHANNEL6_BIT)
#define DIMMER_CHANNEL6_PORT_NUMBER                     1
#define DIMMER_CHANNEL7_SFR_IO_ADDR                     _SFR_IO_ADDR(PORTC)
#define DIMMER_CHANNEL7_SFR_MEM_ADDR                    _SFR_MEM_ADDR(PORTC)
#define DIMMER_CHANNEL7_BIT                             3
#define DIMMER_CHANNEL7_BIT_MASK                        _BV(DIMMER_CHANNEL7_BIT)
#define DIMMER_CHANNEL7_PORT_NUMBER                     2

#ifndef DIMMER_CHANNELS
#define DIMMER_CHANNELS                                 8
#endif

#define DIMMER_CHANNELS_NUM_PORTS                       3 // PORTD, PORTB, PORTC

typedef uint8_t dimmer_enable_mask_t[DIMMER_CHANNELS_NUM_PORTS];

#define DIMMER_CHANNEL_PORT0_SFR_IO_ADDR                _SFR_IO_ADDR(PORTD)
#define DIMMER_CHANNEL_PORT1_SFR_IO_ADDR                _SFR_IO_ADDR(PORTB)
#define DIMMER_CHANNEL_PORT2_SFR_IO_ADDR                _SFR_IO_ADDR(PORTC)

// apply mask and set ports, interrupts need to be disabled during execution
#define DIMMER_CHANNELS_SET_ENABLE_MASK(src)\
    {\
        uint8_t tmp[3];\
        tmp[0] = (PORTD | src[0]);\
        tmp[1] = (PORTB | src[1]);\
        tmp[2] = (PORTC | src[2]);\
        PORTD = tmp[0];\
        PORTB = tmp[1];\
        PORTC = tmp[2];\
    }

#define DIMMER_CHANNELS_CLEAR_ENABLE_MASK(src)\
    {\
        uint8_t tmp[3];\
        tmp[0] = (PORTD & ~src[0]);\
        tmp[1] = (PORTB & ~src[1]);\
        tmp[2] = (PORTC & ~src[2]);\
        PORTD = tmp[0];\
        PORTB = tmp[1];\
        PORTC = tmp[2];\
    }

// clear mask and set all channels to 0
#define DIMMER_CHANNELS_ENABLE_MASK_CLEAR_CHANNELS(dst) { dst[0] = 0; dst[1] = 0; dst[2] = 0; }

// copy mask
#define DIMMER_CHANNELS_ENABLE_MASK_COPY(dst, src)      { dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; }

#define DIMMER_CHANNELS_ENABLE_MASK_SET_CHANNEL(dst, ch)\
    switch(ch) {\
        default:\
            dst[DIMMER_CHANNEL0_PORT_NUMBER] |= DIMMER_CHANNEL0_BIT_MASK;\
            break;\
        case 1:\
            dst[DIMMER_CHANNEL1_PORT_NUMBER] |= DIMMER_CHANNEL1_BIT_MASK;\
            break;\
        case 2:\
            dst[DIMMER_CHANNEL2_PORT_NUMBER] |= DIMMER_CHANNEL2_BIT_MASK;\
            break;\
        case 3:\
            dst[DIMMER_CHANNEL3_PORT_NUMBER] |= DIMMER_CHANNEL3_BIT_MASK;\
            break;\
        case 4:\
            dst[DIMMER_CHANNEL4_PORT_NUMBER] |= DIMMER_CHANNEL4_BIT_MASK;\
            break;\
        case 5:\
            dst[DIMMER_CHANNEL5_PORT_NUMBER] |= DIMMER_CHANNEL5_BIT_MASK;\
            break;\
        case 6:\
            dst[DIMMER_CHANNEL6_PORT_NUMBER] |= DIMMER_CHANNEL6_BIT_MASK;\
            break;\
        case 7:\
            dst[DIMMER_CHANNEL7_PORT_NUMBER] |= DIMMER_CHANNEL7_BIT_MASK;\
            break;\
    }

#define DIMMER_CHANNELS_ENABLE_CHANNEL(ch)\
    switch(ch) {\
        default:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL0_SFR_IO_ADDR), "I" (DIMMER_CHANNEL0_BIT));\
            break;\
        case 1:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL1_SFR_IO_ADDR), "I" (DIMMER_CHANNEL1_BIT));\
            break;\
        case 2:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL2_SFR_IO_ADDR), "I" (DIMMER_CHANNEL2_BIT));\
            break;\
        case 3:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL3_SFR_IO_ADDR), "I" (DIMMER_CHANNEL3_BIT));\
            break;\
        case 4:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL4_SFR_IO_ADDR), "I" (DIMMER_CHANNEL4_BIT));\
            break;\
        case 5:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL5_SFR_IO_ADDR), "I" (DIMMER_CHANNEL5_BIT));\
            break;\
        case 6:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL6_SFR_IO_ADDR), "I" (DIMMER_CHANNEL6_BIT));\
            break;\
        case 7:\
            asm volatile ("sbi %0, %1" :: "I" (DIMMER_CHANNEL7_SFR_IO_ADDR), "I" (DIMMER_CHANNEL7_BIT));\
            break;\
    }

#define DIMMER_CHANNELS_DISABLE_CHANNEL(ch)\
    switch(ch) {\
        default:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL0_SFR_IO_ADDR), "I" (DIMMER_CHANNEL0_BIT));\
            break;\
        case 1:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL1_SFR_IO_ADDR), "I" (DIMMER_CHANNEL1_BIT));\
            break;\
        case 2:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL2_SFR_IO_ADDR), "I" (DIMMER_CHANNEL2_BIT));\
            break;\
        case 3:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL3_SFR_IO_ADDR), "I" (DIMMER_CHANNEL3_BIT));\
            break;\
        case 4:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL4_SFR_IO_ADDR), "I" (DIMMER_CHANNEL4_BIT));\
            break;\
        case 5:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL5_SFR_IO_ADDR), "I" (DIMMER_CHANNEL5_BIT));\
            break;\
        case 6:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL6_SFR_IO_ADDR), "I" (DIMMER_CHANNEL6_BIT));\
            break;\
        case 7:\
            asm volatile ("cbi %0, %1" :: "I" (DIMMER_CHANNEL7_SFR_IO_ADDR), "I" (DIMMER_CHANNEL7_BIT));\
            break;\
    }

constexpr uint8_t channel_to_port_sfr_io_addr[] = { DIMMER_CHANNEL0_SFR_IO_ADDR, DIMMER_CHANNEL1_SFR_IO_ADDR, DIMMER_CHANNEL2_SFR_IO_ADDR, DIMMER_CHANNEL3_SFR_IO_ADDR, DIMMER_CHANNEL4_SFR_IO_ADDR, DIMMER_CHANNEL5_SFR_IO_ADDR, DIMMER_CHANNEL6_SFR_IO_ADDR, DIMMER_CHANNEL7_SFR_IO_ADDR };
constexpr uint8_t channel_to_port_number[] = { DIMMER_CHANNEL0_PORT_NUMBER, DIMMER_CHANNEL1_PORT_NUMBER, DIMMER_CHANNEL2_PORT_NUMBER, DIMMER_CHANNEL3_PORT_NUMBER, DIMMER_CHANNEL4_PORT_NUMBER, DIMMER_CHANNEL5_PORT_NUMBER, DIMMER_CHANNEL6_PORT_NUMBER, DIMMER_CHANNEL7_PORT_NUMBER };
constexpr uint8_t channel_to_port_bit[] = { DIMMER_CHANNEL0_BIT, DIMMER_CHANNEL1_BIT, DIMMER_CHANNEL2_BIT, DIMMER_CHANNEL3_BIT, DIMMER_CHANNEL4_BIT, DIMMER_CHANNEL5_BIT, DIMMER_CHANNEL6_BIT, DIMMER_CHANNEL7_BIT };

#define PIN_D2_SET()                                    asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (2))
#define PIN_D2_CLEAR()                                  asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTD)), "I" (2))
#define PIN_D2_TOGGLE()                                 asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PIND)), "I" (2))
#define PIN_D2_IS_SET()                                 ((_SFR_IO_ADDR(PIND) & _BV(2)) != 0)
#define PIN_D2_IS_CLEAR()                               ((_SFR_IO_ADDR(PIND) & _BV(2)) == 0)

#define PIN_D8_SET()                                    asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (0))
#define PIN_D8_CLEAR()                                  asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (0))
#define PIN_D8_TOGGLE()                                 asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PINB)), "I" (0))
#define PIN_D8_IS_SET()                                 ((_SFR_IO_ADDR(PINB) & _BV(0)) != 0)
#define PIN_D8_IS_CLEAR()                               ((_SFR_IO_ADDR(PINB) & _BV(0)) == 0)

#define PIN_D11_SET()                                   asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (3))
#define PIN_D11_CLEAR()                                 asm volatile("cbi %0, %1" :: "I" (_SFR_IO_ADDR(PORTB)), "I" (3))
#define PIN_D11_TOGGLE()                                asm volatile("sbi %0, %1" :: "I" (_SFR_IO_ADDR(PINB)), "I" (3))
#define PIN_D11_IS_SET()                                ((_SFR_IO_ADDR(PINB) & _BV(3)) != 0)
#define PIN_D11_IS_CLEAR()                              ((_SFR_IO_ADDR(PINB) & _BV(3)) == 0)


