import can
from can import Message
import CanBus

class BmsCanInterface(can.Listener):
    """
    A BmsCanInterface is a subclass of Listener which handles
    a message whenever a message is received. Particularly, it will
    handle messages it identifies as coming from the BMS
    """

    # don't know yet if we need to specify an id for each type of message, or just the device itself
    _arbitration_ids = {
        'battery_pack_voltage': None,
    }

    def __init__(self, bus):
        # not much to do here
        self.bus = bus

    def on_message_received(self, msg):
        # Parse Message
        print("BMS interface message received: " + msg.__str__())

        if msg.arbitration_id == self._arbitration_ids['battery_pack_voltage']:
            self.read_battery_pack_voltage(msg)
        else : 
            print("No appropriate bms message handler found for message: " + msg.__str__())

    def read_battery_pack_voltage(self, msg):
        voltage_bytes = msg.data[2:]
        voltage = int.from_bytes(voltage_bytes, byteorder='little', signed=True)
        print("bms battery voltage = " + voltage)
        self.bus.bms_battery_voltage = voltage

    def send_request(self, arbitration_id, data):
        message = Message(arbitration_id=arbitration_id, is_extended_id=False, data=data)
        self.bus.send(message)

        