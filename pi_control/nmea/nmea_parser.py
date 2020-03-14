# imports


class NMEAFrame:
    frame_size = 0
    frame = ''

    def __init__(self, frame_size, initial_packet=""):
        self.frame_size = frame_size
        if initial_packet != "":
            self.parse_packet(initial_packet)

    def parse_packet(self, packet):
        self.check_end_of_frame()

    def parse_multi_packets(self, packets, num_packets):
        self.check_end_of_frame()

    def check_end_of_frame(self):
        if len(self.frame) < self.frame_size:
            return 0
        elif len(self.frame) == self.frame_size:
            return 1
        else:
            print("Error, more packets received than expected")
            return 0