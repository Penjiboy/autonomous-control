//
// Representation of boat objects
//

#ifndef VESSEL_H
#define VESSEL_H

class Vessel {
public:
    /**
     * Constructor of a vessel object.
     */
    Vessel(); //Constructor a vessel object
    ~Vessel(); // Destructor

    //The relative position of the vessel in relation to Frank
    long relativePositionX;
    long relativePositionY;

    //the relative velocity of the vessel in relation to Frank
    long relativeVelocityX;
    long relativeVelocityY;

    /**
     * Determine the proximity of this vessel in relation to Frank
     * @return euclidean distance to Frank
     */
    long calculateProximity();
    long calculateVelocity(); //calculate the velocity of the vessel in relation to Frank

    /**
     * Update the current position of this vessel. Ideally to be called by AIS
     * @param x position
     * @param y position
     * @modifies relativePositionX and relativePositionY
     */
    void updatePosition(long x, long y);

    /**
     * Request an update of the relative position. Ideally to be called by Control
     */
    void requestUpdatePosition();

    //The vessel ID of this vessel
    long vesselID;
};


#endif //BOAT_H
