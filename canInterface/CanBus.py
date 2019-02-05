import can
import os

class CanBus: 
    
    _bus

    def __init__(self):
        # Initialize the CAN interface
        os.system('sudo /sbin/ip link set can0 up type can bitrate 500000')

        # Gotta check that these config settings actually work for our setup
        _interface = 'socketcan_native' ### Still need to figure out the most appropriate can interface
        _channel = 'can0' 
        _bitrate = 500000

        global _bus
        _bus = can.interface.Bus(bustype=_interface, channel=_channel)
