//
// Created by penjani on 2/3/18.
//

#ifndef AIS_H
#define AIS_H

#include "vessel.h"
#include <vector>

class Ais {
public:
    bool status; // check the status of the ais, true means online, false means offline
    vector<Vessel> scan(); //read input from the ais and return a vector of vessels
    Ais(File aisData); //Initialize the AIS system to read input from a file

private:
    File aisData; //File containing AIS input data

};

#endif //AIS_H
