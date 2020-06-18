/**
 * Author: sascha_lammers@gmx.de
 */

// inline assembler for enabling/disabling channels
//
// set HAVE_ASM_CHANNELS=1 and xBI_CHANNEL#=<arduino pin>
//
// -D DIMMER_CHANNELS=4
// -D DIMMER_MOSFET_PINS="{xBI_CHANNEL0,xBI_CHANNEL1,xBI_CHANNEL2,xBI_CHANNEL3}"
// -D HAVE_ASM_CHANNELS=1
// -D xBI_CHANNEL0=6
// -D xBI_CHANNEL1=8
// -D xBI_CHANNEL2=9
// -D xBI_CHANNEL3=10

#ifndef ARDUINO_AVR_NANO

#error defines for Atmega328P and compatible

#else

#if xBI_CHANNEL0==0
    #define xBI_ARGS_CHANNEL0 "0x0b,0"
#endif
#if xBI_CHANNEL0==1
    #define xBI_ARGS_CHANNEL0 "0x0b,1"
#endif
#if xBI_CHANNEL0==2
    #define xBI_ARGS_CHANNEL0 "0x0b,2"
#endif
#if xBI_CHANNEL0==3
    #define xBI_ARGS_CHANNEL0 "0x0b,3"
#endif
#if xBI_CHANNEL0==4
    #define xBI_ARGS_CHANNEL0 "0x0b,4"
#endif
#if xBI_CHANNEL0==5
    #define xBI_ARGS_CHANNEL0 "0x0b,5"
#endif
#if xBI_CHANNEL0==6
    #define xBI_ARGS_CHANNEL0 "0x0b,6"
#endif
#if xBI_CHANNEL0==7
    #define xBI_ARGS_CHANNEL0 "0x0b,7"
#endif
#if xBI_CHANNEL0==8
    #define xBI_ARGS_CHANNEL0 "0x05,0"
#endif
#if xBI_CHANNEL0==9
    #define xBI_ARGS_CHANNEL0 "0x05,1"
#endif
#if xBI_CHANNEL0==10
    #define xBI_ARGS_CHANNEL0 "0x05,2"
#endif
#if xBI_CHANNEL0==11
    #define xBI_ARGS_CHANNEL0 "0x05,3"
#endif
#if xBI_CHANNEL0==12
    #define xBI_ARGS_CHANNEL0 "0x05,4"
#endif
#if xBI_CHANNEL0==13
    #define xBI_ARGS_CHANNEL0 "0x05,5"
#endif
#if xBI_CHANNEL0==14
    #define xBI_ARGS_CHANNEL0 "0x08,0"
#endif
#if xBI_CHANNEL0==15
    #define xBI_ARGS_CHANNEL0 "0x08,1"
#endif
#if xBI_CHANNEL1==0
    #define xBI_ARGS_CHANNEL1 "0x0b,0"
#endif
#if xBI_CHANNEL1==1
    #define xBI_ARGS_CHANNEL1 "0x0b,1"
#endif
#if xBI_CHANNEL1==2
    #define xBI_ARGS_CHANNEL1 "0x0b,2"
#endif
#if xBI_CHANNEL1==3
    #define xBI_ARGS_CHANNEL1 "0x0b,3"
#endif
#if xBI_CHANNEL1==4
    #define xBI_ARGS_CHANNEL1 "0x0b,4"
#endif
#if xBI_CHANNEL1==5
    #define xBI_ARGS_CHANNEL1 "0x0b,5"
#endif
#if xBI_CHANNEL1==6
    #define xBI_ARGS_CHANNEL1 "0x0b,6"
#endif
#if xBI_CHANNEL1==7
    #define xBI_ARGS_CHANNEL1 "0x0b,7"
#endif
#if xBI_CHANNEL1==8
    #define xBI_ARGS_CHANNEL1 "0x05,0"
#endif
#if xBI_CHANNEL1==9
    #define xBI_ARGS_CHANNEL1 "0x05,1"
#endif
#if xBI_CHANNEL1==10
    #define xBI_ARGS_CHANNEL1 "0x05,2"
#endif
#if xBI_CHANNEL1==11
    #define xBI_ARGS_CHANNEL1 "0x05,3"
#endif
#if xBI_CHANNEL1==12
    #define xBI_ARGS_CHANNEL1 "0x05,4"
#endif
#if xBI_CHANNEL1==13
    #define xBI_ARGS_CHANNEL1 "0x05,5"
#endif
#if xBI_CHANNEL1==14
    #define xBI_ARGS_CHANNEL1 "0x08,0"
#endif
#if xBI_CHANNEL1==15
    #define xBI_ARGS_CHANNEL1 "0x08,1"
#endif
#if xBI_CHANNEL2==0
    #define xBI_ARGS_CHANNEL2 "0x0b,0"
