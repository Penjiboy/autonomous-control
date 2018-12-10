#ifndef RAS_PI_SERIAL_H
#define RAS_PI_SERIAL_H

//#include <string.h>
//#include <queue.h>
//#include <queue>
//#include <queue.h>
//#include <QueueArray.h>
//#include "QueueArray.h"
#include "libraries/QueueArray/QueueArray.h"
#include "componentIDs.h"

using namespace std;


enum ICode {
    GET, SET, VAL, ERR
};

struct RasPiMessage {
    String fullMessage;
    ICode iCode;
    int id;
    String messageBody;
};

class RasPiSerial {
public:
    QueueArray <RasPiMessage*> messageQueue;

    /**
     * Read serial input and return a pointer to the constructed
     * RasPiMessage object
     */
    void readSerial(String inMessage);

    /**
     * Build an output String to be written to the serial output
     * for the RasPi
     */
    String buildOutMessage(const RasPiMessage& outMessage);
    
    /**
     * Build an output String given the individual parameters
     * to be written to the serial output for the RasPi
     */
    String buildOutMessage(ICode iCode, int id, String messageBody);
};

#endif
