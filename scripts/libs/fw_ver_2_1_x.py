#
#  Author: sascha_lammers@gmx.de
#

from ctypes import *

class config_options_t(Structure):
    _pack_ = 1
    _fields_ = [("restore_level", c_uint8, 1),
                ("report_metrics", c_uint8, 1),
                ("temperature_alert", c_uint8, 1),
                ("frequency_low", c_uint8, 1),
                ("frequency_high", c_uint8, 1),
                ("___reserved", c_uint8, 3)]

class config_options_t_union(Union):
    _pack_ = 1
    _fields_ = [("byte", c_uint8),
                ("bits", config_options_t)]


class register_mem_cfg_t(Structure):
    _pack_ = 1
    _fields_ = [("options", c_uint8),
                ("max_temp", c_uint8),
                ("fade_in_time", c_float),
                ("temp_check_interval", c_uint8),
                ("linear_correction_factor", c_float),
                ("halfwave_adjust_ticks", c_int8),
                ("zero_crossing_delay_ticks", c_uint8),
                ("minimum_on_time_ticks", c_uint16),
                ("minimum_off_time_ticks", c_uint16),
                ("internal_1_1v_ref", c_float),
                ("int_temp_offset", c_int8),
                ("int8_t ntc_temp_offset", c_int8),
                ("report_metrics_max_interval", c_uint8)]

class dimmer_metrics_t(Structure):
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
                ("bytes_written", c_uint8)]

