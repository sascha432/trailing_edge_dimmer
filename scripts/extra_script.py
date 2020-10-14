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


env.AlwaysBuild(env.Alias("disassemble", None, disassemble))
env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", disassemble)
