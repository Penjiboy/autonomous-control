import can
from can import Message
from common.can_bus import CanBus

class BmsUtility():

    def __init__(self, message_bus):
        """
        Parameters
        ----------
        message_bus : interface
            The can interface
        """
        self.bus = message_bus
    
    def sendMessage(self, message, message_bus):
        self.bus.send(message)
        return True
        