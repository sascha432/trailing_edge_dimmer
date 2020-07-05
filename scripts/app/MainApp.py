#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
from os import path
import json
from lib.serial_console import SerialConsole
from lib.dimmer_connection import *
import serial
import math
from cefpython3 import cefpython as cef
from app.StartPage import StartPage
from app.StatusPage import StatusPage
from app.ConfigurationPage import ConfigurationPage
from app.CubicInterpolationPage import CubicInterpolationPage
from app.CubicInterpolationEditCurvePage import CubicInterpolationEditCurvePage

def appdir_relpath(filename):
    app_dir = path.dirname(path.realpath(__file__))
    return path.realpath(path.join(app_dir, filename))

class MainApp(tk.Tk):

    def __init__(self, logger, consts, *args, **kwargs):

        self.logger = logger

        tk.Tk.__init__(self, *args, **kwargs)
        tk.Tk.wm_title(self, "Trailing Edge Dimmer Firmware Configuration")
        cef.Initialize()

        self.minsize(1280, 800);

        self.pages = [
            { 'text': 'Start Page', 'class': StartPage },
            { 'text': 'Status', 'class': StatusPage },
            { 'text': 'Configuration', 'class': ConfigurationPage },
            { 'text': 'Cubic Interpolation', 'class': CubicInterpolationPage },
            { 'text': None, 'class': CubicInterpolationEditCurvePage },
        ]

        self.connection = None
        self.consts = consts
        self.console = SerialConsole()

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
        try:
            frame.on_raise()
        except:
            pass
        return frame

    def get_frame(self, _class):
        return self.frames[_class]

    def read_config(self):
        if path.exists(self.config_filename):
            try:
                with open(self.config_filename, 'rt') as file:
                    self.config = json.loads(file.read())
                    return
            except Exception as e:
                logger.error("failed to read configuration: %s: %s" % (self.config_filename, e))
        self.config = {
            'connections': [],
            'last_connection': '',
            'slave_address': '0x17',
            'master_address': '0x18',
            'baudrate': '115200',
            'theme': '',
        }

    def write_config(self):
        try:
            with open(self.config_filename, 'wt') as file:
                file.write(json.dumps(self.config))
        except Exception as e:
            self.logger.error('failed to write configuration: %s: %s' % (self.config_filename, e))

    # BaseConnection callback
    def on_open(self, connection):
        self.frames[StartPage].update_start_page_form(connection.get_status(), True)

    # BaseConnection callback
    def on_close(self, connection):
        self.frames[StartPage].update_start_page_form(connection.get_status(), False)

    # BaseConnection callback
    def on_error(self, connection, error):
        self.frames[StartPage].update_start_page_form(connection.get_status(), True)

    # DimmerConnection callback
    def on_version_info(self, connection, version):
        self.frames[StatusPage].title.configure(text='Version=%u.%u.%u' % version)
        self.show_frame(StatusPage)

    # DimmerConnection callback
    def on_update_metrics(self, connection, info):
        parts = []
        if 'version' in self.info:
            parts.append('Version=%s' % self.info['version'])
            parts.append('Channels=%u' % self.info['num_channels'])
            parts.append('Levels=%u' % self.info['num_levels'])
        if 'vcc' in info and info['vcc']>0:
            parts.append('VCC=%.2f' % (info['vcc'] / 1000.0))
        if 'temperature' in info and not math.isnan(info['temperature']):
            parts.append('NTC %.2f°C' % info['temperature'])
        if 'temperature2' in info and not math.isnan(info['temperature2']):
            parts.append('ATmega %.2f°C' % info['temperature2'])
        if 'frequency' in info and not math.isnan(info['frequency']):
            parts.append('%.2fHz' % info['frequency'])

        self.frames[StatusPage].title.configure(text=' '.join(parts))

    def on_update_info(self, connection, info):
        self.info = info
        self.on_update_metrics(connection, {})
        self.frames[CubicInterpolationPage].set_channels(self.info['num_channels'])

    def get_page_title(self, _class):
        for page in self.pages:
            if _class == page['class']:
                return page['text']
        return None

