# I2C/UART protocol

The dimmer is controlled via I2C or UART interface.

The default address is 0x17 (referred to as ADDRESS) for the slave. When sending data, the dimmer acts as master and sends to address 0x18 (slave address + 1, refred to as MASTER_ADDRESS).

The values for the registers and commands can be found in [dimmer_protocol.h](../src/dimmer_protocol.h)

The examples are using the UART protocol and can send to the dimmer using any terminal software.

Using the Arduino TwoWire class (or the drop-in replacement for UART [SerialTwoWire](https://github.com/sascha432/i2c_uart_bridge)) instead:

    // to slave +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_READ_VCC (+I2CT=17,0A,22)
    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_VCC);
    if (Wire.endTransmission() == 0) {

        // to slave +I2CR=ADDRESS,02 (+I2CR=17,02)
        uint16_t vcc;
        if (Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(vcc)) == sizeof(vcc)) {         // from slave: +I2CT=ADDRESS,CD,12 (+I2CT=17,CD,12)
            Wire.readBytes(reinterpret_cast<const uint8_t *>(&vcc), sizeof(vcc));       // vcc = 0x12CD/4813 (4.813V)
        }
    }

## Translating commands

Writing HEX commands is cumbersome. There is a python script that can translate constants into HEX commands. It can process single commands or an entire file.

`scripts/trans_cmd.py`

Supported values are:

- ADDRESS
- MASTER_ADDRESS
- Name of the constant (DIMMER_REGISTER_FROM_LEVEL, DIMMER_COMMAND_READ_VCC, ...)
- Short version of the constant (REGISTER_FROM_LEVEL, COMMAND_READ_VCC)
- int8 (ff or b-1)
- uint8 (ff or b255)
- int16 (ffff or w-1)
- uint16 (ffff or w65535)
- Float (ffffffff or 100.5)
- Hex uint32 (eeeeeeee or q4008636142)

```
# trans_cmd.py command "I2CT=ADDRESS,COMMAND_READ_VCC,DIMMER_REGISTER_FROM_LEVEL,1f,2faa,100.5,4a3b2c1d,b-1,w1000,w-1"
+I2CT=17,22,01,1F,2F,AA,42,c9,00,00,4A,3B,2C,1D,FF,03,E8,FF,FF
```

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

Set **from level** to current level -1, **channel** to 0, **to level** to 2250, **time** 7.5 (seconds) and execute fade command

    +I2CT=ADDRESS,REGISTER_FROM_LEVEL,w-1,00,w2250,7.5,COMMAND_FADE (+I2CT=17,01,FF,FF,00,CA,08,00,00,F0,40,11)

Set **channel** to all channels (0xff = -1), **to level** to 1533, **time** 7.5 and execute fade

    +I2CT=ADDRESS,REGISTER_CHANNEL,b-1,w1533,7.5,COMMAND_FADE (+I2CT=17,03,FF,FD,05,00,00,F0,40,11)

## DIMMER_COMMAND_SET_LEVEL

The fading command uses following registers

- DIMMER_REGISTER_CHANNEL (int8)
- DIMMER_REGISTER_TO_LEVEL (int16)

Set **channel** to 1, **to level** to 777 and execute set level command

    +I2CT=ADDRESS,REGISTER_CHANNEL,01,w777 (+I2CT=17,03,01,09,03)
    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_SET_LEVEL (+I2CT=17,0A,10)

To send the command in one transmission, the time can be filled with any data

    +I2CT=ADDRESS,REGISTER_CHANNEL,01,w777,0.0,COMMAND_SET_LEVEL (+I2CT=17,03,01,09,03,00,00,00,00,10)

## DIMMER_COMMAND_READ_xxx

This applies to

- DIMMER_COMMAND_READ_NTC (float)
- DIMMER_COMMAND_READ_INT_TEMP (float)
- DIMMER_COMMAND_READ_VCC (uint16)

If no further data is sent after the read command, the register is set automatically to

