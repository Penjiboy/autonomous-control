#!/usr/bin/python3

import time
from SerialIO import SerialIO

print("Starting, reading GPS")

gps_ready = 0
interface = SerialIO()

while gps_ready == 0:
    tmp = interface.getGpsSpeed()
    print(tmp)
    if tmp != 0:
        gps_ready = 1
    else:
        time.sleep(1)

print("GPS ready...")
