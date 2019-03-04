import can
from can import Message
from canInterface.CanBus import CanBus # not sure if this is necessary

class GpsCanInterface(can.Listener):
    """
    A GpsCanInterface is a subclass of Listener which handles
    a message whenever a message is received. Particularly, it will
    handle messages it identifies as coming from the GPS
    """

    # don't know yet if we need to specify an id for each type of message, or just the device itself
    _arbitration_ids = {
        'gps_position_detailed': None,
        'gps_position_abbreviated': None,
        'gps_speed_and_direction': None,
    }

    def __init__(self, bus):
        # not much to do here
        self.bus = bus

    def on_message_received(self, msg):
        # Parse Message
        print("GPS interface message received: " + msg.__str__())
        
        if msg.arbitration_id == self._arbitration_ids['gps_position_detailed']:
            self.process_gps_position_detailed(msg)
        elif msg.arbitration_id == self._arbitration_ids['gps_position_abbreviated']:
            self.process_gps_position_abbreviated(msg)
        elif msg.arbitration_id == self._arbitration_ids['gps_speed_and_direction']:
            self.process_gps_speed_and_direction(msg)
        else :
            print("No appropriate gps message handler found for message: " + msg.__str__())
        

    def process_gps_position_detailed(self,msg):
        print("processing gps position detailed")
        # TODO: Implement this
        pass

    def process_gps_position_abbreviated(self,msg):
        print("processing gps position abbreviated")
        result = {}

        # Parse data
        # latitude is the first 32 bits
        latitude_bytes = msg.data[:4]
        # convert to a number
        latitude = int.from_bytes(latitude_bytes, byteorder='big', signed=True)
        # multiply by 0.0000001
        latitude = latitude * 0.0000001
        # check that value is between -90 and 90
        assert -90 <= latitude <= 90

        # longitude is the last 32 bits
        longitude_bytes = msg.data[4:]
        # convert to a number
        longitude = int.from_bytes(longitude_bytes, byteorder='big', signed=True)
        # multiply by 0.0000001
        longitude = longitude * 0.0000001
        # check that value is between -180 and 180
        assert -180 <= longitude <= 180

        result.latitude = latitude
        result.longitude = longitude
        print("latitude = " + latitude)
        print("longitude = " + longitude)
        self.bus.gps_position_abbreviated = result

    def process_gps_speed_and_direction(self,msg):
        print("processing gps speed and direction")
        # TODO: Implement this
        pass