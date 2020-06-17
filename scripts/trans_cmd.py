#!/usr/bin/python3
#
# Author: sascha_lammers@gmx.de
#

import time
import sys
import argparse
import re
import struct
import json
import tempfile
import signal
import os
import platform
import subprocess
import shlex
import stat
from os import path

# .\scripts\trans_cmd.py -v command "I2CT=ADDRESS,COMMAND_READ_VCC,DIMMER_REGISTER_FROM_LEVEL,1f,2faa,100.5,4a3b2c1d,b-1,w1000,w-1"
# .\scripts\trans_cmd.py -O file .\docs\PROTOCOL_template.md -o .\docs\PROTOCOL.md
# .\scripts\trans_cmd.py compile - -D DIMMER_CUBIC_INT_TABLE_SIZE=8 -D SERIALTWOWIRE_MAX_INPUT_LENGTH=0xff -D DEBUG=1
# .\scripts\trans_cmd.py -O compile "C:/SPB_Data/dimmer_const.cpp" -D DIMMER_CUBIC_INT_TABLE_SIZE=8 -D SERIALTWOWIRE_MAX_INPUT_LENGTH=0xff -D DEBUG=1
# .\scripts\trans_cmd.py -O compile ".\scripts\trans_cmd_cfg_struct.json" -D DIMMER_CUBIC_INT_TABLE_SIZE=8 -D SERIALTWOWIRE_MAX_INPUT_LENGTH=0xff -D DEBUG=1 -C "gcc %SRC% -o %EXE%"

# I2C/UART protocol
# .\scripts\trans_cmd.py command "+I2CT=ADDRESS,REGISTER_FROM_LEVEL,w-1,00,w8192,1.72,COMMAND_FADE" "+I2CT=ADDRESS,REGISTER_FROM_LEVEL,w0,00,w8192,1.72,COMMAND_FADE" "+I2CT=ADDRESS,REGISTER_FROM_LEVEL,w8192,00,w0,1.72,COMMAND_FADE" "+I2CT=ADDRESS,REGISTER_COMMAND,COMMAND_DUMP_MEM" "+I2CT=ADDRESS,REGISTER_COMMAND,DIMMER_COMMAND_DUMP_CFG"

class DimmerConst(object):
    def __init__(self):
        self.list = {}

    def read_json(self, file):
        with open(file, "rt") as file:
            self.list = json.loads(file.read())
            file.close()

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
        hex_str = ''
        for b in struct.pack('<f', value):
            hex_str = hex_str + ('%02X' % b)
        return hex_str

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
                    if re.match('(b|w|q)?[0-9a-fA-F\.-]', value_str):
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

def create_cpp_source(file):
    for define in defines:
        file.write('#define %s %s\n' % ( define[0], define[1]))

    file.writelines(['#include <stdio.h>\n', '#include "%s"\n' % args.structures_header.name, 'int main() {\n', 'printf("{\\n");\n'])

    n = 0
    for define in defines:
        n = n + 1
        name = define[0]
        if name.startswith('DIMMER_'):
            short = name[7:]
            if short.split('_', 2)[0] in ['COMMAND', 'REGISTER', 'OPTIONS', 'TIMINGS', 'RESPONSE', 'CONFIG']:
                file.write('printf("\\\"%s\\\": %%d%s\\n", %s);\n' % (short, (n < len(defines) and ',' or ''), name))

    file.writelines(['printf("}\\n");\n', 'return 0; }\n'])

class CleanupTmpFiles:
    def __init__(self):
        signal.signal(signal.SIGINT, self.handler)
        signal.signal(signal.SIGTERM, self.handler)
        self.files = []

    # if file is not a string, the method close() will be invoked before attempting to delete file.name
    # any exceptions are caught to make sure all files are deleted
    def add(self, file):
        self.files.append(file)

    def remove(self, file):
        self.files.remove(file)

    # can be called at any time to remove all files in the list
    def cleanup(self):
        for file in self.files:
            if isinstance(file, str):
                try:
                    os.unlink(file)
                except:
                    pass
            else:
                try:
                    file.close()
                except:
                    pass
                try:
                    os.unlink(file.name)
                except:
                    pass
        self.files = []

    def handler(self, sig, frame):
        self.cleanup()
        sys.exit(sig)

# -------------------------------------------------------------------------
# main
# -------------------------------------------------------------------------

script_dir = path.dirname(sys.argv[0])
src_dir = path.join(script_dir, '..', 'src') + path.sep
json_file = path.join(script_dir, 'trans_cmd_cfg_struct.json')

parser = argparse.ArgumentParser(prog='trans-cmd', description='Translate constants to HEX code', formatter_class=argparse.ArgumentDefaultsHelpFormatter)
subparsers  = parser.add_subparsers(help='sub-command help')

command_parser = subparsers.add_parser('command', help='translate one or more commands')
command_parser.add_argument('command', help='command to translate', nargs='+')

file_parser = subparsers.add_parser('file', help='translate commands in a file')
file_parser.add_argument('file', help='file to translate', type=argparse.FileType('rt', encoding='UTF-8'))
file_parser.add_argument('-o', '--output', help='output of translated file', action=DelayedFileAction, type=DelayedFileType('wt', encoding='UTF-8', keep_existing='overwrite'), default='-')

