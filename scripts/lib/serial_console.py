#
# Author: sascha_lammers@gmx.de
#

import tkinter

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
            self.text.insert(tkinter.INSERT, message)
            self.text.see(tkinter.END)


