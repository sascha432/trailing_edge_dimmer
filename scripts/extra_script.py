Import("env");
import subprocess
import os
from os import path
import sys
import inspect
import shlex
from SCons.Script import ARGUMENTS
import tempfile

def run_sfr_tool(source, target, env):

    create_inline_asm = False
    pins = None
    verbose_flag = False
    script = path.realpath(path.join(path.dirname(inspect.getfile(inspect.currentframe())), 'sfr_tool.py'))
    board = env["BOARD_MCU"]

    def error(msg):
        print(msg, file=sys.stderr)
        sys.exit(1)

    def verbose(msg):
        if verbose_flag:
            print(msg)

    args = [
        env.subst("$PYTHONEXE"),
        script,
        '--mmcu', board,
        '--output', path.realpath(path.join(env.subst("$PROJECT_SRC_DIR"), 'dimmer_sfr.h')),
        '--pin-funcs', '2', '8', '11'
    ]

    if int(ARGUMENTS.get("PIOVERBOSE", 0)):
        verbose_flag = True
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

        popen = subprocess.run(args, shell=True)
        return_code = popen.returncode
        if return_code!=0:
            error("%s failed to run, exit code %u\ncommand: '%s'" % (path.basename(script), return_code, ' '.join(args)))


def disassemble(source, target, env):
    exec_obj_dump = False
    for define in env['CPPDEFINES']:
        if isinstance(define, str):
            name = define
            value = 1
        elif isinstance(define, tuple):
            name = define[0]
            value = env.subst(str(define[1]))
        if name=='EXEC_OBJ_DUMP':
            exec_obj_dump = True
    if exec_obj_dump:

        output = path.realpath(path.join(env.subst("$BUILD_DIR"), 'firmware.lst'))
        project_dir = path.realpath(env.subst("$PROJECT_DIR"))
        print(project_dir)
        args = [
            'avr-objdump',
            '-d',
            '-S',
            '-l',
            '-C',
            '-j',
            '.text',
            str(target[0]),
            '>',
            output
        ]
        print("Disassembling %s" % output)
        print(' '.join(args))
        subprocess.run(args, shell=True)

run_sfr_tool(None, None, env)

env.AlwaysBuild(env.Alias("build_sfr_header", None, run_sfr_tool))
env.AlwaysBuild(env.Alias("sfr_tool", None, run_sfr_tool))

env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", disassemble)
