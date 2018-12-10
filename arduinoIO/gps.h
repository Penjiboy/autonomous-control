#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

class GPS {
	float _latitude, _longitude;
	float _heading, _sog;
public:
  void begin();
  
  int parseNMEA(char nmea[]);
  float getLatitude();
  float getLongitude();
  float getHeading();
  float getSOG();
private:
  void debug(String msg);
  int NMEAChecksum(char msg[]);
};
#endif
