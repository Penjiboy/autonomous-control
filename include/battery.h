//
// Created by Alex on 2/4/18
//

#ifndef BATTERY_H
#define BATTERY_H

#include <vector>

/**
 *Battery: contains information on the condition of the battery
 */
class Battery{

public:
    
    long designedCapacity; //the original capacity
    int cycles; //the number of cycles the battery has gone through
    
    /**
     * Constructor of a batter object
     * @param batteryData the file name
     */
    Battery(File batterData);
    
    /**
     * reads input and give the battery's current full capacity
     * @return the capacity in mAh
     */
    long fullCapacity(void);
    
    /**
     * read from file and gives the remaining charge left in the battery
     * @return the remaining charge left in the battery in mAh as a long value
     */
    long remainingCharge();
    
    /**
     * read from file and give the battery's cycle count(A cycle is from fully charged to discharge)
     * @return the battery cycle count
     */
    long cycleLife(void);
    
    /**
     * Reads from file ang gives a list of all devices that are using power
     * @return a list of devices
     */
    Vector<String> devicesInUse(void);
    
    /**
     * Reads from the input and output power and determines if the net charge is increasing
     * @return a boolean value, true for charging, false for discharging
     */
    bool isCharging(void); //return if the over all charge is increasing
    
    /**
     * Reads from the file and determine the output level for a specific device
     * @param device the device that is to be quried
     * @return the power a device is using in watt/hours as a long value
     */
    long outputLevel(String device);
    
private:
    File batteryData;
    Vector<String>; //keep track of the devices using power
};
#endif
