//
// Representation of boat objects
//

#ifndef VESSEL_H
#define VESSEL_H

class Vessel {
public:
    Vessel(); //Constructor a vessel object
    ~Vessel(); // Destructor

    //The relative position of the vessel in relation to Frank
    long relativePositionX;
    long relativePositionY;

    //the relative velocity of the vessel in relation to Frank
    long relativeVelocityX;
    long relativeVelocityY;

    long calculateProximity(); // calculate the proximity of the vessel in relation to Frank
    long calculateVelocity(); //calculate the velocity of the vessel in relation to Frank
};


#endif //BOAT_H
