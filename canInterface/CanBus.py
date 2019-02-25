import can
import os
import datetime
import time
import threading
from can import Message

class CanBus: 
    
    _bus = None
    _mainListener = None
    _notifier = None

    # global variables
    bms_soc = None
    bms_temps = None
    gps_position_detailed = None # GNSSPositionData
    gps_position_abbreviated = None # GNSSPositionRapidUpdates
    gps_speed_and_direction = None # NMEACogSogData

    # don't know yet if we need to specify an id for each type of message, or just the device itself
    arbitration_ids = {
        'gps_position_detailed': None,
        'gps_position_abbreviated': None,
        'gps_speed_and_direction': None,
        'bms': None,
    }

    _error_buffer = []

    def __init__(self):
        # Initialize the CAN interface
        os.system('sudo /sbin/ip link set can0 up type can bitrate 500000')

        _interface = 'socketcan_native'
        _channel = 'can0' 
        _bitrate = 500000

        # Setup the initialize the bus
        global _bus
        _bus = can.interface.Bus(bustype=_interface, channel=_channel)

        # initialize the main listener
        global _mainListener
        #_mainListener = can.BufferedReader()
        _mainListener = MessageListener(self)

        # initialize the file logger
        ## universal time in UTC
        ts=time.time()
        currentTime = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d_%H:%M:%S')
        fileLogger = can.Printer("logs_" + currentTime + ".txt")

        listenersList = [_mainListener, fileLogger]

        # initialize the notifier
        global _notifier
        _notifier = can.Notifier(_bus, listenersList)

        
    def get_new_errors(self):
        new_error_list = list(self._error_buffer)
        self._error_buffer.clear()
        return new_error_list

    def send_message(self, arbitration_id=0, data=None, is_extended_id=False):
        message = Message(arbitration_id=arbitration_id,is_extended_id=is_extended_id,data=data)

        global _bus
        _bus.send(message)


class MessageListener(can.Listener):
    """
    A MessageListener is a subclass of Listener which handles
    a message whenever a message is received
    """

    def __init__(self, bus):
        # not much to do here
        self.bus = bus
        pass

    def on_message_received(self, msg):
        # Parse Message
        print("Message received: " + msg.__str__())
        
        if msg.arbitration_id == self.bus.arbitration_ids['gps_position_detailed']:
            self.process_gps_position_detailed(msg)
        elif msg.arbitration_id == self.bus.arbitration_ids['gps_position_abbreviated']:
            self.process_gps_position_abbreviated(msg)
        elif msg.arbitration_id == self.bus.arbitration_ids['gps_speed_and_direction']:
            self.process_gps_speed_and_direction(msg)
        else :
            print("No appropriate message handler found for message: " + msg.__str__())
        

    def process_gps_position_detailed(self,msg):
        print("processing gps position detailed")
        pass

    def process_gps_position_abbreviated(self,msg):
        print("processing gps position abbreviated")
        result = {}

        # Parse data
        # latitude is the first 32 bits
        latitude = msg.data[:5]
        # convert to a number
        # multiply by 0.0000001
        # check that value is between -90 and 90

        # longitude is the last 32 bits
        longitude = msg.data[5:]
        # convert to a number
        # multiply by 0.0000001
        # check that value is between -180 and 180

        result.latitude = latitude
        result.longitude = longitude
        self.bus.gps_position_abbreviated = result

    def process_gps_speed_and_direction(self,msg):
        print("processing gps speed and direction")
        pass