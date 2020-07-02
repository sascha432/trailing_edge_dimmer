#!/usr/bin/python3
#
# Author: sascha_lammers@gmx.de
#

# pip install matplotlib websocket-client

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
import serial.tools.list_ports
import serial
import sys
import re
import time
import threading
import json
import hashlib
from os import path
from lib.dimmer_connection import DimmerConnection
from lib.serial_console import SerialConsole
from lib.tk_form_var import TkFormVar
from lib.dimmer_const import DimmerConst

LARGE_FONT = ("Verdana", 16)
MEDIUM_FONT = ("Verdana", 13)

def appdir_relpath(filename):
    app_dir = path.dirname(path.realpath(__file__))
    return path.realpath(path.join(app_dir, filename))

class MainApp(tk.Tk):

    def __init__(self, connection, consts, *args, **kwargs):

        tk.Tk.__init__(self, *args, **kwargs)

        tk.Tk.wm_title(self, "Trailing Edge Dimmer Firmware Configuration")

        self.minsize(800, 320);

        self.pages = [
            { 'text': 'Start Page', 'class': StartPage },
            { 'text': 'Status', 'class': StatusPage },
            { 'text': 'Configuration', 'class': ConfigurationPage },
            { 'text': 'Cubic Interpolation', 'class': CubicInterpolationPage },
        ]

        self.connection = connection
        self.consts = consts
        self.console = SerialConsole()
        self.connection.set_console(self.console)
        self.connection.set_controller(self)

        self.config_filename = appdir_relpath('.dimmer_fw_config.json')
        self.read_config()

        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand = True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}
        self.active = False

        for page in self.pages:
            frame = page['class'](container, self)
            self.frames[page['class']] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        self.show_frame(StartPage)

    def show_frame(self, _class):
        frame = self.frames[_class]
        self.active = _class
        frame.tkraise()

    def get_frame(self, _class):
        return self.frames[_class]

    def read_config(self):
        try:
            with open(self.config_filename, 'rt') as file:
                self.config = json.loads(file.read())
        except Exception as e:
            print("Failed to read configuration: %s" % e)
            self.config = {
                'connections': [],
                'last_connection': '',
                'slave_address': '0x17',
                'master_address': '0x18',
                'baudrate': '115200',
            }

    def write_config(self):
        try:
            with open(self.config_filename, 'wt') as file:
                file.write(json.dumps(self.config))
        except Exception as e:
            print("Failed to write configuration: %s" % e)

    def update_metrics(self, info):
        self.frames[StatusPage].title.configure(text='Version=%s Channels=%u Levels=%u VCC=%.2f NTC %.2f°C ATmega %.2f°C %.2fHz' % (self.info['version'], self.info['num_channels'], self.info['num_levels'], info['vcc'] / 1000.0, info['temperature'], info['temperature2'], info['frequency']))

    def update_info(self, info):
        if 'num_channels' in info:
            n = info['num_channels']
            self.frames[StatusPage].title.configure(text='Version=%s Channels=%u Levels=%u' % (info['version'], n, info['num_levels']))
        else:
            n = 8
            info['num_channels'] = 8
            self.frames[StatusPage].title.configure(text='Status')
        self.info = info
        self.frames[CubicInterpolationPage].set_channels(n)


class BasePage(tk.Frame):

    def __init__(self, parent, controller):

        tk.Frame.__init__(self, parent)
        self.controller = controller
        self.top = tk.Frame(self)
        self.top.pack(side=tkinter.TOP, pady=10, padx=10, expand=True, fill=tkinter.BOTH)

        self.menu_outer_frame = tk.Frame(self)
        self.menu_outer_frame.pack(in_=self.top, side=tkinter.TOP, pady=10, padx=10)

        self.menu_frame = tk.Frame(self)
        self.menu_frame.pack(in_=self.menu_outer_frame, side=tkinter.LEFT, pady=30, padx=10)
        self.title_frame = tk.Frame(self)
        self.title_frame.pack(in_=self.menu_outer_frame, side=tkinter.RIGHT, pady=30, padx=10)

        self.main_menu(self, self.menu_frame, self.__class__)
        self.title(self, self.title_frame, self.get_page_title(self.__class__))

    def main_menu(self, frame, content, current):
        self.fixed_menu = tk.Frame(self)
        self.fixed_menu.place(relwidth=1.0, height=80, x=20, y=0)
        for page in self.controller.pages:
            button = ttk.Button(self, text=page['text'], state=(current==page['class'] and tk.DISABLED or tk.NORMAL), command=lambda param=page['class']: self.controller.show_frame(param))
            button.pack(in_=self.fixed_menu, side=tkinter.LEFT, padx=6)

    def get_page_title(self, _class):
        for page in self.controller.pages:
            if _class == page['class']:
                return page['text']
        return None

    def title(self, frame, menu, text):
        self.title_frame = tk.Frame(self)
        self.title_frame.place(in_=self.fixed_menu, relwidth=1.0, height=80, x=400, y=0)
        label = tk.Label(frame, text=text, font=LARGE_FONT)
        label.pack(in_=self.title_frame, side=tkinter.LEFT, pady=6, padx=10)
        self.title = label