- DIMMER_REGISTER_TEMP (float)
- DIMMER_REGISTER_INT_TEMP (float)
- DIMMER_REGISTER_VCC (uint16)

**NOTE:** Reading VCC and temperature takes ~50ms. The +I2CR command must be delayed that long.

Read VCC

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_READ_VCC (+I2CT=17,0A,22)
    ...wait 50ms
    +I2CR=ADDRESS,02 (+I2CR=17,02)

Response ("\x21\x13" = 0x1321 = 4.897V)

    +I2CT=ADDRESS,21,13 (+I2CT=17,21,13)

Read internal temperature

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_READ_INT_TEMP (+I2CT=17,0A,21)
    ...wait 50ms
    +I2CR=ADDRESS,04 (+I2CR=17,04)

Response ("\x55\x5C\x86\x41" = 16.795°C)

    +I2CT=ADDRESS,55,5C,86,41 (+I2CT=17,55,5C,86,41)

Read AC frequency

    +I2CT=ADDRESS,REGISTER_COMMAND,23 (+I2CT=17,0A,23)
    +I2CR=ADDRESS,04 (+I2CR=17,04)

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

Channel 1 - 4 (0x40)

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_READ_CHANNELS,40 (+I2CT=17,0A,12,40)
    +I2CR=ADDRESS,08 (+I2CR=17,08)

Channel 8 (0x17)

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_READ_CHANNELS,17 (+I2CT=17,0A,12,17)
    +I2CR=ADDRESS,02 (+I2CR=17,02)

Channel 2 and 3 (0x21)

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_READ_CHANNELS,21 (+I2CT=17,0A,12,21)
    +I2CR=ADDRESS,04 (+I2CR=17,04)

## DIMMER_COMMAND_WRITE_EEPROM

Store configuration and current levels in EEPROM

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_WRITE_EEPROM (+I2CT=17,0A,50)

## DIMMER_COMMAND_RESTORE_FS

Restore factory settings and re-initialize EEPROM wear leveling

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_RESTORE_FS (+I2CT=17,0A,51)

## DIMMER_COMMAND_READ_TIMINGS

Read timings for fine tuning. The return type is float and all values are in micro seconds

- DIMMER_TIMINGS_TMR1_TICKS_PER_US
- DIMMER_TIMINGS_TMR2_TICKS_PER_US
- DIMMER_TIMINGS_ZC_DELAY_IN_US
- DIMMER_TIMINGS_MIN_ON_TIME_IN_US
- DIMMER_TIMINGS_ADJ_HW_TIME_IN_US

Read zero crossing delay

    +I2CT=ADDRESS,REGISTER_COMMAND,REGISTER_CONFIG_OFS,TIMINGS_ZC_DELAY_IN_US (+I2CT=17,0A,23,03)
    +I2CR=ADDRESS,04 (+I2CR=17,04)

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

length is sizeof(register_mem_cfg_t), 0x10 in this example

    +I2CT=ADDRESS,REGISTER_READ_LENGTH,10,REGISTER_OPTIONS (+I2CT=17,0B,10,23)
    +I2CR=ADDRESS,10 (+I2CR=17,10)

Read temperature check interval

    +I2CT=ADDRESS,REGISTER_READ_LENGTH,REGISTER_START_ADDR,REGISTER_TEMP_CHECK_INT (+I2CT=17,0B,01,29)
    +I2CR=ADDRESS,01 (+I2CR=17,01)

Response (0x02, 2 seconds)

    +I2CT=ADDRESS,02 (+I2CT=17,02)

Set temperature check interval/metrics reporting to 30 seconds

    +I2CT=ADDRESS,REGISTER_TEMP_CHECK_INT,b30 (+I2CT=17,29,1E)

**NOTE:** The interval changes after the next check. DIMMER_COMMAND_FORCE_TEMP_CHECK (*+I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_FORCE_TEMP_CHECK (+I2CT=17,0A,54)*) can be used to force a check without waiting

