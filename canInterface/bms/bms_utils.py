import can
import os

from can import Message
from common import CanBus

class BmsCanInterface(can.Listener):
    """
    A BmsCanInterface is a subclass of Listener which handles
    a message whenever a message is received. Particularly, it will
    handle messages it identifies as coming from the BMS
    """

    # don't know yet if we need to specify an id for each type of message, or just the device itself
    _arbitration_ids = {
        'battery_pack_voltage': None,
        'request_identifier': '01000000001',
        'response_identifier': '01001000001'
    }

    request_unique_ids = {
        'newest_events': '\x11',
        'all_events': '\x12',
        'battery_pack_voltage': '\x14',
        'battery_pack_current': '\x15',
        'battery_pack_max_cell_voltage': '\x16',
        'battery_pack_min_cell_voltage': '\x17',
        'online_status': '\x18',
        'lifetime_counter': '\x19',
        'estimated_SOC_value': '\x1a',
        'device_temperatures': '\x1b',
        'battery_pack_cells_voltages': '\x1c',
        'version': '\x1e',
        'calculated_speed__left_distance__estimated_time': '\x20',
    }

    def __init__(self, bus):
        # not much to do here
        self.bus = bus

    def on_message_received(self, msg):
        # Parse Message
        #print("BMS interface message received: " + msg.__str__())

        if msg.arbitration_id == self._arbitration_ids['response_identifier']:
            self.parse_response(msg.data)
        else : 
            #print("No appropriate bms message handler found for message: " + msg.__str__())
            pass

    def parse_response(self, data):
        print("message received being parsed by bms handler")
        if data[1] == self.request_unique_ids['newest_events']:
            self.read_newest_events(data)


    def read_newest_events(self, data):
        if data[0] == '\x00':
            print("error reading newest events")
            return
        
        print("read newest events: " + data.__str__())

    def read_battery_pack_voltage(self, data):
        if data[0] == '\x00':
            print("error reading battery pack voltage")
            return

        voltage = int.from_bytes(data[2:], byteorder='big', signed=True)
        self.bus.bms_battery_voltage = voltage
        print("battery pack voltage = " + voltage)
        return data[2:]

    def send_request(self, data, arbitration_id=_arbitration_ids['request_identifier']):
        message = Message(arbitration_id=arbitration_id, is_extended_id=False, data=data)
        self.bus._bus.send(message)

    def send_generic_request(self, unique_id):
        request_data = self.generic_request_data(unique_id)
        message = Message(arbitration_id=self._arbitration_ids['request_identifier'], is_extended_id=False, data=request_data)
        self.bus._bus.send(message)

    def generic_request_data(self, unique_id):
        return bytearray(unique_id + '\x00\x00\x00\x00\x00\x00\x00')

        