class StartPage(BasePage):

    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)

        ttk.Label(self, text="I2C over UART, TCP and web sockets is supported", font=MEDIUM_FONT).pack(in_=self.top, side=tkinter.TOP, padx=5, pady=5)

        form_frame = tk.Frame(self)
        self.form_frame = form_frame
        form_frame.pack(in_=self.top, side=tkinter.TOP, padx = 50, pady = 20)

        button_frame = tk.Frame(self)
        button_frame.pack(in_=self.top, side=tkinter.TOP, padx = 10, pady = 20)

        # self.form = { 'hostname': tk.StringVar(), 'username': tk.StringVar(), 'password': tk.StringVar(), 'safe_credentials': tk.IntVar() }
        # self.form['safe_credentials'].set(1)

        pad = 2

        ttk.Label(self, text="Port, Hostname or IP:").grid(in_=form_frame, row=0, column=0, padx=pad, pady=pad)

        self.config = {'username': '', 'password': '', 'safe_credentials': False}
        self.form = TkFormVar(self.controller.config, self.config)

        baudrates = ['9600', '19200', '38400', '57600', '76800', '115200', '230400']

        values = ['']
        try:
            for conn in self.controller.config['connections']:
                values.append(conn['username'] + '@' + conn['hostname'])
        except:
            pass

        self.hostname = ttk.Combobox(self, width=40, values=values, textvariable=self.form['last_connection'], postcommand=self.update_serial_ports)
        self.serial_ports_hash = False
        self.hostname.grid(in_=form_frame, row=0, column=1, padx=pad, pady=pad)
        self.hostname.bind('<<ComboboxSelected>>', self.on_select)

        ttk.Label(self, text="Baud rate:").grid(in_=form_frame, row=3, column=0, padx=pad, pady=pad)
        ttk.Combobox(self, width=40, values=baudrates, textvariable=self.form['baudrate']).grid(in_=form_frame, row=3, column=1, padx=pad, pady=pad)

        ttk.Label(self, text="I2C Slave Address:").grid(in_=form_frame, row=1, column=0, padx=pad, pady=pad)
        ttk.Entry(self, width=43, textvariable=self.form['slave_address']).grid(in_=form_frame, row=1, column=1, padx=pad, pady=pad)

        ttk.Label(self, text="I2C Master Address:").grid(in_=form_frame, row=2, column=0, padx=pad, pady=pad)
        ttk.Entry(self, width=43, textvariable=self.form['master_address']).grid(in_=form_frame, row=2, column=1, padx=pad, pady=pad)

        self.username = ttk.Label(self, text="Username:");
        self.username.grid(in_=form_frame, row=4, column=0, padx=pad, pady=pad)
        ttk.Entry(self, width=43, textvariable=self.form['username']).grid(in_=form_frame, row=4, column=1, padx=pad, pady=pad)

        self.password = ttk.Label(self, text="Password:");
        self.password.grid(in_=form_frame, row=5, column=0, padx=pad, pady=pad)
        ttk.Entry(self, width=43, show='*', textvariable=self.form['password']).grid(in_=form_frame, row=5, column=1, padx=pad, pady=pad)

        ttk.Checkbutton(self, text="Safe credentials", variable=self.form['safe_credentials']).grid(in_=form_frame, row=6, column=0, padx=pad, pady=pad, columnspan=2)

        self.connect_button = ttk.Button(self, text="Connect", command=self.connect);
        self.connect_button.grid(in_=button_frame, row=5, column=0, padx=pad, pady=pad, columnspan=2)

        self.controller.connection.bind(self.update_start_page_form)

    def enable_form(self, state):
        start = False
        for child in self.winfo_children():
            if child==self.form_frame:
                start = True
            elif child==self.connect_button:
                start = False
            if start:
                try:
                    child.configure(state=state)
                except:
                    pass

    def info_callback(self, address, data, info):

        info = self.controller.consts.unpack_struct(self.controller.consts.register_mem_info_t, data)

        n = info['version']
        info['version'] = '%u.%u.%u' % (n >> 10, (n >> 5) & 0x1f, n & 0x17)

        self.controller.show_frame(StatusPage)
        self.controller.update_info(info)


    def update_start_page_form(self, text, status):
        self.title['text'] = 'Start Page - %s' % text
        if status:
            self.connect_button['text'] = 'Disconnect'
            self.connect_button['command'] = self.disconnect
            self.enable_form(tk.DISABLED)
            self.controller.update_info({})
            C = self.controller.consts
            size = self.controller.consts.register_mem_info_t['__SIZE']
            self.controller.connection.send_command([C.ADDRESS, C.REGISTER_CMD_READ_LENGTH, size, C.REGISTER_INFO_VERSION], size, self.info_callback)
        else:
            self.connect_button['text'] = 'Connect'
            self.connect_button['command'] = self.connect
            self.enable_form(tk.NORMAL)

    def disconnect(self):
        self.controller.connection.close();

    def connect(self):
        print(self.controller.config, self.config)
        ctrl = self.controller
        config = ctrl.config
        name = config['last_connection']
        try:
            if self.is_com_port(name):
                port = name.split(':', 2)[0];
                ctrl.connection.console.clear()
                ctrl.connection.set_slave_address(config['slave_address'])
                ctrl.connection.set_master_address(config['master_address'])
                if not ctrl.connection.open_serial(port, ctrl.config['baudrate']):
                    raise RuntimeError('Cannot open %s' % port)
                if ctrl.connection.connected:
                    ctrl.write_config()
            else:
                raise RuntimeError('Currently only serial ports are supported')
        except RuntimeError as e:
            tk.messagebox.showerror(title='Error', message=str(e))

        # if cur==0:
        #     //tk.messagebox.showerror(title='Error', message='Enter new connection details or select existing connection')
        # else:
        #     print(cur)
        #     if self.is_com_port(cur):
        #         print(cur)

    def is_com_port(self, value):
        try:
            m = re.match('^(/dev/[a-z0-9/]+|COM[0-9]+): ', value, re.IGNORECASE)
            return m != None
        except:
            return False

    def update_serial_ports(self):
        widget = self.hostname
        ports = serial.tools.list_ports.comports()
        new_values = []
        for port, desc, hwid in sorted(ports):
            new_values.append("{}: {} [{}]".format(port, desc, hwid))
        hash = hashlib.md5(str(new_values).encode())
        if self.serial_ports_hash!=hash:
            self.serial_ports_hash = hash
            values = widget['values']
            for value in values:
                if not self.is_com_port(value):
                    new_values.append(value)
            widget['values'] = new_values


    def on_select(self, event):
        str = event.widget['values'][event.widget.current()]
        # if self.is_com_port(str):
        #     self.username['text'] = 'Baud rate'
        # else:
        #     self.username['text'] = 'Username'

        # //self.update_serial_ports(event.widget)
        pass
        # print(event.widget)
        # cur = event.widget.current()
        # if cur>0:
        #     conn = self.config['connections'][cur - 1]
        #     self.form['username'].set(conn['username'])
        #     self.form['password'].set(self.password_placeholder)
        #     self.form['safe_credentials'].set(1)
        # else:
        #     self.form['username'].set('')
        #     self.form['password'].set('')

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
        if tkinter.messagebox.askyesno(title='Question', message='Reset MCU?'):
            self.controller.connection.reset_mcu()

    def send_command(self, request, response, callback, ask=False):
        if ask:
            if not tkinter.messagebox.askyesno(title='Question', message='Execute %s?' % ask):
                return
        self.controller.connection.send_command(request, response, callback)


    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)

        self.title.configure(font=MEDIUM_FONT)

        spacer = tk.Frame(self)
        spacer.pack(in_=self.top, side=tkinter.BOTTOM, padx=0, pady=10)

        console_frame = tk.Frame(self)
        console_frame.pack(in_=self.top, side=tkinter.TOP, padx=10, pady=0, expand=1, fill=tkinter.BOTH)

        menu = tk.Frame(self)
        menu.pack(in_=console_frame, side=tkinter.LEFT, padx=10, pady=0)

        C = self.controller.consts

        commands = [
            ( 'Dimmer Info', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_PRINT_INFO ], None, None ),
            ( 'Read VCC', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_VCC, 0.1 ], [ 'VCC %umV', 'H' ], None ),
            ( 'Read Temperature', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_TEMPERATURE2, 0.1 ], [ 'ATMega Temp. %.1f°C', 'f' ], None ),
            ( 'Read NTC', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_TEMPERATURE, 0.1 ], [ 'NTC %.1f°C', 'f' ], None ),
            ( 'Read Frequency', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_FREQUENCY ], [ 'Frequency %.2fHz', 'f' ], None ),
            ( 'Read Channels', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_READ_CHANNELS ], [ 'Channel 1=%u,2=%u,3=%u,4=%u,5=%u,6=%u,7=%u,8=%u', 'hhhhhhhh' ], None ),
            ( 'Print Cubic', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_PRINT_CUBIC_INT ], None, None ),
            ( 'EEPROM Settings', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_WRITE_SETTINGS ], None, None ),
            ( 'EEPROM Configuration', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_WRITE_EEPROM ], None, None ),
            ( '!EEPROM Restore', [ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_RESTORE_FACTORY ], None, None ),
            ( 'Dump Memory', [ C.ADDRESS, C.REGISTER_CMD_READ_LENGTH, C.REGISTER_MEM_SIZE, C.REGISTER_MEM_START_OFFSET ], C.REGISTER_MEM_SIZE, self.dump_mem_callback ),
        ]

        button = ttk.Button(self, text="Clear Console", width=35, command=self.controller.console.clear)
        button.pack(in_=menu, side=tkinter.TOP, padx=6)
        button = ttk.Button(self, text="Reset MCU", width=35, command=self.ask_reset)
        button.pack(in_=menu, side=tkinter.TOP, padx=6)

        for cmd in commands:
            button = ttk.Button(self, text=cmd[0].strip('!'), width=35, command=lambda request=cmd[1],response=cmd[2],callback=cmd[3],ask=cmd[0][0]=='!' and cmd[0][1:] or False: self.send_command(request, response, callback, ask))
            button.pack(in_=menu, side=tkinter.TOP, padx=6)

        text = tk.Text(self, width=80, height=30, takefocus=0)
        text.pack(in_=console_frame, expand=1, fill=tkinter.BOTH, side=tk.LEFT)

        scrollbar = tk.Scrollbar(self)
        scrollbar.pack(in_=console_frame, side=tk.RIGHT, fill=tkinter.Y)

        text.configure(yscrollcommand=scrollbar)

        self.controller.console.text = text
        self.controller.console.scrollbar = scrollbar

