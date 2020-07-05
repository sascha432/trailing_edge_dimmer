#
# Author: sascha_lammers@gmx.de
#

import tkinter
import math

class SerialConsole(object):

    def __init__(self, text : tkinter.Text = None, scrollbar = None, auto_scroll = True):
        self.text = text;
        self.scrollbar = scrollbar
        self.auto_scroll = auto_scroll

    def clear(self):
        if self.text:
            self.text.delete('1.0', tkinter.END)

    def write(self, message):
        if self.text:
            self.text.insert(tkinter.END, message)
            if self.auto_scroll:
                self.text.see(tkinter.END)

    def write_hb(self, message, width=78):
        hb = (width - len(message)) / 2.0
        self.write('%s %s %s\n' % ('=' * math.floor(hb), message, '=' * math.ceil(hb)))
