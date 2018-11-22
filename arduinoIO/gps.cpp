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
	char message_id[3];
	char args[82];
	int checksum;

	char north, east;
	int hour, minute;
	float second;
	char valid[1];

	sscanf(nmea, "%[$!]%5s,%[^*]*%2x", start_delimiter, message_handle, args, &checksum);

	if(!strncmp(message_handle, "GPGLL", 5)) {
		sscanf(args, "%lf,%c,%lf,%c,%2i%2i%5f,%[AV],%*c", &_latitude, &north, &_longitude, &east, &hour, &minute, &second, valid);

			if(north == 'S') {
				_latitude *= -1;
			} else if(north != 'N') {
				//invalid data
			}

			if(east == 'W') {
				_longitude *= -1;
			} else if(east != 'E') {
				//invalid data
			}
	} else if(!strncmp(message_handle, "GPVTG", 5)) {
		sscanf(args, "%lf,%*c,%*lf,%*c,%*lf,%*c,%lf,%*c,%*c", &_heading, &_sog);
	}
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

}
