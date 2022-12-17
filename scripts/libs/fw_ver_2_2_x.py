#
#  Author: sascha_lammers@gmx.de
#

from ctypes import *
from . import floats

class c_internal_vref11(floats.c_int8_ShiftedFloat):
    def __init__(self):
        floats.ShiftedFloat.__init__(self, 0x3f8ccccd, 12, 6)
    __init_subclass__ = floats.c_int8_ShiftedFloat.__init_subclass__

class c_vcc_t(floats.c_int8_ShiftedFloat):
    def __init__(self):
        floats.ShiftedFloat.__init__(self, 0x40880000, 16, 2)
    __init_subclass__ = floats.c_int8_ShiftedFloat.__init_subclass__

class c_temperature_t(floats.c_int16_FixedPointFloat):
    def __init__(self):
        floats.FixedPointFloat.__init__(self, 60000, 300, 3)
    __init_subclass__ = floats.c_int16_FixedPointFloat.__init_subclass__

class c_temp_ofs_t(floats.c_int8_FixedPointFloat):
    def __init__(self):
        floats.FixedPointFloat.__init__(self, 4, 1, 2)
    __init_subclass__ = floats.c_int8_FixedPointFloat.__init_subclass__

class dimmer_timers_t(Structure):
    _pack_ = 1
    _fields_ = [("timer1_ticks_per_us", c_float)]

class dimmer_version_t(Structure):
    _pack_ = 1
    _fields_ = [("revision", c_uint16, 5),
                ("minor", c_uint16, 5),
                ("major", c_uint16, 5),
                ("___reserved", c_uint16, 1)]

    def __repr__(self):
        return '%u.%u.%u' % (self.major, self.minor, self.revision)

class dimmer_config_info_t(Structure):
    _pack_ = 1
    _fields_ = [("max_levels", c_uint16),
                ("channel_count", c_uint8),
                ("cfg_start_address", c_uint8),
                ("length", c_uint8)]

    def __repr__(self):
        return {
            'max_levels': self.max_levels,
            'channel_count': self.channel_count,
            'cfg_start_address': self.cfg_start_address,
            'length': self.length,
        }

class dimmer_version_info_t(Structure):
    _pack_ = 1
    _fields_ = [("version", dimmer_version_t),
                ("info", dimmer_config_info_t)]

    def __repr__(self):
        return {
            'version': self.version,
            'info': self.info,
        }

class c_internal_temp_calibration_t(Structure):
    _pack_ = 1
    _fields_ = [("ts_offset", c_uint8),
                ("ts_gain", c_uint8)]

    def __repr__(self):
        return {"ts_offset": self.ts_offset, "ts_gain": self.ts_gain}

class config_options_t(Structure):
    _pack_ = 1
    _fields_ = [("restore_level", c_uint8, 1),
                ("leading_edge", c_uint8, 1),
                ("over_temperature_alert_triggered", c_uint8, 1),
                ("negative_zc_delay", c_uint8, 1),
                ("___reserved", c_uint8, 4)]

    def __repr__(self):
        return {
            "restore_level": self.restore_level,
            "leading_edge": self.leading_edge,
            "over_temperature_alert_triggered": self.over_temperature_alert_triggered,
            "negative_zc_delay": self.negative_zc_delay,
        }

class config_options_t_union(Union):
    _pack_ = 1
    _fields_ = [("byte", c_uint8),
                ("bits", config_options_t)]

    def __getattribute__(self, key):
        if key=='options':
            return Union.__getattribute__(self, 'byte')
        elif key in('bits', 'byte'):
            return Union.__getattribute__(self, key)
        else:
            bits = Union.__getattribute__(self, 'bits')
            return Structure.__getattribute__(bits, key)

    def __setattr__(self, key, val):
        if key=='options':
            return Union.__setattr__(self, 'byte', val)
        elif key in('bits', 'byte'):
            return Union.__getattribute__(self, key, val)
        else:
            bits = Union.__getattribute__(self, 'bits')
            return Structure.__getattribute__(bits, key, val)

    # def __repr__(self):
    #     bits = Union.__getattribute__(self, 'bits')
    #     return {
    #         "restore_level": bits.restore_level,
    #         "leading_edge": bits.leading_edge,
    #         "over_temperature_alert_triggered": bits.over_temperature_alert_triggered,
    #         "negative_zc_delay": bits.negative_zc_delay,
    #     }

