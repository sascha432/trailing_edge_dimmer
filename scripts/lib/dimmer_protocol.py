# AUTO GENERATED FILE - DO NOT MODIFY
#
# Author: sascha_lammers@gmx.de
#

class DimmerProtocol(object):
    def __init__(self):
        self.register_mem_info_t = {
            '__SIZE': 6,
            'version': 'H',
            'num_levels': 'h',
            'num_channels': 'b',
            'options': 'B',
        }
        self.register_mem_command_t = {
            '__SIZE': 2,
            'command': 'B',
            'read_length': 'b',
        }
        self.register_mem_t = {
            '__SIZE': 87,
            'points': { 
                'x': 'B',
                'y': 'B',
                'x': 'B',
                'y': 'B',
                'x': 'B',
                'y': 'B',
                'x': 'B',
                'y': 'B',
                'x': 'B',
                'y': 'B',
                'x': 'B',
                'y': 'B',
                'x': 'B',
                'y': 'B',
                'x': 'B',
                'y': 'B',
             },
            'frequency': 'f',
            'temperature': 'f',
            'temperature2': 'f',
            'vcc': 'H',
            'from_level': 'h',
            'time': 'f',
            'channel': 'b',
            'to_level': 'h',
            'command': 'B',
            'read_length': 'b',
            'options': 'B',
            'max_temperature': 'B',
            'fade_time': 'f',
            'temp_check_interval': 'B',
            'metrics_report_interval': 'B',
            'zc_offset_ticks': 'h',
            'min_on_ticks': 'H',
            'min_off_ticks': 'H',
            'vref11': 'f',
            'temperature_offset': 'b',
            'temperature2_offset': 'b',
            'level': [ 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h',  ],
            'zc_misfire': 'B',
            'temperature': 'B',
            'i2c_errors': 'B',
            'version': 'H',
            'num_levels': 'h',
            'num_channels': 'b',
            'options': 'B',
            'address': 'B',
        }
        self.register_mem_metrics_t = {
            '__SIZE': 14,
            'frequency': 'f',
            'temperature': 'f',
            'temperature2': 'f',
            'vcc': 'H',
        }
        self.dimmer_temperature_alert_t = {
            '__SIZE': 2,
            'current_temperature': 'B',
            'max_temperature': 'B',
        }
        self.constants =         {
            "I2C_ADDRESS": 23,
            "I2C_MASTER_ADDRESS": 24,
            "REGISTER_MEM_START_OFFSET": 0,
            "REGISTER_CUBIC_INT_DATA_POINTS_OFFSET": 0,
            "REGISTER_METRICS_FREQUENCY": 16,
            "REGISTER_METRICS_TEMPERATURE": 20,
            "REGISTER_METRICS_TEMPERATURE2": 24,
            "REGISTER_METRICS_VCC": 28,
            "REGISTER_CHANNEL_FROM_LEVEL": 30,
            "REGISTER_CHANNEL_TIME": 32,
            "REGISTER_CHANNEL_CHANNEL": 36,
            "REGISTER_CHANNEL_TO_LEVEL": 37,
            "REGISTER_CMD_COMMAND": 39,
            "REGISTER_CMD_READ_LENGTH": 40,
            "REGISTER_OPTIONS": 41,
            "REGISTER_CFG_MAX_TEMPERATURE": 42,
            "REGISTER_CFG_FADE_TIME": 43,
            "REGISTER_CFG_TEMP_CHECK_INTERVAL": 47,
            "REGISTER_CFG_METRICS_REPORT_INTERVAL": 48,
            "REGISTER_CFG_ZC_OFFSET_TICKS": 49,
            "REGISTER_CFG_MIN_ON_TICKS": 51,
            "REGISTER_CFG_MIN_OFF_TICKS": 53,
            "REGISTER_CFG_VREF11": 55,
            "REGISTER_CFG_TEMPERATURE_OFFSET": 59,
            "REGISTER_CFG_TEMPERATURE2_OFFSET": 60,
            "REGISTER_ERRORS_ZC_MISFIRE": 77,
            "REGISTER_ERRORS_TEMPERATURE": 78,
            "REGISTER_ERRORS_I2C_ERRORS": 79,
            "REGISTER_INFO_VERSION": 80,
            "REGISTER_INFO_NUM_LEVELS": 82,
            "REGISTER_INFO_NUM_CHANNELS": 84,
            "REGISTER_INFO_OPTIONS": 85,
            "REGISTER_ADDRESS": 86,
            "REGISTER_MEM_SIZE": 87,
            "REGISTER_COMMAND": "DIMMER_REGISTER_CMD_COMMAND",
            "OPTIONS_FACTORY_SETTINGS": 1,
            "OPTIONS_CUBIC_INTERPOLATION": 2,
            "OPTIONS_REPORT_METRICS": 4,
            "OPTIONS_RESTORE_LEVEL": 8,
            "OPTIONS_INFO_HAS_CUBIC_INTERPOLATION": 1,
            "OPTIONS_INFO_HAS_TEMPERATURE": 2,
            "OPTIONS_INFO_HAS_TEMPERATURE2": 4,
            "OPTIONS_INFO_HAS_VCC": 8,
            "OPTIONS_INFO_HAS_FADING_COMPLETED_EVENT": 16,
            "COMMAND_SET_LEVEL": 16,
            "COMMAND_FADE": 17,
            "COMMAND_READ_CHANNELS": 18,
            "COMMAND_READ_TEMPERATURE": 32,
            "COMMAND_READ_TEMPERATURE2": 33,
            "COMMAND_READ_VCC": 34,
            "COMMAND_READ_FREQUENCY": 35,
            "COMMAND_READ_METRICS": 36,
            "COMMAND_WRITE_SETTINGS": 80,
            "COMMAND_RESTORE_FACTORY": 81,
            "COMMAND_PRINT_INFO": 83,
            "COMMAND_FORCE_TEMP_CHECK": 84,
            "COMMAND_PRINT_METRICS": 85,
            "COMMAND_PRINT_CUBIC_INT": 96,
            "COMMAND_GET_CUBIC_INT": 97,
            "COMMAND_READ_CUBIC_INT": 98,
            "COMMAND_WRITE_CUBIC_INT": 99,
            "COMMAND_CUBIC_INT_TEST_PERF": 100,
            "COMMAND_SET_ZC_OFS": 146,
            "COMMAND_WRITE_EEPROM": 147,
            "MASTER_COMMAND_METRICS_REPORT": 240,
            "MASTER_COMMAND_TEMPERATURE_ALERT": 241,
            "MASTER_COMMAND_FADING_COMPLETE": 242,
            "CUBIC_INT_DATA_POINTS": 8
        }
        self.I2C_ADDRESS = 23
        self.I2C_MASTER_ADDRESS = 24
        self.REGISTER_MEM_START_OFFSET = 0
        self.REGISTER_CUBIC_INT_DATA_POINTS_OFFSET = 0
        self.REGISTER_METRICS_FREQUENCY = 16
        self.REGISTER_METRICS_TEMPERATURE = 20
        self.REGISTER_METRICS_TEMPERATURE2 = 24
        self.REGISTER_METRICS_VCC = 28
        self.REGISTER_CHANNEL_FROM_LEVEL = 30
        self.REGISTER_CHANNEL_TIME = 32
        self.REGISTER_CHANNEL_CHANNEL = 36
        self.REGISTER_CHANNEL_TO_LEVEL = 37
        self.REGISTER_CMD_COMMAND = 39
        self.REGISTER_CMD_READ_LENGTH = 40
        self.REGISTER_OPTIONS = 41
        self.REGISTER_CFG_MAX_TEMPERATURE = 42
        self.REGISTER_CFG_FADE_TIME = 43
        self.REGISTER_CFG_TEMP_CHECK_INTERVAL = 47
        self.REGISTER_CFG_METRICS_REPORT_INTERVAL = 48
        self.REGISTER_CFG_ZC_OFFSET_TICKS = 49
        self.REGISTER_CFG_MIN_ON_TICKS = 51
        self.REGISTER_CFG_MIN_OFF_TICKS = 53
        self.REGISTER_CFG_VREF11 = 55
        self.REGISTER_CFG_TEMPERATURE_OFFSET = 59
        self.REGISTER_CFG_TEMPERATURE2_OFFSET = 60
        self.REGISTER_ERRORS_ZC_MISFIRE = 77
        self.REGISTER_ERRORS_TEMPERATURE = 78
        self.REGISTER_ERRORS_I2C_ERRORS = 79
        self.REGISTER_INFO_VERSION = 80
        self.REGISTER_INFO_NUM_LEVELS = 82
        self.REGISTER_INFO_NUM_CHANNELS = 84
        self.REGISTER_INFO_OPTIONS = 85
        self.REGISTER_ADDRESS = 86
        self.REGISTER_MEM_SIZE = 87
        self.OPTIONS_FACTORY_SETTINGS = 1
        self.OPTIONS_CUBIC_INTERPOLATION = 2
        self.OPTIONS_REPORT_METRICS = 4
        self.OPTIONS_RESTORE_LEVEL = 8
        self.OPTIONS_INFO_HAS_CUBIC_INTERPOLATION = 1
        self.OPTIONS_INFO_HAS_TEMPERATURE = 2
        self.OPTIONS_INFO_HAS_TEMPERATURE2 = 4
        self.OPTIONS_INFO_HAS_VCC = 8
        self.OPTIONS_INFO_HAS_FADING_COMPLETED_EVENT = 16
        self.COMMAND_SET_LEVEL = 16
        self.COMMAND_FADE = 17
        self.COMMAND_READ_CHANNELS = 18
        self.COMMAND_READ_TEMPERATURE = 32
        self.COMMAND_READ_TEMPERATURE2 = 33
        self.COMMAND_READ_VCC = 34
        self.COMMAND_READ_FREQUENCY = 35
        self.COMMAND_READ_METRICS = 36
        self.COMMAND_WRITE_SETTINGS = 80
        self.COMMAND_RESTORE_FACTORY = 81
        self.COMMAND_PRINT_INFO = 83
        self.COMMAND_FORCE_TEMP_CHECK = 84
        self.COMMAND_PRINT_METRICS = 85
        self.COMMAND_PRINT_CUBIC_INT = 96
        self.COMMAND_GET_CUBIC_INT = 97
        self.COMMAND_READ_CUBIC_INT = 98
        self.COMMAND_WRITE_CUBIC_INT = 99
        self.COMMAND_CUBIC_INT_TEST_PERF = 100
        self.COMMAND_SET_ZC_OFS = 146
        self.COMMAND_WRITE_EEPROM = 147
        self.MASTER_COMMAND_METRICS_REPORT = 240
        self.MASTER_COMMAND_TEMPERATURE_ALERT = 241
        self.MASTER_COMMAND_FADING_COMPLETE = 242
        self.CUBIC_INT_DATA_POINTS = 8
        self.ADDRESS = self.I2C_ADDRESS
        self.constants['ADDRESS'] = self.I2C_ADDRESS
        self.REGISTER_COMMAND = self.REGISTER_CMD_COMMAND
        self.constants['REGISTER_COMMAND'] = self.REGISTER_CMD_COMMAND
        