class ConfigurationPage(BasePage):

    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)

class CubicInterpolationPage(BasePage):

    def read_response_callback(self, address, data, info):
        channel = info[0]
        for n in range(0, 8):
            self.cubic_int[channel][n].set('%u:%u' % (data[n * 2], data[n * 2 + 1]))
        self.callback_executed = True

    def write_response_callback(self, address, data, info):
        self.callback_executed = True

    def clear_cubic_int(self):
        for channel in range(0, 8):
            for n in range(0, 8):
                self.cubic_int[channel][n].set('255:255')

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
            print(e)
            pass
        self.set_button_state(False)

    def _write_cubic_int(self):
        C = self.controller.consts
        try:
            for channel in range(0, self.channels):
                cmd = [ C.ADDRESS, C.REGISTER_CUBIC_INT_DATA_POINTS_OFFSET ]
                for n in range(0, 8):
                    tmp = self.cubic_int[channel][n].get()
                    try:
                        values = tmp.split(':')
                        cmd.append(int(values[0]))
                        cmd.append(int(values[1]))
                    except:
                        msg = 'Invalid data point: %s' % tmp
                        tk.messagebox.showerror(message=msg)
                        raise RuntimeError(msg)
                self.callback_executed = False
                self.controller.connection.send_command(cmd, None, None)
                self.controller.connection.send_command([ C.ADDRESS, C.REGISTER_COMMAND, C.COMMAND_WRITE_CUBIC_INT, channel ], 2, callback=self.write_response_callback)
                self.wait_for_callback()
        except Exception as e:
            print(e)
            pass
        self.set_button_state(False)

    def set_button_state(self, disable):
        for button in self.buttons:
            button.configure(state=disable and tk.DISABLED or tk.NORMAL)

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
            for var in self.cubic_int[i]:
                var.set('?:?')
        for i in range(n, 8):
            for e in self.channel_entries[i]:
                e.configure(state=tkinter.DISABLED)
            for var in self.cubic_int[i]:
                var.set('')


    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)

        self.channels = 8

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

        self.channel_entries = []
        for j in range(0, 8):
            label = "Channel #%u:" % (j + 1)
            channel = ttk.Label(self, text=label);
            channel.grid(in_=form_frame, row=j, column=0, padx=pad, pady=pad)
            items = []
            for i in range(0, 8):
                e = ttk.Entry(self, width=20, textvariable=self.cubic_int[j][i])
                e.grid(in_=form_frame, row=j, column=(i + 1), padx=pad, pady=pad)
                items.append(e)
            self.channel_entries.append(items)



consts = DimmerConst()
app = MainApp(DimmerConnection(consts), consts)
app.mainloop()

