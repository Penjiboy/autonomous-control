# Import Python core modules
import can
import time
import sys

# Import our common modules
import bms
import common
import gps
import logs
import vesc




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
    print("running")

    #loop to execute forever
    while True:
        #start thread to read remote controller input, store as global variable, update variables above
        print("looping")
        time.sleep(3)



    return
def autonomous_run():
    #decide what we should do here
    return

def controller_run():
    #decide what we should do here
    return

if __name__ == "__main__":
    run()
