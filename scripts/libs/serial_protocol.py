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
        self.address = address
        self.master_address = master_address

    def readline(self):
        while True:
            line = self.serial.readline()
            line = line.decode().strip('\r\n')
            self.raw_line = line
            if line!='':
                break

        if line.lower().startswith('+rem='):
            err = 'comment'
        else:
            err = 'unknown data'
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

        print('Received %s: %s' % (err, line))
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
                        fmt = 'BBHfff'
                        (t, temp, vcc, frequency, ntc_temp, internal_temp, ) = struct.unpack(fmt, data)
                        print('Metrics: temp=%u°C VCC=%umV frequency=%.3fHz ntc=%.2f°C int=%.2f°C' % (temp, vcc, frequency, ntc_temp, internal_temp))
                        return 0xf0
                    if data[0]==0xf1:
                        fmt = 'BBB'
                        (t, temp, max_temp, ) = struct.unpack(fmt, data)
                        print('OVER TEMPERATURE: temp=%u°C max=%u°C' % (temp, max_temp))
                        return 0xf1
                    if data[0]==0xf3:
                        fmt = '<BIHB'
                        (t, cycle, pos, written) = struct.unpack(fmt, data)
                        print('EEPROM written: cycle=%u position=%u written=%u' % (cycle, pos, written))
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
        self.write('Transmitting %d bytes to 0x%02x' % (len(data) / 2, self.address), '+I2CT=%02x%s' % (self.address, data))

    def receive(self, length):
        self.write('Requesting %d bytes from 0x%02x' % (length, self.address), '+I2CR=%02x%02x' % (self.address, length))

    def get_version(self):
        self.transmit('8a02b9')
        self.receive(2)
        return 2

    def get_config(self):
        self.transmit('8991')

    def store_config(self):
        self.transmit('8992')
