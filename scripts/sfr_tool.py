#
# Author: sascha_lammers@gmx.de
#

import sys
import os
from os import path
import argparse
import tempfile
import time
import re
import hashlib

# can be found in 'framework-arduino-avr/variants/<TYPE>/pins_arduino.h'
class PinMapping:
    def __init__(self, mcu = None):
        self.mapping = None
        self.mappings = {
            'atmega328p': {
                'name': 'ATmega328P',
                'port_range': (0, 19),
                'analog_to_pin': {
                    14: ['A0', 'PIN_A0'],
                    15: ['A1', 'PIN_A1'],
                    16: ['A2', 'PIN_A2'],
                    17: ['A3', 'PIN_A3'],
                    18: ['A4', 'PIN_A4'],
                    19: ['A5', 'PIN_A5'],
                },
                'pin_to_port': [
                    'PORTD', 'PORTD', 'PORTD', 'PORTD', 'PORTD', 'PORTD', 'PORTD', 'PORTD',     # 0-7
                    'PORTB', 'PORTB', 'PORTB', 'PORTB', 'PORTB', 'PORTB',                       # 8-13
                    'PORTC', 'PORTC', 'PORTC', 'PORTC', 'PORTC', 'PORTC'                        # 14-19
                ],
                'pin_to_pin': [
                    'PIND', 'PIND', 'PIND', 'PIND', 'PIND', 'PIND', 'PIND', 'PIND',             # 0-7
                    'PINB', 'PINB', 'PINB', 'PINB', 'PINB', 'PINB',                             # 8-13
                    'PINC', 'PINC', 'PINC', 'PINC', 'PINC', 'PINC'                              # 14-19
                ],
                'pin_to_ddr': [
                    'DDRD', 'DDRD', 'DDRD', 'DDRD', 'DDRD', 'DDRD', 'DDRD', 'DDRD',             # 0-7
                    'DDRB', 'DDRB', 'DDRB', 'DDRB', 'DDRB', 'DDRB',                             # 8-13
                    'DDRC', 'DDRC', 'DDRC', 'DDRC', 'DDRC', 'DDRC'                              # 14-19
                ],
                'pin_to_bit': [
                    0, 1, 2, 3, 4, 5, 6, 7,                                                     # PORTD
                    0, 1, 2, 3, 4, 5,                                                           # PORTB
                    0, 1, 2, 3, 4, 5                                                            # PORTC
                ]
            }
        }
        self.mappings['atmega328pb'] = self.clone('atmega328p', 'ATmega328PB')
        self.set_mcu(mcu)

    def clone(self, mmcu, name):
        mapping = self.mappings[mmcu].copy()
        mapping['name'] = name
        return mapping

    def set_mcu(self, mcu):
        self.mcu_name = None
        self.mcu = mcu
        self.mapping = None
        if mcu:
            if not mcu in self.mappings:
                raise RuntimeError('MCU %s not supported' % mcu)
            self.mapping = self.mappings[self.mcu]
            self.mcu_name = self.mapping['name']

    def is_pin_valid(self, pin):
        if pin<0 or pin>len(self.mapping['pin_to_port']):
            return False
        return True

    def create_analog_mapping(self):
        vars = {}
        for pin in self.mapping['analog_to_pin']:
            for name in self.mapping['analog_to_pin'][pin]:
                vars[name] = pin
        return vars

    def pin_to_arduino_name(self, pin):
        if pin in self.mapping['analog_to_pin']:
            return self.mapping['analog_to_pin'][pin][0]
        else:
            return 'D%u' % pin

    def pin_to_port_bit_str(self, pin, add_pin = False):
        s = ''
        if add_pin:
            s = s + self.pin_to_arduino_name(pin) + '='
        s = s + '%s:%u' % (self.pin_to_port(pin), self.pin_to_bit(pin))
        return s

    def pin_to_type(self, pin, type):
        if type=='port':
            return self.pin_to_port(pin)
        elif type=='pin':
            return self.mapping['pin_to_pin'][pin]
        elif type=='ddr':
            return self.mapping['pin_to_ddr'][pin]
        raise RuntimeError('invalid type: %s' % type)

    def pin_to_sfr_addr(self, pin, type = 'port', use_mem_addr = False):
        addr = use_mem_addr and '_SFR_MEM_ADDR' or '_SFR_IO_ADDR'
        name = self.pin_to_type(pin, type)
        return '%s(%s)' % (addr, name)

    def pin_to_port(self, pin):
        return self.mapping['pin_to_port'][pin]

    def pin_to_bit(self, pin):
        return self.mapping['pin_to_bit'][pin]

    def range(self):
        return range(self.mapping['port_range'][0], self.mapping['port_range'][1])

    def str(self, pins, sep = ',', add_pin = True):
        parts = []
        if isinstance(pins, list):
            for pin in pins:
                parts.append(self.pin_to_port_bit_str(pin, add_pin))
        else:
            parts.append(self.pin_to_port_bit_str(pins, add_pin))
        return sep.join(parts)

