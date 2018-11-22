#include "serialParse.h"
#include "wiringSerial.h"
//#include "arduino-serial-lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using namespace std;

SerialParse::SerialParse(){
    serialDoneInit = false;
    serialFd = -1;
};

void SerialParse::setRpm(int rpmVal){
    std::string message = "$SET07";
    message = message + std::to_string(rpmVal) + "*";
    
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
    if(returnArg.substr(0, 2) == "07"){
        int msglen = (int)returnArg.length();
        return stoi(returnArg.substr(2, msglen - 2));
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
    if(returnArg.substr(0, 2) == "01"){
        int msglen = (int)returnArg.length();
        return atof(returnArg.substr(2, msglen - 2).c_str());
    }
    
    return -1;
}


/*
void SerialParse::setLatitude(double latitudeVal){
    std::string message = "$SET01";
    stringstream stream;
    stream << fixed << setprecision(2) << latitudeVal;
    
    message = message + stream.str() + "*";
    sendMessage(message);
    
}
*/


double SerialParse::getLongitude(){
    std::string message = "$GET02*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.substr(0, 2) == "02"){
        int msglen = (int)returnArg.length();
        return atof(returnArg.substr(2, msglen - 2).c_str());
    }
    
    return -1;
}


/*
void SerialParse::setLongitude(double longitudeVal){
    std::string message = "$SET02";
    stringstream stream;
    stream << fixed << setprecision(2) << longitudeVal;
    
    message = message + stream.str() + "*";
    sendMessage(message);
}
*/


double SerialParse::getMotorPower(){
    std::string message = "$GET03*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.substr(0, 2) == "03"){
        int msglen = (int)returnArg.length();
        return atof(returnArg.substr(2, msglen - 2).c_str());
    }
    
    return -1;
}



void SerialParse::setMotorPower(double watt){
    std::string message = "$SET03";
    stringstream stream;
    stream << fixed << setprecision(2) << watt;
    
    message = message + stream.str() + "*";
    sendMessage(message);
}


double SerialParse::getBatteryLevel(){
    std::string message = "$GET04*";
    
    std::string returnArg;
    
    sendMessage(message);
    
    //keep looping until a response is retrieved from the arduino
    while(!receiveMessage(returnArg)){
        
    }
    
    //check the ID
    if(returnArg.substr(0, 2) == "04"){
        int msglen = (int)returnArg.length();
        return atof(returnArg.substr(2, msglen - 2).c_str());
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
    if(returnArg.substr(0, 2) == "05"){
        int msglen = (int)returnArg.length();
        return atof(returnArg.substr(2, msglen - 2).c_str());
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
    if(returnArg.substr(0, 2) == "06"){
        int msglen = (int)returnArg.length();
        return atof(returnArg.substr(2, msglen - 2).c_str());
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
    if(returnArg.substr(0, 2) == "51"){
        int msglen = (int)returnArg.length();
        return atof(returnArg.substr(2, msglen - 2).c_str());
    }
    
    return -1;
}



void SerialParse::setRudderAngle(double angle){
    std::string message = "$SET51";
    
    stringstream stream;
    stream << fixed << setprecision(2) << angle;
    
    message = message + stream.str() + "*";
    sendMessage(message);
}


/*
void SerialParse::sendMessage(std::string & message){
    ofstream writeFile;
    std::cout << message <<endl;
    //open the file and set initial position at the end of the file
    writeFile.open("serialLogs.txt", std::ios::app);
    
    message = "\n" + message;
    
    if (!writeFile.is_open()){
        std::cout << "file cannot be opened!!\n" <<endl;
    }
    
    writeFile.write( message.c_str(), sizeof(char)*message.length());
    
    writeFile.close();
}
*/

/*
bool SerialParse::receiveMessage(std::string &returnArg){
    std::ifstream file;
    std::string str, substring;
    
    file.open("serialLogs.txt");
    
    if(file.is_open()) {
        cout << "file is open\n";
        file.seekg(-1,ios_base::end);                // go to one spot before the EOF
        
        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            file.get(ch);                            // Get current byte's data
            
            if((int)file.tellg() <= 1) {             // If the data was at or before the 0th byte
                file.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if(ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                file.seekg(-2,ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }
        
        getline(file,str);                      // Read the current line
        //cout << "Result: " << str << '\n';     // Display it
        
        file.close();
    }

 
    if(str.length() < 4){
        std::cout << "error\n";
        return false;
    }
 
     
    //std::cout << str << "str\n";
    substring = str.substr(1, 3);
    //std::cout << substring;
    
    if(substring == "VAL"){
        int msglen = (int)str.length();
        returnArg = str.substr(4, msglen - 5);
        //std::cout << returnArg << endl;
        return true;
    }
        
    return false;
}
*/

void SerialParse::sendMessage(std::string & message){
    //iniitalize the serial port if not already done so
    while(!serialDoneInit || serialFd == -1){
        cout << "trying to initialize serial port\n";
        serialFd = serialOpen (portName, baudrate) ;
        serialDoneInit = true;
    }
    cout << "serial opened, fd: " << serialFd << endl;
    
    
    serialPuts(serialFd, message.c_str());
}

bool SerialParse::receiveMessage(std::string &returnArg){
    cout << "receiving from fd: " << serialFd << endl;
    //assert(serialFd == -1);
    //assert(serialDoneInit == false);
    //get the number of characters written to the serial port
    int serial_numChar;
    do{
        //serialDataAvail returns the number of characters available for reading, or -1 for any error condition
        serial_numChar = serialDataAvail(serialFd);
        std::cout << "Reading characters available from the serial" << endl;
    }while(serial_numChar == 0 || serial_numChar == -1);
    
    std::cout<< "read " << serial_numChar << " characters from the serial" << endl;
    
    std::string str = "";
    std::string substring;
    
    std::cout<< "begin to read the characters" << endl;
    //retreive all characters and construct message
    for(int countChar = 0; countChar <= serial_numChar; countChar++){
        str = str + (char)serialGetchar(serialFd);
        std::cout<< "read a character from serial port" << endl;
    }
    
    substring = str.substr(1, 3);
    
    if(substring == "VAL"){
        int msglen = (int)str.length();
        returnArg = str.substr(4, msglen - 5);
        //std::cout << returnArg << endl;
        return true;
    }
    
    return false;
}
