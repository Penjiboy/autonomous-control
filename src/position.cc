#include "position.h"

Position::Position(LogHandle log, Gps gps) {
	Position(log, gps, 0);
}

Position::Position(LogHandle log, Gps gps, Imu imu) {
	log_ = log;
	gps_ = gps;
	imu_ = imu;
}

int Position::init() {
	int err;
	log_.info("Position: Initialising GPS...");
	if((err = gps_.init()))
		log_.err("Position: GPS initialization failed with error " + (string)err + ".");
	if(imu_) {
		log_.info("Position: Initialising IMU...");
		if((err = imu_.init()))
			log_.err("Position: IMU initialization failed with error " + (string)err + ".");
	}
}

int Position::update() {
	int err;
	if((err = gps_.update()))
		log_.err("Position: GPS update failed with error " + (string)err)
}
int getHeading();

int logPos();
int logPos(LogHandle log);
