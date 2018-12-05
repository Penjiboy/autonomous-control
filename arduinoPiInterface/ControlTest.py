#!/usr/bin/python3

import time
from SerialIO import SerialIO

print("Starting, waiting for GPS...")

gps_ready = 0
interface = SerialIO()

while gps_ready == 0:
    if interface.getGpsSpeed() != 0:
        gps_ready = 1
    else:
        time.sleep(1)

print("GPS ready...")

while True:
    print("Latitiude:" + interface.getLatitude())
    print("Longitude:" + interface.getLongitude())
    print("Heading:" + interface.getGpsHeading())
    print("Speed:" + interface.getGpsSpeed())
    print("===")
    time.sleep(1)
