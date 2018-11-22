#include "motor.h"
#include "rudder.h"
#include "pins.h"
#include "gps.h"

#define GPSSERIAL Serial1

Motor motor;
Rudder rudder;
GPS gps;

// GPS code
// =========================================

char tmp;
char NMEAbuf[82];
char NMEAbuf_pointer = 0;

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Starting...");

  motor.begin(MOTOR_ESC_PIN);
  rudder.begin(RUDDER_SERVO_PIN);
  gps.begin();

  GPSSERIAL.begin(115200, SERIAL_8N1);

}

void loop() {
  motor.setSpeed(1);
  Serial.println("Motor on");
  delay(2500);
  motor.setSpeed(0);
  Serial.println("Motor off");
  delay(1000);
  rudder.setAngle(25);
  Serial.println("Rudder angle +10 degrees");
  delay(1000);
  rudder.setAngle(-25);
  Serial.println("Rudder angle -10 degrees");
  delay(1000);
  rudder.setAngle(0);
}

void serialEvent1() {
  while(GPSSERIAL.available()) {
    if((NMEAbuf[NMEAbuf_pointer++] = GPSSERIAL.read()) == '\n') {
      Serial.print("Message: ");
      Serial.println(NMEAbuf);
      gps.parseNMEA(NMEAbuf);
      NMEAbuf_pointer = 0;
    }
  }
}
