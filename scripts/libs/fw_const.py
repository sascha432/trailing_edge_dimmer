#
#  Author: sascha_lammers@gmx.de
#

class OutputWrapper(object):
    def __init__(self, attr, as_hex = True):
        self.attr = attr
        self.hex = as_hex

    def keys(self):
        def is_name(name):
            return len(name)>1 and name[0]!='_'
        return filter(is_name, dir(object.__getattribute__(self, 'attr')))

    def items(self):
        attr = object.__getattribute__(self, 'attr')
        parts = []
        for key in self.keys():
            parts.append((key, self.hexstr(attr.__getattribute__(key))))
        return parts

    def hexstr(self, value):
        if self.hex and isinstance(value, int) and value>=0:
            return '0x%02x' % value
        return value

    def __getattribute__(self, name):
        try:
            return object.__getattribute__(self, name)
        except:
            pass
        value = object.__getattribute__(self.attr, name)
        return self.hexstr(value)

class DimmerConstBase(object):
    def __init__(self):
        self.VERSION = None
        self.attr = {}
        self.hex_output = False
        self.is_complete = False

    # positive integers will be converted to hex strings
    def set_hex_output(self, enable):
        self.hex_output = enable

    def is_hex_output(self):
        return object.__getattribute__(self, 'hex_output')

    def keys(self, objects = False):
        parts = []
        for key, val in self.attr.items():
            if objects==self.is_object(val):
                parts.append(key)
        return parts

    def items(self):
        return object.__getattribute__(self, 'attr')

    def encode_value(self, value):
        if self.is_hex_output() and isinstance(value, int) and value>=0:
            return '0x%02x' % value
        return value

    def is_object(self, attr):
        return not isinstance(attr, (int, float, str))

    def __getattribute__(self, name):
        try:
            return object.__getattribute__(self, name)
        except:
            pass
        attr = self.items()
        if not name in attr:
            raise AttributeError("'DIMMER' object has no attribute '%s'" % name)
        attr = attr[name]

        # wrap inlined objects
        if self.is_object(attr):
            return OutputWrapper(attr, self.is_hex_output())

        return self.encode_value(attr)
