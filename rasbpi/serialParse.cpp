#include "serialParse.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;


void SerialParse::setRpm(unsigned int rpmVal){
    std::string message = "$SET07";
    message = message + rpmVal + "*";
    sendMessage(message);
}



int SerialParse::getRpm(){
    std::string message = "$GET07*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("07")){
        return stoi(returnArg.subStr(6, 7));
    }
    
    return -1;
}



double SerialParse::getLatitude(){
    std::string message = "$GET01*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("01")){
        return atof(returnArg.subStr(6, 7).c_str());
    }
    
    return -1;
}



void SerialParse::setLatitude(signed double latitudeVal){
    std::string message = "$SET01";
    message = message + latitudeVal + "*";
    sendMessage(message);
    
}



double SerialParse::getLongitude(){
    std::string message = "$GET02*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("02")){
        return atof(returnArg.subStr(6, 7).c_str());
    }
    
    return -1;
}



void SerialParse::setLongitude(signed double longitudeVal){
    std::string message = "$SET02";
    message = message + longitudeVal + "*";
    sendMessage(message);
}



double SerialParse::getMotorPower(){
    std::string message = "$GET03*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("03")){
        return atof(returnArg.subStr(6, 7).c_str());
    }
    
    return -1;
}



void SerialParse::setMotorPower(unsigned double watt){
    std::string message = "$SET03";
    message = message + watt + "*";
    sendMessage(message);
}


double SerialParse::getBatterLevel(){
    std::string message = "$GET04*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("04")){
        return atof(returnArg.subStr(6, 7).c_str());
    }
    
    return -1;
}



double SerialParse::getMotorTemperature(){
    std::string message = "$GET05*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("05")){
        return atof(returnArg.subStr(6, 7).c_str());
    }
    
    return -1;
}



double SerialParse::getBatteryVoltage(){
    std::string message = "$GET06*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("06")){
        return atof(returnArg.subStr(6, 7).c_str());
    }
    
    return -1;
}



double SerialParse::getRudderAngle(){
    std::string message = "$GET51*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.subStr(4, 5).compare("51")){
        return atof(returnArg.subStr(6, 7).c_str());
    }
    
    return -1;
}



void SerialParse::setRudderAngle(signed double angle){
    std::string message = "$SET51";
    message = message + angle + "*";
    sendMessage(message);
}



void SerialParse::sendMessage(std::string & message){
    fstream writeFile;
    //open the file and set initial position at the end of the file
    writeFile.open("serialLogs.txt", ios::ate);
    message = message + "\n";
    
    writeFile.write( message, sizeof(char)*message.length());
    
    writeFile.close();
}



bool SerialParse::receiveMessage(std::string returnArg){
    std::ifstream file("serialLogs.txt");
    std::string str, subString;
    
    std::getline(file, str);
    
    subString = str.subStr(1, 3);
    
    if(subString.compare("VAL")){
        returnArg = str.subStr(0, 7);
        return true;
    }
        
    return false;
}
