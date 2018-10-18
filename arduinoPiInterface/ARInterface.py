#!/usr/bin/python3

# Coordinate interaction between Raspberry Pi's C++ code/instructions with the Arduino serial and vice versa 
# through reading/writing a file and mirroring on the serial

import serial

ser = null
serialLogs = null

if __name__ == "__main__":
    
    # configure the arduino serial channel
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600)
    
    except:
        print('arduino not available on /dev/ttyACM0')

    else :
        try:
            ser = serial.Serial('/dev/ttyACM1', 9600)

        except:
            print('arduino not available on /dev/ttyACM1')
    
    if ser == null:
        print('arduino serial unavailable')
        return

    # open the text file for reading and writing
    serialLogs = open('serialLogs.txt', 'a+')

    run()

def serialRead() :
    return ser.read_until("*")


def serialWrite(message) :
    ser.write(bytes(message, "utf8"))


def run():
    # watch for changes in the text file
    pass


