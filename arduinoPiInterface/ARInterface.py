#!/usr/bin/python3

# Coordinate interaction between Raspberry Pi's C++ code/instructions with the Arduino serial and vice versa 
# through reading/writing a file and mirroring on the serial

import serial
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

ser = None
serialLogsFile = None
filePosition = 0


def serialRead():
    print("serial reading: ")
    messageRead = ser.read_all()
    print(messageRead)
    return messageRead.decode("utf8")


def serialWrite(message):
    print("serial writing")
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
                print("entered Watcher loop, about to serial read")
                messageToWriteToFile = serialRead()
                print("finished serial reading")
                print(messageToWriteToFile)
                if messageToWriteToFile != "":
                    print("writing to file")
                    event_handler.handleWriteToFile(messageToWriteToFile)
                time.sleep(2)
        except Exception as ex:
            self.observer.stop()
            print("Error in running File watcher")
            print(ex)

        self.observer.join()


class Handler(FileSystemEventHandler):

    def handleWriteToSerial(self):
        # move the file object's position to the last set position
        global filePosition
        serialLogsFile.seek(filePosition)
        
        # write to the Arduino Serial the next line in the file
        serialWrite(serialLogsFile.readline())

        # readjust the file position
        filePosition = serialLogsFile.tell()

    @staticmethod
    def on_any_event(event):
        if event.is_directory:
            return None

        elif event.event_type == 'created':
            # Take any action here when a file is first created.
            print("Received created event - %s." % event.src_path)

        elif event.event_type == 'modified':
            # Taken any action here when a file is modified.
            print("Received file modified event - %s." % event.src_path)
            
            # move the file object's position to the last set position
            global filePosition
            serialLogsFile.seek(filePosition)
            
            # write to the Arduino Serial the next line in the file
            messageToWriteToSerial = serialLogsFile.readline()
            print("message to write to serial: ", messageToWriteToSerial)
            if messageToWriteToSerial != '':
                serialWrite(messageToWriteToSerial)

            # readjust the file position
            filePosition = serialLogsFile.tell()


    def handleWriteToFile(self, message):
        serialLogsFile.write(message)
        serialLogsFile.flush()

        global filePosition
        filePosition = serialLogsFile.tell()

# END------------------------------------


def main():
    print("AR Interface started...")
    # configure the arduino serial channel

    # TODO: parametrize the serial port so that it can be passed in from command line
    try:
        global ser
        ser = serial.Serial('/dev/ttyACM1', 9600)
    
    except:
        print('arduino not available on /dev/ttyACM1')
    
    if ser is None:
        print('arduino serial unavailable')
        return

    print("Arduino available and connected")
    ser.read_all()

    # open the text file for reading and writing
    print("opening logs file")
    global serialLogsFile
    serialLogsFile = open('./SerialLogger/serialLogs.txt', 'a+')

    print("Starting file watcher")
    fileWatcher = Watcher()
    fileWatcher.run()


if __name__ == "__main__":
    main()