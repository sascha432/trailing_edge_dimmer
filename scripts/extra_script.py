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
import hashlib
import click

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
    if input_file=='disassemble' or input_file=='disasm':
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

    # project_dir = path.realpath(env.subst("$PROJECT_DIR"))
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
    zc_pin = None

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
        if key=='ZC_SIGNAL_PIN':
            zc_pin = str(int(val))
        if key=='DIMMER_MOSFET_PINS':
            if ',' in str(val):
                for pin in val.split(','):
                    pin = pin.strip()
                    pin = int(pin, 0)
                    pins.append(str(pin))
            else:
                pins.append(str(int(val)))

    if have_inline_asm==False:
        return

    python = env.subst("$PYTHONEXE")
    project_dir = path.abspath(env.subst("$PROJECT_DIR"))
    script = path.abspath(path.join(project_dir, 'scripts/avr_sfr_tool.py'))
    output = path.abspath(path.join(env.subst('$BUILD_DIR'), 'dimmer_inline_asm.h'))
    header = path.abspath(path.join(env.subst("$PROJECT_SRC_DIR"), 'dimmer_inline_asm.h'))

    print_created = False
    if not path.isfile(header):
        output = header
        print_created = True

    if zc_pin==None:
        click.secho('ZC_SIGNAL_PIN not set', fg='red')
        env.Exit(1)

    args = [ python, script, '--output', output, '--zc-pin', zc_pin,  '--pins' ] + pins
    return_code = subprocess.run(args, shell=True).returncode
    if return_code!=0:
        error('Failed to run script: exit code %u: %s' % (return_code, ' '.join(args)))

    if output!=header:
        with open(output, 'rb') as file:
            contents = file.read()
            hash1 = hashlib.sha1(contents)
        with open(header, 'rb') as file:
            hash2 = hashlib.sha1(file.read())
        if hash1.hexdigest()!=hash2.hexdigest():
            with open(header, 'wb') as file:
                file.write(contents)
                print_created = True

    if print_created:
        click.secho('Header %s updated' % header, fg='yellow')
        # click.secho('Run build process again...', fg='yellow')
        # env.Exit(1)


env.AddPreAction('$BUILD_DIR/scripts/print_def.cpp.o', read_def)
env.AddPreAction('$BUILD_DIR/src/dimmer.cpp.o', update_dimmer_inline_asm)

env.AlwaysBuild(env.Alias("disassemble", None, disassemble))

if env.subst("$PIOENV") not in ("printdef"):
    env.AddPostAction(env.subst('$PIOMAINPROG'), disassemble)
