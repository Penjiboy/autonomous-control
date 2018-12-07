#!/usr/bin/python3

import serial
from serial import SerialException

BAUD = 9600


class SerialIO:
    """Serial Communication with arduino for voyage craft nimrod."""

    ser = None

    def __read(self):
        messageRead = self.ser.read_all().decode("utf8")

        while messageRead == "":
            messageRead = self.ser.read_all().decode("utf8")

        return messageRead

    def __write(self, message):
        self.ser.write(message)

    def verifyCorrectID(self, message, correctID):
        """Verify the correct ID."""
        id = message[4:6]
        if id == correctID:
            return True
        else:
            return False

    def __getGeneric(self, id):
        message = "$GET" + id + "*"
        self.__write(message)
        response = self.__read()

        while not self.verifyCorrectID(response, id):
            print("incorrect msg: " + response)
            response = self.__read()

        return response[6:-3]

    def __setGeneric(self, id, value):
        message = "$SET" + id + value + "*"
        self.__write(message)

    def setRudderAngle(self, angle):
        self.__setGeneric("51", str(angle))

    def getGpsHeading(self):
        return self.__getGeneric("08")

    def getGpsSpeed(self):
        return self.__getGeneric("09")

    def setRpm(self, rpmVal):
        self.__setGeneric("07", str(rpmVal))

    def getRpm(self):
        return self.__getGeneric("07")

    def getLatitude(self):
        return self.__getGeneric("01")

    def getLongitude(self):
        return self.__getGeneric("02")

    def getBoatPower(self):
        return self.__getGeneric("03")

    def setMotorPower(self, percent):
        self.__setGeneric("50", str(percent))

    def getBatteryLevel(self):
        return self.__getGeneric("04")

    def getMotorTemperature(self):
        return self.getGeneric("05")

    def getBatteryVoltage(self):
        return self.__getGeneric("06")

    def __init__(self, port=None):

        if port is not None:
            self.ser = serial.Serial(port, BAUD)

        else:

            try:
                self.ser = serial.Serial('/dev/ttyACM0', BAUD)

            except SerialException:
                print('arduino not available on /dev/ttyACM0')

            if self.ser is None:
                try:
                    self.ser = serial.Serial('/dev/ttyACM1', BAUD)

                except SerialException:
                    print('arduino not available on /dev/ttyACM1')

            if self.ser is None:
                try:
                    self.ser = serial.Serial('/dev/ttyACM2', BAUD)

                except SerialException:
                    print('arduino not available on /dev/ttyACM2')

            if self.ser is None:
                try:
                    self.ser = serial.Serial('/dev/ttyACM3', BAUD)

                except SerialException:
                    print('arduino not available on /dev/ttyACM3')

        if self.ser is None:
            print('arduino serial unavailable')
            raise Exception("Failed to initialize arduino")

        print("Arduino available and connected")
        self.ser.read_all()


if __name__ == "__main__":
    io = SerialIO()
    print(io.getBoatPower())
