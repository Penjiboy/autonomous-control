#!/usr/bin/python3

import logging as log
import atexit
import time
import datetime
import PID
from Vector import Vector as v2
from SerialIO import SerialIO

log.basicConfig(filname="test.log", format='%(asctime)s %(message)s')
log.info("tetst log message")

def end():
    global interface
    print("exiting gracefully...")
    interface.setMotorPower(0)
    interface.setRudderAngle(0)


atexit.register(end)

targetnum = 0
aux = 0

target = [v2(49.273889, -123.191995), v2(49.273232, -123.193417), v2(), v2()]
home = v2(49.273010, -123.191855)
position = v2()
course = v2()


def getTarget():
    if(aux == 0 and targetnum < len(target)):
        return target[targetnum]
    else:
        return home


gps_ready = 0
interface = SerialIO()

print("Starting, waiting for GPS...")

while gps_ready == 0:
    if interface.getGpsSpeed() != 0:
        gps_ready = 1
    else:
        print("Gps Not ready...")
        time.sleep(3)

print("GPS ready...")
print("Running init")

for _ in range(3):
    print("Latitiude:" + interface.getLatitude())
    print("Longitude:" + interface.getLongitude())
    print("Heading:" + interface.getGpsHeading())
    print("Speed:" + interface.getGpsSpeed())
    print("===")
    time.sleep(1)

time.sleep(5)

position.set_coords((interface.getLatitude(), interface.getLongitude()))
course.set_from_polar(interface.getGpsSpeed(), interface.getGpsHeading())

print("Autonomous mode...")
print("Seeking coordinates: " + str(getTarget()))
print("From position: " + str(position))

interface.setMotorPower(0.05)

pid = PID.PID(.3, .1, .01)

while True:
    # until within very approximately 10m of desination

    if(position.distance_to(getTarget()) < .001):
        targetnum += 1
        print("Target reached")

    position.set_coords((interface.getLatitude(), interface.getLongitude()))
    course.set_from_polar(interface.getGpsSpeed(), interface.getGpsHeading())
    aux = interface.getBatteryLevel()

    print("Position: " + str(position))
    print("Course: " + str(course))
    print("Angle to proper heading: " + str(course.angle_to(getTarget()-position)))

    interface.setRudderAngle(course.angle_to(getTarget()-position)/5)

    time.sleep(1)

interface.setMotorPower(0)
