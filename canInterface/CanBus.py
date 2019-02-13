import can
import os
import datetime
import time
import threading

class CanBus: 
    
    _bus = None
    _mainListener = None
    _notifier = None

    # global variables
    bms_soc = None
    bms_temps = None
    gps_position = None
    gps_heading = None

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
        _mainListener = can.BufferedReader()

        # initialize the file logger
        ## universal time in UTC
        ts=time.time()
        currentTime = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d_%H:%M:%S')
        fileLogger = can.Printer("logs_" + currentTime + ".txt")

        listenersList = [_mainListener, fileLogger]

        # initialize the notifier
        global _notifier
        _notifier = can.Notifier(_bus, listenersList)

        # Not sure if this is necessary with notifier
        #listener_thread = threading.Thread(target=self._listener_loop)

    def get_new_errors(self):
        new_error_list = list(self._error_buffer)
        self._error_buffer.clear()
        return new_error_list

    def send_message(self):
        # TODO
        pass

    # def _listener_loop(self):
    #     while True:
    #         #listen for messages


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

        # Act on Message


        