#
# create code helper
#
# write_code(["string" or int])
#
# "any string" concatenates to the code
# "\t" indent to second column position
# int:
# 0 new line (or "\n")
# 1 new line + next line indentation +1 level
# -1 new line + next line indentation -1 level
#

indent_level = 0
indentation = '    '
line_length = 0
lines = []
new_line = '\n'

def _write_code_update_level(level = 0):
    global indent_level
    if level==-1 or level==-2:
        indent_level = indent_level + level
        if indent_level<0:
            raise RuntimeError('indent_level < 0')
    elif level==1:
        indent_level = indent_level + 1
    elif level!=0:
        raise RuntimeError("allowed level values are [-2, -1, 0, 1]: got %d" % lvel)

def write_code(msg = None):

    global indentation, indent_level, lines, line_length, new_line

    if not msg or len(msg)==0:
        lines.append(new_line)
        line_length = 0
        return

    for part in msg:
        if isinstance(part, int) or part=='\n':
            level = _write_code_update_level(int(part))
            lines.append(new_line)
            line_length = 0
            part = indentation * indent_level
        elif part=='\t':
            # second column position
            space_left = 56 - line_length
            if space_left<1:
                space_left = 1
            part = ' ' * space_left

        line_length = line_length + len(part)
        lines.append(part)

#
# main
#

parser = argparse.ArgumentParser(description="SFR Tool")
parser.add_argument("-O", "--output", help="output header file", required=True)
parser.add_argument("-P", "--pins", help="C array of pins i.e. '{8,9,A2}'", required=True)
parser.add_argument("--mmcu", help="MCU type i.e. 'atmega328p'", required=True)
parser.add_argument("--pin-funcs", help="create inline functions for specified pins", nargs='+', default=[])
parser.add_argument("-v", "--verbose", help="verbose output", action="store_true", default=False)

args = parser.parse_args()

def error(msg):
    print(msg, file=sys.stderr)
    sys.exit(1)

def verbose(msg):
    if args.verbose:
        print(msg)

pin_mapping = PinMapping()
try:
    pin_mapping = PinMapping(args.mmcu)
except RuntimeError as e:
    error(e)

try:
    locals().update(pin_mapping.create_analog_mapping())
    pins = []
    s = args.pins.replace('{', '[').replace('}', ']');
    for pin in eval(s):
        pin = int(pin)
        if not pin_mapping.is_pin_valid(pin):
            error("invalid pin: MCU %s: %u" % (pin_mapping.mcu_name, pin))
        pins.append(pin)
except Exception as e:
    error("failed to parse pins array: %s: %s" % (e, args.pins))

verbose("Pins: %s = %s" % (args.pins, pin_mapping.str(pins)))
verbose("MCU: %s (%s)" % (pin_mapping.mcu_name, args.mmcu))
verbose("Output file: %s" % (args.output))

#
# create header
#

write_code([
    '// AUTO GENERATED FILE - DO NOT MODIFY', 0,
    '// MCU: %s' % pin_mapping.mcu_name, 0,
    '// Channels: %s' % pin_mapping.str(pins), 0,
    '#pragma once', 0,
    '#include <avr/io.h>', 0,
    0,
])

