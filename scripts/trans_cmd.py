#!/usr/bin/python3
#
# Author: sascha_lammers@gmx.de
#

import time
import sys
import argparse
import re
import struct
from os import path

# .\scripts\trans_cmd.py -v command "I2CT=ADDRESS,COMMAND_READ_VCC,DIMMER_REGISTER_FROM_LEVEL,1f,2faa,100.5,4a3b2c1d,b-1,w1000,w-1"
# .\scripts\trans_cmd.py -v -O file .\docs\PROTOCOL_template.md -o .\docs\PROTOCOL.md
# .\scripts\trans_cmd.py -v compile - -D DIMMER_CUBIC_INTERPOLATION=1 -D SERIALTWOWIRE_MAX_INPUT_LENGTH=0xff -D DEBUG=1
# .\scripts\trans_cmd.py -v -O compile "C:/SPB_Data/dimmer_const.cpp" -D DIMMER_CUBIC_INTERPOLATION=1 -D SERIALTWOWIRE_MAX_INPUT_LENGTH=0xff -D DEBUG=1

class DimmerConst(object):
    def __init__(self):
        self.list = {
            'REGISTER_START_ADDR': 0x01,
            'REGISTER_SIZE': 0xbb,
            'REGISTER_FROM_LEVEL': 0x01,
            'REGISTER_CHANNEL': 0x03,
            'REGISTER_TO_LEVEL': 0x04,
            'REGISTER_TIME': 0x06,
            'REGISTER_COMMAND': 0x0a,
            'REGISTER_READ_LENGTH': 0x0b,
            'REGISTER_COMMAND_STATUS': 0x0c,
            'REGISTER_CHANNELS_START': 0x0d,
            'REGISTER_CH0_LEVEL': 0x0d,
            'REGISTER_CH1_LEVEL': 0x0f,
            'REGISTER_CH2_LEVEL': 0x11,
            'REGISTER_CH3_LEVEL': 0x13,
            'REGISTER_CH4_LEVEL': 0x15,
            'REGISTER_CH5_LEVEL': 0x17,
            'REGISTER_CH6_LEVEL': 0x19,
            'REGISTER_CH7_LEVEL': 0x1b,
            'REGISTER_CHANNELS_END': 0x1d,
            'REGISTER_TEMP': 0x1d,
            'REGISTER_VCC': 0x21,
            'REGISTER_CONFIG_OFS': 0x23,
            'REGISTER_CONFIG_SZ': 0x93,
            'REGISTER_OPTIONS': 0x23,
            'REGISTER_MAX_TEMP': 0x24,
            'REGISTER_FADE_IN_TIME': 0x25,
            'REGISTER_TEMP_CHECK_INT': 0x29,
            'REGISTER_ZC_DELAY_TICKS': 0x2a,
            'REGISTER_MIN_ON_TIME_TICKS': 0x2b,
            'REGISTER_ADJ_HALFWAVE_TICKS': 0x2d,
            'REGISTER_INT_1_1V_REF': 0x2f,
            'REGISTER_INT_TEMP_OFS': 0x33,
            'REGISTER_METRICS_INT': 0x35,
            'REGISTER_ERRORS_FREQ_LOW': 0xb8,
            'REGISTER_ERRORS_FREQ_HIGH': 0xb9,
            'REGISTER_ERRORS_ZC_MISFIRE': 0xba,
            'REGISTER_CH0_CUBIC_INT': 0x36,
            'REGISTER_CH1_CUBIC_INT': 0x46,
            'REGISTER_CH2_CUBIC_INT': 0x56,
            'REGISTER_CH3_CUBIC_INT': 0x66,
            'REGISTER_CH4_CUBIC_INT': 0x76,
            'REGISTER_CH5_CUBIC_INT': 0x86,
            'REGISTER_CH6_CUBIC_INT': 0x96,
            'REGISTER_CH7_CUBIC_INT': 0xa6,
            'REGISTER_VERSION': 0xb6,
            'REGISTER_ADDRESS': 0xbb,
            'REGISTER_END_ADDR': 0xbc,
            'RESPONSE_METRICS_REPORT': 0xf0,
            'RESPONSE_TEMPERATURE_ALERT': 0xf1,
            'RESPONSE_FADING_COMPLETE': 0xf2,
            'RESPONSE_EEPROM_WRITTEN': 0xf3,
            'RESPONSE_FREQUENCY_WARNING': 0xf4,
            'COMMAND_SET_LEVEL': 0x10,
            'COMMAND_FADE': 0x11,
            'COMMAND_READ_CHANNELS': 0x12,
            'COMMAND_READ_NTC': 0x20,
            'COMMAND_READ_INT_TEMP': 0x21,
            'COMMAND_READ_VCC': 0x22,
            'COMMAND_READ_AC_FREQUENCY': 0x23,
            'COMMAND_WRITE_EEPROM': 0x50,
            'COMMAND_RESTORE_FS': 0x51,
            'COMMAND_READ_TIMINGS': 0x52,
            'COMMAND_PRINT_INFO': 0x53,
            'COMMAND_FORCE_TEMP_CHECK': 0x54,
            'COMMAND_PRINT_METRICS': 0x55,
            'COMMAND_PRINT_CUBIC_INT': 0x56,
            'COMMAND_ZC_TIMINGS_OUTPUT': 0x60,
            'COMMAND_ZC_DECREASE': 0x82,
            'COMMAND_ZC_INCREASE': 0x83,
            'COMMAND_SET_ZC': 0x92,
            'COMMAND_FORCE_WRITE_EEPROM': 0x93,
            'COMMAND_DUMP_MEM': 0xee,
            'COMMAND_STATUS_OK': 0x00,
            'COMMAND_STATUS_ERROR': 0xffffffff,
            'OPTIONS_RESTORE_LEVEL': 0x01,
            'OPTIONS_REPORT_METRICS': 0x02,
            'OPTIONS_TEMP_ALERT_TRIGGERED': 0x04,
            'OPTIONS_FREQ_LOW_ALERT': 0x08,
            'OPTIONS_FREQ_HIGH_ALERT': 0x10,
            'OPTIONS_CUBIC_INT': 0x20,
            'TIMINGS_TMR1_TICKS_PER_US': 0x01,
            'TIMINGS_TMR2_TICKS_PER_US': 0x02,
            'TIMINGS_ZC_DELAY_IN_US': 0x03,
            'TIMINGS_MIN_ON_TIME_IN_US': 0x04,
            'TIMINGS_ADJ_HW_TIME_IN_US': 0x05,
            'COMMAND_SIMULATE_ZC': 0xe0,
        }

    def get_by_value(self, value):
        for key, val in self.list.items():
            if val==value:
                return key
        return False


    def get(self, name):
        if name in self.list:
            return self.list[name]
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
        return hex(struct.unpack('<I', struct.pack('<f', value))[0])[2:].upper()

    def to_hex(self, value, type, split_bytes = True):

        if type.endswith('int32'):
            if value<0:
                value = (1<<32) + value
            hex_str = '%02X' % (value & 0xff)
            if split_bytes:
                hex_str = hex_str + ','
            hex_str = hex_str + '%02X' % ((value >> 8) & 0xff)
            if split_bytes:
                hex_str = hex_str + ','
            hex_str = hex_str + '%02X' % ((value >> 16) & 0xff)
            if split_bytes:
                hex_str = hex_str + ','
            hex_str = hex_str + '%02X' % ((value >> 24) & 0xff)
            return hex_str
        elif type.endswith('int16'):
            if value<0:
                value = (1<<16) + value
            hex_str = '%02X' % (value & 0xff)
            if split_bytes:
                hex_str = hex_str + ','
            hex_str = hex_str + '%02X' % ((value >> 8) & 0xff)
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
                    if re.match('(b|w|q)?[0-9a-fA-F\.]', value_str):
                        raise RuntimeError('invalid argument length, expected 2, 4 or 8: got %u: %s' % (len(value_str), value_str))
                    raise RuntimeError('invalid argument: %s' % value_str)
            return (int(value_str, 16), type)
        except ValueError as e:
            raise RuntimeError(RuntimeError('invalid argument: %s' % e))

