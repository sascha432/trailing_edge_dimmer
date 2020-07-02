#
# Author: sascha_lammers@gmx.de
#

import json
import struct
from lib.dimmer_protocol import DimmerProtocol

class DimmerConst(DimmerProtocol):
    def __init__(self):
        DimmerProtocol.__init__(self)

    def unpack_struct(self, structure, data):
        parts = {}

        def print_fmt(type):
            if type in 'BHIL':
                return '%u'
            elif type in 'bhil':
                return '%d'
            elif type in 'f':
                return '%f'
            return '%s'

        format = '='
        for name, type in structure.items():
            if name=='__SIZE':
                pass
            elif isinstance(type, list):
                for _type in type:
                    format += _type
            else:
                format += type
        values = struct.unpack(format, data)
        n = 0
        for name, type in structure.items():
            if name=='__SIZE':
                pass
            elif isinstance(type, dict):
                start_n = n
                for _name, _type in type.items():
                    format = format + _type
                    if not name in parts:
                        parts[name] = {}
                    if not _name in parts[name]:
                        parts[name][_name] = {}
                    parts[name][_name][n - start_n] = values[n] #print_fmt(_type) % values[n]
                    n += 1
            elif isinstance(type, list):
                start_n = n
                for _type in type:
                    format = format + _type
                    if not name in parts:
                        parts[name] = {}
                    parts[name][n - start_n] = values[n] #print_fmt(_type) % values[n]
                    n += 1
            else:
                parts[name] = values[n] #print_fmt(type) % values[n]
                n += 1
        return parts

    def get_by_value(self, value):
        for key, val in self.constants.items():
            if val==value:
                return key
        return False

    def get(self, name):
        if name in self.constants:
            return self.constants[name]
        return False

    def parse_command(self, command):
        type = '+i2ct'
        if '=' in command:
            type, data = command.split('=', 2)
            if type and type[0]!='+':
                    type = '+' + type
        else:
            data = command

        type = type.upper()
        types = ['+I2CT', '+I2CR']
        if type not in types:
            print("command type invalid: %s: '%s': choices: %s" % (type, command, ','.join(types)))
            sys.exit(-1)

        return (type, data)

    def float_to_hex(self, value):
        hex_str = ''
        for b in struct.pack('<f', value):
            hex_str += ('%02X' % b)
        return hex_str

    def to_hex(self, value, type, split_bytes = True):

        if type.endswith('int32'):
            if value<0:
                value = (1<<32) + value
            hex_str = '%02X' % (value & 0xff)
            if split_bytes:
                hex_str += ','
            hex_str += '%02X' % ((value >> 8) & 0xff)
            if split_bytes:
                hex_str += ','
            hex_str += '%02X' % ((value >> 16) & 0xff)
            if split_bytes:
                hex_str += ','
            hex_str += '%02X' % ((value >> 24) & 0xff)
            return hex_str
        elif type.endswith('int16'):
            if value<0:
                value = (1<<16) + value
            hex_str = '%02X' % (value & 0xff)
            if split_bytes:
                hex_str += ','
            hex_str += '%02X' % ((value >> 8) & 0xff)
            return hex_str
        elif type=='float':
            hex_str = self.float_to_hex(value)
            if split_bytes:
                return ','.join(re.findall('..', hex_str))
            return hex_str
        if value<0:
            value = (1<<8) + value
        return '%02X' % value

    def translate_command(self, command):
        type, data = command
        data = data.split(',')
        verbose('command type=%s, data=%s' % (type, data))

        parts = []
        parts_verbose = [ 'type=%s' % type ]
        for arg in data:
            part, verbose_type = self.to_value(arg)
            part_str = self.to_hex(part, verbose_type)
            verbose_part_str = self.to_hex(part, verbose_type, False)
            parts.append(part_str)
            if verbose_type=='const':
                parts_verbose.append('const:%s' % self.get_by_value(part))
            elif verbose_type=='float':
                parts_verbose.append('%s:%s (%f)' % (verbose_type, self.float_to_hex(part), part))
            else:
                fmt = '%s:%s (%d)'
                if verbose_type.startswith('u'):
                    fmt = '%s:%s (%u)'
                parts_verbose.append(fmt % (verbose_type, verbose_part_str, part))

        verbose('command parts: %s' % str(parts_verbose))

        return type + '=' + ','.join(parts)

    def to_command(self, value, pos):
        try:
            value = int(value, 16)
            if pos==0:
                if value==args.slave_address:
                    return 'ADDRESS'
                elif value==args.master_address:
                    return 'MASTER_ADDRESS'
            value_str = self.get_by_value(value)
            if value_str:
                return value_str
            return '%02X' % value
        except Exception as e:
            verbose('to_command: value=%s, pos=%u: %s' % (value, pos, e))
            return value

    def to_value(self, value_str):
        if value_str.startswith('DIMMER_'):
            value_str = value_str[7:]
        value = self.get(value_str)
        if value:
            return (value, 'const')
        if value_str=='ADDRESS':
            return (args.slave_address, 'slave_addr')
        elif value_str=='MASTER_ADDRESS':
            return (args.master_address, 'master_addr')

        def int_type_str(type):
            ts = 'b'
            if type=='f':
                return 'float'
            elif type=='q':
                ts = 'int32'
            elif type=='w':
                ts = 'int16'
            elif type=='b':
                ts = 'int8'
            if len(type)<2 or not type[1]=='-':
                ts = 'u' + ts
            return ts

        try:
            if value_str.startswith('b') or value_str.startswith('w') or value_str.startswith('q'):
                return (int(value_str[1:]), int_type_str(value_str[0]))
            elif '.' in value_str:
                return (float(value_str), 'float')
            else:
                if value_str.startswith('0x'):
                    value_str = value_str[2:]
                if len(value_str)<=2:
                    type = 'uint8'
                elif len(value_str)==4:
                    type = 'uint16'
                elif len(value_str)==8:
                    type = 'uint32'
                else:
                    if re.match('(b|w|q)?[0-9a-fA-F\.-]', value_str):
                        raise RuntimeError('invalid argument length, expected 2, 4 or 8: got %u: %s' % (len(value_str), value_str))
                    raise RuntimeError('invalid argument: %s' % value_str)
            return (int(value_str, 16), type)
        except ValueError as e:
            raise RuntimeError(RuntimeError('invalid argument: %s' % e))
