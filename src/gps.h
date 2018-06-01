#ifndef GPS_H
#define GPS_H

#include <cstdint>
#include <string>
#include "loghandle.h"

using namespace std;

class Gps {
public:
	Gps(LogHandle log);

	int init();

	int update();

private:
	LogHandle log_;
};

#endif
