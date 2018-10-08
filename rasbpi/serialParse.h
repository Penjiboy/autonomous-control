#ifndef SERIAL_PARSE_H
#define SERIAL_PARSE_H

#include <string>

/* SerialParse
 * Get the message to perform tasks according to set convention
 * "$[GET|SET|VAL]ID____0-32 characters____*"
 */
Class SerialParse {
public:
    
    /* setRmp
     * parameter: rmpVal - the rpm value to set to
     * returns: the message that can be used set rpm for the motor
     * ID: 07
     */
    std::string setRpm(unsigned int rpmVal);
    
    /* getRmp
     * returns: the message that can be used set rpm for the motor
     * ID: 07
     */
    std::string getRpm();
    
    /* getLatitude
     * returns: the message that can be used to getLatitude
     * ID: 01
     */
    std::string getLatitude();
    
    /* setLatitude
     * parameter: latitudeVal - the latitude to set to, format: DDDMM.mmmmm
     * returns: the message that can be used to set latitude
     * ID: 01
     */
    std::string setLatitude(signed double latitudeVal);
    
    /* getLongitude
     * returns: the message that can be used to get longitude
     * ID: 02
     */
    std::string getLongitude();
    
    /* setLongitude
     * parameter: longitudeVal - the longitude to set to, format: DDDMM.mmmmm
     * returns: the message that can be used to set longitude
     * ID: 02
     */
    std::string setLongitude(signed double longitudeVal);
    
    /* getMotorPower
     * returns: the message that can be used to get the motor power
     * ID: 03
     */
    std::string getMotorPower();
    
    /* setMotorPower
     * returns: the message that can be used to set the motor power, unsigned double
     * ID: 03
     */
    std::string setMotorPower(unsigned double watt);
    
    /* getBatteryLevel
     * returns: the message that can be used to get the battery level
     * ID: 04
     */
    std::string getBatteryLevel();
    
    /* setBatteryLevel
     * parameter: level - the battery level to set to, unsigned double, should b between 1-0
     * returns: the message that can be used to set the battery level
     * ID: 04
     */
    std::string setBatteryLevel(unsigned double level);
    
    /* getMotorTemperature
     * returns: the message that can be used to get the motor temperature, value in kelvin
     * ID: 05
     */
    std::string getMotorTemperature();
    
    /* getBatteryVoltage
     * returns: the message that can be used to get the battery level, value is signed double
     * ID: 06
     */
    std::string getbatteryVoltage();
    
    /* getRudderAngle
     * returns: the message that can be used to get the rudder angle, value is signed double
     * ID: 51
     */
    std::string getRudderAngle();
    
    /* setRudderAngle
     * parameter: angle - the angle value to set to in signed double
     * returns: the message that can be used to set tte rudder angle
     * ID: 51
     */
    std::string setRudderAngle(signed double angle);
    
private:
    
    /*
     *
     */
    void sendMessage(std::string & message);
    
    /*
     *
     */
    std::string receiveMessage();
};

#endif
