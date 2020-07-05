#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
import app.MainApp
import re


class BasePage(tk.Frame):

    def __init__(self, parent, controller):

        tk.Frame.__init__(self, parent)

        self.LARGE_FONT = ("Verdana", 16)
        self.MEDIUM_FONT = ("Verdana", 13)
        self.CONSOLE_FONT = ("Consolas", 10)

        self.controller = controller
        self.logger = controller.logger
        self.top = tk.Frame(self)
        self.top.pack(side=tkinter.TOP, pady=10, padx=10, expand=True, fill=tkinter.BOTH)

        self.menu_outer_frame = tk.Frame(self)
        self.menu_outer_frame.pack(in_=self.top, side=tkinter.TOP, pady=10, padx=10)

        self.menu_frame = tk.Frame(self)
        self.menu_frame.pack(in_=self.menu_outer_frame, side=tkinter.LEFT, pady=30, padx=10)
        self.title_frame = tk.Frame(self)
        self.title_frame.pack(in_=self.menu_outer_frame, side=tkinter.RIGHT, pady=30, padx=10)

        self.main_menu(self, self.menu_frame, self.__class__)
        self.title(self, self.title_frame, self.controller.get_page_title(self.__class__))

    def main_menu(self, frame, content, current):
        self.fixed_menu = tk.Frame(self)
        self.fixed_menu.place(relwidth=1.0, height=80, x=20, y=0)
        for page in self.controller.pages:
            if page['text']:
                button = ttk.Button(self, text=page['text'], state=(current==page['class'] and tk.DISABLED or tk.NORMAL), command=lambda param=page['class']: self.controller.show_frame(param))
                button.pack(in_=self.fixed_menu, side=tkinter.LEFT, padx=6)

    def title(self, frame, menu, text):
        self.title_frame = tk.Frame(self)
        self.title_frame.place(in_=self.fixed_menu, relwidth=1.0, height=80, x=400, y=0)
        label = tk.Label(frame, text=text, font=self.LARGE_FONT)
        label.pack(in_=self.title_frame, side=tkinter.LEFT, pady=6, padx=10)
        self.title = label