class register_mem_cfg_t(Structure):
    _pack_ = 1
    _fields_ = [("options", config_options_t_union),
                ("max_temp", c_uint8),
                ("fade_in_time", c_float),
                ("zero_crossing_delay_ticks", c_uint16),
                ("minimum_on_time_ticks", c_uint16),
                ("minimum_off_time_ticks", c_uint16),
                ("range_begin", c_uint16),
                ("range_divider", c_uint16),
                ("internal_vref11", c_internal_vref11),
                ("internal_temp_calibration", c_internal_temp_calibration_t),
                ("ntc_temp_cal_offset", c_temp_ofs_t),
                ("report_metrics_max_interval", c_uint8)]

    def __dir__(self):
        parts = []
        for name, c_type in self._fields_:
            parts.append(name)
        parts.append('range_end')
        return parts

    def __getattribute__(self, key):
        if key=='range_end':
            return self.__get_range_end()
        return Structure.__getattribute__(self, key)

    def __setattr__(self, key, val):
        if key=='range_end':
            self.__set_range_end(val)
        else:
            Structure.__setattr__(self, key, val)

    def __get_range_end(self):
        range_divider = Structure.__getattribute__(self, 'range_divider')
        if range_divider==0:
            return self.max_level
        return int((self.max_level * self.max_level) / (range_divider - Structure.__getattribute__(self, 'range_begin')))

    def __set_range_end(self, range_end):
        range_begin = self.__getattribute__('range_begin')
        if range_end==0:
            range_begin = 0
            range_divider = 0
        elif range_end==self.max_level:
            if range_begin==0:
                range_divider = 0
            else:
                range_divider = range_begin
        else:
            range_divider = int(self.max_level * self.max_level / range_end + range_begin);
        Structure.__setattr__(self, 'range_begin', range_begin)
        Structure.__setattr__(self, 'range_divider', range_divider)

class dimmer_metrics_t(Structure):
    _pack_ = 1
    _fields_ = [("temp_check_value", c_uint8),
                ("vcc", c_uint16),
                ("frequency", c_float),
                ("ntc_temp", c_float),
                ("internal_temp", c_int16)]

    def __str__(self):
        return 'temp=%u°C VCC=%umV frequency=%.3fHz ntc=%.2f°C int=%d°C' % (self.temp_check_value, self.vcc, self.frequency, self.ntc_temp, self.internal_temp)

class dimmer_over_temperature_event_t(Structure):
    _pack_ = 1
    _fields_ = [("current_temp", c_uint8),
                ("max_temp", c_uint8)]

    def __str__(self):
        return 'temp=%u°C max=%u°C' % (self.current_temp, self.max_temp)

class dimmer_eeprom_written_t(Structure):
    _pack_ = 1
    _fields_ = [("write_cycle", c_uint32),
                ("write_position", c_uint16),
                ("bytes_written", c_uint8),
                ("config_updated", c_uint8, 1),
                ("__reserved", c_uint8, 7)]

    def __str__(self):
        return 'EEPROM written: cycle=%u position=%u written=%u config_updated=%u' % (self.write_cycle, self.write_position, self.bytes_written, self.config_updated)

class dimmer_sync_event_t(Structure):
    _pack_ = 1
    _fields_ = [("invalid signals", c_uint16),
                ("halfwave_counter", c_uint16)]

    def __str__(self):
        global DIMMER
        if self.type==DIMMER.SYNC_EVENT_TYPE_.LOST:
            return 'type=LOST half cycles=%u' % (self.halfwave_counter)
        elif self.type==DIMMER.SYNC_EVENT_TYPE_.SYNC:
            return 'type=SYNC difference=%u' % (self.sync_difference_cycles)
        return 'type=UNKNOWN'