dimmer = DimmerConst()

# Like FileType, but does not open the file immediately and can show an error before overwriting a file
#
# example:
#
#   # create a file if it does not exist or the overwrite flag is set
#   parser.add_argument('-o', '--output', help='output of translated file', action=DelayedFileAction, type=DelayedFileType('wt', encoding='UTF-8', keep_existing='overwrite'), default='-')
#   parser.add_argument('-O', '--overwrite', action='store_true', default=False, help='overwrite output file if exists')
#   args = parser.parse_args()
#
#   # check if file exists prior to open, the overwrite argument is stored for open()
#   args.output.check_overwrite(args.overwrite)
#
#   # do some work
#
#   with args.output.open() as file:
#       print(file)
#
#   # if check_overwrite() has not been called, add overwrite
#   with args.output.open(overwrite=args.overwrite) as file:
#       print(file)
#
# arguments
#   keep_existing=False         overwrite existing files
#   keep_existing=True          do not overwrite existing files
#   keep_existing='metavar'     do not overwrite existing files and display argument how to overwrite
#                               stdout/- will not cause an error
#   default='-'                 use stdin/stdout
#
# properties
#   name                        name of the file
#
# methods
#   check_overwrite(overwrite)              if keep_existing is set, check if the file exists and if it does, exit
#   open(newline = None, overwrite = None)  call check_overwrite(), open file set and return file object
#   exists()                                checks if the file exists. returns True for stdin/stdout
#
class DelayedFileType(object):
    def __init__(self, mode='r', bufsize=-1, encoding=None, errors=None, keep_existing=False):
        self._parser = None
        self._option_strings = []
        self._mode = mode
        self._bufsize = bufsize
        self._encoding = encoding
        self._errors = errors
        self._keep_existing = keep_existing
        self._overwrite_action = None
        self._overwrite = None
        if 'w' in mode:
            self._overwrite = True
            if keep_existing:
                self._overwrite = False
        elif keep_existing:
                raise argparse.ArgumentTypeError('keep_existing is only allowed for w and w+')
        self._file = None
        self.name = None

    def __call__(self, string):
        if string == '-':
            if 'r' in self._mode:
                self._file = sys.stdin
            elif 'w' in self._mode:
                self._file = sys.stdout
            else:
                raise argparse.ArgumentTypeError("'-' requires read or write mode")
            self.name = self._file.name
        else:
            self.name = path.abspath(string)
        return self;

    def _error(self, msg):
        self._parser.error('argument %s: %s' % ('/'.join(self._option_strings), msg))

    def exists(self):
        if self._file:
            return True
        return path.exists(self.name)

    def check_overwrite(self, overwrite):
        if overwrite:
            self._overwrite = True
        else:
            if self._overwrite!=None:
                if not self._file and not self._overwrite and self.exists():
                    if not path.isfile(self.name):
                        self._error("is a directory: '%s'" % self.name)
                    help = ''
                    if self._overwrite_action:
                        help = '\nuse argument %s: %s' % ('/'.join(self._overwrite_action.option_strings), self._overwrite_action.help)
                    self._error("already exists: '%s'%s" % (self.name, help))

    def open(self, newline = None, overwrite = None):
        if overwrite!=None:
            self.check_overwrite(overwrite)
        else:
            self.check_overwrite(self._overwrite)
        if not self._file:
            try:
                self._file = open(self.name, mode = self._mode, encoding = self._encoding, errors = self._errors, newline = newline)
            except OSError as e:
                self._parser.error(str(e))
        return self._file

    def close(self):
        if self._file:
            self._file.close()
            self._file = None

