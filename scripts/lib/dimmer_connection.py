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
import websocket
import _thread

class TimerCallback(object):
    def __init__(self):
        self.stop = False
        self.thread = None
        self.callback = None
        self.timeout = 0

    def kill(self):
        if self.thread:
            self.stop = True
            self.thread.join(0.1)
            self.thread = None

    def run(self):
        end = time.time() + self.timeout
        while time.time()<end:
            if self.stop:
                return
            time.sleep(0.01)
        self.callback()
        self.stop = True

    def is_running(self):
        return not self.stop

    def setTimeout(self, timeout, callback):
        self.kill()
        self.stop = False
        self.timeout = timeout
        self.callback = callback
        self.thread = threading.Thread(target=self.run)
        self.thread.daemon = True
        self.thread.start()

class BaseConnection(object):

    def create_connection(controller, console, logger, connection):
        if connection['name'].startswith('ws://'):
            return DimmerWebsocketConnection(connection['name'], connection['username'], connection['password'], controller, console, logger)
        else:
            port = BaseConnection.valid_com_port(connection['name'])
            if port:
                return DimmerSerialConnection(port, connection['baudrate'], controller, console, logger)
        raise RuntimeError('Connection not supported: %s' % connection['name'])

    def valid_com_port(connection):
        try:
            m = re.search('(^serial://|^)(/dev/[a-z0-9/]+|COM[0-9]+)(: )?', connection, re.IGNORECASE)
            if m!=None:
                return m[2]
        except Exception as e:
            return False

    def __init__(self, controller, console, logger):
        self.controller = controller
        self.connected = False
        self.connection_details = '%s'
        self.error = None
        self.console = console
        self.logger = logger
        self.on_open_callback = None
        self.on_close_callback = None

    def set_controller(self, controller):
        self.controller = controller

    def set_console(self, console):
        self.console = console

    def set_logger(self, logger):
        self.logger = logger

    def get_status(self):
        if self.error:
            return self.connection_details % self.error
        if self.connected:
            return self.connection_details % 'connected'
        return self.connection_details % 'disconnected'

    def on_receive(self, data):
        self.console.write(data)

    def on_message(self, message):
        pass

    def on_error(self, error):
        self.connected = False
        self.on_open_callback = None
        self.on_close_callback = None
        self.logger.error(error)
        self.controller.on_error(self, error)

    def on_close(self):
        self.connected = False
        if self.on_close_callback:
            tmp = self.on_close_callback
            self.on_close_callback = None
            tmp()
        self.controller.on_close(self)

    def on_open(self):
        if self.on_open_callback:
            tmp = self.on_open_callback
            self.on_open_callback = None
            tmp()
        self.connected = True
        self.controller.on_open(self)

    def open(self):
        if self.connected:
            self.on_close_callback = self.real_connect
            self.close()
        else:
            self.real_connect()

    def real_connect(self):
        self.on_open()

    def close(self):
        self.on_close()

    def send_message(self, message):
        pass


