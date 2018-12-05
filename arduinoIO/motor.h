#ifndef MOTOR_H
#define MOTOR_H

using namespace std;

#include <Servo.h>
#include <Arduino.h>

class Motor {
	float speed_;
	int esc_period_;
  int period_override_;
	Servo esc_;
public:
  void begin(int pin);

  void setSpeed(float speed);
  void setPeriod(int period);
  void releasePeriod();
  float getSpeed();
private:
  void debug(String msg);
  void calculatePeriod();
};
#endif
