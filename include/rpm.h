//
// Representation of the RPM sensor for the motor/propeller
//

#ifndef RPM_H
#define RPM_H

#include <vector>
#include <cstdio>
#include <stdio.h>

class Rpm {
public:

    //The desired RPM, which is set by the system
    long desiredRPM;

    /**
     * Calculate the actual rpm
     * @return rpm value
     */
    long actualRPM();

    /**
     * checks whether the rpm is decreasing based on the data. Return true if it is decreasing, false otherwise.
     * @return true if the rpm is decreasing, false otherwise
     */
    bool isDecreasing();

    /**
     * Constructor for the RPM object
     * @param file containing the sensor data
     */
    explicit Rpm(FILE* file);

private:
    //File containing the sensor input data
    FILE* file;

    struct reading {
        long value; //the actual rpm reading
        long time;  //the timestamp for the reading
    };

    // A data structure to hold a number of rpm readings for analysis
    // In the constructor we might want to consider setting the maximum capacity for this vector so that it doesn't get crazy
    std::vector<reading>* readings;

    /**
     * Read the input file to process new rpm readings
     * @modifies readings vector
     */
    void updateReadings();
};

#endif //RPM_H
