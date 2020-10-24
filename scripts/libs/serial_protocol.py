#
#  Author: sascha_lammers@gmx.de
#

import re
import time
import struct

class Protocol:

    def __init__(self, serial, address, master_address=None):
        if address==None:
            address = 0x17
        if master_address==None:
            master_address = address + 1
        self.serial = serial
        self.structs = None
        self.address = address
        self.master_address = master_address
        self.display_rx = False

    def readline(self):
        repeat = True
        while repeat:
            while True:
                line = self.serial.readline().decode(errors='replace').strip('\r\n')
                if line!='':
                    break
            self.raw_line = line
            if line.lower().startswith('+rem='):
                err = 'comment'
                repeat = False
            else:
                err = 'unknown data'
                regexp = '^([0-9]+) (.*)'
                m = re.match(regexp, line, re.IGNORECASE)
                if m:
                    err = 'DEBUG'
                    line = '%011.3f: %s' % (int(m[1]) / 1000.0, m[2])
                else:
                    repeat = False
                    regexp = '^\+i2c([tr])=([0-9a-f]+)'
                    m = re.match(regexp, line, re.IGNORECASE)
                    if m:
                        type = m[1].upper()
                        try:
                            data = bytearray.fromhex(m[2])
                            addr = int(data[0])
                            if type=='T':
                                if addr!=self.address and addr!=self.master_address:
                                    raise ValueError('transmission from invalid address 0x%02x' % addr)
                            if type=='R':
                                raise ValueError('request from slave')
                            return data[1:]
                        except ValueError as e:
                            err = str(e)
                        except Exception as e:
                            err = 'invalid data: ' + str(e)

            if self.display_rx:# and err!='unknown data':
                print('RX %s: %s' % (err, line))
        return line

    def read_request(self, length, timeout=None):
        if timeout==None:
            timeout = self.serial.timeout
        end = time.monotonic() + timeout
        while time.monotonic()<end:
            line = self.readline()
            if isinstance(line, str):
                if line.startswith('+REM=BOOT'):
                    return None
            elif isinstance(line, bytearray):
                if len(line)==length:
                    return line
            else:
              raise Exception('invalid response')
        return False

    def print_data(self, data):
        try:
            if len(data):
                if isinstance(data, bytearray):
                    if data[0]==0xf0:
                        metrics = self.structs.dimmer_metrics_t.from_buffer_copy(data[1:])
                        print('Metrics: temp=%u°C VCC=%umV frequency=%.3fHz ntc=%.2f°C int=%.2f°C' % (metrics.temp_check_value, metrics.vcc, metrics.frequency, metrics.ntc_temp, metrics.internal_temp))
                        return 0xf0
                    if data[0]==0xf1:
                        event = self.structs.dimmer_over_temperature_event_t.from_buffer_copy(data[1:])
                        print('OVER TEMPERATURE: temp=%u°C max=%u°C' % (event.current_temp, event.max_temp))
                        return 0xf1
                    if data[0]==0xf3:
                        event = self.structs.dimmer_eeprom_written_t.from_buffer_copy(data[1:])
                        print('EEPROM written: cycle=%u position=%u written=%u' % (event.write_cycle, event.write_position, event.bytes_written))
                        return 0xf3
        except Exception as e:
            print('Invalid data: %s: %s' % (e, self.raw_line))
            return None

        print('Raw data: %s' % self.raw_line)
        return False

    def write(self, info, line):
        print('%s: %s' % (info, line))
        self.serial.write((line + '\n').encode());

    def transmit(self, data):
        self.write('TX %d bytes to 0x%02x' % (len(data) / 2, self.address), '+I2CT=%02x%s' % (self.address, data))

    def receive(self, length):
        self.write('RQ %d bytes from 0x%02x' % (length, self.address), '+I2CR=%02x%02x' % (self.address, length))

    def get_version(self):
        self.transmit('8a02b9')
        self.receive(2)
        return 2

    def print_config(self):
        self.transmit('8991')

    def store_config(self):
        self.write_eeprom(True)

    def write_eeprom(self, config = False):
        if config:
            self.transmit('899392')
        else:
            self.transmit('8993')

    def measure_frequency(self):
        self.transmit('8994')

    def reset_factory_settings(self):
        self.transmit('8951')