channel_to_port_sfr_io_addr = {}
channel_to_port_number = {}
channel_to_port_bit = {}
port_number_sfr_io_addr = {}
port_number_port = {}
channel = 0
port_number = 0
ports = []
for pin in pins:
    pin = int(pin)
    bit = pin_mapping.pin_to_bit(pin)
    port = pin_mapping.pin_to_port(pin)
    channel_to_port_sfr_io_addr[channel] = 'DIMMER_CHANNEL%u_SFR_IO_ADDR' % channel;
    channel_to_port_number[channel] = 'DIMMER_CHANNEL%u_PORT_NUMBER' % channel;
    channel_to_port_bit[channel] = 'DIMMER_CHANNEL%u_BIT' % channel;
    if port not in ports:
        ports.append(port)
        port_number_sfr_io_addr[port_number] = "_SFR_IO_ADDR(%s)" % port
        port_number_port[port_number] = port
        port_number = port_number + 1
    port_mask = bit << (port_number * 3)
    write_code([
        '#define DIMMER_CHANNEL%u_SFR_IO_ADDR' % channel, '\t', '%s' % pin_mapping.pin_to_sfr_addr(pin), 0,
        '#define DIMMER_CHANNEL%u_SFR_MEM_ADDR' % channel, '\t', '%s' % pin_mapping.pin_to_sfr_addr(pin, 'port', True), 0,
        '#define DIMMER_CHANNEL%u_BIT' % channel, '\t', '%u' % bit, 0,
        '#define DIMMER_CHANNEL%u_BIT_MASK' % channel, '\t', '_BV(DIMMER_CHANNEL%u_BIT)' % channel, 0,
        '#define DIMMER_CHANNEL%u_PORT_NUMBER' % channel, '\t', '%u' % (port_number - 1), 0,
    ])
    channel = channel + 1


write_code([
    0,
    '#ifndef DIMMER_CHANNELS', 0,
    '#define DIMMER_CHANNELS', '\t', '%u' % len(pins), 0,
    '#endif', 0,
    0,
    '#define DIMMER_CHANNELS_NUM_PORTS', '\t', '%u' % len(ports), ' // %s' % ', '.join(ports), 0,
    0,
    'typedef uint8_t dimmer_enable_mask_t[DIMMER_CHANNELS_NUM_PORTS];', 0,
    0
])

port_range = range(0, len(ports))

for port_number in port_range:
    write_code([
        '#define DIMMER_CHANNEL_PORT%u_SFR_IO_ADDR' % port_number, '\t', port_number_sfr_io_addr[port_number], 0,
    ])
write_code()

def write_apply_enable_mask(name, operation):
    write_code([
        '#define %s(src)\\' % name, 1,
        '{\\', 1,
        'uint8_t tmp[%u];\\' % len(ports)
    ])
    for port_number in port_range:
        write_code([0, 'tmp[%u] = %s;\\' % (port_number, operation % (port_number_port[port_number], port_number))])
    for port_number in port_range:
        write_code([0, '%s = tmp[%u];\\' % (port_number_port[port_number], port_number)])
    write_code([
        -1,
        '}', -1,
        0
    ])

write_code(['// apply mask and set ports, interrupts need to be disabled during execution', 0])
write_apply_enable_mask('DIMMER_CHANNELS_SET_ENABLE_MASK', '(%s | src[%u])')
write_apply_enable_mask('DIMMER_CHANNELS_CLEAR_ENABLE_MASK', '(%s & ~src[%u])')

write_code(['// clear mask and set all channels to 0', 0])
write_code(['#define DIMMER_CHANNELS_ENABLE_MASK_CLEAR_CHANNELS(dst)', '\t', '{ ']);
for port_number in port_range:
    write_code(['dst[%u] = 0; ' % (port_number)])
write_code(['}', 0, 0])

write_code(['// copy mask', 0])
write_code(['#define DIMMER_CHANNELS_ENABLE_MASK_COPY(dst, src)', '\t', '{ ']);
for port_number in port_range:
    write_code(['dst[%u] = src[%u]; ' % (port_number, port_number)])
write_code(['}', 0, 0])

write_code([
    '#define DIMMER_CHANNELS_ENABLE_MASK_SET_CHANNEL(dst, ch)\\', 1,
    'switch(ch) {\\', 1
])
for i in range(0, channel):
    if i==0:
        write_code(['default:\\', 1])
    else:
        write_code(['case %u:\\' % i, 1])
    write_code(['dst[DIMMER_CHANNEL%u_PORT_NUMBER] |= DIMMER_CHANNEL%u_BIT_MASK;\\' % (i, i), 0])
    write_code(['break;\\'])
    if i!=channel - 1:
        write_code([-1])
