#
#  Author: sascha_lammers@gmx.de
#

from . import fw_const

class DimmerConst(fw_const.DimmerConstBase):
    def __init__(self):
        fw_const.DimmerConstBase.__init__(self)
        self.VERSION = '2.1.x'
        self.attr = {
            'I2C_ADDRESS': 0x17,
            'I2C_MASTER_ADDRESS': 0x18,
            'REGISTER_START_ADDR': 0x80
        }
