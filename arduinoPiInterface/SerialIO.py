import serial

class SerialIO :
    ser = None

    def read(self):
        messageRead = ser.read_all()
        while messageRead != "":
            messageRead = ser.read_all()

        return messageRead.decode("utf8")

    def write(self, message):
        ser.write(bytes(message, "utf8"))

    def verifyCorrectID(self, message, correctID):
        """Verify the correct ID"""
        id = message[4:6]
        if id == correctID:
            return True
        else:
            return False

    def getGeneric(self, id):
        message = "$GET" + id + "*"
        self.write(message)
        response = self.read()

        while not self.verifyCorrectID(response, id):
            response = self.read()

        return response[6:-1]

    def setGeneric(self, id, value):
        message = "$SET" + id + value + "*"
        self.write(message)

    def setRudderAngle(self, angle):
        self.setGeneric("51", angle)

    def getGpsHeading(self):
        return self.getGeneric("08")

    def initialize(self, port=None):
        ### Return true if initialized successfully, false otherwise
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
            return False

        print("Arduino available and connected")
        ser.read_all()
        return True