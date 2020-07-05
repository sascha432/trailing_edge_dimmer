#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
from app.BasePage import BasePage

class ConfigurationPage(BasePage):

    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)
