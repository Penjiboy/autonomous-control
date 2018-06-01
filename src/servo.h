#ifndef SERVO_H
#define SERVO_H

#include <cstdint>
#include <string>
#include "loghandle.h"

using namespace std;

class Servo {
public:
	Servo(LogHandle log, int channel);

	int setAngle(float angle);

private:
	LogHandle log_;
	int channel_;
};

#endif
