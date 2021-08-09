# Changelog

## 2.2.0

- Removed linear correction
- Removed ZC_MAX_TIMINGS
- Level range can be configured
- Minimum on-time can be adjusted dynamically for devices that need a certain voltage level to start-up
- Configurable trailing/leading edge mode
- Frequency auto detection (50/60Hz)
- Increased ZC delay to 16bit / 500ns resolution
- Support for asynchronous ZC signals
- Filter invalid ZC signals and continue to run up to several seconds without being synchronized
- Python tool to configure/monitor the dimmer over the serial port (for version 2.1.x and 2.2.x only)
- EEPROM wear leveling improved and fail-safe added
- Tool to generate inline assembler for toggling MOSFET pins
- Support for TRIACs (leading edge only) added - tested with MOSFETs, BJTs and TRIACs
- Improved performance and reduced code size using the ADC interrupt
- Reboot notification event after the frequency measurement has been completed
- Patch for Arduino library
- Structure updates
- Fix issue in serial protocol of the python config tool

## 2.1.5

- Fixed issues with millis overflow
- Replaced frequency and misfire error with single type of error
- SerialTwoWire updated
- Replaced crc16.cpp with a library
- Changed default max. temperature to 75°C and metrics update interval to 5 seconds
- Added environments for flashing the bootloader to ATMega328P and ATMega328PB @ 8MHz and BOD disabled
- Improved reading VCC and internal temperature

## 2.1.4

- Added DIMMER_ZC_INTERRUPT to specify rising or falling interrupt triggering
- Removed DIMMER_COMMAND_RESET since it was not working with several versions of the bootloader

## 2.1.3

- Fixed bug in EEPROM wear leveling and invalid CRC after cycling
- Added output of EEPROM read/write status to serial port

## 2.1.2

- Fixed 32bit overflow in timer that caused the zero crossing detection to malfunction
- Added +REM=BOOT message in setup()

## 2.1.1

- Changed max. temperature to 90°C which is the maximum operation temperature allowed for dimmers (195F)
- Added filter to skip all ZC interrupts above 90Hz (@60Hz mains)
- Added error counter for high/low frequency and zero crossing misfire
- Added debugging code to send zero crossing interrupt timings to serial port (ZC_MAX_TIMINGS)
- Fixed wrong NTC PIN at dimmer info

## 2.1.0

- Added version to register memory (DIMMER_REGISTER_VERSION)
- Added print dimmer info command (DIMMER_COMMAND_PRINT_INFO)
- Added command force temperature check (DIMMER_COMMAND_FORCE_TEMP_CHECK)
- Added structure dimmer_metrics_t for DIMMER_METRICS_REPORT
- Added CRC16 to EEPROM configuration
- Added event that indicates that the EEPROM has been written (DIMMER_EEPROM_WRITTEN)
- Added print metrics on serial port (DIMMER_COMMAND_PRINT_METRICS)
- Added offset for internal temperature sensor and ntc (DIMMER_REGISTER_xxx_TEMP_OFS, int8 * 0.25 °C, ~ +-32°C)
- Added warning if the AC frequency is below 75% or above 120% (DIMMER_FREQUENCY_WARNING)
- Added undocumented commands for testing and calibration (0x80-0x91, i2c_slave.cpp)
- Added MCU detection for adjusting internal temperature sensor
- DIMMER_COMMAND_READ_NTC, DIMMER_COMMAND_READ_INT_TEMP and DIMMER_COMMAND_READ_AC_FREQUENCY return NaN if not available, DIMMER_COMMAND_READ_VCC 0
- Fixed outdated debug code
- Fixed issue with reading ADC values and delay() inside the I2C interrupt callback
- Fixed empty configuration structure after reset without calling _write_config()
- Fixed int overflow for temp_check_interval > 32
- Fixed pin mode for NTC
- Fixed fading with short time intervals and float not having enough precision for a sinle step
- Changed default values for ZC crossing delay and other timings to match my dimmer design
- Changed DIMMER_TEMPERATURE_REPORT to DIMMER_METRICS_REPORT

## 2.0.2

- Configurable timing parameters for the MOSFET
- Added documentation for timings to dimmer.h
- Display compile settings and values during start up (HIDE_DIMMER_INFO)
- Added AC frequency measurement (FREQUENCY_TEST_DURATION)
- Enabled printf float formatting and removed PrintEx library
- Added event to indicate when a fading operation has been completed (HAVE_FADE_COMPLETION_EVENT)
- Fixed an issue with floats and rounding when using fading

## 2.0.1

- Changed default I2C address to 0x17/0x18
- Increased delay when reading internal temperature and VCC
- Added macros for thermistor temperature calculation
- Changed macro names to match pattern, additional macros to enable/disable reading VCC, NTC, internal temp. sensor

## 2.0.0

- Added [I2C slave protocol](docs/protocol.md)
- The serial protocol was replaced by [I2C over UART emulation](https://github.com/sascha432/i2c_uart_bridge)
- Added example how to control the dimmer via I2C and UART
- Removed SLIM version
- Auto select prescaler bits for DIMMER_TIMER2_PRESCALER
- Changes for Platform IO 4.0

## 1.0.9

- Added some extra ticks if timer interrupts are close to avoid skipping one
- Improved the timing of the zero crossing interrupt using timer2
- Added min. "on" time

## 1.0.8

- Added VCC to dimmer info and temperature report (INTERNAL_VREF_1_1V might need some adjustments to be precise)
- Added CPU Frequency to dimmer info
- Support for ATMEGA Mini Pro 3.3V @ 8MHz
- Set default prescaler to 8 increasing dimming levels to 16666 for 16MHz and 8333 for 8MHz
- Respond to invalid commands with error
- Changed part of the fade response from "to=" to "lvl="

## 1.0.7

- Support for the internal temperature sensor of the ATMEGA

## 1.0.6

- EEPROM wear leveling to increase writes ((EEPROM size - 8 byte) / size of configuration) = 50, which should be ~5 million writes

## 1.0.5

- EEPROM write delay to reduce writes
- Added prefix "~$" for commands

## 1.0.4

- Slim version with less than 7.5kb for ATMEGA88. No EEPROM support and different serial protocol

## 1.0.3

- Serial command to change configuration
- Store configuration in EEPROM

## 1.0.2

- NTC with configurable over temperature shutdown
- Store last levels in EEPROM and restore when power is turned on

## 1.0.1

- Added support for multiple channels to the dimmer library
- Added debug code
- Increased dimming levels to 32767 (DIMMER_MAX_LEVEL)

## 1.0.0

- Initial version