class DelayedFileAction(argparse.Action):
    def __init__(self, *args, **kwargs):
        if not 'type' in kwargs:
            raise ValueError('type not set')
        if not isinstance(kwargs["type"], DelayedFileType):
            raise ValueError('type not DelayedFileType')
        self._type = kwargs["type"]

        super(DelayedFileAction, self).__init__(*args, **kwargs)

    def _find_dest(self, dest):
        for action in parser._actions:
            if action.dest==dest:
                return action
        return False


    def __call__(self, parser, namespace, values, option_string=None):
        self._type._parser = parser
        for action in parser._actions:
            if action==self:
                self._type._option_strings = action.option_strings
                if isinstance(self._type._keep_existing, str):
                    self._type._overwrite_action = self._find_dest(self._type._keep_existing)
                    if not self._type._overwrite_action:
                        raise ValueError("keep_existing metavar '%s' not found" % self._type._keep_existing)
        setattr(namespace, self.dest, values)


class CppParser(object):
    def __init__(self, defines = []):
        self._defines = defines
        self.IF_BLOCK_TRUE = 'if_true'
        self.IF_BLOCK_FALSE = 'if_false'
        self.IF_BLOCK_NONE = 'if_none'
        self.IF_BLOCK_END = 'if_end'
        self.line = 0

    def add_define(self, define):
        self._defines.append((define[0], ' '.join(define[1:])))

    def is_defined(self, name):
        for define in self._defines:
            if define[0]==name:
                return True
        return False

    def resolve_if(self, define):
        if_clause = ' '.join(define)
        for define in self._defines:
            if_clause = if_clause.replace(define[0], str(define[1]))
            if_clause = if_clause.replace('!', ' not ').replace('true', 'True').replace('false', 'False').replace('&&', ' and ').replace('||', ' or ').replace('defined', 'self.is_defined')
        result = not eval(if_clause)==0 and self.IF_BLOCK_TRUE or self.IF_BLOCK_FALSE
        # print("resolve_if %s %s" %(if_clause, result))
        self.set_if_block(result)
        return result

    def is_if_block(self):
        return self.if_block_level==0 or self.if_block[self.if_block_level]==self.IF_BLOCK_TRUE

    def is_if_block_not_done(self):
        return self.if_block[self.if_block_level] not in [self.IF_BLOCK_TRUE, self.IF_BLOCK_END]

    def set_if_block(self, val):
        self.if_block[self.if_block_level] = val

    def parse_line(self, line):
        self.line = self.line + 1
        try:
            if line and line[-1]=='\\':
                line = line[0:-1]
                self.line_cont = self.line_cont + line.split(" \t\\\"")
            else:
                if self.define:
                    type = self.define[0]
                    # print(type)
                    if type=='endif':
                        del self.if_block[self.if_block_level]
                        self.if_block_level = self.if_block_level - 1
                    else:
                        self.define = self.define[1:]
                        # print(type,self.define)
                        # print('level %d' % self.if_block_level)
                        # print(self.if_block)
                        if type=='if':
                            if not self.is_if_block():
                                self.if_block_level = self.if_block_level + 1
                                self.set_if_block(self.IF_BLOCK_END)
                            else:
                                self.if_block_level = self.if_block_level + 1
                                self.resolve_if(self.define)
                        elif type=='ifdef' or type=='ifndef':
                            if not self.is_if_block():
                                self.if_block_level = self.if_block_level + 1
                                self.set_if_block(self.IF_BLOCK_END)
                            else:
                                self.if_block_level = self.if_block_level + 1
                                result = self.is_defined(self.define[0]) == self.IF_BLOCK_TRUE
                                if type=='ifndef':
                                    result = not result
                                self.set_if_block(result and self.IF_BLOCK_TRUE or self.IF_BLOCK_FALSE)
                        elif type=='elif':
                            if self.is_if_block_not_done():
                                self.resolve_if(self.define)
                            else:
                                self.set_if_block(self.IF_BLOCK_END)
                        elif type=='else':
                            if self.is_if_block_not_done():
                                self.set_if_block(self.IF_BLOCK_TRUE)
                            else:
                                self.set_if_block(self.IF_BLOCK_END)
                        elif self.is_if_block() and type=='define':
                            self.add_define(self.define)
                        # print(self.is_if_block(), self.if_block_level, ' '.join(self.define))
                    self.define = False

                args = line.split()
                self.comment = False
                if args:
                    if self.line_cont:
                        args = self.line_cont + args
                        self.line_cont = []
                    for arg in args:
                        if arg=='#':
                            self.num_sign = True
                        else:
                            org_arg = arg
                            if self.num_sign:
                                arg = '#' + arg
                                self.num_sign = False
                            is_string = False
                            is_comment = self.block_comment or self.comment
                            if not is_comment:
                                if '"' in arg:
                                    is_string = True
                                    tmp = arg.replace('\\"', '').replace('""', '')
                                    if tmp.count('"') % 2 == 1:
                                        self.string = not self.string
                            if not is_string:
                                pos = arg.find('//')
                                if pos!=-1:
                                    arg = arg[0:pos]
                                    self.comment = True
                                    # print("line_comment")
                                arg = re.sub(r'/\*.*?\*/', '', arg)
                                while '/*' in arg or '*/' in arg:
                                    if self.block_comment and '*/' in arg:
                                        # print("end block")
                                        arg = re.sub(r'.*?\*/', '', arg)
                                        self.block_comment = False
                                    elif not self.block_comment and '/*' in arg:
                                        # print("start block")
                                        arg = re.sub(r'/\*.*$', '', arg)
                                        self.block_comment = True

                            if not is_string and not is_comment:
                                # print(arg)
                                if arg in ['#if', '#ifdef', '#ifndef', '#endif', '#elif', '#else', '#define']:
                                    self.define = [arg[1:]]
                                elif arg in ['#pragma']:
                                    pass
                                elif arg.startswith('#'):
                                    raise ValueError('preprocessor directive not supported: "%s"' % arg)
                                elif self.define!=False:
                                    self.define.append(arg)
        except Exception as e:
            print('error in line %u' % self.line)
            raise e

    def parse(self, file):
        self.comment = False
        self.block_comment = False
        self.num_sign = False
        self.string = False
        self.line_cont = []
        self.define = False
        self.if_block_level = 0
        self.if_block = {}
        for line in file:
            line = line.strip("\r\n")
            self.parse_line(line)
        # EOF marker
        self.parse_line('//')