#endif
#if xBI_CHANNEL2==1
    #define xBI_ARGS_CHANNEL2 "0x0b,1"
#endif
#if xBI_CHANNEL2==2
    #define xBI_ARGS_CHANNEL2 "0x0b,2"
#endif
#if xBI_CHANNEL2==3
    #define xBI_ARGS_CHANNEL2 "0x0b,3"
#endif
#if xBI_CHANNEL2==4
    #define xBI_ARGS_CHANNEL2 "0x0b,4"
#endif
#if xBI_CHANNEL2==5
    #define xBI_ARGS_CHANNEL2 "0x0b,5"
#endif
#if xBI_CHANNEL2==6
    #define xBI_ARGS_CHANNEL2 "0x0b,6"
#endif
#if xBI_CHANNEL2==7
    #define xBI_ARGS_CHANNEL2 "0x0b,7"
#endif
#if xBI_CHANNEL2==8
    #define xBI_ARGS_CHANNEL2 "0x05,0"
#endif
#if xBI_CHANNEL2==9
    #define xBI_ARGS_CHANNEL2 "0x05,1"
#endif
#if xBI_CHANNEL2==10
    #define xBI_ARGS_CHANNEL2 "0x05,2"
#endif
#if xBI_CHANNEL2==11
    #define xBI_ARGS_CHANNEL2 "0x05,3"
#endif
#if xBI_CHANNEL2==12
    #define xBI_ARGS_CHANNEL2 "0x05,4"
#endif
#if xBI_CHANNEL2==13
    #define xBI_ARGS_CHANNEL2 "0x05,5"
#endif
#if xBI_CHANNEL2==14
    #define xBI_ARGS_CHANNEL2 "0x08,0"
#endif
#if xBI_CHANNEL2==15
    #define xBI_ARGS_CHANNEL2 "0x08,1"
#endif
#if xBI_CHANNEL3==0
    #define xBI_ARGS_CHANNEL3 "0x0b,0"
#endif
#if xBI_CHANNEL3==1
    #define xBI_ARGS_CHANNEL3 "0x0b,1"
#endif
#if xBI_CHANNEL3==2
    #define xBI_ARGS_CHANNEL3 "0x0b,2"
#endif
#if xBI_CHANNEL3==3
    #define xBI_ARGS_CHANNEL3 "0x0b,3"
#endif
#if xBI_CHANNEL3==4
    #define xBI_ARGS_CHANNEL3 "0x0b,4"
#endif
#if xBI_CHANNEL3==5
    #define xBI_ARGS_CHANNEL3 "0x0b,5"
#endif
#if xBI_CHANNEL3==6
    #define xBI_ARGS_CHANNEL3 "0x0b,6"
#endif
#if xBI_CHANNEL3==7
    #define xBI_ARGS_CHANNEL3 "0x0b,7"
#endif
#if xBI_CHANNEL3==8
    #define xBI_ARGS_CHANNEL3 "0x05,0"
#endif
#if xBI_CHANNEL3==9
    #define xBI_ARGS_CHANNEL3 "0x05,1"
#endif
#if xBI_CHANNEL3==10
    #define xBI_ARGS_CHANNEL3 "0x05,2"
#endif
#if xBI_CHANNEL3==11
    #define xBI_ARGS_CHANNEL3 "0x05,3"
#endif
#if xBI_CHANNEL3==12
    #define xBI_ARGS_CHANNEL3 "0x05,4"
#endif
#if xBI_CHANNEL3==13
    #define xBI_ARGS_CHANNEL3 "0x05,5"
#endif
#if xBI_CHANNEL3==14
    #define xBI_ARGS_CHANNEL3 "0x08,0"
#endif
#if xBI_CHANNEL3==15
    #define xBI_ARGS_CHANNEL3 "0x08,1"
#endif
#if xBI_CHANNEL4==0
    #define xBI_ARGS_CHANNEL4 "0x0b,0"
#endif
#if xBI_CHANNEL4==1
    #define xBI_ARGS_CHANNEL4 "0x0b,1"
#endif
#if xBI_CHANNEL4==2
    #define xBI_ARGS_CHANNEL4 "0x0b,2"
#endif
#if xBI_CHANNEL4==3
    #define xBI_ARGS_CHANNEL4 "0x0b,3"
#endif
#if xBI_CHANNEL4==4
    #define xBI_ARGS_CHANNEL4 "0x0b,4"
#endif
#if xBI_CHANNEL4==5
    #define xBI_ARGS_CHANNEL4 "0x0b,5"
#endif
#if xBI_CHANNEL4==6
    #define xBI_ARGS_CHANNEL4 "0x0b,6"
#endif
#if xBI_CHANNEL4==7
    #define xBI_ARGS_CHANNEL4 "0x0b,7"