compile_parser = subparsers.add_parser('compile', help='create c++ source or JSON file for dimmer constants', formatter_class=argparse.ArgumentDefaultsHelpFormatter)
compile_parser.add_argument('source', help='compile header files', action=DelayedFileAction, type=DelayedFileType('wt', keep_existing='overwrite'))
compile_parser.add_argument('-D', '--define', help='define constant', action='append', type=str, default=[])
compile_parser.add_argument('-p', '--protocol-header', help='protocol header', action=DelayedFileAction, type=DelayedFileType('rt'), default=src_dir + 'dimmer_protocol.h')
compile_parser.add_argument('-s', '--structures-header', help='structures header', action=DelayedFileAction, type=DelayedFileType('rt'), default=src_dir + 'dimmer_reg_mem.h')
compile_parser.add_argument('-C', '--compiler-cmd', help="command to compile the C++ code (i.e. gcc %SRC% -o %EXE%)", type=str, default=None)
compile_parser.add_argument('-n', '--no-cleanup', help="do not delete temporary files on compliation error", action='store_true', default=False)

parser.add_argument('-j', '--json', help='JSON configuration', default=json_file)
parser.add_argument('-O', '--overwrite', action='store_true', default=False, help='overwrite existing files')
parser.add_argument('-v', '--verbose', help='verbose output', action='store_true', default=False)
parser.add_argument('--slave-address', type=str, default='0x17', help='I2C slave address')
parser.add_argument('--master-address', type=str, default='0x18', help='I2C master address')

args = parser.parse_args()

args.slave_address = parse_number(args.slave_address)
args.master_address = parse_number(args.master_address)
verbose('slave address: 0x%02X' % args.slave_address)
verbose('master address: 0x%02X' % args.master_address)

if 'command' in args:
    dimmer.read_json(args.json)
    verbose('commands: %s' % (args.command))
    for command in args.command:
        try:
            pc = dimmer.parse_command(command)
            print(dimmer.translate_command(pc))
        except RuntimeError as e:
            print('parse error in command: %s\n%s' % (command, e))
            sys.exit(1)

elif 'source' in args:
    dimmer.read_json(args.json)
    args.source.check_overwrite(args.overwrite)
    verbose('source output file: %s%s' % (args.source.name, args.source.exists() and ' (file exists, overwrite flag set)' or ''))
    verbose('protocol header: ' + path.normpath(args.protocol_header.name))
    verbose('structures header: ' + path.normpath(args.structures_header.name))
    defines, text = format_defines(args.define, '         ')
    verbose('defines: ' + text)

    defines = parse_protocol_header(args.protocol_header.open(), defines)
    args.protocol_header.close()

    if args.compiler_cmd:
        cleanup = CleanupTmpFiles()

        cpp_file = tempfile.NamedTemporaryFile('wt', suffix='.cpp', delete=False)
        cleanup.add(cpp_file)
        exe_file = tempfile.NamedTemporaryFile('wt', suffix=platform.system()=='Windows' and '.exe' or None, delete=False)
        cleanup.add(exe_file)
        exe_file.close()

        create_cpp_source(cpp_file)
        cpp_file.close()

        compile_cmd = args.compiler_cmd.replace('%SRC%', shlex.quote(cpp_file.name)).replace('%EXE%', shlex.quote(exe_file.name));
        compile_args = shlex.split(compile_cmd)
        compile_cmd = ' '.join(compile_args)
        verbose("compile command: '%s'" % compile_cmd)

        try:
            p = subprocess.run(compile_args)
            if p.returncode!=0:
                if args.no_cleanup:
                    print('temporary source file was not deleted: %s' % cpp_file.name)
                    cleanup.remove(cpp_file)
                raise RuntimeError("failed to compile source: exit code: %d: '%s'" % (p.returncode, compile_cmd))

            with args.source.open() as file:
                os.chmod(exe_file.name, stat.S_IXUSR)
                proc = subprocess.Popen(exe_file.name, stdout=file)
                returncode = proc.wait()
                if returncode!=0:
                    raise RuntimeError("failed to execute compiled file: exit code: %d '%s'" % (returncode, compile_cmd))

        except Exception as e:
            cleanup.cleanup()
            if not isinstance(e, RuntimeError):
                raise e
            print(e)
            sys.exit(1)

        verbose('JSON output: %s' % args.source.name)
        cleanup.cleanup()

    else:
        with args.source.open() as file:
            create_cpp_source(file)

elif 'file' in args:

    dimmer.read_json(args.json)
    args.output.check_overwrite(args.overwrite)
    verbose('input: %s' % args.file.name)
    verbose('output: %s%s' % (args.output.name, args.output.exists() and ' (file exists, overwrite flag set)' or ''))

    with args.output.open() as file:
        n = 0
        for line in args.file:
            n = n + 1
            line = line.rstrip()
            m = re.findall('(\+(i2c[tr]=[a-z0-9_,\.-]+?)(,\.{3})? \(raw_cmd:[^\)]*\))', line, re.IGNORECASE)
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
            file.write(line)
            file.write('\n')