## DIMMER_COMMAND_PRINT_INFO

Print dimmer info on serial port

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_PRINT_INFO (+I2CT=17,0A,53)

Response

Signature, compile options, current values and errors are returned

    +REM=sig=1e-95-0f,fuses=l:ff,h:da,e:fd,MCU=ATmega328P@16Mhz
    +REM=options=EEPROMwr=0,NTC=A0,IntTemp,TempChk,VCC,Fade,ACFrq=60,Pr=UART,CE=1,Addr=17,Pre=8/128,Ticks=2.0/0.125us,MaxLvls=16666,GPIO/lvl=6/0,8/0,9/0,10/0
    +REM=values=Restore=1,MainsFrq=60.24,Ref11=1.1,NTC=24.19/+0.0C,IntTemp=16.80/-10.0C,MaxTmp=65/2s,MetricsInt=30s,VCC=4.876,MinOn=240/120.00us,AdjHW=400/200.00us,ZCDelay=10/80.00us
    +REM=errors=FrqHi/Low=0/0,ZCmisfire=0,EEPROMCrcErr=1

## DIMMER_COMMAND_ZC_TIMINGS_OUTPUT

If ZC_MAX_TIMINGS is enabled, the dimmer outputs the zero crossing timings to the serial console every ZC_MAX_TIMINGS_INTERVAL milliseconds. ZC_MAX_TIMINGS needs to be equal or higher than the amount of expected data within this period. Collecting the data does not cause a delay of the ZC interrupt.

The data expected is a boolean. Non-zero values enable the output on.

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_ZC_TIMINGS_OUTPUT,01 (+I2CT=17,0A,60,01)

### Outut format

The first argument is the return value of micros() (uint32) hex encoded. Every following the difference to the previous time (uint16)

+REM=ZC,\<microseconds\> [\<delay\> [\<delay\> ...]]

    +REM=ZC,17f8c010 20b8 20b4 20b4 20b8 20b4 20b8 ...

## DIMMER_COMMAND_PRINT_METRICS

Print metrics every 5 seconds on serial port in human readable form. The following byte enables (non 0) or disables the output

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_PRINT_METRICS,05 (+I2CT=17,0A,55,05)

## DIMMER_COMMAND_PRINT_CUBIC_INT

Prints the cubic interpolation tables to the serial port. The first byte is the channel, -1 for all

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_PRINT_CUBIC_INT,b-1 (+I2CT=17,0A,56,FF)

Format:

Channel, X values, Y values, interpolated values per level

    +REM=ch=<num>,x=[0,1,...],y=[0,1,...],l=[0,1,7,20,300,...]

## DIMMER_COMMAND_GET_CUBIC_INT

Translate up to 11 levels for the provided table at once. This can be used to retrieve a preview of the entire curve. The returned values are int16

Table format:

`<level:int16>,<number of levels:uint8>,<x1:uint8>,<x2>,...,<y1:int16>,<y2>,...`

    +I2CT=ADDRESS,REGISTER_COMMAND,DIMMER_COMMAND_GET_CUBIC_INT,w10,b11,00,02,07,w0,w2500,w8192 (+I2CT=17,0A,57,0A,00,0B,00,02,07,00,00,C4,09,00,20)
    +I2CR=ADDRESS,b22 (+I2CR=17,16)

## DIMMER_COMMAND_FORCE_TEMP_CHECK

Force temperature check and report metrics if enabled

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_FORCE_TEMP_CHECK (+I2CT=17,0A,54)

## DIMMER_COMMAND_DUMP_MEM

Dump the content of the register memory to the serial port

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_DUMP_MEM (+I2CT=17,0A,EE)

## DIMMER_COMMAND_DUMP_CFG

Print the entire configration on the serial port as backup

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_DUMP_CFG (+I2CT=17,0A,91)

## DIMMER_COMMAND_SIMULATE_ZC

