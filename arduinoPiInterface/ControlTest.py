#!/usr/bin/python3

import csv
import atexit
import time
import datetime
import PID
from Vector import Vector as v2
from SerialIO import SerialIO


def end():
    global interface
    print("exiting gracefully...")
    interface.setMotorPower(0)
    interface.setRudderAngle(0)


atexit.register(end)

targetnum = 0
aux = 0

target = [v2(49.273889, -123.191995), v2(49.273232, -123.193417), v2(49.273232, -123.193417), v2(49.273891, -123.194179)]
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

interface.setMotorPower(0.1)

time.sleep(5)

while True:
    # until within very approximately 10m of desination

    if(position.distance_to(getTarget()) < .001):
        targetnum += 1
        print("Target reached")

    position.set_coords((interface.getLatitude(), interface.getLongitude()))
    course.set_from_polar(interface.getGpsSpeed(), interface.getGpsHeading())
    aux = interface.getBatteryLevel()

    print("Aux status: " + str(aux))
    print("Position: " + str(position))
    print("Target: " + str(getTarget()))
    print("Course: " + str(course))
    print("Angle to proper heading: " + str(course.angle_to(getTarget()-position)))

    with open('test.csv', 'a') as test:
        writer = csv.writer(test)
        writer.writerow([str(datetime.datetime.now()), str(position), str(course), str(getTarget()), str(course.angle_to(getTarget()-position))])

    interface.setRudderAngle(course.angle_to(getTarget()-position)/3)

    time.sleep(1)

interface.setMotorPower(0)
