# Import Python core modules
import can
import os
import datetime
import time
import threading
from can import Message

from gps.gps_listener import GpsCanInterface
from gps.gps_utils import GpsUtility
from bms.bms_listener import BmsCanInterface
from bms.bms_utils import BmsUtility
from vesc.vesc_listener import VescCanInterface
from vesc.vesc_util import VescUtility
from ais.ais_listener import AisCanInterface
from ais.ais_util import AisUtility

class CanBus: 
    
    _bus = None
    _main_listener = None
    _gps_interface = None
    _bms_interface = None
    _vesc_interface = None
    _file_logger = None
    _notifier = None

    _bms_util =  None
    _ais_util =  None
    _gos_util =  None
    _vesc_util =  None

    # global variables
    bms_soc = None
    bms_temps = None
    bms_battery_voltage = None
    gps_position_detailed = None # GNSSPositionData
    gps_position_abbreviated = None # GNSSPositionRapidUpdates
    gps_speed_and_direction = None # NMEACogSogData

    _error_buffer = []

    def __init__(self):
        # Initialize the CAN interface
        os.system('sudo /sbin/ip link set can0 down type can')
        os.system('sudo /sbin/ip link set can0 up type can bitrate 500000')

        _interface = 'socketcan_native'
        _channel = 'can0' 
        _bitrate = 500000

        # Setup the initialize the bus
        self._bus = can.interface.Bus(bustype=_interface, channel=_channel)

        # initialize the main listener
        self._main_listener = can.BufferedReader()
        self._gps_interface = GpsCanInterface(self)
        self._bms_interface = BmsCanInterface(self)
        self._vesc_interface = VescCanInterface(self)
        self._ais_interface = VescCanInterface(self)

        # initialize the utility objects
        self._bms_util = BmsUtility(self._bus)
        self._gps_util = BmsUtility(self._bus)
        self._ais_util = BmsUtility(self._bus)
        self._vesc_util = BmsUtility(self._bus)

        # initialize the file logger
        ## universal time in UTC
        ts=time.time()
        currentTime = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d_%H:%M:%S')
        logFile = open("logs_" + currentTime + ".txt", 'w+')
        logFile.write("Logging messages\n")
        logFile.flush()
        self._file_logger = can.Printer(logFile)

        listenersList = [self._main_listener, self._file_logger, self._gps_interface, self._bms_interface, self._vesc_interface]

        # initialize the notifier
        self._notifier = can.Notifier(self._bus, listenersList)

        
    def get_new_errors(self):
        new_error_list = list(self._error_buffer)
        self._error_buffer.clear()
        return new_error_list

    #One method for each set action
    def setVoltage(self,data):
        # We should be able to get these information from the datasheet
        arbId = 0
        isExtended = False
        message = Message(arbitration_id=arbId,is_extended_id=isExtended,data=data)
        self._bms_util.sendMessage(message, self._bus)

