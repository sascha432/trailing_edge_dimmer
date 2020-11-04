Import("env");
import subprocess
import os
from os import path
import sys
import inspect
import shlex
import click
from SCons.Script import ARGUMENTS
import tempfile

verbose_flag = int(ARGUMENTS.get("PIOVERBOSE", 0)) and True or False

def error(msg):
    print(msg, file=sys.stderr)
    sys.exit(1)

def verbose(msg):
    if verbose_flag:
        print(msg)

#
# disassemble ELF binary
#

def disassemble(source, target, env):

    input_file = str(target[0])
    if input_file=='disassemble':
        input_file = env.subst("$BUILD_DIR/${PROGNAME}.elf")
    input_file = path.realpath(input_file)

    try:
        target_file = env.subst(env.GetProjectOption('custom_disassemble_target'))
        if not target_file:
            raise RuntimeError('disabled')
    except:
        verbose('custom_disassemble_target not defined')
        return

    try:
        options = env.subst(env.GetProjectOption('custom_disassemble_options')).split(' ')
    except:
        options = ['-S', '-C']

    if not path.exists(input_file):
        error("no such file or directory: %s" % path.relpath(input_file))

    project_dir = path.realpath(env.subst("$PROJECT_DIR"))
    target_file = path.realpath(target_file)
    args = [
        'avr-objdump'
    ] + options + [
        input_file,
        '>',
        target_file
    ]
    click.echo('Writing disassembly to ', nl=False)
    click.secho(path.relpath(target_file), fg='yellow')

    if verbose_flag:
        print(' '.join(args))

    return_code = subprocess.run(args, shell=True).returncode
    if return_code!=0:
        error('Failed to disassemble binary: exit code %u: %s' % (return_code, ' '.join(args)))

#
# ceate constants of the defines used in dimmer_protocol.h
#

def read_def(source, target, env):

    python = env.subst("$PYTHONEXE")
    project_dir = path.realpath(env.subst("$PROJECT_DIR"))
    script = path.realpath(path.join(project_dir, './scripts/read_def.py'))
    args = [ python, script ]
    return_code = subprocess.run(args, shell=True).returncode
    if return_code!=0:
        error('Failed to run script: exit code %u: %s' % (return_code, ' '.join(args)))


def update_dimmer_inline_asm(source, target, env):

    have_inline_asm = False
    pins = []

    cppdefines = env.get('CPPDEFINES')
    for data in cppdefines:
        if len(data)==1:
            key = data[0]
            val = 1
        else:
            key = data[0]
            val = data[1]
        if key=='HAVE_CHANNELS_INLINE_ASM':
            try:
                val = int(val)
            except:
                val = 0
            if val!=0:
                have_inline_asm = True
        if key=='DIMMER_MOSFET_PINS':
            for pin in val.split(','):
                pin = pin.strip()
                pin = int(pin, 0)
                pins.append(str(pin))

    if have_inline_asm==False:
        return

    python = env.subst("$PYTHONEXE")
    project_dir = path.realpath(env.subst("$PROJECT_DIR"))
    script = path.realpath(path.join(project_dir, './scripts/avr_sfr_tool.py'))
    output = path.realpath(path.join(project_dir, './src/dimmer_inline_asm.h'))
    args = [ python, script, '--output', output, '--pins' ] + pins
    return_code = subprocess.run(args, shell=True).returncode
    if return_code!=0:
        error('Failed to run script: exit code %u: %s' % (return_code, ' '.join(args)))


env.AddPreAction("$BUILD_DIR/scripts/print_def.cpp.o", read_def)
env.AddPreAction("$BUILD_DIR/src/dimmer.cpp.o", update_dimmer_inline_asm)

env.AlwaysBuild(env.Alias("disassemble", None, disassemble))

if env.subst("$PIOENV") not in ("printdef"):
    env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", disassemble)

