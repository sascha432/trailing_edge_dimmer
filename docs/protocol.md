# I2C/UART protocol

The dimmer is controlled via I2C or UART interface.

The default address is 0x17 for the slave. When sending data, the dimmer acts as master and sends to address 0x18 (slave address + 1).

The values for the registers and commands can be found in [dimmer_protocol.h](../src/dimmer_protocol.h)

The examples are using the UART protocol and can send to the dimmer using any terminal software.

Using the Arduino TwoWire class (or the drop-in replacement for UART [SerialTwoWire](https://github.com/sascha432/i2c_uart_bridge)) instead:


    // +i2ct=17,89,22
    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_VCC);
    if (Wire.endTransmission() == 0) {

        // +i2cr=17,02
        uint16_t vcc;
        if (Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(vcc)) == sizeof(vcc)) {
            Wire.readBytes(reinterpret_cast<const uint8_t *>(&vcc), sizeof(vcc));
        }
    }


## DIMMER_COMMAND_FADE

The fading command uses following registers

- DIMMER_REGISTER_FROM_LEVEL (int16, little endian)
- DIMMER_REGISTER_CHANNEL (int8)
- DIMMER_REGISTER_TO_LEVEL (int16)
- DIMMER_REGISTER_TIME (float, 32bit, little endian)

The fade command can be sent in a single write operation.

### From level

If set to -1 / 0xffff, it will start with the current level set. The default value is -1.

### Channel

Channels are 0 based and -1 / 0xff means all channels

### Examples

Set *from level* to -1, *channel* to 0, *to level* to 0x0301, *time* 7.5 (seconds) and execute fade command

    +i2ct=17,80,ff,ff,00,03,01,00,00,f0,40,11
                ^^^^^ from level           ^^ command
                      ^^ channnel
                         ^^^^^ to level
                               ^^^^^^^^^^^ time

Short version

    +i2ct=7580ffff0003000000f04011

Assuming *from level* is the default -1, set *channel* to -1, *to level* to 0x0301, *time* 7.5

    +i2ct=17,82,ff,03,01,00,00,f0,40,11

## DIMMER_COMMAND_SET_LEVEL

The fading command uses following registers

- DIMMER_REGISTER_CHANNEL (int8)
- DIMMER_REGISTER_TO_LEVEL (int16)

Set *channel* to 1, *to level* to 777 (0x0309) and execute set level command

    +i2ct=17,82,01,09,03
    +i2ct=17,89,10

To send the command in one transmission, the time can be filled with any data

    +i2ct=17,82,01,09,03,00,00,00,00,10

## DIMMER_COMMAND_READ_xxx

This applies to

- DIMMER_COMMAND_READ_NTC (float)
- DIMMER_COMMAND_READ_INT_TEMP (float)
- DIMMER_COMMAND_READ_VCC (uint16)

If no further data is sent after the read command, the register is set automatically to

- DIMMER_REGISTER_TEMP (float)
- DIMMER_REGISTER_VCC (uint16)

Read VCC

    +i2ct=17,89,22
    +i2cr=17,02

Response (0x3613 = 4.918V)

    +I2CT=753613

Read internal temperature

    +i2ct=17,89,21
    +i2cr=17,04

Read int. temp and VCC

In this example, *DIMMER_REGISTER_READ_LENGTH* is set manually to 6 byte, followed by the start address *DIMMER_REGISTER_TEMP*

    +i2ct=17,89,21,89,22,8a,06,9c
    +i2cr=17,06

If the temperature is requested last, it is not required to set read length and register address

    +i2ct=17,89,22,89,21
    +i2cr=17,06


Read AC frequency

    +i2ct=17,89,23
    +i2cr=17,04


## DIMMER_COMMAND_READ_CHANNELS

Read one or more channel

- DIMMER_REGISTER_CH0_LEVEL (int16)
- DIMMER_REGISTER_CH1_LEVEL
- DIMMER_REGISTER_CH2_LEVEL
- DIMMER_REGISTER_CH3_LEVEL
- DIMMER_REGISTER_CH4_LEVEL
- DIMMER_REGISTER_CH5_LEVEL
- DIMMER_REGISTER_CH6_LEVEL
- DIMMER_REGISTER_CH7_LEVEL

The byte after command specifies the number of channels and start address, each 4 bit. If omitted, all 8 channels are read.

Channel 1 - 4

    +i2ct=17,89,12,40
    +i2cr=17,08

Channel 8

    +i2ct=17,89,12,17
    +i2cr=17,02

