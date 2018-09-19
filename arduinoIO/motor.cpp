#include "motor.h"

#define MOTOR_PERIOD_NEUTRAL 1500
#define MOTOR_PERIOD_RANGE 1000

void Motor::begin(int pin) {
	debug("Initializing Motor.");
	esc_.attach(pin);
	setSpeed(0);
}

void Motor::setSpeed(float speed) {
	speed_ = speed > 1 ? 1 : (speed < -1 ? -1 : speed);
	calculatePeriod();
	esc_.writeMicroseconds(esc_period_);
}

float Motor::getSpeed() {
	return speed_;
}

void Motor::debug(String msg) {
	Serial.println(msg);
}

void Motor::calculatePeriod() {
	esc_period_ = MOTOR_PERIOD_NEUTRAL + (speed_ * MOTOR_PERIOD_RANGE/2);
}
