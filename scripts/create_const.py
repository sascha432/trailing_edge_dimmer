#
#  Author: sascha_lammers@gmx.de
#

#
# ceate constants of the defines used in dimmer_protocol.h
#

import re
import sys
import os
import json

filename = './src/dimmer_protocol_const.h'
outfile1 = './scripts/libs/fw_const_ver_2_2_x.py'
version = '2.2.x'

with open(outfile1, 'w', newline='\n') as ofh1:
    ofh1.write('from . import fw_const\n');
    ofh1.write('class DimmerConst(fw_const.DimmerConstBase):\n');
    ofh1.write('    def __init__(self):\n');
    ofh1.write('        fw_const.DimmerConstBase.__init__(self)\n');
    ofh1.write('        self.is_complete = True\n');
    ofh1.write('        self.VERSION = \'%s\'\n' % version);

    attr = {}
    objs = {}
    with open(filename, 'r') as ifh:
        for line in ifh.read().split('\n'):
            line = line.strip()
            # get name and integral or float value
            m = re.match('^#define\s+([^\s]*)\s+([0-9a-fA-Fx\-\.]+)', line)
            if m:
                name = m[1].replace('DIMMER_', '')
                np_name = name
                if name.startswith('REGISTER_'):
                    np_name = np_name[np_name.index('_') + 1:]
                    obj_name = 'REGISTER'
                elif name.startswith('I2C_'):
                    np_name = np_name[np_name.index('_') + 1:]
                    obj_name = 'I2C'
                elif name.startswith('COMMAND_'):
                    np_name = np_name[np_name.index('_') + 1:]
                    obj_name = 'COMMAND'
                elif name.startswith('OPTIONS_'):
                    np_name = np_name[np_name.index('_') + 1:]
                    obj_name = 'OPTIONS'
                elif name.startswith('EEPROM_FLAGS_'):
                    np_name = np_name[13:]
                    obj_name = 'EEPROM_FLAGS'
                elif name=='EEPROM_WRITTEN':
                    name = 'EVENT_' + name
                    obj_name = 'EVENT'
                else:
                    obj_name = 'EVENT'
                    name = 'EVENT_' + name

                value = m[2]
                try:
                    value = int(value)
                except:
                    try:
                        value = float(value)
                    except:
                        pass
                ovalue = m[2]
                try:
                    ovalue = int(ovalue, 0)
                except:
                    try:
                        ovalue = float(ovalue)
                    except:
                        pass
                attr[name] = value
                if obj_name:
                    if not obj_name in objs:
                        objs[obj_name] = {}
                    objs[obj_name][np_name] = ovalue

    ofh1.write('        self.attr = {\n');
    lines = json.dumps(attr, indent=4, sort_keys=str).split('\n')
    fc = None
    for line in lines:
        if line.startswith('}'):
            # add subdivided constants as inlined object
            ofh1.write('        \n')
            for key, val in objs.items():
                json_str = json.dumps(val).replace('"', '\'')
                outtmp = "'%s': type('obj', (object,), %s)()," % (key, json_str)
                ofh1.write('            %s\n' % outtmp)
        elif not line.startswith('{'):
            # add indent, replace " with ' and remove quotes for hex values
            outtmp = re.sub(': "(0x[0-9a-f]+)"', lambda m: ': ' + m[1], line.strip('\r\n'), re.IGNORECASE).replace('"', '\'')
            try:
                # add newline after the first character changes
                tmp = outtmp.strip(' \t\r\n')[1]
                if fc!=tmp:
                    if fc:
                        ofh1.write('        \n')
                    fc = tmp
            except:
                pass

            ofh1.write('        %s,\n' % outtmp.rstrip(','))
    ofh1.write('        }\n')

