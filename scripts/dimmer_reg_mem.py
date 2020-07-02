#
# Author: sascha_lammers@gmx.de
#

import re
import math
import sys
import json
import argparse
from os import path

def appdir_relpath(filename):
    app_dir = path.dirname(path.realpath(__file__))
    return path.realpath(path.join(app_dir, filename))

parser = argparse.ArgumentParser(description="Protocol Tool")
parser.add_argument("-c", "--create", help="create output files", action="store_true", required=True)
parser.add_argument("-H", "--header", help="header output file", type=argparse.FileType('w'), default=appdir_relpath('../src/dimmer_protocol.h'))
parser.add_argument("-P", "--python", help="python output file", type=argparse.FileType('w'), default=appdir_relpath('../scripts/lib/dimmer_protocol.py'))
parser.add_argument("-v", "--verbose", help="verbose output", action="store_true", default=False)

args = parser.parse_args()

def error(msg):
    print(msg, file=sys.stderr)
    sys.exit(1)

def verbose(msg):
    if args.verbose:
        print(msg)

python_defines = {}
file = args.header
base_indent = ''

verbose('Creating %s' % file.name)

def output(msg='', end='\n', indent=True):
    if indent:
        file.write(base_indent)
    file.write(msg + end)

class CStruct(object):
    def __init__(self, name=None, struct={}, type='typedef struct packed', define_prefix=None):
        self.name = name
        self.struct = struct
        self.type = type.replace('packed', '__attribute__packed__')
        self.define_prefix = define_prefix

    def pack_to_c(self, fmt):
        fmt = fmt.lstrip('0123456789')
        fmt = fmt.split(':', 2)[0]
        if fmt=='c':
            return 'char'
        elif fmt=='b':
            return 'int8_t'
        elif fmt=='B':
            return 'uint8_t'
        elif fmt=='h':
            return 'int16_t'
        elif fmt=='H':
            return 'uint16_t'
        elif fmt=='i':
            return 'int32_t'
        elif fmt=='I':
            return 'uint32_t'
        elif fmt=='f':
            return 'float'
        elif fmt=='d':
            return 'double'
        raise TypeError('invalid format: %s' % fmt)

    def pack_to_bytes(self, fmt):
        fmt = fmt.lstrip('0123456789')
        tmp = fmt.split(':', 2)
        fmt = tmp[0]
        if len(tmp)==2:
            return int(tmp[1]) / 8.0
        if fmt=='c':
            return 1
        elif fmt=='b':
            return 1
        elif fmt=='B':
            return 1
        elif fmt=='h':
            return 2
        elif fmt=='H':
            return 2
        elif fmt=='i':
            return 4
        elif fmt=='I':
            return 4
        elif fmt=='f':
            return 4
        elif fmt=='d':
            return 8
        raise TypeError('invalid format: %s' % fmt)

    def size(self):
        sum = 0
        is_union = 'union' in self.type
        for name, fmt in self.struct.items():
            (fmt, num) = fmt
            if isinstance(fmt, CStruct):
                if is_union:
                    sum = max(sum, fmt.size())
                else:
                    sum = sum + fmt.size()
            else:
                if num==0:
                    num = 1
                if is_union:
                    sum = max(sum, (num * self.pack_to_bytes(fmt)))
                else:
                    sum = sum + (num * self.pack_to_bytes(fmt))
        return math.ceil(sum)

    def bit_set(self, fmt):
        n = self.pack_to_bytes(fmt)
        if n < 1.0:
            return ': %u' % (8.0 * n)
        return ''

    def dump_python(self, header=True):
        global base_indent
        if header:
            output('self.%s = {' % self.name)
            output("    '__SIZE': %u," % self.size())
        is_union = 'union' in self.type
        for name, fmt in self.struct.items():
            (fmt, num) = fmt
            if isinstance(fmt, CStruct):
                if num==0:
                    fmt.dump_python(False)
                else:
                    n = int(len(base_indent) / 4)
                    output("    '%s': { " % (name))
                    base_indent = '    ' * (n + 1)
                    for i in range(0, num):
                        fmt.dump_python(False)
                    output(" },")
                    base_indent = '    ' * n
            else:
                if not ':' in fmt:
                    if num==0:
                        output("    '%s': '%s'," % (name, fmt))
                    else:
                        output("    '%s': [ " % (name), end='')
                        for i in range(0, num):
                            output("'%s', " % (fmt), end='', indent=False)
                        output(" ],", indent=False)
            if is_union:
                break
        if header:
            output('}')

    def dump(self, indent=0, end='\n'):
        indent_str = '    ' * indent
        output('%s%s {' % (indent_str, self.type))
        for name, fmt in self.struct.items():
            (fmt, num) = fmt
            if isinstance(fmt, CStruct):
                if fmt.name:
                    if num:
                        output('%s    %s %s[%u];' % (indent_str, fmt.name, name, num))
                    else:
                        output('%s    %s %s;' % (indent_str, fmt.name, name))
                else:
                    fmt.dump(indent + 1, '')
            else:
                if num:
                    output('%s    %s %s[%u];' % (indent_str, self.pack_to_c(fmt), name, num))
                else:
                    output('%s    %s %s%s;' % (indent_str, self.pack_to_c(fmt), name, self.bit_set(fmt)))
        if self.name:
            output('%s} %s;' % (indent_str, self.name))
        else:
            output('%s};' % (indent_str))
        # output('// %f' % self.size())
        output(end=end)

