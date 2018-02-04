//
// Created by Alex on 2/4/18
//

#ifndef ATMOSPHRER_H
#define ATMOSPHRER_H

#inclde <vector>

/**
 * Information is obtained from a weather sensor
 */
class Atmosphere{
public:
    /**
     * Atmosphere object constructor
     * @param atmosphereData the file name
     */
    Atmosphere(File atmosphereData);
    
    /**
     * Reads from the file and returns the current atmosphereic pressure
     * @returns pressure in pa as a double value
     */
    double currentPressure();
    
    /**
     * Reads from the file and returns the current temperature
     * @returns temperature in degree celsius as a double value
     */
    double currentTemperature();
    
    
private:
    File atmosphereData;
};
#endif //ATMOSPHRER_H
