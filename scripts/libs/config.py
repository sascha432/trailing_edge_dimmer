#
#  Author: sascha_lammers@gmx.de
#

import re
import struct
import json
import importlib
import sys

class Config:

    def is_version_supported(major, minor, revision=0, throw=False):
        try:
            version_key = '%u_%u_%u' % (major, minor, revision)
            structs = importlib.import_module('libs.fw_ver_%u_%u_%u' % (major, minor, revision), package=None)
        except:
            try:
                version_key = '%u_%u_x' % (major, minor)
                structs = importlib.import_module('libs.fw_ver_%u_%u_x' % (major, minor), package=None)
            except:
                raise Exception('version %u.%u.x not supported' % (major, minor))
        return structs

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
        self.structs = Config.is_version_supported(major, minor, revision)
        self.version = 'unknown'
        self.register_mem_cfg_t = None

    def bytearray_to_hex(self, array):
        return ''.join('%02x' % b for b in array)

    def get_command(self):
        if self.register_mem_cfg_t==None:
            raise Exception('register_mem_cfg_t not set')
        return '+I2CT=17a2' + self.bytearray_to_hex(bytearray(self.register_mem_cfg_t))

    def set_items_fromhex(self, data):
        data = bytearray.fromhex(data)
        self.register_mem_cfg_t = self.structs.register_mem_cfg_t.from_buffer_copy(data[2:])

    def get_json(self):
        # self.register_mem_cfg_t.__getattribute__('internal_vref11').value = 1.12
        # self.register_mem_cfg_t.int_temp_offset.value = 1.25
        # print(self.register_mem_cfg_t.__getattribute__('internal_vref11'))
        # print(int(self.register_mem_cfg_t.__getattribute__('internal_vref11')))
        # print(self.register_mem_cfg_t.__getattribute__('internal_vref11'))
        # print(self.register_mem_cfg_t.__getattribute__('internal_vref11').value)

        json = {}
        for field in self.register_mem_cfg_t._fields_:
            name = field[0]
            json[name] = self.register_mem_cfg_t.__getattribute__(name).__repr__()
        return json

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
            self.structs = Config.is_version_supported(major, minor, revision, True)
            self.version = '%u.%u.%u' % (major, minor, revision)
            self.set_items_fromhex(m[2])
            return True

        raise ValueError("could not find valid hex data")

    def set_item(self, key, val):
        if self.register_mem_cfg_t==None:
            raise Exception('register_mem_cfg_t not set')
        n = 0
        num = None
        for field in self.register_mem_cfg_t._fields_:
            if field[0]==key:
                num = n
                break
            n += 1
        if num==None:
            raise Exception('field %s not found', val)

        # self.register_mem_cfg_t._fields_[num] =  val
        # print(bytearray(self.register_mem_cfg_t))

