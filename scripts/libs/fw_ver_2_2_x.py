#
#  Author: sascha_lammers@gmx.de
#

from ctypes import *
from . import floats

class c_internal_vref11(floats.c_int8_ShiftedFloat):
    def __init__(self):
        floats.ShiftedFloat.__init__(self, 0x3f8ccccd, 12, 6)
        # floats.c_int8_ShiftedFloat._self_ = self
    __init_subclass__ = floats.c_int8_ShiftedFloat.__init_subclass__


class c_temp_ofs_t(floats.c_int8_FixedPointFloat):
    def __init__(self):
        floats.FixedPointFloat.__init__(self, 4, 1, 2)
    __init_subclass__ = floats.c_int8_FixedPointFloat.__init_subclass__


class config_options_t(Structure):
    _pack_ = 1
    _fields_ = [("restore_level", c_uint8, 1),
                ("leading_edge", c_uint8, 1),
                ("over_temperature_alert_triggered", c_uint8, 1),
                ("___reserved", c_uint8, 5)]

class config_options_t_union(Union):
    _pack_ = 1
    _fields_ = [("byte", c_uint8),
                ("bits", config_options_t)]

class register_mem_cfg_t(Structure):
    _pack_ = 1
    _fields_ = [("options", c_uint8),
                ("max_temp", c_uint8),
                ("fade_in_time", c_float),
                ("zero_crossing_delay_ticks", c_uint16),
                ("minimum_on_time_ticks", c_uint16),
                ("minimum_off_time_ticks", c_uint16),
                ("range_begin", c_int16),
                ("range_end", c_int16),
                ("internal_vref11", c_internal_vref11),
                ("int_temp_offset", c_temp_ofs_t),
                ("ntc_temp_offset", c_temp_ofs_t),
                ("report_metrics_max_interval", c_uint8),
                ("halfwave_adjust_ticks", c_int8),
                ("switch_on_minimum_ticks", c_uint16),
                ("switch_on_count", c_uint8)]

class dimmer_metrics_t(Structure):
    _pack_ = 1
    _fields_ = [("temp_check_value", c_uint8),
                ("vcc", c_uint16),
                ("frequency", c_float),
                ("ntc_temp", c_float),
                ("internal_temp", c_float)]

class dimmer_over_temperature_event_t(Structure):
    _pack_ = 1
    _fields_ = [("current_temp", c_uint8),
                ("max_temp", c_uint8)]

class dimmer_eeprom_written_t(Structure):
    _pack_ = 1
    _fields_ = [("write_cycle", c_uint32),
                ("write_position", c_uint16),
                ("bytes_written", c_uint8),
                ("config_updated", c_uint8, 1),
                ("__reserved", c_uint8, 7)]
