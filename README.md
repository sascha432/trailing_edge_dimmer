# Trailing Edge MOSFET Dimmer

Firmware for a trailing edge MOSFET dimmer.

* 14bit / 16666 different dimming levels
* Up to 8 different channels
* Store last levels in EEPROM and restore during startup
* EEPROM wear level protection
* Serial protocol to control the dimmer
* I2C or UART interface
* Over temperature protection using an external NTC or the internal ATmega temperature sensor
* Highly configurable to match any hardware

[I2C/UART protocol](docs/protocol.md)

[Change Log v2.1.4](CHANGELOG.md)

## New and improved in-wall dimmer STL files

I have improved and updated the housing for the in-wall dimmer and added print instructions.

* Switches can be mounted on a PCB attached to the plate
* Space for 2 optional LEDs
* Invisible hole for reset switch
* Space for a 20mm fuse holder
* Labels for wires

[3D model in-wall version 1.1](stl/housing/v1.1)

[Instructions](stl/housing/v1.1/README.md)

## New plugin version for 1 Channel Dimmer

Check section [3D models](#3D-models-released) for a plugin housing.

![Plugin Dimmer](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/plugin.jpg)

## Updated 4 Channel Dimmer with Power Monitoring

Non isolated version with an offline primary side buck regulator (LNK306), reduced standby consumption of 0.45W compared to 0.58W of the 1 Channel dimmer. Up to 500W with heatsink.

![4 Channel Dimmer](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/new_4ch_dimmer.jpg)

[4 Channel Dimmer Schematics and PCB TO-252-2](https://easyeda.com/sascha23095123423/iot-4-channel-dimmer-with-pm)

[4 Channel Dimmer Schematics and PCB TO-220](https://easyeda.com/sascha23095123423/iot-4-channel-dimmer-with-pm_copy)

## Power Monitoring

I've finished testing the new power monitoring feature based on HLW8012 and compatible chips.
The new design uses the Hi-link 3.3V/1A power supply and the MP150, an offline primary side buck regulator, for the non-isolated 5V rail. The regular dimmer got an update as well and 4 MOSFETs can be installed to increase the maximum power up to 200/400W.

[1 Channel Dimmer with Power Monitor](https://easyeda.com/sascha23095123423/iot_1ch_dimmer_copy_copy_copy)

[1 Channel Dimmer with 4 MOSFETs](https://easyeda.com/sascha23095123423/iot_1ch_dimmer_copy_copy_copy_copy)

[New WiFi control board](https://easyeda.com/sascha23095123423/esp12e_iot_module_copy)

![New PCBs](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/1ch_dimmer_with_pm.jpg)

![KFC Firmware UI](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/kfcfw_ui3.jpg)

## WiFi Firmware update

The recent version of the KFC firmware supports programming the ATmega over the STK500v1 protocol directly from the ESP8266. I am using the Arduino bootloader for the ATmega328P mini PRO board@8MHz (ATmegaBOOT_168_atmega328_pro_8MHz.hex)

[KFC Firmware @ Github](https://github.com/sascha432/esp8266-kfc-fw)

![WiFi Firmware Update](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/wifi_firmware_update.jpg)

![KFC Firmware UI](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/kfcfw_ui2.jpg)

## Zero crossing detection update

I've improved the zero crossing detection by adding a RC filter, which improves the signal but still has a 0.5% error rate compared to 2.2% before.
Software filtering reduces the error rate to 0.001% even without the RC filter.

Test environment: 4x10W LED + 60W incandescent bulb, 50% dimmed, random 1000-2500V transients 5-20µs several times per second on the AC side.

![Comparision of unfiltered and filtered signal](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/zero_crossing_signal_filtering.png)

## 3D models released

![Printed version](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/housing_small.jpg)

[Open image](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/housing.jpg)

![3D model](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/housing_3d_model_tn.jpg)

[Open image](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/housing_3d_model.jpg)

[3D model in-wall version](stl/housing)

[3D model plugin version](stl/housing/plugin)

## Tested PCB Rev 3.3 is online

* [4 Channel Dimmer](https://easyeda.com/sascha23095123423/trailing-edge-dimmer-rev2)

![KFC FW UI](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/kfcfw_ui.jpg)
![4 Channel Dimmer](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/4ch_dimmer.JPG)

## PCBs arrived and first prototype is working

* In-Wall Dimmer
* ESP8266 with MQTT and Home Assistant integration
* Atmega328P as controller over UART
* [ESP12E/Atmega328P Control Module](https://easyeda.com/sascha23095123423/esp12e_iot_module)
* [1 Channel Dimmer Module](https://easyeda.com/sascha23095123423/iot_1ch_dimmer)

![1 Channel Dimmer](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/1ch_dimmer.JPG)

Testing it with a PWM generator to simulate the zero crossing signal, dimming a LED instead switching the MOSFET. The 120V part is waiting for opto couplers.

![Testing PCB](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/IMG_9100.JPG)

## Schematics of the final design

* 3.3V only
* Improved power consumption (~0.3-0.4W idle depending on the power supply)
* Improved MOSFET switching

![Final design](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/Schematic_4Ch-Dimmer-Rev3_1.png)

[Open schematics...](https://easyeda.com/sascha23095123423/trailing-edge-dimmer-rev2)

## Improved zero crossing detection

* Low current consumption (0.15mA @ 120V)
* Tested with 85-265V 50/60Hz
* Logic level output with different opto isolators (4N25, PC817, ACPL-217)
* 50-110us pulse width to extend opto isolator live

![Zero crossing detection](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/Schematic_Isolated-zero-crossing-detection-with-logic-level-output.png)

[Open schematics...](https://easyeda.com/sascha23095123423/isolated-zero-crossing-detection-with-logic-level-output)

## In action

![In action](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/oscilloscope_example.jpg)

## Dev board schematics with ESP8266

![Dev board](https://raw.githubusercontent.com/sascha432/trailing_edge_dimmer/master/docs/images/Schematic_4Ch-Dimmer-Rev1.3_dev_example.png)

[Open schematics...](https://github.com/sascha432/trailing_edge_dimmer/blob/master/docs/schematics/Schematic_4Ch-Dimmer-Rev1.3_dev_example.svg)
