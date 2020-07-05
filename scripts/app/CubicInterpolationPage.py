#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
import threading
import time
import re
from lib.tk_ez_grid import TkEZGrid
from app.BasePage import BasePage
from app.CubicInterpolationEditCurvePage import CubicInterpolationEditCurvePage

class CubicInterpolationPage(BasePage):

    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)

        self.channels = 8
        self.edit_curve = False

        menu = tk.Frame(self)
        menu.pack(in_=self.top, side=tkinter.TOP, padx = 50, pady = 20)

        button = ttk.Button(self, text="Clear Data", command=lambda: self.clear_cubic_int())
        button.pack(in_=menu, side=tkinter.LEFT, padx=6, pady=6)
        self.buttons = [button]

        button = ttk.Button(self, text="Read Data", command=lambda: self.read_cubic_int())
        button.pack(in_=menu, side=tkinter.LEFT, padx=6, pady=6)
        self.buttons.append(button)

        button = ttk.Button(self, text="Write Data", command=lambda: self.write_cubic_int())
        button.pack(in_=menu, side=tkinter.LEFT, padx=6, pady=6)
        self.buttons.append(button)

        form_frame = tk.Frame(self)
        form_frame.pack(in_=self.top, side=tkinter.TOP, padx = 50, pady = 20)
        self.form_frame = form_frame

        self.cubic_int = []
        for i in range(0, 8):
            self.cubic_int.append([])
            for j in range(0, 8):
                self.cubic_int[i].append(tkinter.StringVar())

        pad = 5
        grid = TkEZGrid(self, form_frame, pad, pad)

        self.channel_entries = []
        for j in range(0, 8):
            label = "Channel #%u:" % (j + 1)
            channel = grid.label(label)
            # ttk.Label(self, text=label);
            # channel.grid(in_=form_frame, row=j, column=0, padx=pad, pady=pad)
            items = []
            for i in range(0, 8):
                # e.grid(in_=form_frame, row=j, column=(i + 1), padx=pad, pady=pad)
                items.append(grid.next(ttk.Entry(self, width=10, textvariable=self.cubic_int[j][i])))

            button = grid.next(ttk.Button(self, text="Edit Curve", command=lambda channel=j: self.show_curve(channel)))
            # button.grid(in_=form_frame, row=j, column=9, padx=pad, pady=pad)
            self.buttons.append(button)
            # items.append(button)
            self.channel_entries.append(items)

    def split(self, value):
        try:
            values = re.split('[;:,\.\s]', value)
            values[0] = int(values[0])
            values[1] = int(values[1])
            values[0] = max(0, min(values[0], 255))
            values[1] = max(0, min(values[1], 255))
        except Exception as e:
            self.logger.error('split failed: %s: %s: %s' % (value, values, e))
            return [0, 0]
        else:
            return values

    def join(self, x, y):
        try:
            return '%u,%u' % (x, y)
        except:
            self.logger.error('join %s:%s failed' % (str(x), str(y)))
            return '0,0'

    def on_raise(self):
        if self.edit_curve:
            self.controller.show_frame(CubicInterpolationEditCurvePage)

    def show_curve(self, channel):
        self.set_button_state(True)
        self.edit_curve = True
        frame = self.controller.show_frame(CubicInterpolationEditCurvePage)
        frame.init_chart(channel, self.cubic_int[channel])

    def read_response_callback(self, address, data, info):
        channel = info[0]
        for n in range(0, 8):
            self.cubic_int[channel][n].set(self.join(data[n * 2], data[n * 2 + 1]))
        self.callback_executed = True

    def write_response_callback(self, address, data, info):
        self.callback_executed = True

    def clear_cubic_int(self):
        for channel in range(0, 8):
            for n in range(0, 8):
                self.cubic_int[channel][n].set(self.join(0, 0))

    def wait_for_callback(self):
        for i in range(0, 30):
            if self.callback_executed:
                return
            time.sleep(0.1)
        if not self.callback_executed:
            self.controller.console.write('TIMEOUT\n')
        raise RuntimeError("Timeout")

    def _read_cubic_int(self):
        C = self.controller.consts
        try:
            for channel in range(0, self.channels):
                self.callback_executed = False
                self.controller.connection.send_command([ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_CUBIC_INT, channel ], [ channel, C.CUBIC_INT_DATA_POINTS * 2 ], callback=self.read_response_callback)
                self.wait_for_callback()
        except Exception as e:
            self.logger.error('reading cubic int table failed: %s' % e)
            pass
        self.set_button_state(False)

    def _write_cubic_int(self):
        C = self.controller.consts
        try:
            for channel in range(0, self.channels):
                cmd = [ C.ADDRESS, C.REGISTER_CUBIC_INT_DATA_POINTS_OFFSET ]
                for n in range(0, 8):
                    values = self.split(self.cubic_int[channel][n].get())
                    cmd.append(values[0])
                    cmd.append(values[1])
                self.callback_executed = False
                self.controller.connection.send_command(cmd, None, None)
                self.controller.connection.send_command([ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_WRITE_CUBIC_INT, channel ], 2, callback=self.write_response_callback)
                self.wait_for_callback()
        except Exception as e:
            self.logger.error('writing cubic int table failed: %s' % e)
            pass
        self.set_button_state(False)

    def set_button_state(self, disable):
        if not disable:
            self.edit_curve = False
        n = 0
        for button in self.buttons:
            button.configure(state=disable and tk.DISABLED or tk.NORMAL)
            if n>3+self.channels:
                break
            n += 1

    def read_cubic_int(self):
        self.set_button_state(True)
        thread = threading.Thread(target = self._read_cubic_int)
        thread.daemon = True
        thread.start()

    def write_cubic_int(self):
        self.set_button_state(True)
        thread = threading.Thread(target = self._write_cubic_int)
        thread.daemon = True
        thread.start()

    def set_channels(self, n):
        self.channels = n
        for i in range(0, n):
            for e in self.channel_entries[i]:
                e.configure(state=tkinter.NORMAL)
                self.buttons[i + 3].configure(state=tkinter.NORMAL)
            for var in self.cubic_int[i]:
                var.set(self.join(0, 0))
        for i in range(n, 8):
            for e in self.channel_entries[i]:
                e.configure(state=tkinter.DISABLED)
                self.buttons[i + 3].configure(state=tkinter.DISABLED)
            for var in self.cubic_int[i]:
                var.set(self.join(0, 0))