def parse_protocol_header(file, defines):
    cp = CppParser(defines)
    cp.parse(file)
    return cp._defines

def format_defines(defines, indent = '  '):
    results = []
    if not defines:
        return (results, "None")
    out = ''
    for define in defines:
        parts = define.split('=', 2)
        if len(parts)==1:
            define = (parts[0].strip(), 1)
        else:
            define = (parts[0].strip(), parts[1].strip())
        results.append(define)
        if out:
            out = out + indent
        out = out + ('%s=%s\n' % define)
    return (results, out)

def parse_number(number):
    if number.startswith('0x'):
        return int(number[2:], 16)
    return int(number)

def verbose(msg):
    global args
    if args.verbose:
        print(msg)

# main()

src_dir = path.join(path.dirname(sys.argv[0]), '..', 'src') + path.sep;

parser = argparse.ArgumentParser(prog='trans-cmd', description='Translate constants to HEX code', formatter_class=argparse.ArgumentDefaultsHelpFormatter)
subparsers  = parser.add_subparsers(help='sub-command help')

command_parser = subparsers.add_parser('command', help='translate one or more commands')
command_parser.add_argument('command', help='command to translate', nargs='+')

file_parser = subparsers.add_parser('file', help='translate commands in a file')
file_parser.add_argument('file', help='file to translate', type=argparse.FileType('rt', encoding='UTF-8'))
file_parser.add_argument('-o', '--output', help='output of translated file', action=DelayedFileAction, type=DelayedFileType('wt', encoding='UTF-8', keep_existing='overwrite'), default='-')

