//
//  main.cpp
//  serialParse
//
//  Created by Alex Lee on 2018-10-24.
//  Copyright © 2018 UBC Voyage. All rights reserved.
//

#include "serialParse.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    int temp1;
    double temp2;
    
    SerialParse serial;
    serial.setRpm(10);
    serial.setMotorPower(0.5);
    serial.setMotorPower(120);
    serial.setRudderAngle(20.1);
    //std::cout<<serial.getRpm();
    
    temp2 = serial.getLatitude();
    std::cout<<"latitude value is: "<< temp2 << std::endl;
    
    temp2 = serial.getLongitude();
    std::cout<<"longitude value is: "<< temp2 << std::endl;
    
    temp1 = serial.getRpm();
    std::cout<<"rpme value is: "<< temp1 << std::endl;
    
    temp2 = serial.getMotorPower();
    std::cout<<"motor power is: "<< temp2 << std::endl;
    
    temp2 = serial.getBatteryLevel();
    std::cout<<"battery level is: "<< temp2 << std::endl;
    
    temp2 = serial.getMotorTemperature();
    std::cout<<"motor temperature is: "<< temp2 << std::endl;
    
    temp2 = serial.getBatteryVoltage();
    std::cout<<"battery voltage is: "<< temp2 << std::endl;
    
    temp2 = serial.getGpsHeading();
    std::cout<<"gps heading is: "<< temp2 << std::endl;
    
    temp2 = serial.getGpsSpeed();
    std::cout<<"gps speed is: "<< temp2 << std::endl;
    
    
    
    return 0;
}
