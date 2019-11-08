import can
from can import Message
import CanBus

class VescCanInterface(can.Listener):
    """
    A VescCanInterface is a subclass of Listener which handles
    a message whenever a message is received. Particularly, it will
    handle messages it identifies as coming from the VESC
    """

    node_ids = {
        'SET_DUTY': 0,
        'SET_CURRENT': 1,
        'SET_CURRENT_BRAKE': 2,
        'SET_RPM': 3,
        'SET_POS': 4,
        'FILL_RX_BUFFER': 5,
        'FILL_RX_BUFFER_LONG': 6,
        'PROCESS_RX_BUFFER': 7,
        'PROCESS_SHORT_BUFFER': 8,
        'STATUS': 9,
        'SET_CURRENT_REL': 10,
        'SET_CURRENT_REL_BRAKE': 11,
    }

    def __init__(self, bus):
        self.bus = bus

    def on_message_received(self, msg):
        return super().on_message_received(msg)

    def send_message(self, id, data=None):
        request_data = data if data is not None else bytearray('\x00\x00\x00\x00\x00\x00\x00\x00')
        message = Message(arbitration_id=id, is_extended_id=True, data=request_data)
        self.bus._bus.send(message)