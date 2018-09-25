#include "rasPiSerial.h"

RasPiMessage* RasPiSerial::readSerial(string& inMessage){
    //TODO: Implement this function
    RasPiMessage* result = new RasPiMessage();

    if(inMessage[0] != '$'){
        result->iCode = ERR;
        return result;
    }

    string newICode = inMessage.substr(1,3);
    result->iCode = 
        newICode == "GET" ? GET : 
        (newICode == "SET" ? SET : (
            newICode == "VAL" ? VAL : ERR
            )
        );

    result->id = stoi(inMessage.substr(4,2));
    result->messageBody = inMessage.substr(6);

    return result;
}

string RasPiSerial::buildOutMessage(const RasPiMessage& outMessage){
    if(!&(outMessage.fullMessage)){
        return outMessage.fullMessage;
    }

    return (RasPiSerial::buildOutMessage(outMessage.iCode, outMessage.id, outMessage.messageBody));
}

string RasPiSerial::buildOutMessage(ICode iCode, uint id, string messageBody){
    string result = "$";
    
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