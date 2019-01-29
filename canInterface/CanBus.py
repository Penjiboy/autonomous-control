import can

class CanBus: 
    
    __bus

    def __init__(self):
        # Gotta check that these config settings actually work for our setup
        _interface = 'pcan' ### Still need to figure out the most appropriate can interface
        _channel = 'vcan0' 
        _bitrate = 500000

        __bus = can.interface.Bus(bustype=_interface, channel=_channel, bitrate=_bitrate)