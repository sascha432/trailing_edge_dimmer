#
#  Author: sascha_lammers@gmx.de
#

import sys
import argparse
import libs.config as config
import libs.fw_const
import time
import json

def read_config(sp, args, cfg):
    sp.print_config()
    try:
        line = sp.read_request(regex='^\+rem=v[0-9a-f]{1,4},')
    except protocol.TimeoutError:
        print('Timeout receiving configuration')
        sys.exit(-1)
    cfg.get_from_rem_command(line)
    print('Received config version: %s' % cfg.version)
    print('Set command: %s' % cfg.get_command())


def display_config(args, cfg):
    if args.json==True:
        print(json.dumps(cfg.get_json(), indent=2))
    else:
        print(cfg.get_command())

def set_items(cfg, items):
    key = '?'
    val = '?'
    try:
        for pair in items:
            pair = pair.split('=', 2)
            key = str(pair[0].strip())
            val = str(pair[1].strip())
            cfg.set_item(key, val)
            print('Set %s to %s' % (key, val))
    except Exception as e:
        raise ValueError('failed to set value: %s=%s: %s' % (key, val, str(e)))

def modify_config(args, cfg):
    try:
        set_items(cfg, args.set)
    except Exception as e:
        print(str(e))
        sys.exit(-1)

def get_version(parser, args):
    if not args.version:
        parser.error('--version required')
    else:
        try:
            version = args.version.split('.')
            if len(version)<2 or len(version)>3:
                raise Exception()
            parts = []
            for val in version:
                parts.append(int(val))
            if len(parts) == 2:
                parts.append(None)
            return parts
        except:
            parser.error('version format: major.minor[.revision]')
    return version

DIMMER = libs.fw_const.DimmerConstBase()

actions = {
    'display': 'display firmware configuration',
    'modify': 'modify firmware configuration',
    'write': 'store firmware configuration in EEPROM',
    'monitor': 'monitor dimmer connected to serial port',
    'factory': 'restore factory settings',
    'measure_frequency': 'execute measure frequency command',
    'const': 'display constants for specified version'
}

actions_help = []
for key, val in actions.items():
    actions_help.append('%-24.24s %s' % (key, val))
actions_help = '\n'.join(actions_help)

parser = argparse.ArgumentParser(description='Firmware Configuration Tool', formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('action', metavar='ACTION', help=actions_help, choices=actions.keys())
parser.add_argument('-d', '--data', help='data to read or modify', required=False, default=None)
parser.add_argument('-V', '--version', help='version of the data provided. For example 2.1.x', type=str, default=None)
parser.add_argument('-p', '--port', help='serial port', type=str, default=None)
parser.add_argument('-b', '--baud', help='serial port rate', type=int, default=57600)
parser.add_argument('-a', '--address', help='dimmer address', type=int, default=None)
parser.add_argument('-s', '--set', help='set key=value', nargs='+', default=[])
parser.add_argument('-j', '--json', help='use JSON as output format', action='store_true', default=False)
parser.add_argument('-v', '--verbose', help='verbose', action='store_true', default=False)
parser.add_argument('--store', help='execute store command after modifying configuration', action='store_true', default=False)

args = parser.parse_args()

if args.action=='const':
    version = get_version(parser, args)
    cfg = config.Config(version[0], version[1], version[2])
    DIMMER = cfg.consts.DimmerConst()
    if not DIMMER.is_complete:
        print('---------------------------------------------------')
        print('WARNING: constants for this versions are incomplete')
        print('---------------------------------------------------')

    DIMMER.set_hex_output(True)
    if DIMMER.keys(True):
        for key in DIMMER.keys(True):
            for key2, val2 in DIMMER.__getattribute__(key).items():
                print('DIMMER.%s.%s = %s' % (key, key2, val2))
    else:
        for key in DIMMER.keys():
            print('DIMMER.%s = %s' % (key, DIMMER.__getattribute__(key)))

    sys.exit(0)

if args.action in ('write', 'factory', 'monitor'):
    if not args.port:
        parser.error('--port required')
else:
    if not args.data and not args.port:
        parser.error('--data or --port required')

if args.data:
    version = get_version(parser, args)

if args.port:
    try:
        import serial
    except:
        parser.error('cannot import serial. install pyserial: pip install pyserial')

    import libs.serial_protocol as protocol

    monitor = args.action=='monitor'

    ser = serial.Serial(baudrate=args.baud, timeout=5)
    sp = protocol.Protocol(ser, args.address)
    if args.verbose:
        print('Verbose mode enabled...')
        sp.display_rx = True

    ser.port = args.port
    ser.dtr = False
    ser.rts = True
    ser.open()
    if ser.isOpen():
        try:
            try:
                data = sp.read_request(length = sp.get_version())
            except protocol.RebootError:
                print('Reboot detected, waiting 3 seconds...')
                time.sleep(3)
                data = sp.read_request(length = sp.get_version())
            except protocol.TimeoutError:
                raise protocol.ProtocolError('Serial timeout')

            if isinstance(data, bytearray):
                version = config.Config.get_version(data)
                print('Detected version: %u.%u.%u' % (version[0], version[1], version[2]))
                version_key = config.Config.is_version_supported(version[0], version[1], version[2], False)
                if version_key==False:
                    raise protocol.ProtocolError('version %s.%s.%s not supported' % (str(version[0]), str(version[1]), str(version[2])))
                cfg = config.Config(version[0], version[1], version[2])
                sp.structs = cfg.structs
                sp.DIMMER = cfg.consts.DimmerConst()
                DIMMER = sp.DIMMER
            else:
                raise protocol.ProtocolError('Failed to retrieve version')

            # custom actions
            if args.action=='factory':
                print('Resetting factory settings...')
                sp.reset_factory_settings()

            elif args.action=='write':
                print('Writing configuration to EEPROM...')
                sp.write_eeprom(True)

            elif args.action=='measure_frequency':
                print('Measuring frequency...')
                sp.measure_frequency()

            # monitor or display
            if monitor:
                print('Monitoring serial port...')
                while monitor:
                    line = sp.readline()
                    sp.print_data(line)
            else:
                if args.action=='display':
                    read_config(sp, args, cfg)
                    display_config(args, cfg)

                elif args.action=='modify':

                    read_config(sp, args, cfg)
                    modify_config(args, cfg)
                    sp.send_config(cfg)

                    if args.store:
                        sp.store_config()
                        sp.wait_for_eeprom()

                    read_config(sp, args, cfg)
                    display_config(args, cfg)

                    print('Closing connection...')
                    ser.close()

        except protocol.ProtocolError as e:
            print('Protocol error: %s' % (e))
            sys.exit(-1)

else:
    cfg = config.Config(version[0], version[1], version[2])

    try:
        cfg.get_from_rem_command(args.data)
        print('Detected version: %s' % cfg.version)
    except Exception as e:
        try:
            cfg.get_from_command(args.data)
        except Exception as e:
            parser.error('invalid data: %s' % str(e))

    if args.address!=None:
        cfg.set_item('i2c_address', args.address)

    modify_config(args, cfg)

    display_config(args, cfg)

