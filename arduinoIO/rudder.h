#ifndef RUDDER_H
#define RUDDER_H

#include <Servo.h>
#include <Arduino.h>

class Rudder {
	float angle_;
	int rudder_servo_period_;
	Servo rudder_servo_;
public:
  void begin(int pin);

  void setAngle(float speed);
  float getAngle();
private:
  void debug(String msg);
  void calculatePeriod();
};
#endif
