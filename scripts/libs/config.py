#
#  Author: sascha_lammers@gmx.de
#

import re
import struct
import json
import importlib
from . import floats
from . import fw_const

class Config:

    def is_version_supported(major, minor, revision=0, throw=False):
        try:
            version_key = '%u_%u_%u' % (major, minor, revision)
            structs = importlib.import_module('libs.fw_ver_%u_%u_%u' % (major, minor, revision), package=None)
            consts = importlib.import_module('libs.fw_const_ver_%u_%u_%u' % (major, minor, revision), package=None)
        except:
            try:
                version_key = '%u_%u_x' % (major, minor)
                structs = importlib.import_module('libs.fw_ver_%u_%u_x' % (major, minor), package=None)
                consts = importlib.import_module('libs.fw_const_ver_%u_%u_x' % (major, minor), package=None)
            except:
                raise Exception('version %u.%u.x not supported' % (major, minor))
        return (structs, consts)

    def get_version(data):
        if isinstance(data, str):
            (version, ) = struct.unpack('>H', bytearray.fromhex(data.zfill(4))[0:2])
        else:
            (version, ) = struct.unpack('<H', data[0:2])
        major = version >> 10
        minor = (version >> 5) & 0x1f
        revision = version & 0x1f
        return (major, minor, revision)

    def __init__(self, major, minor, revision):
        (self.structs, self.consts, ) = Config.is_version_supported(major, minor, revision)
        self.version = 'unknown'
        self.register_mem_cfg = None
        self.info = None
        self.i2c_address = 0x17

    def bytearray_to_hex(self, array):
        return ''.join('%02x' % b for b in array)

    def get_command(self):
        if self.register_mem_cfg==None:
            raise Exception('register_mem_cfg not set')
        return '+I2CT=17%02x%s' % (self.info.cfg_start_address, self.bytearray_to_hex(bytearray(self.register_mem_cfg)))

    def set_items_fromhex(self, data):
        data = bytearray.fromhex(data)
        self.i2c_address = data[0]
        self.length = len(data) - 1
        self.register_mem_cfg = self.structs.register_mem_cfg_t.from_buffer_copy(data[2:])

    def get_config(self):
        return self.register_mem_cfg

    def __repr__(self):
        self.register_mem_cfg.max_level = self.info.max_levels
        dct = {}
        for name in dir(self.register_mem_cfg):
            dct[name] = self.register_mem_cfg.__getattribute__(name).__repr__()
        return dct

    def reset(self):
        self.version = 'unknown'
        self.i2c_address = 0x17
        self.info = None

    def get_from_command(self, cmd):
        m = re.match('^\+i2ct=([0-9a-f]+)', cmd, re.IGNORECASE)
        if m:
            self.reset()
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
            (self.structs, self.consts, ) = Config.is_version_supported(major, minor, revision, True)
            self.version = '%u.%u.%u' % (major, minor, revision)
            self.set_items_fromhex(m[2])
            return True
        raise ValueError("could not find valid hex data")

    def set_item(self, key, val):
        if self.register_mem_cfg==None:
            raise ValueError('register_mem_cfg not set')

        conf = self.register_mem_cfg

        if '.' in key:
            pair = key.split('.', 2)
            sub = pair[0]
            attr = conf.__getattribute__(sub)
            if not isinstance(attr, object):
                raise ValueError('Invalid type: %s: %s' % (type(attr), sub))
            key = pair[1]
            conf = attr

        attr = conf.__getattribute__(key)
        if isinstance(attr, int):
            conf.__setattr__(key, int(val))
        elif isinstance(attr, float):
            conf.__setattr__(key, float(val))
        elif isinstance(attr, floats.ShiftedFloat) or isinstance(attr, floats.FixedPointFloat):
            attr.value = float(val)
        else:
            raise ValueError('Invalid type: %s: %s' % (type(attr), key))