compile_parser = subparsers.add_parser('compile', help='create c++ source for dimmer constants', formatter_class=argparse.ArgumentDefaultsHelpFormatter)
compile_parser.add_argument('source', help='compile header files', action=DelayedFileAction, type=DelayedFileType('wt', keep_existing='overwrite'))
compile_parser.add_argument('-D', '--define', help='define constant', action='append', type=str, default=[])
compile_parser.add_argument('-p', '--protocol-header', help='protocol header', action=DelayedFileAction, type=DelayedFileType('rt'), default=src_dir + 'dimmer_protocol.h')
compile_parser.add_argument('-s', '--structures-header', help='structures header', action=DelayedFileAction, type=DelayedFileType('rt'), default=src_dir + 'dimmer_reg_mem.h')

parser.add_argument('-O', '--overwrite', action='store_true', default=False, help='overwrite existing files')
parser.add_argument('-v', '--verbose', help='verbose output', action='store_true', default=False)
parser.add_argument('--slave-address', type=str, default='0x17', help='I2C slave address')
parser.add_argument('--master-address', type=str, default='0x18', help='I2C master address')

args = parser.parse_args()

def fprint(str, end='\n'):
    global file
    file.write(str)
    file.write(end)

args.slave_address = parse_number(args.slave_address)
args.master_address = parse_number(args.master_address)
verbose('slave address: 0x%02X' % args.slave_address)
verbose('master address: 0x%02X' % args.master_address)

