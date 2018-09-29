#ifndef RAS_PI_SERIAL_H
#define RAS_PI_SERIAL_H

#include <string>
#include <queue>

using namespace std;


enum ICode {
    GET, SET, VAL, ERR
};

struct RasPiMessage {
    string fullMessage;
    ICode iCode;
    uint id;
    string messageBody;
};

class RasPiSerial {
public:
    static queue<RasPiMessage*> messageQueue;

    /**
     * Read serial input and return a pointer to the constructed
     * RasPiMessage object
     */
    void readSerial(string& inMessage);

    /**
     * Build an output string to be written to the serial output
     * for the RasPi
     */
    string buildOutMessage(const RasPiMessage& outMessage);
    
    /**
     * Build an output string given the individual parameters
     * to be written to the serial output for the RasPi
     */
    string buildOutMessage(ICode iCode, uint id, string messageBody);

    /**
     * Depending on the message contents, delegate responsibility
     * to the appropriate part of the system
     */
    void delegateMessageResponsibility(RasPiMessage* &message);
};

#endif