#import library/modules
import can
import time
import sys

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



def run():
    #start thread to read remote controller input, store as global variable, update variables above
    if 

    return

if __name__ == "__main__":
    run