def define_name(prefix, name, prefix2=None):
    parts = ['DIMMER', prefix]
    if prefix2:
        parts.append(prefix2)
    parts.append(name)
    return '_'.join(parts).upper()

def define(name, value, type=None, comment=''):
    if type == 'BIT':
        value = 1 << value
        value_str = "0x%02x // 0b%s" % (value, format(value, '08b'))
    elif isinstance(value, int):
        value_str = "0x%02x // %- 3u" % (value, value)
    elif isinstance(value, float):
        value_str = ("%f" % value).rstrip('0') + '0'
    else:
        value_str = value
    if not '(' in name:
        python_defines[name[7:]] = value
    return '#define %- 47s %s %s' % (name, value_str, comment)

def create_defines(struct, prefix, offset=0, array_num=0, array_size=0):
    start_ofs = offset
    for name, fmt in struct.struct.items():
        (fmt, num) = fmt
        if 'union' in struct.type:
            cur_ofs = start_ofs
        else:
            cur_ofs = offset
        if isinstance(fmt, CStruct):
            create_defines(fmt, prefix, cur_ofs, array_num=num, array_size=fmt.size())
            offset = offset + fmt.size() * (num and num or 1)
        else:
            if ':' in fmt:
                if start_ofs==0:
                    output(define(define_name(prefix, name, struct.define_prefix), int(8.0 * cur_ofs), 'BIT'))
            else:
                index = ''
                value = cur_ofs
                if num:
                    index = '(n)'
                    value = '(0x%02x + ((N) * %u)) // %u:%u' % (cur_ofs, struct.pack_to_bytes(fmt), cur_ofs, num)
                elif array_num:
                    index = '(n)'
                    value = '(0x%02x + ((N) * %u)) // %u:%u' % (cur_ofs, array_size, cur_ofs, array_num)
                output(define(define_name(prefix, name + index, struct.define_prefix), value, None, struct.pack_to_c(fmt)))
                if index and cur_ofs==0 and offset==start_ofs:
                    output(define(define_name(prefix, 'OFFSET', struct.define_prefix), cur_ofs, None, struct.pack_to_c(fmt)))
            if not 'union' in struct.type:
                offset += struct.pack_to_bytes(fmt)
    return offset


MAX_CHANNELS = 8

