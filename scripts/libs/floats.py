#
#  Author: sascha_lammers@gmx.de
#

from ctypes import *
from _ctypes import _SimpleCData
import struct

class ShiftedFloat(object):
    def __init__(self, offset, shift, precision):
        self._offset_ = offset
        self._shift_ = shift
        self._precision_ = precision

    def ___to_float(self):
        packed = struct.pack('i', int((self.value << self._shift_) + self._offset_))
        (val, ) = struct.unpack('f', packed)
        return val;

    def ___from_float(self, value):
        packed = struct.pack('f', float(value))
        (val, ) = struct.unpack('i', packed)
        return int((val - self._offset_) >> self._shift_)

    def __float__(self):
        return self.___to_float()

    def __int__(self):
        return self.value

    def __setattr__(self, name, value):
        if isinstance(value, float):
            value = self.___from_float(value)
        _SimpleCData.__setattr__(self, name, value)

    def __repr__(self):
        return ('%%.%uf' % self._precision_) % self.___to_float()


class c_int8_ShiftedFloat(ShiftedFloat, _SimpleCData):
    _type_ = "b"
    def __init_subclass__(_class):
        _class.__init__(_class)


class FixedPointFloat(object):
    def __init__(self, _Multiplier, _Divider = 1, _Precision = 4):
        self._multiplier_ = _Multiplier / float(_Divider);
        self._inverted_multiplier_ = 1.0 / self._multiplier_;
        self._rounding_ = 1.0 / self._multiplier_ / 1.9999999;
        self._precision_ = _Precision;

    def ___to_float(self):
        return float(self.value) * self._inverted_multiplier_

    def ___from_float(self, value):
        return int((float(value) + self._rounding_) * self._multiplier_)

    def __float__(self):
        return self.___to_float()

    def __int__(self):
        return self.value

    def __setattr__(self, name, value):
        if isinstance(value, float):
            value = self.___from_float(value)
        _SimpleCData.__setattr__(self, name, value)

    def __repr__(self):
        return ('%%.%uf' % self._precision_) % self.___to_float()


class c_int8_FixedPointFloat(FixedPointFloat, _SimpleCData):
    _type_ = "b"
    def __init_subclass__(_class):
        _class.__init__(_class)
