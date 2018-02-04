//
// Representation of the RPM sensor for the motor/propeller
//

#ifndef RPM_H
#define RPM_H

class Rpm {
public:
    /**
     * Calculate the current rpm
     * @return rpm value
     */
    long currentRPM(); //calculate the current rpm from the sensor data

    /**
     * checks whether the rpm is decreasing based on the data. Return true if it is decreasing, false otherwise.
     * @return true if the rpm is decreasing, false otherwise
     */
    bool isDecreasing();

    /**
     * Constructor for the RPM object
     * @param file containing the sensor data
     */
    Rpm(File file);

private:
    //File containing the sensor input data
    File file;
};

#endif //RPM_H
