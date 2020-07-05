#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
from app.BasePage import BasePage

class StatusPage(BasePage):

    def dump_mem_callback(self, address, data, info):
        output = ''
        n = 0
        for value in list(data):
            if n % 8 == 0:
                output = output + ('\n%04x: ' % n)
            output = output + ('%02x ' % value)
            n = n + 1
        self.controller.console.write(output[1:] + '\n')

    def read_response_callback(self, address, data, info):
        for n in range(0, 8):
            self.cubic_int[info[0]][n].set(data[n])
        self.callback_executed = True

    def ask_reset(self):
        if tkinter.messagebox.askyesno(title='Confirmation', message='Reset MCU?'):
            self.controller.connection.reset_mcu()

    def send_command(self, cmd):
        request = cmd[2]
        response = cmd[3]
        callback = cmd[4]
        confirm = cmd[1] and cmd[0] or False
        if confirm:
            if not tkinter.messagebox.askyesno(title='Confirmation', message='Execute %s?' % confirm):
                return
        self.controller.connection.send_command(request, response, callback)


    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)

        self.title.configure(font=self.MEDIUM_FONT)

        spacer = tk.Frame(self)
        spacer.pack(in_=self.top, side=tkinter.BOTTOM, padx=0, pady=10)

        console_frame = tk.Frame(self)
        console_frame.pack(in_=self.top, side=tkinter.TOP, padx=10, pady=0, expand=1, fill=tkinter.BOTH)

        menu = tk.Frame(self)
        menu.pack(in_=console_frame, side=tkinter.LEFT, padx=10, pady=0)

        C = self.controller.consts

        commands = [
            ( 'Dimmer Info', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_PRINT_INFO ], None, None ),
            ( 'Read VCC', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_VCC, 0.1 ], [ 'VCC %umV', 'H' ], None ),
            ( 'Read Temperature', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_TEMPERATURE2, 0.1 ], [ 'ATMega Temp. %.1f°C', 'f' ], None ),
            ( 'Read NTC', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_TEMPERATURE, 0.1 ], [ 'NTC %.1f°C', 'f' ], None ),
            ( 'Read Frequency', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_FREQUENCY ], [ 'Frequency %.2fHz', 'f' ], None ),
            ( 'Read Channels', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_CHANNELS ], [ 'Channel 1=%d,2=%d,3=%d,4=%d,5=%d,6=%d,7=%d,8=%d', 'hhhhhhhh' ], None ),
            ( 'Channel 1 - 0%', False, [ C.ADDRESS, C.REGISTER_CHANNEL_FROM_LEVEL, 0xff, 0xff, 0x00, 0x00, 0xA0, 0x41, 0, 0x00, 0x00, C.COMMAND_FADE ], None, None ),
            ( 'Channel 1 - 100%', False, [ C.ADDRESS, C.REGISTER_CHANNEL_FROM_LEVEL, 0xff, 0xff, 0x00, 0x00, 0xA0, 0x41, 0, 0xfe, 0xfe, C.COMMAND_FADE ], None, None ),
            ( 'Print Cubic', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_PRINT_CUBIC_INT, 127 ], None, None ),
            ( 'Test Cubic', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_CUBIC_INT_TEST_PERF ], None, None ),
            ( 'Get Cubic', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_GET_CUBIC_INT, 0x00,0x00, 8, 127,  0,40,199,255, 0,218,39,255 ], [ 'Levels %d,%d,%d,%d,%d,%d,%d,%d', 'hhhhhhhh' ], None ),
            ( 'EEPROM Write Settings', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_WRITE_SETTINGS ], None, None ),
            ( 'EEPROM Write Config.', False, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_WRITE_EEPROM ], None, None ),
            ( 'EEPROM Restore', True, [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_RESTORE_FACTORY ], None, None ),
            ( 'Dump Memory', False, [ C.ADDRESS, C.REGISTER_CMD_READ_LENGTH, C.REGISTER_MEM_SIZE, C.REGISTER_MEM_START_OFFSET ], C.REGISTER_MEM_SIZE, self.dump_mem_callback ),
        ]

        button = ttk.Button(self, text="Clear Console", width=35, command=self.controller.console.clear)
        button.pack(in_=menu, side=tkinter.TOP, padx=6)
        button = ttk.Button(self, text="Reset MCU", width=35, command=self.ask_reset)
        button.pack(in_=menu, side=tkinter.TOP, padx=6)

        for cmd in commands:
            button = ttk.Button(self, text=cmd[0], width=35, command=lambda cmd=cmd: self.send_command(cmd))
            button.pack(in_=menu, side=tkinter.TOP, padx=6)

        text = tk.Text(self, width=80, height=30, takefocus=0, font=self.CONSOLE_FONT)
        text.pack(in_=console_frame, expand=1, fill=tkinter.BOTH, side=tk.LEFT)

        scrollbar = tk.Scrollbar(self, command=text.yview)
        scrollbar.pack(in_=console_frame, side=tk.RIGHT, fill=tkinter.Y)

        text.configure(yscrollcommand=scrollbar.set)

        self.controller.console.text = text
        self.controller.console.scrollbar = scrollbar
