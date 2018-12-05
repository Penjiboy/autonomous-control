#!/usr/bin/python3

import serial

class SerialIO :
    ser = None

    def __read(self):
        messageRead = ser.read_all().decode("utf8")

        while messageRead == "":
            messageRead = ser.read_all().decode("utf8")

        return messageRead

    def __write(self, message):
        ser.write(bytes(message, "utf8"))

    def verifyCorrectID(self, message, correctID):
        """Verify the correct ID"""
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
            response = self.__read()

        return response[6:-3]

    def __setGeneric(self, id, value):
        message = "$SET" + id + value + "*"
        self.__write(message)

    def setRudderAngle(self, angle):
        self.__setGeneric("51", angle)

    def getGpsHeading(self):
        return self.__getGeneric("08")

    def getGpsSpeed(self):
        return self.__getGeneric("09")

    def setRpm(self, rpmVal):
        self.__setGeneric("07", rpmVal)

    def getRpm(self):
        return self.__getGeneric("07")

    def getLatitude(self):
        return self.__getGeneric("01")

    def getLongitude(self):
        return self.__getGeneric("02")

    def getBoatPower(self):
        return self.__getGeneric("03")

    def setMotorPower(self, percent):
        self.__setGeneric("50", percent)

    def getBatteryLevel(self):
        return self.__getGeneric("04")

    def getMotorTemperature(self):
        return self.getGeneric("05")

    def getBatteryVoltage(self):
        return self.__getGeneric("06")

    def __init__(self, port=None):
        if port is not None:
            global ser
            ser = serial.Serial(port, 9600)

        else :

            try:
            #global ser
                ser = serial.Serial('/dev/ttyACM0', 9600)
        
            except:
                print('arduino not available on /dev/ttyACM0')
                
            if ser is None:
                try:
                    #global ser
                    ser = serial.Serial('/dev/ttyACM1', 9600)

                except:
                    print('arduino not available on /dev/ttyACM1')

            if ser is None:
                try:
                    #global ser
                    ser = serial.Serial('/dev/ttyACM2', 9600)

                except:
                    print('arduino not available on /dev/ttyACM2')

            if ser is None:
                try:
                    #global ser
                    ser = serial.Serial('/dev/ttyACM3', 9600)

                except:
                    print('arduino not available on /dev/ttyACM3')
    
        if ser is None:
            print('arduino serial unavailable')
            raise Exception("Failed to initialize arduino")

        print("Arduino available and connected")
        ser.read_all()


if __name__ == "__main__":
    io = SerialIO()
    print(io.getBoatPower())