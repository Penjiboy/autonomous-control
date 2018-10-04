#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

class GPS {
	float latitude, longitude;
public:
  int parseNMEA(char[82] nmea);
  float getLatitude();
  float getLongitude();
private:
  void debug(String msg);
  void NMEAchecksum(char[] checksum);
};
#endif
