import can
from can import Message
from BmsCanInterface import BmsCanInterface
from VescCanInterface import VescCanInterface

class VescControl:
#TODO: requst data from BMS module, if values are within a certain range, control the ESC accordingly

#request from BMS:
#newest event on the bus
#battery pack voltage
#battery pack current
#device temp
