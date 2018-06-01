#include "rudder.h"

Rudder::Rudder(LogHandle log, Servo servo) {
	Rudder(log, servo, 0);
}

Rudder::Rudder(LogHandle log, Servo servo, float offset) {
	log_ = log;
	servo_ = servo;
	offset_ = offset;
	angle_ = 0;
}

void Rudder::setOffset(float offset) {
	offset_ = offset;
}

int Rudder::setAngle(float angle) {
	int err;
	angle_ = angle;
	if((err = servo_.setAngle(angle_ + offset_)))
		log_.err("Unable to change servo angle to " + (string)(angle_ + offset_) + ". Error " + (string)err + ".");
	return 0;
}

float Rudder::getAngle() {
	return angle_;
}

float Rudder::getCurrentAngle() {
	return angle_ + offset_;
}

float Rudder::getTorque() {
	return 0;
}
