#ifndef POSITION_H
#define POSITION_H

#include <cstdint>
#include <string>
#include "loghandle.h"
#include "gps.h"
#include "imu.h"

using namespace std;

class Position {
public:
	Position(LogHandle log, Gps gps);
	Position(LogHandle log, Gps gps, Imu imu);

	int init();

	int update();
	int getHeading();

	int logPos();
	int logPos(LogHandle log);

private:
	LogHandle log_;
	Gps gps_;
	Imu imu_;
	double lat_, long_;
	double pitch_, yaw_;
	double heading_;
};

#endif
