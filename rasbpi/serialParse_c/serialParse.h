#ifndef SERIAL_PARSE_H
#define SERIAL_PARSE_H

#include <string>

/* SerialParse
 * Get the message to perform tasks according to set convention
 * "$[GET|SET|VAL]ID____0-32 characters____*"
 */
class SerialParse {
public:
    
    SerialParse();
    
    /* setRmp
     * parameter: rmpVal - the rpm value to set to
     * ID: 07
     */
    void setRpm(int rpmVal);
    
    /* getRmp
     * returns: the rpm for the motor
     * ID: 07
     */
    int getRpm();
    
    /* getLatitude
     * returns: the Latitude
     * ID: 01
     */
    double getLatitude();
    
    /* setLatitude
     * parameter: latitudeVal - the latitude to set to, format: DDDMM.mmmmm
     * ID: 01
     */
    //void setLatitude(double latitudeVal);
    
    /* getLongitude
     * returns: the message that can be used to get longitude
     * ID: 02
     */
    double getLongitude();
    
    /* setLongitude
     * parameter: longitudeVal - the longitude to set to, format: DDDMM.mmmmm
     * ID: 02
     */
    //void setLongitude(double longitudeVal);
    
    /* getMotorPower
     * returns: the message that can be used to get the motor power
     * ID: 03
     */
    double getMotorPower();
    
    /* setMotorPower
     * ID: 03
     */
    void setMotorPower(double watt);
    
    /* getBatteryLevel
     * returns: the battery level
     * ID: 04
     */
    double getBatteryLevel();
    
    /* getMotorTemperature
     * returns: the motor temperature, value in kelvin
     * ID: 05
     */
    double getMotorTemperature();
    
    /* getBatteryVoltage
     * returns: the battery level, value is signed double
     * ID: 06
     */
    double getBatteryVoltage();
    
    
    /* getGpsHeading
     * returns: the gps heading, value is signed double
     * ID: 08
     */
    double getGpsHeading();
    
    /* getGpsSpeed
     * returns: the gps speed, value is signed double
     * ID: 09
     */
    double getGpsSpeed();
    
    /* getRudderAngle
     * returns: the rudder angle, value is signed double
     * ID: 51
     */
    double getRudderAngle();
    
    /* setRudderAngle
     * parameter: angle - the angle value to set to in signed double
     * ID: 51
     */
    void setRudderAngle(double angle);
    
private:
    
    bool serialDoneInit;
    int serialFd;
    const char* portName = "/dev/cu.usbmodem4697410";
    const int baudrate = 9600;
    
    
    /*
     * write the message to the file
     */
    void sendMessage(std::string & message);

    
    /*
     * Read from file to determine if valid arduino response
     * valid: if start with $VAL
     * return: true if value false otherwise
     * returnArg: the argument extracted from the line of code
     */
    bool receiveMessage(std::string &returnArg);
};

#endif
