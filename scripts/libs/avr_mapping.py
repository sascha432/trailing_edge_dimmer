#
#  Author: sascha_lammers@gmx.de
#

import re
import struct
import json
import importlib

class AvrPinMapping(object):

    def __init__(self, mcu):
        self.mcu = mcu
        file = 'libs.avr_mapping_%s' % mcu.lower()
        try:
            self.module = importlib.import_module(file, package=None)
        except:
            raise Exception('MCU %s not supported' % mcu)
        self.mapping = self.module.Mapping

    def dump(self):
        print(self.mapping.pins)
        print(self.mapping.analog_pins)
        print(self.mapping.digital_pins)
        print(self.mapping.pin_to_PIN)
        print(self.mapping.pin_to_PORT)
        print(self.mapping.pin_to_DDR)
        print(self.mapping.pin_to_BIT)
        print(self.mapping.timers)

    def get_bit(self, pin):
        return self.mapping.pin_to_BIT.__getitem__(pin)[0]

    def get_bv(self, pin):
        return self.mapping.pin_to_BIT.__getitem__(pin)[1]

    def get_pin(self, pin):
        return self.mapping.pin_to_PIN.__getitem__(pin)

    def get_port(self, pin):
        return self.mapping.pin_to_PORT.__getitem__(pin)

    def get_mcu_name(self):
        return self.mapping.name

    def get_signature(self):
        return self.mapping.signature