class DimmerConnection(BaseConnection):
    def __init__(self, controller, console, logger, consts=None, slave_address=0x17, master_address=None):
        BaseConnection.__init__(self, controller, console, logger)

        self.consts = consts
        self.slave_address = self.parse_address(slave_address)
        if master_address:
            self.master_address = self.parse_address(master_address)
        else:
            self.master_address = self.slave_address + 1
        self.response_handlers = []
        self.version = None
        self.info = None
        self.timer = TimerCallback()

    def set_consts(self, consts):
        self.consts = consts

    def parse_address(self, value):
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

    def set_slave_address(self, address):
        self.slave_address = self.parse_address(address)

    def set_master_address(self, address):
        self.master_address = self.parse_address(address)

    def response_callback(self, address, data, response):
        values = struct.unpack(response[1], data)
        output = response[0] % values
        self.console.write('I2C response from=0x%02x: %s\n' % (address, output));

    def add_response_handler(self, address, length, response, callback = None):
        self.response_handlers.append((address, length, response, callback));

    def parse_i2c_to_master(self, address, data):
        _event = self.consts.get_by_value(data[0])
        self.logger.debug('I2C master address=0x%02x length=%u data=%s' % (address, len(data), data.hex()))
        if not self.version:
            self.logger.error('I2C skipping master event, version not determined')
            return
        try:
            event = _event.replace('MASTER_COMMAND_', '')
            if event=='METRICS_REPORT':
                values = self.consts.unpack_struct(self.consts.register_mem_metrics_t, data[1:])
                self.controller.on_update_metrics(self, values)
            elif event=='TEMPERATURE_ALERT':
                values = self.consts.unpack_struct(self.consts.dimmer_temperature_alert_t, data[1:])
            elif event=='FADING_COMPLETE':
                values = self.consts.unpack_struct(self.consts.dimmer_temperature_alert_t, data[1:])
            else:
                self.logger.error('I2C unknown master event: id=%u event=%s data=%s' % (int(data[0]), str(event), data.hex()))
                raise RuntimeError()
            for key, val in values.items():
                if isinstance(val, float):
                    values[key] = '%.3f' % val
            values = json.dumps(values)
        except RuntimeError as e:
            self.logger.error('I2C master error: %s: address=0x%02x data=%s' % (e, address, data.hex()))
            event = "EVENT 0x%02x, length %u" % (data[0], len(data) - 1)
            values = []
            for val in list(data[1:]):
                values.append(str(val))
            values = ', '.join(values)

        self.console.write("I2C master transmit=0x%02x event=%s: %s\n" % (address, event, values))

    def uint16_to_version(self, value):
        return (value >> 10, (value >> 5) & 0x1f, value & 0x1f)

    def set_version(self, data):
        try:
            values = struct.unpack('H', data)
            if values[0]==0xffff:
                self.version = None
                self.logger.debug('I2C version: 0xffff')
            else:
                self.version = self.uint16_to_version(values[0])
                self.logger.debug('I2C version %u.%u.%u' % (self.version))
        except Exception as e:
            self.logger.error('I2C failed to parse version: %s: data=%s' % (e, data.hex()))
            self.version = None
        else:
            self.console.write('Version %u.%u.%u detected\n' % (self.version))
            if self.version[0] == 3:
                self.retries = 0
                self.timer.setTimeout(0.5, self.request_info)
            else:
                self.console.write_hb('VERSION NOT SUPPORTED')

    # version 2.x
    def version_callback(self, address, data, response):
        self.set_version(data)
        if self.version:
            self.controller.on_version_info(self, self.version)
        else:
            self.retries += 1
            if self.retries<5:
                self.timer.setTimeout(3, self.request_version)

    # version >=3.x
    def info_callback(self, address, data, response):
        try:
            info = self.consts.unpack_struct(self.consts.register_mem_info_t, data)
            version = self.uint16_to_version(info['version'])
            self.info = {
                'version': '%u.%u.%u' % version,
                'num_levels': info['num_levels'],
                'num_channels': info['num_channels'],
                'options': info['options'],
            }
            self.logger.debug('I2C info %s' % str(self.info))
        except Exception as e:
            raise e
            self.on_error('I2C error parsing firmware information: %s' % e)
        else:
            if self.version!=version:
                self.logger.error('version mismatch: %s!=%s' % (('%u.%u.%u' % self.version), ('%u.%u.%u' % version)))
            self.controller.on_update_info(self, self.info)

    def request_info(self):
        self.console.write('Requesting info...%s\n' % (self.retries and (' Retry#' % self.retries) or ''))
        size = self.consts.register_mem_info_t['__SIZE']
        self.send_command([self.slave_address, self.consts.REGISTER_CMD_READ_LENGTH, size, self.consts.REGISTER_INFO_VERSION], size, self.info_callback)

    def request_version(self):
        self.console.write('Requesting version...%s\n' % (self.retries and (' Retry#' % self.retries) or ''))
        # version 2.x
        self.send_command(['ADDRESS', 0x8a, 2, 0xb9], 2, self.version_callback)

    def on_error(self, error):
        self.timer.kill()
        BaseConnection.on_error(self, error)

    def on_close(self):
        self.timer.kill()
        BaseConnection.on_close(self)

    def on_open(self):
        self.version = None
        self.info = None
        self.logger.debug('I2C slave=0x%02x master=0x%02x' % (self.slave_address, self.master_address))
        self.response_handlers = []
        self.retries = 0
        self.timer.setTimeout(0.5, self.request_version)
        BaseConnection.on_open(self)

    def on_message(self, line):
        line.strip();
        m = re.match('^\+(rem)=(.*)', line, re.IGNORECASE)
        if m:
            pass
        else:
            m = re.match('^\+(i2c[rt])=(([0-9a-z]{2}(,?))+)', line, re.IGNORECASE)
            if m:
                type = m[1].lower()
                data = bytes.fromhex(m[2].replace(',', ''))
                address = data[0]
                data = data[1:]
                if type=='i2ct':
                    if address==self.master_address:
                        self.parse_i2c_to_master(address, data)

                    if self.response_handlers:
                        handler = self.response_handlers[0]
                        if handler[0] == address and handler[1] == len(data):
                            if handler[3]:
                                self.console.write('I2C response from=0x%02x: %s\n' % (address, data.hex()));
                                handler[3](address, data, handler[2])
                            else:
                                self.response_callback(address, data, handler[2])
                            # remove
                            self.response_handlers = self.response_handlers[1:]
                        else:
                            self.logger.debug('I2C ignoring address=0x%02x data=%s' % (address, data.hex()))

    def send_command(self, request, response=None, callback=None):
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
                value = self.slave_address
            elif item=='MASTER_ADDRESS':
                value = self.master_address
            else:
                value = self.consts.get(item)
                if value==0:
                    self.logger.error('I2C cannot resolve name: %s' % item)
                    raise RuntimeError('%s not found' % item)

            # print('%s=%x (%u)' % (item, value, value))
            parts.append('%02x' % value)

        try:
            request_str = '+I2CT=%s\n' % (''.join(parts))
            self.logger.debug('I2C transmit: data %s' % request_str.strip())
            self.console.write("Transmitting: %s" % request_str)
            self.send_message(request_str.encode('cp1252'))

            if response:
                if delay:
                    time.sleep(delay)

                if isinstance(response, int):
                    length = response
                elif isinstance(response[1], int):
                    length = response[1]
                else:
                    length = struct.calcsize(response[1])

                self.add_response_handler(self.slave_address, length, response, callback)

                request_str = '+I2CR=%02x%02x\n' % (self.slave_address, length)
                self.logger.debug('I2C request: %s' % request_str.strip())
                self.console.write("Requesting: %s" % request_str)
                self.send_message(request_str.encode('cp1252'))

        except Exception as e:
            self.logger.error('I2C send command failed: %s' % e)

    def reset_mcu(self):
        pass


