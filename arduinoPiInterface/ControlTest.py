#!/usr/bin/python3

from SerialIO import *

print("Starting, reading GPS")

gps_ready = 0
interface = SerialIO()

while gps_ready == 0:
	tmp = interface.getGpsSpeed()
	print(tmp)
	if tmp != 0:
		gps_ready = 1

print("GPS ready...")
