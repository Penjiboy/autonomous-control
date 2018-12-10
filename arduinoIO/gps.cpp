#include "gps.h"

void GPS::begin() {
  _latitude = 0;
  _longitude = 0;
  _heading = 0;
  _sog = 0;
}

int GPS::parseNMEA(char nmea[]) {
	char start_delimiter[1];
	char message_handle[6];
	char args[82];
	int checksum;

	int lat_base, long_base;
  char north, east;
  int hour, minute;
  float second;
  char valid[1];

  sscanf(nmea, "%[$!]%5s,%[^*]*%2x", start_delimiter, message_handle, args, &checksum);

  if(!strncmp(message_handle, "GPGLL", 5)) {
    sscanf(args, "%2i%f,%c,%3i%f,%c,%2i%2i%5f,%[AV],%*c", &lat_base, &_latitude, &north, &long_base, &_longitude, &east, &hour, &minute, &second, valid);

    _latitude = (_latitude / 60.0) + lat_base;
    if(north == 'S') {
      _latitude *= -1;
    } else if(north != 'N') {
      return -1;
    }

    _longitude = (_longitude / 60.0) + long_base;
    if(east == 'W') {
      _longitude *= -1;
    } else if(east != 'E') {
      return -1;
    }
  } else if(!strncmp(message_handle, "GPVTG", 5)) {
    sscanf(args, "%f,%*c,%*f,%*c,%*f,%*c,%f,%*c,%*c", &_heading, &_sog);
  }
  return 0;
}

float GPS::getLongitude() {
	return _longitude;
}

float GPS::getLatitude() {
	return _latitude;
}

float GPS::getHeading() {
	return _heading;
}

float GPS::getSOG() {
	return _sog;
}

int GPS::NMEAChecksum(char msg[]) {
  return 0;
}
