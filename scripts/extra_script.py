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
# create protocol
#

def build_protocol(source, target, env):

    script = path.realpath(path.join(path.dirname(inspect.getfile(inspect.currentframe())), 'dimmer_reg_mem.py'))

    args = [
        env.subst("$PYTHONEXE"),
        script,
        '--create'
    ]
    if verbose_flag:
        args.append('--verbose')

    return_code = subprocess.run(args, shell=True).returncode
    if return_code!=0:
        error("%s failed to run, exit code %u\ncommand: '%s'" % (path.basename(script), return_code, ' '.join(args)))

#
# run SFR tool
#

def run_sfr_tool(source, target, env):

    create_inline_asm = False
    pins = None
    script = path.realpath(path.join(path.dirname(inspect.getfile(inspect.currentframe())), 'sfr_tool.py'))
    board = env["BOARD_MCU"]

    args = [
        env.subst("$PYTHONEXE"),
        script,
        '--mmcu', board,
        '--output', path.realpath(path.join(env.subst("$PROJECT_SRC_DIR"), 'dimmer_sfr.h')),
        '--pin-funcs', '2', '8', '11'
    ]

    if verbose_flag:
        args.append('--verbose')

    # verbose("CPPDEFINES:")
    for define in env['CPPDEFINES']:
        if isinstance(define, str):
            name = define
            value = 1
        elif isinstance(define, tuple):
            name = define[0]
            value = env.subst(str(define[1]))
        # verbose("%s=%s (%s)" % (name, value, value and "True" or "False"))
        if name=="DIMMER_USE_INLINE_ASM" and value:
            create_inline_asm = True
        if name=="DIMMER_MOSFET_PINS":
            pins = value
            args.append('--pins')
            args.append(value)


    if create_inline_asm:
        verbose("Creating SFR headers: %s" % (' '.join(args)))

        if not pins:
            error('DIMMER_MOSFET_PINS not defined')

        return_code = subprocess.run(args, shell=True).returncode
        if return_code!=0:
            error("%s failed to run, exit code %u\ncommand: '%s'" % (path.basename(script), return_code, ' '.join(args)))

#
# disassemble ELF binary
#

def disassemble(source, target, env):

    input_file = str(target[0])
    if input_file=='disassemble':
        input_file=env.subst("$BUILD_DIR/${PROGNAME}.elf")
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


run_sfr_tool(None, None, env)

env.AlwaysBuild(env.Alias("sfr_tool", None, run_sfr_tool))
env.AlwaysBuild(env.Alias("disassemble", None, disassemble))
env.AlwaysBuild(env.Alias("build_protocol", None, build_protocol))

env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", disassemble)

