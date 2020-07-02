#
# Author: sascha_lammers@gmx.de
#

import tkinter
import threading
import serial
import re
import time
import json
import struct

class DimmerConnection:

    def __init__(self, consts):
        self.connected = False
        self.connection_details = 'Not connected';
        self.serial = None
        self.callbacks = []
        self.consts = consts
        self.console = None
        self.read_thread = None
        self.addresses = [ 0x17, 0x18 ]
        self.line = ''
        self.response_handlers = []
        self.controller = None

    def set_controller(self, controller):
        self.controller = controller

    def set_slave_address(self, address):
        self.set_addresses(address, self.addresses[1])

    def set_master_address(self, address):
        self.set_addresses(self.addresses[0], address)

    def set_addresses(self, slave, master):
        def parse_address(value):
            if isinstance(value, int):
                return value
            str = value.strip()
            m = re.match('^[0-9]+$', str)
            if m:
                return int(str)
            m = re.match('^(0x|x)?([0-9a-f]+)$', str, re.IGNORECASE)
            if m:
                return int(m[2], 16)
            raise ValueError('invalid address: %s' % str)
        self.addresses = [ parse_address(slave), parse_address(master) ]

    def set_console(self, console):
        self.console = console

    def get_status(self):
        return self.connection_details

    def reset_mcu(self):
        self.response_handlers = []
        self.line = ''
        try:
            self.console.write('============ TOGGLING DTR/RTS ============\n')
            self.serial.reset_input_buffer()
            self.serial.reset_output_buffer()
            self.serial.dtr = not self.serial.dtr
            self.serial.rts = not self.serial.rts
            time.sleep(0.1)
            self.serial.dtr = not self.serial.dtr
            self.serial.rts = not self.serial.rts
        except:
            pass

    def open_serial(self, port, baud_rate):
        self.close()
        baud_rate = int(baud_rate)
        self.line = ''
        self.response_handlers = []
        try:
            print("%s @ %u" % (port, baud_rate))
            self.serial = serial.Serial(baudrate=baud_rate, timeout=.001)
            self.serial.rts = False
            self.serial.dtr = False
            self.serial.port = port
            self.serial.open()

            self.connected = True
            self.update_status('%s@%u' % (port, baud_rate))

            self.read_thread = threading.Thread(target = self.read_thread_function)
            self.read_thread.daemon = True
            self.read_thread.start()

            return self.serial.is_open

        except IOError as e:
            self.connected = False
            self.update_status('Failed to open %s' % (port))

        return False


    def close(self):
        if self.connected:
            self.connected = False
            self.update_status('Connection closed')
        try:
            if self.serial:
                self.serial.close()
        except:
            pass
        try:
            self.read_thread.join(0.1)
        except:
            pass
        self.read_thread = None
        self.serial = None

    def response_callback(self, address, data, response):
        values = struct.unpack(response[1], data)
        output = response[0] % values
        self.console.write('RESPONSE %s\n' % output);

    def add_response_handler(self, address, length, response, callback = None):
        self.response_handlers.append((address, length, response, callback));

    def parse_i2c_to_master(self, address, data):
        event = self.consts.get_by_value(data[0])
        # print(address,data,event,len(data))
        try:
            event = event.replace('MASTER_COMMAND_', '')
            if event=='METRICS_REPORT':
                values = self.consts.unpack_struct(self.consts.register_mem_metrics_t, data[1:])
                self.controller.update_metrics(values)
            elif event=='TEMPERATURE_ALERT':
                values = self.consts.unpack_struct(self.consts.dimmer_temperature_alert_t, data[1:])
            elif event=='FADING_COMPLETE':
                values = self.consts.unpack_struct(self.consts.dimmer_temperature_alert_t, data[1:])
            else:
                raise RuntimeError()
            for key, val in values.items():
                if isinstance(val, float):
                    values[key] = '%.6f' % val
            values = json.dumps(values)
        except Exception as e:
            print(e)
            event = "EVENT 0x%02x, length %u" % (data[0], len(data) - 1)
            values = []
            for val in list(data[1:]):
                values.append(str(val))
            values = ', '.join(values)

        print(address, event, values)

        self.console.write("I2C 0x%02x: %s: %s\n" % (address, event, values))

    def parse_i2c_command(self, line):
        line.strip();
        m = re.match('^\+(i2c[rt])=(([0-9a-z]{2}(,?))+)', line, re.IGNORECASE)
        if m:
            type = m[1].lower()
            data = bytes.fromhex(m[2].replace(',', ''))
            address = data[0]
            data = data[1:]
            if type=='i2ct':
                if address==self.addresses[1]:
                    self.parse_i2c_to_master(address, data)

                if self.response_handlers:
                    handler = self.response_handlers[0]
                    # print(address, data, handler)
                    if handler[0] == address and handler[1] == len(data):
                        if handler[3]:
                            handler[3](address, data, handler[2])
                        else:
                            self.response_callback(address, data, handler[2])
                        # remove
                        self.response_handlers = self.response_handlers[1:]

    def read_thread_function(self):
        while self.serial:
            try:
                data = self.serial.read(8192)
            except OSError as e:
                return
            except Exception as e:
                print(type(e), e)

            if data:
                str = data.decode('cp1252');
                while len(str):
                    pos = str.find('\n')
                    if pos!=-1:
                        self.console.write(str[0:pos + 1])
                        self.parse_i2c_command(self.line + str[0:pos])
                        self.line = ''
                        str = str[pos + 1:]
                    else:
                        self.line = self.line + str
                        self.console.write(str)
                        break

    def update_status(self, text):
        self.connection_details = text
        for callback in self.callbacks:
            callback(self.get_status(), self.connected)

    def bind(self, callback):
        self.callbacks.append(callback)
        callback(self.get_status(), self.connected)

    def unbind(self, callback):
        del self.callbacks[callback]

    def send_command(self, request, response = None, callback = None):

        delay = 0
        parts = []
        request_str = ''
        for item in request:
            if isinstance(item, float):
                delay = delay + item
                continue
            elif isinstance(item, int):
                value = item
            elif item=='SLAVE_ADDRESS' or item=='ADDRESS':
                value = self.addresses[0]
            elif item=='MASTER_ADDRESS':
                value = self.addresses[1]
            else:
                value = self.consts.get(item)
                if value==0:
                    raise RuntimeError('%s not found' % item)

            # print('%s=%x (%u)' % (item, value, value))

            parts.append('%02x' % value)

        try:
            request_str = '+I2CT=%s\n' % (''.join(parts))
            print('sending %s' % request_str.strip())
            self.console.write("SENDING: %s" % request_str)
            self.serial.write(request_str.encode('cp1252'))
            self.serial.flush()

            if response:
                if delay:
                    time.sleep(delay)

                if isinstance(response, int):
                    length = response
                elif isinstance(response[1], int):
                    length = response[1]
                else:
                    length = struct.calcsize(response[1])

                self.add_response_handler(self.addresses[0], length, response, callback)

                request_str = '+I2CR=%02x%02x\n' % (self.addresses[0], length)
                print('sending %s' % request_str.strip())
                self.console.write("SENDING: %s" % request_str)
                self.serial.write(request_str.encode('cp1252'))
                self.serial.flush()

        except Exception as e:
            print(e)