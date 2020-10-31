# I2C/UART protocol

The dimmer is controlled via I2C or UART interface.

The default address is 0x17 for the slave. When sending data, the dimmer acts as master and sends to address 0x18 (slave address + 1).

The values for the registers and commands can be found in [dimmer_protocol.h](../src/dimmer_protocol.h)

The examples are using the UART protocol and can send to the dimmer using any terminal software. The commands might not be up-to-date.

Using the Arduino TwoWire class (or the drop-in replacement for UART [SerialTwoWire](https://github.com/sascha432/i2c_uart_bridge)) instead:

    // +I2CT=17,89,22
    Wire.beginTransmission(DIMMER_I2C_ADDRESS);
    Wire.write(DIMMER_REGISTER_COMMAND);
    Wire.write(DIMMER_COMMAND_READ_VCC);
    if (Wire.endTransmission() == 0) {

        // +I2CR=17,02
        uint16_t vcc;
        if (Wire.requestFrom(DIMMER_I2C_ADDRESS, sizeof(vcc)) == sizeof(vcc)) {
            Wire.readBytes(reinterpret_cast<const uint8_t *>(&vcc), sizeof(vcc));
        }
    }

## Python tool

The dimmer can be configured and monitored over the serial port or a I2C to serial converter with the python CLI tool

    python ./scripts/cfg_tool.py --port COM6 -j monitor
    TX 3 bytes to 0x17: +I2CT=178a02b9
    RQ 2 bytes from 0x17: +I2CR=1702
    Detected version: 2.2.0
    Monitoring serial port...
    Metrics: temp=26°C VCC=4840mV frequency=60.084Hz ntc=-273.15°C int=26.55°C
    Metrics: temp=26°C VCC=4844mV frequency=60.084Hz ntc=-273.15°C int=26.71°C

For more options check

    python ./scripts/cfg_tool.py --help

### Modifying the dimmer configuration

The configuation can be modifed for a specific version without a physical connection to the dimmer.

    python ./scripts/cfg_tool.py modify --version 2.2 --data '+REM=v840,i2ct=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500000020001412' -s range_begin=1
    Detected version: 2.2.0
    Set range_begin to 1
    +I2CT=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500

JSON output instead of the SerialTwoWire command

    python ./scripts/cfg_tool.py display --version 2.2 --data '+REM=v840,i2ct=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500000020001412' -j
    Detected version: 2.2.0
    {
        "options": "2",
        "max_temp": "75",
        "fade_in_time": "4.5",
        "zero_crossing_delay_ticks": "2",
        "minimum_on_time_ticks": "0",
        "minimum_off_time_ticks": "1200",
        "range_begin": "3583",
        "range_end": "512",
        "internal_vref11": "1.075098",
        "int_temp_offset": "-13.00",
        "ntc_temp_offset": "-29.00",
        "report_metrics_max_interval": "63",
        "halfwave_adjust_ticks": "0",
        "switch_on_minimum_ticks": "1280",
        "switch_on_count": "0"
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

    +I2CT=17,80,ff,ff,00,03,01,00,00,f0,40,11
                ^^^^^ from level           ^^ command
                      ^^ channnel
                         ^^^^^ to level
                               ^^^^^^^^^^^ time

Short version

    +I2CT=7580ffff0003000000f04011

Assuming *from level* is the default -1, set *channel* to -1, *to level* to 0x0301, *time* 7.5

    +I2CT=17,82,ff,03,01,00,00,f0,40,11

## DIMMER_COMMAND_SET_LEVEL

The fading command uses following registers

- DIMMER_REGISTER_CHANNEL (int8)
- DIMMER_REGISTER_TO_LEVEL (int16)

Set *channel* to 1, *to level* to 777 (0x0309) and execute set level command

    +I2CT=17,82,01,09,03
    +I2CT=17,89,10

To send the command in one transmission, the time can be filled with any data

    +I2CT=17,82,01,09,03,00,00,00,00,10

## DIMMER_COMMAND_READ_xxx

This applies to

- DIMMER_COMMAND_READ_NTC (float)
- DIMMER_COMMAND_READ_INT_TEMP (float)
- DIMMER_COMMAND_READ_VCC (uint16)

If no further data is sent after the read command, the register is set automatically to

- DIMMER_REGISTER_TEMP (float)
- DIMMER_REGISTER_VCC (uint16)

The temperatures and VCC are read once per second

Read VCC

    +I2CT=17,89,22
    +I2CR=17,02

Response (0x3613 = 4.918V)

    +I2CT=753613

Read internal temperature

    +I2CT=17,89,21
    +I2CR=17,04

Read int. temp and VCC

In this example, *DIMMER_REGISTER_READ_LENGTH* is set manually to 6 byte, followed by the start address *DIMMER_REGISTER_TEMP*

    +I2CT=17,89,21,89,22,8a,06,9c
    +I2CR=17,06

If the temperature is requested last, it is not required to set read length and register address

    +I2CT=17,89,22,89,21
    +I2CR=17,06

Read AC frequency

    +I2CT=17,89,23
    +I2CR=17,04

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

    +I2CT=17,89,12,40
    +I2CR=17,08

Channel 8

    +I2CT=17,89,12,17
    +I2CR=17,02

Channel 2 and 3

    +I2CT=17,89,12,21
    +I2CR=17,04

## DIMMER_COMMAND_WRITE_EEPROM

Store current dimming levels in EEPROM. If the following byte is 92, the configuration is also stored. If the data matches the last stored configuration, nothing is written to the EEPROM

***Note:*** The command might be delayed due to the wear leveling algorithm. The maximum delay is *EEPROM_REPEATED_WRITE_DELAY* (5 seconds by default) Any changes during this time will be written to the EEPROM as well

See *DIMMER_COMMAND_WRITE_EEPROM_NOW* how to force writing immediatelly.

In UART or I2C master/master mode, the event *DIMMER_EEPROM_WRITTEN* confirms successful execution. It also indicates if any data has been written to the EEPROM.

    +I2CT=17,89,50[,92]

## DIMMER_COMMAND_PRINT_CONFIG

Print version and configuration on serial port. The I2CT command in the output can be used to restore the configuration if the firmware version matches

    +I2CT=17,89,91

## DIMMER_COMMAND_WRITE_EEPROM_NOW

Store current dimming levels in EEPROM immediately without the wear leveling algorithm or comparing the EEPROM for changes. During normal operation it is recommended to use *DIMMER_COMMAND_WRITE_EEPROM* instead. If the following byte is 92, the configuration is also stored.

In UART or I2C master/master mode, the event *DIMMER_EEPROM_WRITTEN* confirms successful execution

***Note:*** This command cancels all previous *DIMMER_COMMAND_WRITE_EEPROM* commands that have not been executed yet. If the configuration was set to be saved, it will be saved as well.

It is recommended to execute this command several times after the initial calibration. This ensures that several copies of the configuration exist and can be used in case of a read failure or damanged EEPROM cells.

    +I2CT=17,89,93[,92]

## DIMMER_COMMAND_MEASURE_FREQ

Start frequency measurement. This turns all channels off and the dimmer will not execute any commands during measurement. After the measurement has finished, the dimmer restarts and all pending requests (including writing configuration to the EEPROM) are reset

***Note:*** this command is only available if DEBUG or DEBUG_COMMANDS is set

    +I2CT=17,89,94

## DIMMER_COMMAND_INIT_EEPROM

Initialize EEPROM, restore factory defaults and set write counter to 0

***Note:*** this command is only available if DEBUG or DEBUG_COMMANDS is set

    +I2CT=17,89,95

## DIMMER_COMMAND_RESTORE_FS

Restore factory defaults and store in EEPROM

    +I2CT=17,89,51

## DIMMER_COMMAND_GET_TIMER_TICKS

Get ticks per microsecond for Timer 1 as float

    +I2CT=17,89,52
    +I2CR=17,04

## DIMMER_COMMAND_READ_AC_FREQUENCY

Read AC frequency as float

    +I2CT=17,89,23
    +I2CR=17,04

## Reading firmware version

Reading the firmware version is using the same transmission for all versions

```
+I2CT=17,8a,02,b9
+I2CR=17,02

+I2CT=172608
```

- bit 0-4 - Revision
- bit 5-9 - Minor version
- bit 10-14 - Major version
- bit 15 - Reserved

```
v2.1.6
0x0826
[0][00010][00001][00110]
        2      1      6
```


## Reading and writing the dimmer settings

### Settings

- DIMMER_REGISTER_OPTIONS (uint8, bitset, see Options)
- DIMMER_REGISTER_MAX_TEMP (uint8, °C)
- DIMMER_REGISTER_FADE_IN_TIME (float, seconds)
- DIMMER_REGISTER_ZC_DELAY_TICKS (uint16)
- DIMMER_REGISTER_MIN_ON_TIME_TICKS (uint16)
- DIMMER_REGISTER_MIN_OFF_TIME_TICKS (uint16)
- DIMMER_REGISTER_INT_VREF11 (int8, value * 0.488mV + 1.1V)
- DIMMER_REGISTER_INT_TEMP_CAL_OFFSET (uint8_t)
- DIMMER_REGISTER_INT_TEMP_CAL_GAIN (uint8_t)
- DIMMER_REGISTER_NTC_TEMP_OFS (int8, 0.25°C)
- DIMMER_REGISTER_METRICS_INT (uint8, seconds, 0 = disabled)
- DIMMER_REGISTER_ADJ_HW_CYCLES (int8, clock cycles to adjust half wave length)
- DIMMER_REGISTER_RANGE_BEGIN (int16)
- DIMMER_REGISTER_RANGE_END (int16)
- DIMMER_REGISTER_SWITCH_ON_MIN_TIME (uint16)
- DIMMER_REGISTER_SWITCH_ON_COUNT (uint8)

#### Options

- Bit 0: Restore last levels on reset
- Bit 2: Temperature alarm indicator. Needs to be cleared manually after it has been triggered
- Bit 3: Leading edge mode
- Bit 4: Negative ZC delay. The delay is subtracted from the halfwave length and occurs 'n' ticks before the next signal
- Bit 5: unused
- Bit 6: unused
- Bit 7: unused

To make any changes permanent, *DIMMER_COMMAND_WRITE_CFG_NOW* with *DIMMER_COMMAND_WRITE_CONFIG* needs to be executed.

Read all settings

    +I2CT=17,8a,18,a2
    +I2CR=17,18

Set report metrics interval to 30 seconds

    +I2CT=17,b5,1e

**Note:** The interval changes after a metrics report has been sent. DIMMER_COMMAND_FORCE_TEMP_CHECK (*+I2CT=17,89,54*) can be used to force a check without waiting

Read report metrics interval

    +I2CT=17,8a,01,b5
    +I2CR=17,01

Response for 30 seconds

    +I2CT=171e

## DIMMER_COMMAND_SET_MODE

Set dimmer mode. The following byte indicates the mode. 0 is trailing edge, 1 is leading edge. It is recommended to turn all channels off **before** switching mode

    +I2CT=17,89,56,01

## DIMMER_COMMAND_PRINT_INFO

Print dimmer info on serial port

    +I2CT=17,89,53

### Print info details

**NOTE:** This section is not up to date

    +REM=MOSFET Dimmer 2.2.0 Oct 23 2020 19:45:45 Author sascha_lammers@gmx.de
    +REM=sig=1e-95-0f,fuses=l:ff,h:da,e:fd,MCU=ATmega328P@16Mhz
    +REM=options=EEPROM=0,NTC=A6,int.temp,VCC,proto=UART,fading_events=1,addr=17,mode=T,timer1=8/2.00,lvls=8192,p=6,9,range=0-8192
    +REM=values=restore=0,f=60.073Hz,vref11=1.100,NTC=27.15/+0.00,int.temp=26.55/+0.00,max.temp=75,metrics=5,VCC=4.844,min.on-time=5000,min.off=2000,ZC-delay=1000,sw.on-time=0/0

#### sig, fuses, MCU

- AVR MCU signature
- Low, high and extended fuse bits
- MCU name if available

#### options

- EEPROM = eeprom write counter
- NTC = NTC pin
- int.temp = internal temperature sensor available
- VCC = internal VCC reading available
- fading_events = fading completed events enabled
- proto = UART or I2C protocol
- addr = I2C address
- mode = T(trailing)/L(eading) edge
- timer1 = prescaler/ticks per µs
- lvls = max. levels
- pins = gate driver output pins
- range = virtual range between 0 and max. level

#### values

- restore = restore last level on reset / power loss
- f = measured mains frequency
- vref11 = interval 1.1V voltage reference calibration
- NTC = NTC temperature / +-offset correction in °C
- int.temp = internal temperature / +-offset correction in °C
- max.temp = max. temperature before shutting down
- metrics = report metrics interval in seconds or 0 for disabled
- VCC = VCC in V
- min.on-time = minimum on time ticks (timer1)
- min-off = minimum off time ticks
- zcdelay = zero crossing delay in ticks
- sw.on-time = switch on minimum time in ticks / duratiuon in half cycles (120 = 1 second for 60 Hz, 1 = 8.333ms...)

## DIMMER_COMMAND_PRINT_METRICS

Print metrics on serial port in human readable form. The following byte enables or disables the output. The print interval is multiplied by 100ms.

***Note:*** Only available if HAVE_PRINT_METRICS is set to 1

For example 0x04 * 256ms = ~1s

    +I2CT=17,89,55,04

## DIMMER_COMMAND_FORCE_TEMP_CHECK

Force temperature check and report metrics if enabled

    +I2CT=17,89,54

## Commands available if DEBUG or DEBUG_COMMANDS is set to 1

### DIMMER_COMMAND_INCR_ZC_DELAY

Increase zero crossing delay by 1 or the following byte value

    +I2CT=17,89,82[,<byte>]

### DIMMER_COMMAND_DECR_ZC_DELAY

Decrease zero crossing delay by 1 or the following byte value

    +I2CT=17,89,83[,<byte>]

### DIMMER_COMMAND_SET_ZC_DELAY

Set zero crossing delay to the value of the following word

    +I2CT=17,89,84,<lo-byte>,<hi-byte>

### DIMMER_COMMAND_INCR_HW_TICKS

Increase halfwave length by 1 or the following byte value

    +I2CT=17,89,85[,<byte>]

### DIMMER_COMMAND_DECR_HW_TICKS

Decrease halfwave length by 1 or the following byte value

    +I2CT=17,89,86[,<byte>]

### DIMMER_COMMAND_DUMP_CHANNELS

Print dimmed channels. Channels that are off or fully on are not listed

    +I2CT=17,89,ed

### DIMMER_COMMAND_DUMP_MEM

Print the contents of the register memory

    +I2CT=17,89,ee

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

Currently not implemented

## Channel on/off state (DIMMER_CHANNEL_ON_OFF)

When a channel is turned on or off, this event is fired. If fading is used, the event is fired immediately before fading reaches the final state. The event data is one byte containing a bitset of the channel states.

For example channel 0 and 2 are on

    +I2CT=18F505

All channels off

    +I2CT=18F500

## Commands cheatsheet

Not all commands are available if DEBUG_COMMANDS is not enabled. They are marked with (*)

### Increase zero crossing delay by 10 (*)

    +I2CT=17,89,82,0a

### Decrease zero crossing delay by 10 (*)

    +I2CT=17,89,83,0a

### Set zero crossing delay to 1500 (0x05DC) and print setting (*)

    +I2CT=17,89,84,DC,05

### Print register memory(*)

    +I2CT=17,89,ee

### Print configuration

Print current configuration. The command can be used to backup/restore the configuration or translate it to a human readable form with cfg_tool.py

    +I2CT=17,89,91

For example

    +REM=v0840,i2ct=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500000020001412

### Write current settings to EEPROM

    +I2CT=17,89,93,92

### Restore factory defaults

    +I2CT=17,89,51

### Print Information

    +I2CT=17,89,53

### Print metrics every 5 seconds (50=0x32 * 100ms)

Available only if HAVE_PRINT_METRICS is set to 1

    +I2CT=17,89,55,32

### Turn print metrics off

    +I2CT=17,89,55,00

### Read firmware version

    +I2CT=17,8a,02,b9
    +I2CR=17,02
