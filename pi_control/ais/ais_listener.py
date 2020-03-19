import can
from can import Message
#from canInterface.CanBus import CanBus # not sure if this is necessary
from common.can_bus import CanBus # not sure if this is necessary

class AisCanInterface(can.Listener):
    """
    A AisCanInterface is a subclass of Listener which handles
    a message whenever a message is received. Particularly, it will
    handle messages it identifies as coming from the AIS
    """

    # don't know yet if we need to specify an id for each type of message, or just the device itself
    _arbitration_ids = {

    }

    def __init__(self, bus):
        # not much to do here
        self.bus = bus