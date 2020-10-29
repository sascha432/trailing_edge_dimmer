#
#  Author: sascha_lammers@gmx.de
#

# nasty little list helpers

# create list from a to b
# ra(0, 2) = [0, 1, 2]
def ra(a, b):
    return list(range(a, b + 1))

# create bit values for bits in list
# bv([1, 4]) = [2, 16]
def bv(bits):
    return list(map(lambda n: (1 << n), bits))

# create formated list from fmt and list items
# pf('MyValue%03u', [1, 2]) = ['MyValue001', 'MyValue002']
def pf(fmt, items):
    return list(map(lambda n: fmt % (n), items))

# create dict from
# 2 lists                                               (key: val), ...
# one list and dict.items()                             (key: (dict_key, dict_val)), ...
# one list as keys and values                           (key: key), ...
# a list and a single value assigned to all keys        (key, value), (key2, value), ...
def dc(k, v = None):
    if v==None:
        v = k
    elif isinstance(v, dict):
        return dict(zip(k, v.items()))
    elif not isinstance(v, (list, dict)):
        v = [v] * len(k)
    return dict(zip(k, v))

# merge multiple dictionaries
def me(*args):
    d = {}
    for a in args:
        d.update(a)
    return d