Channel 2 and 3

    +i2ct=17,89,12,21
    +i2cr=17,04

## DIMMER_COMMAND_WRITE_EEPROM

Store configuration and current levels in EEPROM

    +i2ct=17,89,50

## DIMMER_COMMAND_RESTORE_FS

Restore factory settings and re-initialize EEPROM wear leveling

    +i2ct=17,89,51

## DIMMER_COMMAND_READ_TIMINGS

Read timings for fine tuning. The return type is float and all values are in micro seconds

- DIMMER_TIMINGS_TMR1_TICKS_PER_US
- DIMMER_TIMINGS_TMR2_TICKS_PER_US
- DIMMER_TIMINGS_ZC_DELAY_IN_US
- DIMMER_TIMINGS_MIN_ON_TIME_IN_US
- DIMMER_TIMINGS_ADJ_HW_TIME_IN_US

Read zero crossing delay

    +i2ct=17,89,23,03
    +i2cr=17,04

**NOTE:** Values are stored in ticks in the EEPROM. DIMMER_TIMINGS_TMR1_TICKS_PER_US and DIMMER_TIMINGS_TMR2_TICKS_PER_US can be used to translate time to ticks.

## Reading and writing the dimmer settings

- DIMMER_REGISTER_OPTIONS (uint8)
- DIMMER_REGISTER_MAX_TEMP (uint8, °C)
- DIMMER_REGISTER_FADE_IN_TIME (float, seconds)
- DIMMER_REGISTER_TEMP_CHECK_INT (uint8, seconds)
- DIMMER_REGISTER_LC_FACTOR (float)
- DIMMER_REGISTER_ZC_DELAY_TICKS (uint8)
- DIMMER_REGISTER_MIN_ON_TIME_TICKS (uint16)
- DIMMER_REGISTER_ADJ_HALFWAVE_TICKS (uint16)

### Options

- Bit 0: Restore last levels on power up
- Bit 1: Report temperature and over-temperature alarm (UART only)
- Bit 2: Temperature alarm indication. Needs to be cleared manually

To make any changes permanent, **DIMMER_COMMAND_WRITE_EEPROM** needs to be executed.

Read all settings

    +i2ct=17,8a,10,a2
    +i2cr=17,10

Read temperature check interval

    +i2ct=17,8a,01,a8
    +i2cr=17,01

Response (0x1e, 30 seconds)

    +I2CT=751E

Set temperature check interval/metrics reporting to 30 seconds

    +i2ct=17,a8,1e

**Note:** The interval changes after the next check. DIMMER_COMMAND_FORCE_TEMP_CHECK (*+i2ct=17,89,54*) can be used to force a check without waiting

Setting the linear correction factor to 1.0

    +i2ct=17,a9,00,00,80,3f

## DIMMER_COMMAND_PRINT_INFO

Print dimmer info on serial port

    +i2ct=17,89,53

## DIMMER_COMMAND_ZC_TIMINGS_OUTPUT

If ZC_MAX_TIMINGS is enabled, the dimmer outputs the zero crossing timings to the serial console every ZC_MAX_TIMINGS_INTERVAL milliseconds. ZC_MAX_TIMINGS needs to be equal or higher than the amount of expected data within this period. Collecting the data does not cause a delay of the ZC interrupt.

The data expected is a boolean. Non-zero values enable the output on.

    +i2ct=17,89,60,1

### Outut format

The first argument is the return value of micros() hex encoded. Every following the difference to the previous time.

+REM=ZC,\<microseconds\> [\<delay\> [\<delay\> ...]]

    +REM=ZC,17f8c010 20b8 20b4 20b4 20b8 20b4 20b8 ...


### Compile options

`+REM=options=EEPROM,NTC=19,Int.Temp,Temp.Chk,VCC,Fade,LCF,ACFrq=60,Pr=UART,CE=1,Addr=17,CPU=8,Pre=8/64,Ticks=1.000/0.125,Lvls=8333,Chs=4`

- EEPROM = EEPROM enabled
- NTC=19 = NTC enabled on PIN 19 (A5)
- Int.Temp = Internal temperature sensor enabled
- Temp.Chk = Temperature check and metrics enabled
- VCC = Read VCC enabled
- Fade = Fading enabled
- LCF = Linear correction factor enabled
- ACFrq=60 - AC frequency 60Hz
- Pr=UART - Protocol UART
- CE=1 - Fading completion event enabled
- Addr=17 - Device address 0x17
- CPU=8 - CPU 8Mhz
- Pre=8/64 - Prescaler for timer1=8, timer2=64
- Ticks=1.000/0.125 - Timer1/2 ticks per µs
- Lvls=8333 - Max. brightness level 8333
- P=6,8,9,10 - MOSFET pins / number of channels supported

