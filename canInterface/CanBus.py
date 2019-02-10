import can
import os
import datetime
import time

class CanBus: 
    
    _bus
    _mainListener
    _notifier

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
        