slave_commands = {
    'SET_LEVEL': 0x10,
    'FADE': 0x11,
    'READ_CHANNELS': 0x12,
    'READ_TEMPERATURE': 0x20,
    'READ_TEMPERATURE2': 0x21,
    'READ_VCC': 0x22,
    'READ_FREQUENCY': 0x23,
    'WRITE_SETTINGS': 0x50,
    'RESTORE_FACTORY': 0x51,
    'PRINT_INFO': 0x53,
    'FORCE_TEMP_CHECK': 0x54,
    'PRINT_METRICS': 0x55,
    'PRINT_CUBIC_INT': 0x60,
    'GET_CUBIC_INT': 0x61,
    'READ_CUBIC_INT': 0x62,
    'WRITE_CUBIC_INT': 0x63,
    'SET_ZC_OFS': 0x92,
    'WRITE_EEPROM': 0x93,
    'SIMULATE_ZC': 0xe0,
}

master_commands = {
    'METRICS_REPORT': 0xf0,
    'TEMPERATURE_ALERT': 0xf1,
    'FADING_COMPLETE': 0xf2,
}

output('/**')
output(' * Author: sascha_lammers@gmx.de')
output(' */')
output()
output('#pragma once')
output()
output('#ifndef DIMMER_I2C_ADDRESS')
output(define(define_name('I2C', 'ADDRESS'), 0x17))
output('#endif')
output()
output('#ifndef DIMMER_I2C_MASTER_ADDRESS')
output(define(define_name('I2C', 'MASTER_ADDRESS'), 0x18))
output('#endif')
output()
output('#include <stdint.h>')
output()
output('#ifndef __attribute__packed__')
output('#define __attribute__packed__                           __attribute__((packed))')
output('#endif')
output()
output('#if _MSC_VER')
output('#pragma pack(push, 1)')
output('#endif')
output()

dimmer_get_cubic_int_header_t = CStruct('dimmer_get_cubic_int_header_t', {
    'start_level': ('h', 0),
    'level_count': ('B', 0),
    'step_size': ('B', 0),
}, define_prefix='cubic_int_header')
dimmer_get_cubic_int_header_t.dump()

register_mem_command_t = CStruct('register_mem_command_t', {
    'command': ('B', 0),
    'read_length': ('b', 0),
}, define_prefix='cmd')
register_mem_command_t.dump()

register_mem_cubic_int_data_point_t = CStruct('register_mem_cubic_int_data_point_t', {
    'x': ('B', 0),
    'y': ('B', 0),
}, 'typedef struct packed', define_prefix='cubic_int_data_points')
register_mem_cubic_int_data_point_t.dump()

register_mem_cubic_int_t = CStruct('register_mem_cubic_int_t', {
    'points': (register_mem_cubic_int_data_point_t, 8),
    'levels': ('h', register_mem_cubic_int_data_point_t.size() * 4),
}, 'typedef union packed', define_prefix='cubic_int')
register_mem_cubic_int_t.dump()

register_mem_options_bits_t = CStruct('register_mem_options_bits_t', {
    'factory_settings': ('B:1', 0),
    'cubic_interpolation': ('B:1', 0),
    'report_metrics': ('B:1', 0),
    'restore_level': ('B:1', 0),
})
register_mem_options_bits_t.dump()

register_mem_options_union_t = CStruct(None, {
    'options': ('B', 0),
    'bits': (register_mem_options_bits_t, 0),
}, 'union')

register_mem_cfg_t = CStruct('register_mem_cfg_t', {
    'options': (register_mem_options_union_t, 0),
    'max_temperature': ('B', 0),
    'fade_time': ('f', 0),
    'temp_check_interval': ('B', 0),
    'metrics_report_interval': ('B', 0),
    'zc_offset_ticks': ('h', 0),
    'min_on_ticks': ('H', 0),
    'min_off_ticks': ('H', 0),
    'vref11': ('f', 0),
    'temperature_offset': ('b', 0),
    'temperature2_offset': ('b', 0),
}, define_prefix='cfg')
register_mem_cfg_t.dump()

