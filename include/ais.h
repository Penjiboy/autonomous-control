//
// Created by penjani on 2/3/18.
//

#ifndef AIS_H
#define AIS_H

#include "vessel.h"
#include <vector>

class Ais {
public:
    /**
     * check the status of the ais
     * @return true if online and operating properly, false otherwise
     */
    bool status;

    /**
     * read input from the ais sensor and return a vector of vessels
     * @return a vector/list of vessels
     */
    vector<Vessel> scan();

    /**
     * Constructor of an AIS object. Initialize AIS system to read input from a file
     * @param aisData file
     */
    Ais(File aisData);

private:
    //File containing AIS input data
    File aisData;

};

#endif //AIS_H
