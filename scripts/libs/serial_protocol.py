#
#  Author: sascha_lammers@gmx.de
#

import re
import time
import struct

class ProtocolError(Exception):
    def __init__(self, msg = None):
        Exception.__init__(self, msg)

class TimeoutError(ProtocolError):
    def __init__(self, msg = 'Serial timeout'):
        ProtocolError.__init__(self, msg)

class ResponseError(ProtocolError):
    def __init__(self, msg = 'Invalid response'):
        ProtocolError.__init__(self, msg)

class RebootError(ProtocolError):
    def __init__(self, msg = 'Reboot detected'):
        ProtocolError.__init__(self, msg)

class AddressError(ProtocolError):
    def __init__(self, msg = 'Address error'):
        ProtocolError.__init__(self, msg)

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
        self.raw_line = b''
        self.last_event = None
        self.last_address = None

    def readline(self):
        self.raw_line = b''
        self.last_event = None
        self.last_address = None
        repeat = True
        while repeat:
            while True:
                line = self.serial.readline().decode(errors='replace').strip('\r\n')
                if line!='':
                    break
            self.raw_line = line
            # print(self.raw_line)
            if line.lower().startswith('+rem='):
                err = 'comment'
                repeat = False
                self.last_event = 'comment'
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
                            self.last_address = addr
                            self.last_event = None
                            if type=='T':
                                if addr!=self.address and addr!=self.master_address:
                                    raise AddressError('transmission from invalid address 0x%02x' % addr)
                                if addr==self.master_address:
                                    self.last_event = int(data[1])
                            if type=='R':
                                raise ProtocolError('request from slave')
                            return data[1:]
                        except ValueError as e:
                            err = str(e)
                        except Exception as e:
                            err = 'invalid data: ' + str(e)

            if self.display_rx:# and err!='unknown data':
                print('RX %s: %s' % (err, line))
        return line

    def read_request(self, length=None, event=None, regex=None, timeout=None):
        if timeout==None:
            timeout = self.serial.timeout
        if (length or event) and regex:
            raise Exception('length or event cannot be combined with regex')

        end = time.monotonic() + timeout
        while time.monotonic()<end:
            line = self.readline()
            match = 0
            count = 0
            if isinstance(line, str):
                if regex!= None and re.match(regex, line, re.IGNORECASE):
                    return line
                if line.lower().startswith('+rem=boot'):
                    raise RebootError()
            elif isinstance(line, bytearray):
                if length!=None:
                    count += 1
                    l = len(line)
                    if (isinstance(length, list) and l in length) or l==length:
                        match += 1
                if event!=None:
                    count += 1
                    if self.last_event==event:
                        match += 1
                if count>0 and count==match:
                    return line
            else:
              raise ResponseError()
        raise TimeoutError()

    def print_data(self, data):
        try:
            if len(data):
                if isinstance(data, bytearray):
                    if data[0]==self.DIMMER.EVENT.METRICS_REPORT:
                        metrics = self.structs.dimmer_metrics_t.from_buffer_copy(data[1:])
                        print('Metrics: %s' % (metrics))
                        return data[0]
                    if data[0]==self.DIMMER.EVENT.TEMPERATURE_ALERT:
                        event = self.structs.dimmer_over_temperature_event_t.from_buffer_copy(data[1:])
                        print('OVER TEMPERATURE: %s' % (event))
                        return data[0]
                    if data[0]==self.DIMMER.EVENT.FADING_COMPLETE:
                        print('FADING COMPLETE EVENT: %s' % (self.raw_line))
                        return data[0]
                    if data[0]==self.DIMMER.EVENT.CHANNEL_ON_OFF:
                        parts = []
                        for i in range(0, 9):
                            if data[1]&(1<<i):
                                parts.append('channel %u = on' % i)
                        if parts:
                            tmp = ', '.join(parts)
                        else:
                            tmp = 'all channels off'
                        print('CHANNEL EVENT: %s' % tmp)
                        return data[0]
                    if data[0]==self.DIMMER.EVENT.EEPROM_WRITTEN:
                        event = self.structs.dimmer_eeprom_written_t.from_buffer_copy(data[1:])
                        print('EEPROM written: %s' % (event))
                        return data[0]
                    if data[0]==self.DIMMER.EVENT.SYNC_EVENT:
                        event = self.structs.dimmer_sync_event_t.from_buffer_copy(data[1:])
                        print('SYNC EVENT: %s' % event)
                        return data[0]
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

    def send_config(self, cfg):
        data = cfg.get_command().encode()
        print("Sending configuration: ", data)
        self.serial.write(data + b'\n')

    def wait_for_eeprom(self):
        return self.read_request(event = self.DIMMER.EVENT.EEPROM_WRITTEN)

    def store_config(self):
        print("Sending write EEPROM command...")
        self.write_eeprom(True)

    def get_version(self):
        self.transmit('8a02b9')
        self.receive(7)
        return [2, 7]

    def print_config(self):
        self.transmit('8991')

    def write_eeprom(self, config = False):
        if config:
            self.transmit('899392')
        else:
            self.transmit('8993')

    def measure_frequency(self):
        self.transmit('8994')

    def reset_factory_settings(self):
        self.transmit('8951')