write_code([-2, '}', -1, 0])

def write_set_channel(name, instr):
    write_code([
        '#define %s(ch)\\' % name, 1,
        'switch(ch) {\\', 1
    ])
    for i in range(0, channel):
        if i==0:
            write_code(['default:\\', 1])
        else:
            write_code(['case %u:\\' % i, 1])
        write_code([
            'asm volatile ("%s %%0, %%1" :: "I" (DIMMER_CHANNEL%u_SFR_IO_ADDR), "I" (DIMMER_CHANNEL%u_BIT));\\' % (instr, i, i), 0,
            'break;\\'
        ])
        if i!=channel - 1:
            write_code([-1])
    write_code([-2, '}', -1, 0])

write_set_channel('DIMMER_CHANNELS_ENABLE_CHANNEL', 'sbi')

write_set_channel('DIMMER_CHANNELS_DISABLE_CHANNEL', 'cbi')

def write_channel_array(name, array):
    parts = []
    for i in range(0, channel):
        parts.append(array[i])
    write_code(['constexpr uint8_t %s[] = { %s };' % (name, ', '.join(parts)), 0])

write_channel_array('channel_to_port_sfr_io_addr', channel_to_port_sfr_io_addr)
write_channel_array('channel_to_port_number', channel_to_port_number)
write_channel_array('channel_to_port_bit', channel_to_port_bit)
write_code([0])

if args.pin_funcs:

    for pin in args.pin_funcs:
        pin = int(pin)
        write_code([
            '#define PIN_%s_SET()' % pin_mapping.pin_to_arduino_name(pin), '\t',
            'asm volatile("sbi %%0, %%1" :: "I" (%s), "I" (%u))' % (pin_mapping.pin_to_sfr_addr(pin), pin_mapping.pin_to_bit(pin)), 0,
            '#define PIN_%s_CLEAR()' % pin_mapping.pin_to_arduino_name(pin), '\t',
            'asm volatile("cbi %%0, %%1" :: "I" (%s), "I" (%u))' % (pin_mapping.pin_to_sfr_addr(pin), pin_mapping.pin_to_bit(pin)), 0,
            '#define PIN_%s_TOGGLE()' % pin_mapping.pin_to_arduino_name(pin), '\t',
            'asm volatile("sbi %%0, %%1" :: "I" (%s), "I" (%u))' % (pin_mapping.pin_to_sfr_addr(pin, 'pin'), pin_mapping.pin_to_bit(pin)), 0,
            '#define PIN_%s_IS_SET()' % pin_mapping.pin_to_arduino_name(pin), '\t',
            '((%s & _BV(%u)) != 0)' % (pin_mapping.pin_to_sfr_addr(pin, 'pin'), pin_mapping.pin_to_bit(pin)), 0,
            '#define PIN_%s_IS_CLEAR()' % pin_mapping.pin_to_arduino_name(pin), '\t',
            '((%s & _BV(%u)) == 0)' % (pin_mapping.pin_to_sfr_addr(pin, 'pin'), pin_mapping.pin_to_bit(pin)), 0,
            0,
        ])

    write_code([0])

#
# write to output
#
if args.output=='-':
    for line in lines:
        print(line, end='')
else:
    if not path.exists(args.output):
        verbose("Creating output file")
        with open(args.output, 'wt') as file:
            for line in lines:
                file.write(lines, end='')
    else:
        file_hash = hashlib.sha1()
        file = open(args.output, 'r+t')
        for line in file:
            line = line.strip('\r\n')
            file_hash.update(line.encode(file.encoding))
        file.seek(0)

        new_hash = hashlib.sha1()
        for line in lines:
            # s = line.replace("\n", "\\n").replace('"', '\\"').replace('\\', '\\\\')
            # print('"%s"' % s)
            line = line.strip('\r\n')
            new_hash.update(line.encode(file.encoding))

        if file_hash.hexdigest()==new_hash.hexdigest():
            verbose("No changes detected")
        else:
            verbose("Overwriting output file")
            file.seek(0);
            file.truncate();
            file.writelines(lines)

        file.close()
