#include "rudder.h"

#define RUDDER_PERIOD_NEUTRAL 1500
#define RUDDER_PERIOD_RANGE 1000

//the travel range of the rudder in degrees i.e. RUDDER_PERIOD_RANGE in us should correspond to RUDDER_ANGLE_RANGE in degrees
#define RUDDER_ANGLE_RANGE 180
#define RUDDER_ANGLE_MAX 40 //half the range of the rudder in degrees
#define RUDDER_ANGLE_NEUTRAL 0 //servo angle for neutral rudder position

void Rudder::begin(int pin) {
	debug("Initializing Rudder Servo.");
  period_override_ = 0;
	rudder_servo_.attach(pin);
	setAngle(0);
}

void Rudder::setAngle(float angle) {
	//confine rudder angle to max range
	angle_ = (angle > RUDDER_ANGLE_MAX) ? RUDDER_ANGLE_MAX : ((angle < -RUDDER_ANGLE_MAX) ? -RUDDER_ANGLE_MAX : angle);
	calculatePeriod();
	if(!period_override_) rudder_servo_.writeMicroseconds(rudder_servo_period_);
}

void Rudder::setPeriod(int period) {
	rudder_servo_.writeMicroseconds(period);
  period_override_ = 1;
}

void Rudder::releasePeriod() {
  period_override_ = 0;
  rudder_servo_.writeMicroseconds(rudder_servo_period_);
}

float Rudder::getAngle() {
	return angle_;
}

void Rudder::debug(String msg) {
	Serial.println(msg);
}

void Rudder::calculatePeriod() {
	rudder_servo_period_ = RUDDER_PERIOD_NEUTRAL + (((angle_ + RUDDER_ANGLE_NEUTRAL)/RUDDER_ANGLE_RANGE) * RUDDER_PERIOD_RANGE);
}
