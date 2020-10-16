#
#  Author: sascha_lammers@gmx.de
#

# convert config command to json and back
#
# command:
# +i2ct=17,89,91
#
# response:
# +REM=v840,i2ct=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500000020001412
#
# if cfg.get_from_rem_command('+REM=v840,i2ct=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500000020001412'):
#     print(cfg.version)
#     print(cfg.get_json())
#
# 2.2.0
# {
#   "i2c_address": "0x17",
#   "mem_address": "0xa2",
#   "options": "00000010",
#   "max_temp": 75,
#   ....
#   "switch_on_count": 18
# }
#
#   cfg.set_item('minimum_off_time_ticks', 1000)
#   print(cfg.get_command())
#
# +I2CT=17a2024b0000904002000000b004ff0de803cdcc8c3f00000500000020001412
#

import re
import struct
import json

class Config:
    def __init__(self):
        self.version = 'unknown'
        self.struct = {
            'i2c_address': 'B',
            'mem_address': 'B',
            'options': 'B',
            'max_temp': 'B',
            'fade_in_time': 'f',
            'temp_check_interval': 'B',
            '__empty0': 'B',
            '__empty1': 'B',
            'halfwave_adjust_ticks': 'b',
            'zero_crossing_delay_ticks': 'H',
            'minimum_on_time_ticks': 'H',
            'minimum_off_time_ticks': 'H',
            'internal_1_1v_ref': 'f',
            'int_temp_offset': 'b',
            'ntc_temp_offset': 'b',
            'report_metrics_max_interval': 'B',
            'range_begin': 'h',
            'range_end': 'h',
            'switch_on_minimum_ticks': 'H',
            'switch_on_count': 'B',
        }
        self.config = {}

    def get_unpack(self):
        s = '<'
        for key, val in self.struct.items():
            s = s + val
        return s

    def set_items(self, items):
        self.config = self.struct.copy();
        n = 0
        for key, val in self.config.items():
            self.config[key] = items[n]
            n += 1

    def validate_value(self, type, val):
        if type in 'BbHh' and not isinstance(val, int):
            raise ValueError('value not integer: %s' % str(val))
        if type in 'f' and not isinstance(val, float):
            raise ValueError('value not float: %s' % str(val))
        if type=='B':
            if val<0 or val>255:
                raise ValueError('value out of range: 0 to 255: %d' % val)
        if type=='b':
            if val<-128 or val>127:
                raise ValueError('value out of range: -128 to 127: %d' % val)
        if type=='H':
            if val<0 or val>65535:
                raise ValueError('value out of range: 0 to 65535: %d' % val)
        if type=='h':
            if val<-32768 or val>32867:
                raise ValueError('value out of range: -32868 to 32867: %d' % val)
        return True

    def set_item(self, key, val):
        if not key in self.config:
            raise KeyError('key does not exist: %s' % key)
        type = self.struct[key]
        if self.validate_value(type, val):
            self.config[key] = val
            return True
        return False

    def dump(self):
        names = list(self.struct.keys())
        for key, val in self.config.items():
            print('%s = %s' % (key, str(val)))

    def get_json(self):
        tmp = self.config.copy();
        tmp['i2c_address'] = '0x%02x' % tmp['i2c_address']
        tmp['mem_address'] = '0x%02x' % tmp['mem_address']
        tmp['options'] = '{:08b}'.format(tmp['options'])
        return json.dumps(tmp, indent=2)

    def get_bytes(self):
        b = bytearray()
        for key, val in self.config.items():
            fmt = self.struct[key]
            try:
                packed = struct.pack('<' + fmt, val)
            except Exception as e:
                raise TypeError('invalid type for key: %s: type: %s' % (key, type(val)))
            b = b + packed;
        return b

    def get_command(self):
        return '+I2CT=' + self.get_bytes().hex()

    def get_from_command(self, cmd):
        m = re.match('^\+i2ct=([0-9a-f]+)', cmd, re.IGNORECASE)
        print(m)
        if m:
            self.version = 'unknown'
            fmt = self.get_unpack()
            config = bytearray.fromhex(m[1])
            self.set_items(struct.unpack(fmt, config[0:struct.calcsize(fmt)]));
            return True
        return False

    def get_from_rem_command(self, cmd):
        m = re.match('^\+rem=v([0-9a-f]{1,4}),i2ct=([0-9a-f]+)', cmd, re.IGNORECASE)
        if m:
            version = m[1]
            while len(version) < 4:
                version = '0' + version
            version = bytearray.fromhex(version)
            (version, ) = struct.unpack('>H', version)
            self.version = '%u.%u.%u' % (version >> 10, ((version >> 5) & 0x1f), version & 0x1f)
            if not self.version.startswith('2.2.'):
                return False

            fmt = self.get_unpack()
            config = bytearray.fromhex(m[2])
            self.set_items(struct.unpack(fmt, config[0:struct.calcsize(fmt)]));
            return True

        return False


cfg = Config()

line = '+REM=v840,i2ct=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500000020001412\n'
if cfg.get_from_rem_command(line):
    # print(cfg.version)
    # print(cfg.get_json())

    cfg.set_item('minimum_off_time_ticks', 1000)

    print(cfg.get_command())

# line = '+i2ct=17a2024b0000904002000000b004ff0d0002cdcc8c3f00000500000020001412\n'
# if cfg.get_from_command(line):
#     print(cfg.get_json())
#     print(cfg.version)