#endif
#if xBI_CHANNEL4==8
    #define xBI_ARGS_CHANNEL4 "0x05,0"
#endif
#if xBI_CHANNEL4==9
    #define xBI_ARGS_CHANNEL4 "0x05,1"
#endif
#if xBI_CHANNEL4==10
    #define xBI_ARGS_CHANNEL4 "0x05,2"
#endif
#if xBI_CHANNEL4==11
    #define xBI_ARGS_CHANNEL4 "0x05,3"
#endif
#if xBI_CHANNEL4==12
    #define xBI_ARGS_CHANNEL4 "0x05,4"
#endif
#if xBI_CHANNEL4==13
    #define xBI_ARGS_CHANNEL4 "0x05,5"
#endif
#if xBI_CHANNEL4==14
    #define xBI_ARGS_CHANNEL4 "0x08,0"
#endif
#if xBI_CHANNEL4==15
    #define xBI_ARGS_CHANNEL4 "0x08,1"
#endif
#if xBI_CHANNEL5==0
    #define xBI_ARGS_CHANNEL5 "0x0b,0"
#endif
#if xBI_CHANNEL5==1
    #define xBI_ARGS_CHANNEL5 "0x0b,1"
#endif
#if xBI_CHANNEL5==2
    #define xBI_ARGS_CHANNEL5 "0x0b,2"
#endif
#if xBI_CHANNEL5==3
    #define xBI_ARGS_CHANNEL5 "0x0b,3"
#endif
#if xBI_CHANNEL5==4
    #define xBI_ARGS_CHANNEL5 "0x0b,4"
#endif
#if xBI_CHANNEL5==5
    #define xBI_ARGS_CHANNEL5 "0x0b,5"
#endif
#if xBI_CHANNEL5==6
    #define xBI_ARGS_CHANNEL5 "0x0b,6"
#endif
#if xBI_CHANNEL5==7
    #define xBI_ARGS_CHANNEL5 "0x0b,7"
#endif
#if xBI_CHANNEL5==8
    #define xBI_ARGS_CHANNEL5 "0x05,0"
#endif
#if xBI_CHANNEL5==9
    #define xBI_ARGS_CHANNEL5 "0x05,1"
#endif
#if xBI_CHANNEL5==10
    #define xBI_ARGS_CHANNEL5 "0x05,2"
#endif
#if xBI_CHANNEL5==11
    #define xBI_ARGS_CHANNEL5 "0x05,3"
#endif
#if xBI_CHANNEL5==12
    #define xBI_ARGS_CHANNEL5 "0x05,4"
#endif
#if xBI_CHANNEL5==13
    #define xBI_ARGS_CHANNEL5 "0x05,5"
#endif
#if xBI_CHANNEL5==14
    #define xBI_ARGS_CHANNEL5 "0x08,0"
#endif
#if xBI_CHANNEL5==15
    #define xBI_ARGS_CHANNEL5 "0x08,1"
#endif
#if xBI_CHANNEL6==0
    #define xBI_ARGS_CHANNEL6 "0x0b,0"
#endif
#if xBI_CHANNEL6==1
    #define xBI_ARGS_CHANNEL6 "0x0b,1"
#endif
#if xBI_CHANNEL6==2
    #define xBI_ARGS_CHANNEL6 "0x0b,2"
#endif
#if xBI_CHANNEL6==3
    #define xBI_ARGS_CHANNEL6 "0x0b,3"
#endif
#if xBI_CHANNEL6==4
    #define xBI_ARGS_CHANNEL6 "0x0b,4"
#endif
#if xBI_CHANNEL6==5
    #define xBI_ARGS_CHANNEL6 "0x0b,5"
#endif
#if xBI_CHANNEL6==6
    #define xBI_ARGS_CHANNEL6 "0x0b,6"
#endif
#if xBI_CHANNEL6==7
    #define xBI_ARGS_CHANNEL6 "0x0b,7"
#endif
#if xBI_CHANNEL6==8
    #define xBI_ARGS_CHANNEL6 "0x05,0"
#endif
#if xBI_CHANNEL6==9
    #define xBI_ARGS_CHANNEL6 "0x05,1"
#endif
#if xBI_CHANNEL6==10
    #define xBI_ARGS_CHANNEL6 "0x05,2"
#endif
#if xBI_CHANNEL6==11
    #define xBI_ARGS_CHANNEL6 "0x05,3"
#endif
#if xBI_CHANNEL6==12
    #define xBI_ARGS_CHANNEL6 "0x05,4"
#endif
#if xBI_CHANNEL6==13
    #define xBI_ARGS_CHANNEL6 "0x05,5"
#endif
#if xBI_CHANNEL6==14
    #define xBI_ARGS_CHANNEL6 "0x08,0"
#endif
#if xBI_CHANNEL6==15
    #define xBI_ARGS_CHANNEL6 "0x08,1"
