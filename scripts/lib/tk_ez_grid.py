#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk

class TkEZGrid(object):
    def __init__(self, frame, in_frame, padx=0, pady=0):
        self.frame = frame
        self.in_frame = in_frame
        self.row = -1
        self.column = 0
        self.padx = padx
        self.pady = pady

    def _set_grid(self, obj, columnspan):
        obj.grid(in_=self.in_frame, row=self.row, column=self.column, padx=self.padx, pady=self.pady, columnspan=columnspan)

    def label(self, text):
        label = ttk.Label(self.frame, text=text)
        return self.first(label)

    def first(self, obj, columnspan=1):
        self.row += 1
        self.column = 0
        self._set_grid(obj, columnspan)
        self.column += columnspan
        return obj

    def next(self, obj, columnspan=1):
        self._set_grid(obj, columnspan)
        self.column += columnspan
        return obj
