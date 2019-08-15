## Changelog

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