class DimmerSerialConnection(DimmerConnection):

    def __init__(self, port, baudrate, controller, console, logger):

        DimmerConnection.__init__(self, controller, console, logger)

        self.connection_details = '%s@%u: %%s' % (port, baudrate)
        self.port = port
        if baudrate:
            self.baudrate = baudrate
        else:
            self.baudrate = 57600

        self.serial = None
        self.callbacks = []
        self.read_thread = None
        self.line = ''

    def reset_mcu(self):
        self.response_handlers = []
        self.line = ''
        try:
            self.console.write_hb('TOGGLING DTR/RTS')
            self.serial.reset_input_buffer()
            self.serial.reset_output_buffer()
            self.serial.dtr = not self.serial.dtr
            self.serial.rts = not self.serial.rts
            time.sleep(0.1)
            self.serial.dtr = not self.serial.dtr
            self.serial.rts = not self.serial.rts
        except:
            pass

    def real_connect(self):
        self.connected = False
        self.line = ''
        try:
            self.logger.debug('open %s @ %u' % (self.port, self.baudrate))
            self.serial = serial.Serial(baudrate=self.baudrate, timeout=.001)
            self.serial.rts = False
            self.serial.dtr = False
            self.serial.port = self.port
            self.serial.open()

            self.read_thread = threading.Thread(target = self.read_thread_function)
            self.read_thread.daemon = True
            self.read_thread.start()

            if self.serial.is_open:
                self.connected = True
                self.on_open()
            else:
                raise IOError('port %s is closed' % port)

        except IOError as e:
            self.on_error('Failed to open port: %s: %s' % (port, e))

    def close(self):
        if self.connected:
            self.connected = False
        self._close()
        DimmerConnection.close(self)

    def _close(self):
        if self.serial:
            tmp = self.serial
            if self.read_thread:
                self.serial = None
                try:
                    self.read_thread.join(0.1)
                except:
                    pass
                self.read_thread = None
            try:
                tmp.serial.close()
            except:
                pass
        elif self.read_thread:
            raise RuntimeError('read_thread set but serial null')

    def on_error(self, error):
        self._close()
        DimmerConnection.on_error(self, error)

    def send_message(self, message):
        try:
            self.serial.write(message)
            self.serial.flush()
        except Exception as e:
            self.on_error('Write error: %s' % e)

    def read_thread_function(self):
        while self.serial:
            try:
                data = self.serial.read(8192)
            except OSError as e:
                self.on_error('Read error: %s' % e)
                return
            except Exception as e:
                self.on_error('Read error: %s' % e)
                raise e

            data_str = data.decode('cp1252');
            if data_str:
                self.on_receive(data_str)
                while len(data_str):
                    pos = data_str.find('\n')
                    if pos!=-1:
                        self.on_message(self.line + data_str[0:pos])
                        self.line = ''
                        data_str = data_str[pos + 1:]
                    else:
                        self.line += data_str
                        break


