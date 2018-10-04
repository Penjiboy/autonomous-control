int GPS::parseNMEA(char[] nmea) {
	char start_delimiter;
	char message_talker;
	char message_id;
	char checksum;

  sscanf(nmea, "%[$!]%2s%3s%*[^*]*%2x", start_delimiter, message_talker, message_id, checksum);

  switch(message_id) {
    case "GLL":
	 	sscanf(nmea, "$GPGLL%lf,%c,%lf,%c,%2i%2i%5f,%*[AV],%c*%x",);
		return 0;
	 break; //read NMEA 0183 GLL string


    default: return -1; break;
  }
}

float getLongitude() {
	return longitude;
}

float getLatitude() {
	return latitude;
}

void GPS::NMEAChecksum(char[] checksum) {

}
