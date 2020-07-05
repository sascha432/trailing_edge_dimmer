#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
import hashlib
import re
import serial.tools.list_ports
import lib.kfcfw_session
from lib.atol import atol

from lib.tk_form_var import TkFormVar
from lib.tk_ez_grid import TkEZGrid
from lib.dimmer_connection import BaseConnection
from app.BasePage import BasePage
from app.StatusPage import StatusPage


class StartPage(BasePage):

    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)

        ttk.Label(self, text="I2C over UART, TCP and web sockets is supported", font=self.MEDIUM_FONT).pack(in_=self.top, side=tkinter.TOP, padx=5, pady=5)

        form_frame = tk.Frame(self)
        self.form_frame = form_frame
        form_frame.pack(in_=self.top, side=tkinter.TOP, padx=50, pady=20)

        button_frame = tk.Frame(self)
        button_frame.pack(in_=self.top, side=tkinter.TOP, padx=10, pady=20)

        # self.form = { 'hostname': tk.StringVar(), 'username': tk.StringVar(), 'password': tk.StringVar(), 'safe_credentials': tk.IntVar() }
        # self.form['safe_credentials'].set(1)

        self.config = {'username': '', 'password': '', 'safe_credentials': False}
        self.form = TkFormVar(self.controller.config, self.config)

        baudrates = ['9600', '19200', '38400', '57600', '76800', '115200', '230400']
        values = self.get_connections()

        self.select_theme(None)

        pad = 2
        grid = TkEZGrid(self, form_frame, pad, pad)

        grid.label("Port, Hostname or IP:")
        self.hostname = grid.next(ttk.Combobox(self, width=40, values=values, textvariable=self.form['last_connection'], postcommand=self.update_serial_ports))
        self.serial_ports_hash = False
        self.hostname.bind('<<ComboboxSelected>>', self.on_select_connection)

        grid.first(ttk.Label(self, text="Baud rate:"))
        grid.next(ttk.Combobox(self, width=40, values=baudrates, textvariable=self.form['baudrate']))

        grid.first(ttk.Label(self, text="I2C Slave Address:"))
        grid.next(ttk.Entry(self, width=43, textvariable=self.form['slave_address']))

        grid.first(ttk.Label(self, text="I2C Master Address:"))
        grid.next(ttk.Entry(self, width=43, textvariable=self.form['master_address']))

        grid.first(ttk.Label(self, text="Username:"))
        self.username = grid.next(ttk.Entry(self, width=43, textvariable=self.form['username']))

        grid.first(ttk.Label(self, text="Password:"))
        self.password = grid.next(ttk.Entry(self, width=43, show='*', textvariable=self.form['password']))

        grid.first(ttk.Checkbutton(self, text="Safe credentials", variable=self.form['safe_credentials']), columnspan=2)

        # style = ttk.Style()
        # grid.label('Theme')
        # theme = grid.next(ttk.Combobox(self, values=style.theme_names(), width=40, textvariable=self.form['theme']))
        # theme.bind('<<ComboboxSelected>>', self.select_theme)

        self.connect_button = grid.first(ttk.Button(self, text="Connect", command=self.connect), columnspan=2)
        self.update_serial_ports()

    def select_theme(self, event):
        try:
            style = ttk.Style()
            if self.controller.config['theme']:
                style.theme_use(self.controller.config['theme'])
        except Exception as e:
            self.logger.error('cannot set theme: %s: %s' % (self.controller.config['theme'], e))

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

    def update_start_page_form(self, text, status):
        self.logger.debug('connection status changed: %s: %s' % (str(status), text))
        self.title.configure(text='Start Page - %s' % text)
        if status:
            # we are connected :)
            self.connect_button['text'] = 'Disconnect'
            self.connect_button['command'] = self.disconnect
            self.enable_form(tk.DISABLED)
        else:
            # we have been disconnected :(
            self.connect_button['text'] = 'Connect'
            self.connect_button['command'] = self.connect
            self.enable_form(tk.NORMAL)
            self.controller.console.write_hb('DISCONNECTED')

    def config_update_connections(self, url, username, password):
        for conn in self.controller.config['connections']:
            if conn['url']==url:
                conn['username'] = username
                conn['password'] = password
                return
        self.controller.config['connections'].append({
            'url': url,
            'username': username,
            'password': password,
        })

    def get_connections(self):
        values = ['']
        try:
            for conn in self.controller.config['connections']:
                values.append(conn['url'])
                # values.append(conn['username'] + '@' + conn['url'])
        except:
            pass
        return values

    def on_select_connection(self, event):
        name = self.controller.config['last_connection']
        for conn in self.controller.config['connections']:
            # print(name, conn['url'])
            if name==conn['url']:
                if not self.config['username']:
                    self.form['username'].set(conn['username']);
                if self.config['password']:
                    self.form['password'].set('')
                break

    def disconnect(self):
        self.controller.connection.close();

    def connect(self):
        self.controller.frames[StatusPage].title.configure(text='Status - Connecting...')
        self.controller.info = {}
        config = self.controller.config
        hash = None
        if self.config['username'] and self.config['password']:
            session = lib.kfcfw_session.Session()
            hash = session.generate(self.config['username'], self.config['password'])
        if self.config['safe_credentials'] and hash:
            self.config_update_connections(config['last_connection'], self.config['username'], hash)

        conn_details = {'name': config['last_connection'], 'baudrate': atol(config['baudrate'], default=57600), 'username': self.config['username'], 'password': hash}
        self.logger.debug('connect: %s' % conn_details)
        self.controller.write_config()

        self.controller.console.clear()
        self.controller.connection = BaseConnection.create_connection(self.controller, self.controller.console, self.logger, conn_details)
        self.controller.connection.set_slave_address(config['slave_address'])
        self.controller.connection.set_master_address(config['master_address'])
        self.controller.connection.set_consts(self.controller.consts)
        self.controller.connection.open()

    def update_serial_ports(self):
        self.logger.debug('update_serial_ports')
        widget = self.hostname
        ports = serial.tools.list_ports.comports()
        new_values = []
        for port, desc, hwid in sorted(ports):
            new_values.append("{}: {} [{}]".format(port, desc, hwid))
        # check if there was any changes
        hash = hashlib.md5(str(new_values).encode())
        if self.serial_ports_hash!=hash:
            self.serial_ports_hash = hash
            # copy all non com port to new list
            values = widget['values']
            for value in values:
                if not BaseConnection.valid_com_port(value):
                    new_values.append(value)
            widget['values'] = new_values
        # remove last_connection if com port does not exist anymore
        last_connection = self.controller.config['last_connection']
        port = BaseConnection.valid_com_port(last_connection)
        if port:
            match = False
            for value in widget['values']:
                if BaseConnection.valid_com_port(value)==port:
                    # update in case the description has changed
                    self.form['last_connection'].set(value)
                    last_connection = value
                    match = True
                    break
            if not match:
                self.form['last_connection'].set('')
                last_connection = ''
        self.hostname.set(last_connection)

