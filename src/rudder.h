#ifndef RUDDER_H
#define RUDDER_H

#include <cstdint>
#include <string>
#include "loghandle.h"
#include "servo.h"

using namespace std;

class Rudder {
public:
Rudder(LogHandle log, Servo servo);
Rudder(LogHandle log, Servo servo, float offset);

void setOffset(float offset);

float getCurrentAngle();

float getAngle();
int setAngle(float angle);

float getTorque();

private:
	LogHandle log_;
	Servo servo_;
	float angle_;
	float offset_;
};

#endif
