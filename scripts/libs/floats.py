#
#  Author: sascha_lammers@gmx.de
#

from ctypes import *
from _ctypes import _SimpleCData
import struct

class IntRanges(object):
    _ranges_ = {
        'b': (-128, 127),
        'B': (0, 255),
        'h': (-32768, 32767),
        'H': (0, 65535),
        'i': (-2147483648, 2147483647),
        'I': (0, 4294967295)
    };

class ShiftedFloat(object):

    def __init__(self, offset, shift, precision):
        self._offset_ = offset
        self._shift_ = shift
        self._precision_ = precision

    def ____to_float(self, value):
        packed = struct.pack(self._type_=='I' and 'I' or 'i', int((value << self._shift_) + self._offset_))
        (val, ) = struct.unpack('f', packed)
        return val;

    def ___to_float(self):
        packed = struct.pack(self._type_=='I' and 'I' or 'i', int((self.value << self._shift_) + self._offset_))
        (val, ) = struct.unpack('f', packed)
        return val;

    def ___from_float(self, value):
        packed = struct.pack('f', float(value))
        (val, ) = struct.unpack(self._type_=='I' and 'I' or 'i', packed)
        val = int((val - self._offset_) >> self._shift_)
        if self._type_ in IntRanges._ranges_:
            (min_val, max_val) = IntRanges._ranges_.__getitem__(self._type_)
            if val<min_val or val>max_val:
                raise ValueError('Out of range: %s: %f-%f' % (str(value), self.____to_float(min_val), self.____to_float(max_val)))
        else:
            raise TypeError('Unknown type: %s' % (self._type_))

        return val

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
    def __init__(self, _Multiplier, _Divider = 1, _Precision = 6):
        self._multiplier_ = _Multiplier / float(_Divider);
        self._inverted_multiplier_ = 1.0 / self._multiplier_;
        self._rounding_ = 1.0 / self._multiplier_ / 1.99999988079071044921875;
        self._precision_ = _Precision;

    def ___to_float(self):
        return float(self.value) * self._inverted_multiplier_

    def ___from_float(self, value):
        if value<0.0:
            return int(float(value) * self._multiplier_ - 0.5)
        return int(float(value) * self._multiplier_ + 0.5)
        # round(0.5, 0) is broken = 0.0
        # return int(round(float(value) * self._multiplier_, 0))

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
