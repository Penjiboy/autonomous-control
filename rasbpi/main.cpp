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
    SerialParse serial;
    serial.setRpm(10);
    //serial.setLatitude(100);
    //serial.setLongitude(10);
    serial.setMotorPower(51);
    serial.setRudderAngle(120);
    //std::cout<<serial.getRpm();
    std::cout<<serial.getLatitude()<<std::endl;
    
    return 0;
}
