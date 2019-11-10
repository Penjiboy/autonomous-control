# Import Python core modules
import can
import time
import sys

# Import our common module
import bms
import common
import gps
import logs
import vesc
import Steering

#define global variables here
#Add data as needed
bmsData = {
    "current draw": 0.0,
    "charge": 100,
    "capacity": 0
}
gpsData = {
    "longatitude": 0.0,
    "latitude": 0.0
}
#control mode: auto or controller
radioData = {
    "control mode": "auto",

}

#result stores item that should be written to the log every iteration
result = {}

def run():
    #create ais, bms, gps, irid, rf instance here
    bus = can.interface.Bus(channel='can0', bustype='socketcan_native') 
    msg = can.Message(arbitration_id=0x7de, data=[0, 25, 0, 1, 3, 1, 4, 1], extended_id=False)

    #loop to execute forever
    while True:
        #start thread to read remote controller input, store as global variable, update variables above
        if radioData.get("control mode", False)  == "controller":
            controller_run()
        elif radioData.get("control mode", False)  == "auto":
            autonomous_run()
        


    return
def autonomous_run():
    #decide what we should do here
    return

def controller_run():
    #decide what we should do here
    return

if __name__ == "__main__":
    run