class DimmerWebsocketConnection(DimmerConnection):

    def __init__(self, url, username, password, controller, console, logger):

        DimmerConnection.__init__(self, controller, console, logger)

        self.connection_details = '%s@%s %%s' % (username, url)
        self.url = url
        self.username = username
        self.password = password
        self.web_socket = None
        self.auth = False

    def on_message(self, data):
        if isinstance(data, str):
            for message in data.split('\n'):
                message = message.rstrip()
                if message:
                    self.logger.debug('WebSocket message: auth=%u: %s' % (self.auth, message))
                    if not self.auth:
                        if message=='+AUTH_OK':
                            self.logger.debug('WebSocket authentication successful')
                            self.console.write('Authentication successful\n')
                            self.auth = True
                            DimmerConnection.on_open(self)
                        elif message == "+AUTH_ERROR":
                            self.on_error('Authentication failed')
                        elif message == "+REQ_AUTH":
                            self.logger.debug('WebSocket sending authentication: %s' % self.password)
                            self.console.write('Sending authentication\n')
                            self.send_message('+SID %s' % self.password)
                    else:
                        if message.startswith('+ATMODE_CMDS_HTTP2SERIAL='):
                            pass
                        elif message.startswith("+CLIENT_ID="):
                            self.client_id = message[11:]
                            self.logger.debug('WebSocket ClientID: %s' % self.client_id)
                        else:
                            self.on_receive(message + '\n')
                            DimmerConnection.on_message(self, message)

    def on_error(self, error):
        self.close()
        DimmerConnection.on_error(self)

    def send_message(self, message):
        try:
            self.web_socket.send(message)
        except Exception as e:
            self.on_error('Write error: %s' % e)

    def open(self):
        if self.web_socket:
            try:
                self.web_socket.close()
            except:
                pass
        self.connected = False
        self.auth = False
        self.web_socket = websocket.WebSocketApp(self.url,
            on_message = self.on_message,
            on_error = self.on_error,
            on_close = self.on_close,
            on_open = self.on_open)

        def run(*args):
            self.web_socket.run_forever()
        _thread.start_new_thread(run, ())

    def on_open(self):
        self.connected = True

    def on_close(self):
        if self.connected:
            DimmerConnection.on_close(self)
        self.connected = False

    def close(self):
        if self.web_socket:
            try:
                self.web_socket.close()
            except:
                pass
            self.web_socket = None
        DimmerConnection.close(self)
