#include "rudder.h"

#define RUDDER_PERIOD_NEUTRAL 1500
#define RUDDER_PERIOD_RANGE 1000

//half the travel range of the rudder in degrees i.e. RUDDER_PERIOD_RANGE in us should correspond to half of RUDDER_ANGLE_RANGE
#define RUDDER_ANGLE_RANGE 90
#define RUDDER_ANGLE_MAX 40 //half the range of the rudder in degrees
#define RUDDER_ANGLE_NEUTRAL 0 //servo angle for neutral rudder position

void Rudder::begin(int pin) {
	debug("Initializing Rudder Servo.");
	rudder_servo_.attach(pin);
	setAngle(0);
}

void Rudder::setAngle(float angle) {
	//confine rudder angle to max range
	angle_ = angle > RUDDER_ANGLE_MAX ? RUDDER_ANGLE_MAX : (angle < -RUDDER_ANGLE_MAX ? -RUDDER_ANGLE_MAX : angle);
	calculatePeriod();
	setPeriod(rudder_servo_period_);
}

void Rudder::setPeriod(int period) {
	rudder_servo_.writeMicroseconds(period);
}

float Rudder::getAngle() {
	return angle_;
}

void Rudder::debug(String msg) {
	Serial.println(msg);
}

void Rudder::calculatePeriod() {
	rudder_servo_period_ = RUDDER_PERIOD_NEUTRAL + (((angle_ + RUDDER_ANGLE_NEUTRAL)/RUDDER_ANGLE_RANGE) * RUDDER_PERIOD_NEUTRAL/2);
}
