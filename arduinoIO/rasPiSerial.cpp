#include "rasPiSerial.h"

static void RasPiSerial::readSerial(String inMessage){
    RasPiMessage* result = new RasPiMessage();

    if(inMessage[0] != '$'){
        result->iCode = ERR;
        RasPiSerial::messageQueue.push(result);
        //RasPiSerial::messageQueue.enqueue(result);
        //return result;
    }

    String newICode = inMessage.substr(1,3);
    result->iCode = 
        newICode == "GET" ? GET : 
        (newICode == "SET" ? SET : (
            newICode == "VAL" ? VAL : ERR
            )
        );

    result->id = stoi(inMessage.substr(4,2));
    result->messageBody = inMessage.substr(6);

    RasPiSerial::messageQueue.push(result);
    //RasPiSerial::messageQueue.enqueue(result);
    //return result;
}

static String RasPiSerial::buildOutMessage(const RasPiMessage& outMessage){
    if(!&(outMessage.fullMessage)){
        return outMessage.fullMessage;
    }

    return (RasPiSerial::buildOutMessage(outMessage.iCode, outMessage.id, outMessage.messageBody));
}

static String RasPiSerial::buildOutMessage(ICode iCode, int id, String messageBody){
    String result = "$";
    
    switch(iCode){
        case GET: result += "GET"; break;
        case SET: result += "SET"; break;
        case VAL: result += "VAL"; break;
        default: result += "ERR"; break;
    }

    result += id;
    result += messageBody;
    return result;
}