register_mem_metrics_t = CStruct('register_mem_metrics_t', {
    'frequency': ('f', 0),
    'temperature': ('f', 0),
    'temperature2': ('f', 0),
    'vcc': ('H', 0),
}, define_prefix='metrics')
register_mem_metrics_t.dump()

output('typedef register_mem_metrics_t dimmer_metrics_t;')
output()

dimmer_temperature_alert_t = CStruct('dimmer_temperature_alert_t', {
    'current_temperature': ('B', 0),
    'max_temperature': ('B', 0),
}, define_prefix='alert')
dimmer_temperature_alert_t.dump()

register_mem_channel_t = CStruct('register_mem_channel_t', {
    'from_level': ('h', 0),
    'time': ('f', 0),
    'channel': ('b', 0),
    'to_level': ('h', 0),
}, define_prefix='channel')
register_mem_channel_t.dump()

register_mem_errors_t = CStruct('register_mem_errors_t', {
    'zc_misfire': ('B', 0),
    'temperature': ('B', 0),
}, define_prefix='errors')
register_mem_errors_t.dump()

register_mem_info_t = CStruct('register_mem_info_t', {
    'version': ('H', 0),
    'num_levels': ('h', 0),
    'num_channels': ('b', 0),
}, define_prefix='info')
register_mem_info_t.dump()

register_mem_channels_t = CStruct('register_mem_channels_t', {
    'level': ('h', MAX_CHANNELS),
}, define_prefix='channels')
register_mem_channels_t.dump()

register_mem_t = CStruct('register_mem_t', {
    'cubic_int': (register_mem_cubic_int_t, 0),
    'metrics': (register_mem_metrics_t, 0),
    'channel': (register_mem_channel_t, 0),
    'cmd': (register_mem_command_t, 0),
    'cfg': (register_mem_cfg_t, 0),
    'channels': (register_mem_channels_t, 0),
    'errors': (register_mem_errors_t, 0),
    'info': (register_mem_info_t, 0),
    'address': ('B', 0),
})
register_mem_t.dump()

register_mem_union_t = CStruct('register_mem_union_t', {
    'data': (register_mem_t, 0),
    'raw': ('B', register_mem_t.size()),
}, 'typedef union packed')
register_mem_union_t.dump()

output()
output(define(define_name('REGISTER', 'MEM_START_OFFSET'), 0))
size = create_defines(register_mem_t, 'REGISTER')
output(define(define_name('REGISTER', 'MEM_SIZE'), size))
output(define(define_name('REGISTER', 'COMMAND'), 'DIMMER_REGISTER_CMD_COMMAND'))
output()
create_defines(register_mem_options_bits_t, 'OPTIONS')
output()

for name, value in slave_commands.items():
    output(define(define_name('COMMAND', name), value))
output()

for name, value in master_commands.items():
    output(define(define_name('MASTER_COMMAND', name), value))
output()
output(define(define_name('CUBIC_INT', 'DATA_POINTS'), 8))
output()


output('#if _MSC_VER')
output('#pragma pack(pop)')
output('#endif')
output()

file.close()

file = args.python
verbose('Creating %s' % file.name)

output('#')
output('# Author: sascha_lammers@gmx.de')
output('#')
output()
output('class DimmerProtocol(object):')
output('    def __init__(self):')

base_indent = '        '
register_mem_info_t.dump_python()
register_mem_command_t.dump_python()
register_mem_t.dump_python()
register_mem_metrics_t.dump_python()
dimmer_temperature_alert_t.dump_python()

output('self.constants = ', end='')
for line in json.dumps(python_defines, indent=4).split('\n'):
    output(line)

for name, value in python_defines.items():
    if isinstance(value, int):
        output('self.%s = %u' % (name, value))

def alias(target, source):
    output('self.%s = self.%s' % (target, source))
    output("self.constants['%s'] = self.%s" % (target, source))

alias('ADDRESS', 'I2C_ADDRESS')
alias('REGISTER_COMMAND', 'REGISTER_CMD_COMMAND')
output()
