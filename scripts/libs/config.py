#
#  Author: sascha_lammers@gmx.de
#

import re
import struct
import json

class Config:

    configs = {
        '2.2.1': {
            'options': {
                'restore_level': 0x01,
                'report_metrics': 0x02,
                'temp_alarm_triggered': 0x04
            },
            'struct': {
                'i2c_address': 'B',
                'mem_address': 'B',
                'options': 'B',
                'max_temp': 'B',
                'fade_in_time': 'f',
                'temp_check_interval': 'B',
                'linear_correction_factor': 'f',
                'zero_crossing_delay_ticks': 'B',
                'minimum_on_time_ticks': 'H',
                'minimum_off_time_ticks': 'H',
                'internal_1_1v_ref': 'f',
                'int_temp_offset': 'b',
                'ntc_temp_offset': 'b',
                'report_metrics_max_interval': 'B'
            }
        },
        '2.2.x': {
            'options': {
                'restore_level': 0x01,
                'report_metrics': 0x02,
                'temp_alarm_triggered': 0x04,
                'leading_edge_mode': 0x20,
            },
            'struct': {
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
        }
    }

    def is_version_supported(major, minor, revision = 'x', throw = False):
        key = '%s.%s.%s' % (str(major), str(minor), str(revision))
        if key in Config.configs:
            return key
        key = '%s.%s.x' % (str(major), str(minor))
        if key in Config.configs:
            return key
        if throw:
            raise Exception('version %s.%s.x not supported' % (str(major), str(minor)))
        return False


    def get_version(data):
        if isinstance(data, str):
            (version, ) = struct.unpack('>H', bytearray.fromhex(data.zfill(4))[0:2])
        else:
            (version, ) = struct.unpack('<H', data[0:2])
        major = version >> 10
        minor = (version >> 5) & 0x1f
        revision = version & 0x1f
        return (major, minor, revision)

    def __init__(self, major_version, minor_version = None):
        if minor_version==None:
            version_key = major_version
        else:
            version_key = Config.is_version_supported(major_version, minor_version, True)
        self.version = 'unknown'
        self.struct = Config.configs[version_key]['struct']
        self.options = Config.configs[version_key]['options']
        self.config = {}

    def get_unpack(self):
        s = '<'
        for key, val in self.struct.items():
            s = s + val
        return s

    def get_length(self):
        return struct.calcsize(self.get_unpack())

    def set_items(self, items):
        self.config = self.struct.copy();
        n = 0
        for key, val in self.config.items():
            self.config[key] = items[n]
            n += 1

    def validate_value(self, type, val):
        if isinstance(val, str):
            if type=='f':
                val = float(val)
            else:
                val = int(val)
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
        return val

    def set_item(self, key, val):
        if not key in self.config:
            raise KeyError('key does not exist: %s' % key)
        type = self.struct[key]
        val = self.validate_value(type, val)
        if val!=None:
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
        tmp['options'] = '0b{:08b}'.format(tmp['options'])
        return json.dumps(tmp, indent=2)

    def get_bytes(self):
        b = bytearray()
        for key, val in self.config.items():
            fmt = self.struct[key]
            try:
                packed = struct.pack('<' + fmt, val)
            except:
                raise Exception('invalid type for key: %s: type: %s' % (key, type(val)))
            b = b + packed;
        return b

    def get_command(self):
        return '+I2CT=' + self.get_bytes().hex()

    def set_items_fromhex(self, data):
            fmt = self.get_unpack()
            config = bytearray.fromhex(data)
            size = struct.calcsize(fmt)
            if len(config)<size:
                raise ValueError('not enough data: required: %u: %u' % (size, len(config)))
            self.set_items(struct.unpack(fmt, config[0:size]));

    def get_from_command(self, cmd):
        m = re.match('^\+i2ct=([0-9a-f]+)', cmd, re.IGNORECASE)
        if m:
            self.version = 'unknown'
            self.set_items_fromhex(m[1])
            return True
        else:
            m = re.match('([0-9a-f]+)', cmd, re.IGNORECASE)
            if m:
                self.set_items_fromhex(m[1])
                return True
        raise ValueError("could not find valid hex data")

    def get_from_rem_command(self, cmd):
        m = re.match('^\+rem=v([0-9a-f]{1,4}),i2ct=([0-9a-f]+)', cmd, re.IGNORECASE)
        if m:
            (major, minor, revision) = Config.get_version(m[1])
            Config.is_version_supported(major, minor, revision, True)
            self.version = '%u.%u.%u' % (major, minor, revision)
            self.set_items_fromhex(m[2])
            return True

        raise ValueError("could not find valid hex data")
