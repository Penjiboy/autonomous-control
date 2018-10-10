#include "rasPiSerial.h"

void RasPiSerial::readSerial(String inMessage){
    RasPiMessage* result = new RasPiMessage();

    if(inMessage[0] != '$'){
        result->iCode = ERR;
        messageQueue.push(result);
    }

    String newICode = inMessage.substring(1,4);
    result->iCode = 
        newICode == "GET" ? GET : 
        (newICode == "SET" ? SET : (
            newICode == "VAL" ? VAL : ERR
            )
        );

    result->id = inMessage.substring(4,6).toInt();
    result->messageBody = inMessage.substring(6);

    messageQueue.push(result);
}

String RasPiSerial::buildOutMessage(const RasPiMessage& outMessage){
    if(!&(outMessage.fullMessage)){
        return outMessage.fullMessage;
    }

    return (RasPiSerial::buildOutMessage(outMessage.iCode, outMessage.id, outMessage.messageBody));
}

String RasPiSerial::buildOutMessage(ICode iCode, int id, String messageBody){
    String result = "$";
    
    switch(iCode){
        case GET: result += "GET"; break;
        case SET: result += "SET"; break;
        case VAL: result += "VAL"; break;
        default: result += "ERR"; break;
    }

    result += id < 10 ? ("0" + (String) id) : id;
    result += messageBody;
    return result;
}