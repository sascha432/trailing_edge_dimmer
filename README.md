# Trailing Edge MOSFET Dimmer

Firmware for a trailing edge MOSFET dimmer.

* 16666 different dimming levels
* Up to 16 different channels
* Store last levels in EEPROM and restore during boot
* EEPROM wear level protection
* Serial protocol to control the dimmer
* Over temperature protection using an external NTC or the internal ATMEGA temperature sensor

# Improved zero crossing detection

* Low current consumption (0.15mA @ 120V)
* Tested with 85-265V 50/60Hz
* Logic level output with different opto isolators (4N25, PC817, ACPL-217)
* 50-110us pulse width to extend opto isolator live

![Zero crossing detection](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/Schematic_Isolated-zero-crossing-detection-with-logic-level-output.png)
[Open schematics...](https://github.com/sascha432/trailing_edge_dimmer/blob/master/docs/schematics/Schematic_Isolated-zero-crossing-detection-with-logic-level-output.svg)



# In action

![In action](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/oscilloscope_example.jpg)

# Dev board schematics with ESP8266

![Dev board](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/Schematic_4Ch-Dimmer-Rev1.3_dev_example.png)
[Open schematics...](https://github.com/sascha432/trailing_edge_dimmer/blob/master/docs/schematics/Schematic_4Ch-Dimmer-Rev1.3_dev_example.svg)
