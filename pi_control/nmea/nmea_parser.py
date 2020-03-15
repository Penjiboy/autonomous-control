# imports
import math


# a packet is a can message, I would be given the number of
# bytes and I should take the upper ceil

class NMEAFrame:
    """
        Class that represents a message exceeding 8 bytes sent through the CANBUS.
        A frame represents the message.
        A packet is the data bytes in a CAN message (Could be 8 bytes or less).
    """
    # size of frame in terms of packets
    num_packets = 0
    # size of frame in terms of bytes
    num_bytes = 0
    # a byte array containing the complete message
    frame = []
    # flag for the state of the frame
    flag = 0

    # Assuming:
    # 1. byte_size is greater than 8
    # 2. the packets are given in an array of bytes (numbers)
    # 3. Packets only contain data (i.e 29 bits of identification are not included)
    def __init__(self, byte_size, initial_packet=[]):
        self.num_packets = math.ceil(byte_size / 8.0)
        self.num_bytes = byte_size
        if initial_packet:
            self.parse_packet(initial_packet)

    # Given an array of bytes called a packet. Add these bytes to the main frame
    def parse_packet(self, packet):
        for i in range(0, len(packet)):
            self.frame.append(packet[i])
        return self.check_end_of_frame()

    # Flag indicates if frame is valid
    def get_frame(self):
        return self.flag, self.frame

    def check_end_of_frame(self):
        if len(self.frame) < self.num_bytes:
            self.flag = 0
        elif len(self.frame) == self.num_bytes:
            self.flag = 1
        else:
            raise ValueError("Error, more bytes received than expected")
            self.flag = -1
        return self.flag


packet = [20, 15, 200, 150, 14, 44, 66, 77]
Frame = NMEAFrame(16, packet)
print("bytes: ", Frame.num_bytes)
print("packets: ", Frame.num_packets)
Frame.parse_packet(packet)
print(Frame.get_frame())
# Frame.parse_packet(packet)
# print(Frame.get_frame())
