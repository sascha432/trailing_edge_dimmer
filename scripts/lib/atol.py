#
# Author: sascha_lammers@gmx.de
#

import re

def atol(text, default=None, base=None):
    if not text:
        return default
    try:
        text = text.strip()
        if base:
            value = int(text, base)
        elif text.startswith('0x'):
            value = int(text[2:], 16)
        elif text.startswith('0b'):
            value = int(text[2:], 2)
        elif text.startswith('b'):
            value = int(text[1:], 2)
        elif re.match('^0[0-7]+$', text):
            value = int(text, 8)
        else:
            value = int(text)
        return value
    except ValueError as e:
        return default