#endif
#if xBI_CHANNEL7==0
    #define xBI_ARGS_CHANNEL7 "0x0b,0"
#endif
#if xBI_CHANNEL7==1
    #define xBI_ARGS_CHANNEL7 "0x0b,1"
#endif
#if xBI_CHANNEL7==2
    #define xBI_ARGS_CHANNEL7 "0x0b,2"
#endif
#if xBI_CHANNEL7==3
    #define xBI_ARGS_CHANNEL7 "0x0b,3"
#endif
#if xBI_CHANNEL7==4
    #define xBI_ARGS_CHANNEL7 "0x0b,4"
#endif
#if xBI_CHANNEL7==5
    #define xBI_ARGS_CHANNEL7 "0x0b,5"
#endif
#if xBI_CHANNEL7==6
    #define xBI_ARGS_CHANNEL7 "0x0b,6"
#endif
#if xBI_CHANNEL7==7
    #define xBI_ARGS_CHANNEL7 "0x0b,7"
#endif
#if xBI_CHANNEL7==8
    #define xBI_ARGS_CHANNEL7 "0x05,0"
#endif
#if xBI_CHANNEL7==9
    #define xBI_ARGS_CHANNEL7 "0x05,1"
#endif
#if xBI_CHANNEL7==10
    #define xBI_ARGS_CHANNEL7 "0x05,2"
#endif
#if xBI_CHANNEL7==11
    #define xBI_ARGS_CHANNEL7 "0x05,3"
#endif
#if xBI_CHANNEL7==12
    #define xBI_ARGS_CHANNEL7 "0x05,4"
#endif
#if xBI_CHANNEL7==13
    #define xBI_ARGS_CHANNEL7 "0x05,5"
#endif
#if xBI_CHANNEL7==14
    #define xBI_ARGS_CHANNEL7 "0x08,0"
#endif
#if xBI_CHANNEL7==15
    #define xBI_ARGS_CHANNEL7 "0x08,1"
#endif

#endif

    // clock cycles during turning on
    // load channel (4)
    // per channel miss (2)
    // per channel hit (5)
    // next channel (8)
    // about twice as fast as using in/out with a table and indirect load

    inline void enableChannel(dimmer_channel_id_t channel) {
        switch(channel) {
            default:
                asm volatile ("sbi " xBI_ARGS_CHANNEL0);
                break;
#if DIMMER_CHANNELS>=2
            case 1:
                asm volatile ("sbi " xBI_ARGS_CHANNEL1);
                break;
#endif
#if DIMMER_CHANNELS>=3
            case 2:
                asm volatile ("sbi " xBI_ARGS_CHANNEL2);
                break;
#endif
#if DIMMER_CHANNELS>=4
            case 3:
                asm volatile ("sbi " xBI_ARGS_CHANNEL3);
                break;
#endif
#if DIMMER_CHANNELS>=5
            case 4:
                asm volatile ("sbi " xBI_ARGS_CHANNEL4);
                break;
#endif
#if DIMMER_CHANNELS>=6
            case 5:
                asm volatile ("sbi " xBI_ARGS_CHANNEL5);
                break;
#endif
#if DIMMER_CHANNELS>=7
            case 6:
                asm volatile ("sbi " xBI_ARGS_CHANNEL6);
                break;
#endif
#if DIMMER_CHANNELS>=8
            case 7:
                asm volatile ("sbi " xBI_ARGS_CHANNEL7);
                break;
#endif
        }
    }

    inline void disableChannel(dimmer_channel_id_t channel)
    {
        switch(channel) {
            default:
                asm volatile ("cbi " xBI_ARGS_CHANNEL0);
                break;
#if DIMMER_CHANNELS>=2
            case 1:
                asm volatile ("cbi " xBI_ARGS_CHANNEL1);
                break;
#endif
#if DIMMER_CHANNELS>=3
            case 2:
                asm volatile ("cbi " xBI_ARGS_CHANNEL2);
                break;
#endif
#if DIMMER_CHANNELS>=4
            case 3:
                asm volatile ("cbi " xBI_ARGS_CHANNEL3);
                break;
#endif
#if DIMMER_CHANNELS>=5
            case 4:
                asm volatile ("cbi " xBI_ARGS_CHANNEL4);
                break;
#endif
#if DIMMER_CHANNELS>=6
            case 5:
                asm volatile ("cbi " xBI_ARGS_CHANNEL5);
                break;
#endif
#if DIMMER_CHANNELS>=7
            case 6:
                asm volatile ("cbi " xBI_ARGS_CHANNEL6);
                break;
#endif
#if DIMMER_CHANNELS>=8
            case 7:
                asm volatile ("cbi " xBI_ARGS_CHANNEL7);
                break;
#endif
        }
    }
