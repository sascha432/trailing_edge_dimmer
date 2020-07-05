#!/usr/bin/python3
#
# Author: sascha_lammers@gmx.de
#

# pip install websocket-client
# pip install cefpython3==66.0

from lib.dimmer_const import DimmerConst
import logging
import sys
from app.MainApp import MainApp
from cefpython3 import cefpython as cef
from lib.dimmer_connection import BaseConnection

default_handler = logging.StreamHandler(stream=sys.stdout)
default_handler.setLevel(logging.DEBUG)
logger = logging.getLogger('dimmer_fw_tool')
logger.setLevel(logging.DEBUG)
logger.addHandler(default_handler)

app = MainApp(logger, DimmerConst())
app.mainloop()
cef.Shutdown()