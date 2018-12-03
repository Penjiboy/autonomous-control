#include "motor.h"

#define MOTOR_PERIOD_NEUTRAL 1000
#define MOTOR_PERIOD_RANGE 2000

void Motor::begin(int pin) {
	debug("Initializing Motor.");
  period_override_ = 0;
	esc_.attach(pin);
	setSpeed(0);
}

void Motor::setSpeed(float speed) {
	speed_ = speed > 1 ? 1 : (speed < -1 ? -1 : speed);
	calculatePeriod();
	if(!period_override_) esc_.writeMicroseconds(esc_period_);
}

void Motor::setPeriod(int period) {
	esc_.writeMicroseconds(period);
  period_override_ = 1;
}

void Motor::releasePeriod() {
  period_override_ = 0;
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
