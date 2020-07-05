#
# Author: sascha_lammers@gmx.de
#

import tkinter
import tkinter as tk
from tkinter import ttk
import tkinter.messagebox
import platform
import urllib
import ctypes
from os import path
from app.BasePage import BasePage
from cefpython3 import cefpython as cef

WINDOWS = (platform.system() == "Windows")
LINUX = (platform.system() == "Linux")
MAC = (platform.system() == "Darwin")

class LoadHandler(object):

    def __init__(self, browser_frame):
        self.browser_frame = browser_frame

    def OnLoadStart(self, browser, **_):
        pass
        # if self.browser_frame.master.navigation_bar:
        #     self.browser_frame.master.navigation_bar.set_url(browser.GetUrl())

class FocusHandler(object):
    def __init__(self, browser_frame):
        self.browser_frame = browser_frame

    def OnTakeFocus(self, next_component, **_):
        pass

    def OnSetFocus(self, source, **_):
        if LINUX:
            return False
        else:
            return True

    def OnGotFocus(self, **_):
        if LINUX:
            self.browser_frame.focus_set()

class BrowserFrame(tk.Frame):

    def __init__(self, master):
        self.resources = path.realpath(path.join(path.dirname(__file__), 'resources'))
        self.base_url = 'file:' + urllib.request.pathname2url(self.resources)
        self.browser = None

        tk.Frame.__init__(self, master)
        # self.master.protocol("WM_DELETE_WINDOW", self.on_close)
        self.master.bind("<Configure>", self.on_root_configure)
        self.bind("<FocusIn>", self.on_focus_in)
        self.bind("<FocusOut>", self.on_focus_out)
        self.bind("<Configure>", self.on_configure)
        self.focus_set()

    def embed_browser(self):
        window_info = cef.WindowInfo()
        rect = [0, 0, self.winfo_width(), self.winfo_height()]
        window_info.SetAsChild(self.get_window_handle(), rect)
        url = self.base_url + '/edit_curve.html'
        settings = {
            'plugins_disabled': True,
        }
        self.browser = cef.CreateBrowserSync(window_info, url=url, settings=settings)
        assert self.browser
        self.browser.SetClientHandler(LoadHandler(self))
        self.browser.SetClientHandler(FocusHandler(self))
        self.set_javascript_bindings()
        self.message_loop_work()

    def message_loop_work(self):
        cef.MessageLoopWork()
        self.after(10, self.message_loop_work)

    def get_window_handle(self):
        if self.winfo_id() > 0:
            return self.winfo_id()
        elif MAC:
            from AppKit import NSApp
            import objc
            return objc.pyobjc_id(NSApp.windows()[-1].contentView())
        else:
            raise Exception("Couldn't obtain window handle")

    def on_root_configure(self, _):
        if self.browser:
            self.browser.NotifyMoveOrResizeStarted()

    def on_mainframe_configure(self, width, height):
        if self.browser:
            if WINDOWS:
                ctypes.windll.user32.SetWindowPos(self.browser.GetWindowHandle(), 0, 0, 0, width, height, 0x0002)
            elif LINUX:
                self.browser.SetBounds(0, 0, width, height)
            self.browser.NotifyMoveOrResizeStarted()

    def on_focus_in(self, _):
        if self.browser:
            self.browser.SetFocus(True)

    def on_focus_out(self, _):
        if LINUX and self.browser:
            self.browser.SetFocus(False)

    def on_configure(self, _):
        if not self.browser:
            self.embed_browser()

    def set_javascript_bindings(self):
        bindings = cef.JavascriptBindings(bindToFrames=False, bindToPopups=False)
        bindings.SetFunction('loadDataset', self.master.js_load_dataset)
        bindings.SetFunction('saveDataset', self.master.js_save_dataset)
        bindings.SetFunction('discardDataset', self.master.js_discard_dataset)
        self.browser.SetJavascriptBindings(bindings)

class CubicInterpolationEditCurvePage(BasePage):

    def __init__(self, parent, controller):

        BasePage.__init__(self, parent, controller)
        self.channel = False
        self.values = None
        self.datapoints = []

        self.browser_frame = None

        # self.protocol("WM_DELETE_WINDOW", self.on_close)
        self.bind("<Configure>", self.on_root_configure)
        self.top.bind("<Configure>", self.on_configure)
        self.top.bind("<FocusIn>", self.on_focus_in)
        self.top.bind("<FocusOut>", self.on_focus_out)

        # BrowserFrame
        self.browser_frame = BrowserFrame(self)
        self.browser_frame.pack(in_=self.top, side=tkinter.BOTTOM, expand=True, fill=tkinter.BOTH)

        from app.CubicInterpolationPage import CubicInterpolationPage
        self.parent = self.controller.frames[CubicInterpolationPage]

    def on_root_configure(self, _):
        if self.browser_frame:
            self.browser_frame.on_root_configure()

    def on_configure(self, event):
        print(event)
        if self.browser_frame:
            width = event.width
            height = event.height
            self.browser_frame.on_mainframe_configure(width, height)

    def on_focus_in(self, _):
        print("MainFrame.on_focus_in")

    def on_focus_out(self, _):
        print("MainFrame.on_focus_out")

    def on_close(self):
        if self.browser_frame:
            self.browser_frame.on_root_close()
        self.master.destroy()

    def get_browser(self):
        if self.browser_frame:
            return self.browser_frame.browser
        return None

    def get_browser_frame(self):
        if self.browser_frame:
            return self.browser_frame
        return None

    def js_load_dataset(self, callback):
        callback.Call(self.channel, self.datapoints)

    def js_discard_dataset(self):
        from app.CubicInterpolationPage import CubicInterpolationPage
        self.parent.set_button_state(False)
        self.controller.show_frame(CubicInterpolationPage)

    def js_save_dataset(self, channel, datapoints):
        if self.channel==channel:
            n = 0
            for p in datapoints:
                self.values[n].set(self.parent.join(p['x'], p['y']))
                n += 1
            while n < len(self.values):
                self.values[n].set(self.parent.join(0, 0))
                n += 1
        else:
            self.logger.error('channel mismatch %d!=%d' % (self.channel, channel))

        from app.CubicInterpolationPage import CubicInterpolationPage
        self.parent.set_button_state(False)
        self.controller.show_frame(CubicInterpolationPage)

    def init_chart(self, channel, values):
        self.channel = channel + 1
        self.values = values
        self.datapoints = []
        prev_x = -1
        for value in values:
            tmp = self.parent.split(value.get());
            x = tmp[0]
            y = tmp[1]
            if x<=prev_x:
                break
            prev_x = x
            self.datapoints.append({'x': x, 'y': y})
        self.title.configure(text='Cubic Interpolation')
        self.browser_frame.browser.ExecuteFunction('initChart')
