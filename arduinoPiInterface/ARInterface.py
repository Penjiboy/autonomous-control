#!/usr/bin/python3

# Coordinate interaction between Raspberry Pi's C++ code/instructions with the Arduino serial and vice versa 
# through reading/writing a file and mirroring on the serial

import serial
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

ser = null
serialLogsFile = null
filePosition = 0

def serialRead() :
    return ser.read_until("*")


def serialWrite(message) :
    ser.write(bytes(message, "utf8"))




### BEGIN-------------------------------------
#  Code referenced from https://www.michaelcho.me/article/using-pythons-watchdog-to-monitor-changes-to-a-directory

class Watcher:
    DIRECTORY_TO_WATCH = "./SerialLogger/"

    def __init__(self):
        self.observer = Observer()

    def run(self):
        event_handler = Handler()
        self.observer.schedule(event_handler, self.DIRECTORY_TO_WATCH, recursive=True)
        self.observer.start()
        try:
            while True:
                messageToWriteToFile = serialRead()
                event_handler.handleWriteToFile(messageToWriteToFile)
                time.sleep(3)
        except:
            self.observer.stop()
            print "Error"

        self.observer.join()


class Handler(FileSystemEventHandler):

    @staticmethod
    def on_any_event(event):
        if event.is_directory:
            return None

        elif event.event_type == 'created':
            # Take any action here when a file is first created.
            print "Received created event - %s." % event.src_path

        elif event.event_type == 'modified':
            # Taken any action here when a file is modified.
            print "Received file modified event - %s." % event.src_path
            handleWriteToSerial()

    def handleWriteToSerial():
        # move the file object's position to the last set position
        serialLogsFile.seek(filePosition)
        
        # write to the Arduino Serial the next line in the file
        serialWrite(serialLogsFile.readline())

        # readjust the file position
        filePosition = serialLogsFile.tell()

    def handleWriteToFile(message):
        serialLogsFile.write(message)

        filePosition = serialLogsFile.tell()

# END------------------------------------


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

    ser.readline();
    ser.readline();

    # open the text file for reading and writing
    serialLogsFile = open('./SerialLogger/serialLogs.txt', 'a+')

    fileWatcher = Watcher()
    fileWatcher.run()