### Parameters and values

`+REM=values=Restore=1,ACFrq=61.871,ref11=1.100,NTC=50.30,Int.Temp=38.78,VCC=3.322,Max.Temp=75,rtime=60,LCF=1.000,Min.on=200,Adj.hw=200,ZC.delay=13`

- Restore=1 - Restore brightness after start`*`
- ACFreq=61.871 - Measured AC frequency
- ref11=1.100 - Reference voltage`*`
- NTC=50.30 - NTC temperature in °C
- Int.temp=38.78 - Atmega internal temperature in °C
- VCC=3.322 - Supply voltage in V
- Max.Temp=75 - Maximum temperature before emergency shutoff`*`
- rtime=60 - Interval for metrics reporting`*`
- LCF=1.000 - Linear correction factor`*`
- Min.on=200 - Minimum on time in ticks (timer1)`*`
- Adj.hw=200 - Adjust havewave time in ticks (timer1)`*`
- ZC.delay=13 - Zero crossing delay in ticks (timer2)`*`

**Note:** `*` These parameters can be changed

## DIMMER_COMMAND_PRINT_METRICS

Print metrics every 5 seconds on serial port in human readable form. The following byte enables (non 0) or disables the output

    +i2ct=17,89,55,01

## DIMMER_COMMAND_FORCE_TEMP_CHECK

Force temperature check and report metrics if enabled

    +i2ct=17,89,54

## DIMMER_COMMAND_DUMP_xxx

- DIMMER_COMMAND_DUMP_MEM
- DIMMER_COMMAND_DUMP_MACROS

This is only available with enabled debugging.

Dump the content of the register memory

    +i2ct=17,89,ee

Dump macros for the register memory.

    +i2ct=17,89,ef

## Temperature, VCC status and AC Frequency (DIMMER_METRICS_REPORT)

If metrics reporting is enabled, the dimmer sends dimmer_metrics_t with DIMMER_TEMPERATURE_REPORT to it's own I2C address + 1.
This can also be trigger with the command DIMMER_COMMAND_FORCE_TEMP_CHECK. The maximum interval is set with cfg.report_metrics_max_interval, the minimum is cfg.temp_check_interval. The event is sent either when the maximum time has been reached, or if any values has changed significantly.

If data is not available, 0 (for VCC) or NaN (for any float) is returned.

    +I2CT=18F02...

## Temperature Alarm (DIMMER_TEMPERATURE_ALERT)

If the max. temperature was exceeded, it sends one alarm with register address DIMMER_TEMPERATURE_ALERT, the current temperature (uint8) and the temperature threshold (uint8)

    +I2CT=18F16A64

## Fading completed (DIMMER_FADING_COMPLETE)

When fading to a new level has been completed, the dimmer sends DIMMER_FADING_COMPLETE, with channel (int8) and level (int16). Channel and level can occur multiple times in the case 2 channels finished at the same time.

Channel 0 and 1 reached 0x1234 and fading is complete:

    +I2CT=18F2001234011234

Channel 0 reached level 0:

    +I2CT=18F2000000

## EEPROM written event (DIMMER_EEPROM_WRITTEN)

EEPROM writes might be delayed due to wear leveling. Once written, DIMMER_EEPROM_WRITTEN with structure dimmer_eeprom_written_t is sent.

    +I2CT=18F301000000000000

## Frequency warning (DIMMER_FREQUENCY_WARNING)

If a too low or high frequency (<75% >120%) is detected, DIMMER_FREQUENCY_WARNING will be sent. The second byte indicates if it was too low (0) or high (1), followed by register_mem_errors_t.
No zero crossing signal does not fire this event, but the frequency measurement will return NaN.

The errors are stored in *cfg.bits.frequency_low* and *cfg.bits.frequency_high*, which need to be reset manually.

## Zero Crossing calibration

Following commands are available for calibration. For more commands see "FOR CALIBRATION" in i2c_slave.cpp


Increase zero crossing delay

    +i2ct=17,89,82

Decrease zero crossing delay

    +i2ct=17,89,83

Set zero crossing delay to 7F and print setting

    +i2ct=17,89,92,7F

The settings need to be stored in the EEPROM. The following command forces to write the EEPROM

    +i2ct=17,89,93