if 'command' in args:
    verbose('commands: %s' % (args.command))
    for command in args.command:
        try:
            pc = dimmer.parse_command(command)
            print(dimmer.translate_command(pc))
        except RuntimeError as e:
            print('parse error in command: %s\n%s' % (command, e))
            sys.exit(1)

elif 'source' in args:
    args.source.check_overwrite(args.overwrite)
    verbose('source output file: %s%s' % (args.source.name, args.source.exists() and ' (file exists, overwrite flag set)' or ''))
    verbose('protocol header: ' + path.normpath(args.protocol_header.name))
    verbose('structures header: ' + path.normpath(args.structures_header.name))
    defines, text = format_defines(args.define, '         ')
    verbose('defines: ' + text)

    defines = parse_protocol_header(args.protocol_header.open(), defines)
    args.protocol_header.close()

    with args.source.open() as file:

        for define in defines:
            fprint('#define %s %s' % ( define[0], define[1]))

        fprint('#include <stdio.h>')
        fprint('#include "%s"' % args.structures_header.name)
        fprint('int main() {')

        for define in defines:
            name = define[0]
            if name.startswith('DIMMER_'):
                short = name[7:]
                if short.split('_', 2)[0] in ['COMMAND', 'REGISTER', 'OPTIONS', 'TIMINGS', 'RESPONSE']:
                    fprint('printf("\'%s\': 0x%%02x,\\n", %s);' % (short, name))

        fprint('return 0; }')

elif 'file' in args:

    args.output.check_overwrite(args.overwrite)
    verbose('input: %s' % args.file.name)
    verbose('output: %s%s' % (args.output.name, args.output.exists() and ' (file exists, overwrite flag set)' or ''))

    with args.output.open(newline='\n') as file:
        n = 0
        for line in args.file:
            n = n + 1
            line = line.rstrip()
            m = re.findall('(\+(i2c[tr]=[a-z0-9_,\.]+?)(,\.{3})? \(raw_cmd:[^\)]*\))', line, re.IGNORECASE)
            if m:
                for arg in m:
                    try:
                        pc = dimmer.parse_command(arg[1])
                        tc = dimmer.translate_command(pc)
                        repl = '+%s%s (%s)' % (arg[1], arg[2], tc)
                        line = line.replace(arg[0], repl)
                    except RuntimeError as e:
                        print('line %u: %s' % (n, e))
                        sys.exit(1)
            fprint(line)
