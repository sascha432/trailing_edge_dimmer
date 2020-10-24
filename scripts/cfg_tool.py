#
#  Author: sascha_lammers@gmx.de
#

import sys
import argparse
import libs.config as config
import time
import json

parser = argparse.ArgumentParser(description="Firmware Configuration Tool")
parser.add_argument("action", help="action to execute", choices=["display", "modify", "write", "monitor", "factory", "measure_frequency"])
parser.add_argument('-d', '--data', help="data to read or modify", required=False, default=None)
parser.add_argument('-V', '--version', help='version of the data provided. For example 2.1.x', type=str, default=None)
parser.add_argument('-p', '--port', help='serial port', type=str, default=None)
parser.add_argument('-b', '--baud', help='serial port rate', type=int, default=57600)
parser.add_argument('-a', '--address', help='dimmer address', type=int, default=None)
parser.add_argument('-s', '--set', help='set key=value', nargs='+', default=[])
parser.add_argument('-j', '--json', help='use JSON as output format', action="store_true", default=False)
parser.add_argument('-v', '--verbose', help='verbose', action="store_true", default=False)

args = parser.parse_args()

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

if args.action in ('write', 'factory', 'monitor'):
    if not args.port:
        parser.error('--port required')
else:
    if not args.data and not args.port:
        parser.error('--data or --port required')

if args.data:
    if not args.version:
        parser.error('--data requires --version')
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
            version = parts
        except:
            parser.error('version format: major.minor[.revision]')

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
        print("Verbose mode enabled...")
        sp.display_rx = True

    ser.port = args.port
    ser.dtr = False
    ser.rts = True
    ser.open()
    if ser.isOpen():
        data = sp.read_request(sp.get_version())
        if data==False:
            if not monitor:
                parser.error('serial read timeout')

        if data==None:
            print("Reboot detected, waiting 3 seconds...")
            time.sleep(3)
            data = sp.read_request(sp.get_version())

        if isinstance(data, bytearray):
            version = config.Config.get_version(data)
            print("Detected version: %u.%u.%u" % (version[0], version[1], version[2]))
            version_key = config.Config.is_version_supported(version[0], version[1], version[2], False)
            if version_key==False:
                parser.error('version %s.%s.%s not supported' % (str(version[0]), str(version[1]), str(version[2])))

            cfg = config.Config(version[0], version[1], version[2])
            sp.structs = cfg.structs

        # custom actions
        if args.action=='factory':
            print("Resetting factory settings...")
            sp.reset_factory_settings()

        elif args.action=='write':
            print("Writing configuration to EEPROM...")
            sp.write_eeprom(True)

        elif args.action=='measure_frequency':
            print("Measuring frequency...")
            sp.measure_frequency()


        # monitor or display
        if monitor:
            print("Monitoring serial port...")
            while monitor:
                line = sp.readline()
                sp.print_data(line)
        else:
            sp.print_config()
            n = 0
            while n < 5:
                line = sp.readline()
                try:
                    cfg.get_from_rem_command(line)
                    print('Received config version: %s' % cfg.version)
                    print('Set command: %s' % cfg.get_command())
                    n = -1
                    break
                except Exception as e:
                    # print('Parse error: %s', str(e))
                    pass
                n += 1

            if n!=-1:
                print('Timeout receiving configuration')
                sys.exit(-1)

            try:
                set_items(cfg, args.set)
            except Exception as e:
                print(str(e))
                sys.exit(-1)

            if args.action=='display':
                if args.json==True:
                    print(json.dumps(cfg.get_json(), indent=2))
                else:
                    print(cfg.get_command())

            elif args.action=='modify':
                data = cfg.get_command().encode()
                print("Sending configuration: ", data)
                ser.write(data + b'\n')
                print("Sending store command...")
                sp.store_config()

                n = 0
                while n < 5:
                    line = sp.readline()
                    if sp.print_data(line)==0xf3:
                        break
                    n += 1

                sp.print_config()
                if args.json==True:
                    print(json.dumps(cfg.get_json(), indent=2))
                else:
                    print(cfg.get_command())

                print('Closing connection...')
                ser.close()

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

    if len(args.set):
        if args.json==None:
            args.json = False
        try:
            set_items(cfg, args.set)
        except Exception as e:
            parser.error(str(e))

    if args.address!=None:
        cfg.set_item('i2c_address', args.address)

    if args.json==True:
        print(cfg.get_json())
    else:
        print(cfg.get_command())