Simulate zero crossing events for 8 seconds. This will cause misfire if DIMMER_SIMULATE_ZC is not set

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_SIMULATE_ZC,08 (+I2CT=17,0A,E0,08)

## Temperature, VCC status and AC Frequency (DIMMER_RESPONSE_METRICS_REPORT)

If metrics reporting is enabled, the dimmer sends dimmer_metrics_t with DIMMER_TEMPERATURE_REPORT to it's own I2C address + 1.
This can also be trigger with the command DIMMER_COMMAND_FORCE_TEMP_CHECK. The maximum interval is set with cfg.report_metrics_max_interval, the minimum is cfg.temp_check_interval. The event is sent either when the maximum time has been reached, or if any values has changed significantly.

If data is not available, 0 (for VCC) or NaN (for any float) is returned.

    +I2CT=MASTER_ADDRESS,RESPONSE_METRICS_REPORT,02,... (+I2CT=18,F0,02)

## Temperature Alarm (DIMMER_RESPONSE_TEMPERATURE_ALERT)

If the max. temperature was exceeded, it sends one alarm with register address DIMMER_RESPONSE_TEMPERATURE_ALERT, the current temperature (uint8) and the temperature threshold (uint8)

Current temperature 37°C, threshold 85°C

    +I2CT=MASTER_ADDRESS,RESPONSE_TEMPERATURE_ALERT,25,55 (+I2CT=18,F1,25,55)

## Fading completed (DIMMER_RESPONSE_FADING_COMPLETE)

When fading to a new level has been completed, the dimmer sends DIMMER_RESPONSE_FADING_COMPLETE, with channel (int8) and level (int16). Channel and level can occur multiple times in the case 2 channels finished at the same time.

Channel 0 and 1 reached 0x1234 and fading is complete:

    +I2CT=MASTER_ADDRESS,RESPONSE_FADING_COMPLETE,00,12,34,01,12,34 (+I2CT=18,F2,00,12,34,01,12,34)

Channel 0 reached level 0:

    +I2CT=MASTER_ADDRESS,RESPONSE_FADING_COMPLETE,00,00,00 (+I2CT=18,F2,00,00,00)

## EEPROM written event (DIMMER_RESPONSE_EEPROM_WRITTEN)

EEPROM writes might be delayed due to wear leveling. Once written, DIMMER_RESPONSE_EEPROM_WRITTEN with structure DIMMER_RESPONSE_EEPROM_WRITTEN_t is sent.

    +I2CT=MASTER_ADDRESS,RESPONSE_EEPROM_WRITTEN,01,00,00,00,21,00,DC (+I2CT=18,F3,01,00,00,00,21,00,DC)

## Frequency warning (DIMMER_RESPONSE_FREQUENCY_WARNING)

If a too low or high frequency (<75% >120%) is detected, DIMMER_RESPONSE_FREQUENCY_WARNING will be sent. The second byte indicates if it was too low (0) or high (1), followed by register_mem_errors_t.
No zero crossing signal does not fire this event, but the frequency measurement will return NaN.

The errors are stored in *cfg.bits.frequency_low* and *cfg.bits.frequency_high*, which need to be reset manually.

## Zero Crossing calibration

Following commands are available for calibration.

Increase zero crossing delay by 1 tick

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_ZC_INCREASE (+I2CT=17,0A,83)

Decrease zero crossing delay

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_ZC_DECREASE (+I2CT=17,0A,82)

Set zero crossing delay to -31 ticks or -15.5µs and print setting

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_SET_ZC,w-31 (+I2CT=17,0A,92,E1,FF)
    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_SET_ZC,-15.5 (+I2CT=17,0A,92,00,00,78,C1)

The settings need to be stored in the EEPROM. The following command forces to write the EEPROM

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_FORCE_WRITE_EEPROM (+I2CT=17,0A,93)

Restore factory settings

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_RESTORE_FS (+I2CT=17,0A,51)

Display dimmer info

    +I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_PRINT_INFO (+I2CT=17,0A,53)
