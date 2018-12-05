#include "motor.h"
#include "rudder.h"
#include "pins.h"
#include "rasPiSerial.h"
#include "gps.h"

#include <PulsePosition.h>

#define GPSSERIAL Serial1

Motor motor;
Rudder rudder;
GPS gps;

// GPS code
// =========================================

char tmp;
char NMEAbuf[82];
char Serialbuf[82];
int NMEAbuf_pointer = 0;
int Serialbuf_pointer = 0;
int rc_timeout;
RasPiSerial rasPiSerialInstance;
PulsePositionInput rc;
IntervalTimer RCTimer;


/**
 * Depending on the message contents, delegate responsibility
 * to the appropriate part of the system
 */
void delegateMessageResponsibility(RasPiMessage* message) {
  if(message->iCode == ICode::ERR){
    Serial.println("$ERR0RinInputMessage*");
    rasPiSerialInstance.messageQueue.pop();
    delete(message);
    return;
  }

  String outMessage = "";

  switch(message->id){

    case GPS_LATITUDE_ID: {
      if(message->iCode == ICode::SET){
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, GPS_LATITUDE_ID, "NA");
          Serial.println(outMessage);
      } else if(message->iCode == ICode::GET) {
        // get GPS latitude
        float latitude = gps.getLatitude();
        outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, GPS_LATITUDE_ID, String(latitude));
        Serial.println(outMessage);
      }
      break;
    }

    case GPS_LONGITUDE_ID: {
      if(message->iCode == ICode::SET){
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, GPS_LONGITUDE_ID, "NA");
          Serial.println(outMessage);
      } else if(message->iCode == ICode::GET) {
          // get GPS longitude
        float longitude = gps.getLongitude();
        outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, GPS_LONGITUDE_ID, String(longitude));
        Serial.println(outMessage);
      }
      break;
    }

    case BOAT_POWER_ID: {
      if(message->iCode == ICode::SET){
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, BOAT_POWER_ID, "NA");
          Serial.println(outMessage);
      } else if(message->iCode == ICode::GET) {
          // get boat power (Watts)
        outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, BOAT_POWER_ID, "NA");
        Serial.println(outMessage);
      }
      break;
    }

    case BATTERY_LEVEL_ID: {
      if(message->iCode == ICode::SET){
        outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, BATTERY_LEVEL_ID, "NA");
        Serial.println(outMessage);
      } else if(message->iCode == ICode::GET) {
          // get Battery level (percent)
        // not yet implemented
        outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, BATTERY_LEVEL_ID, "NA");
        Serial.println(outMessage);
      }
      break;
    }

    case MOTOR_TEMPERATURE_ID: {
      if(message->iCode == ICode::SET){
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, MOTOR_TEMPERATURE_ID, "NA");
          Serial.println(outMessage);
      } else if(message->iCode == ICode::GET) {
          // get Motor temperature (Kelvin)
        outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, MOTOR_TEMPERATURE_ID, "NA");
        Serial.println(outMessage);
      }
      break;
    }

    case BATTERY_VOLTAGE_ID: {
      if(message->iCode == ICode::SET){
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, BATTERY_VOLTAGE_ID, "NA");
          Serial.println(outMessage);
      } else if(message->iCode == ICode::GET) {
          // get Battery voltage
        outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, BATTERY_VOLTAGE_ID, "NA");
        Serial.println(outMessage);
      }
      break;
    }

    case MOTOR_POWER_PERCENT_ID: {
      if(message->iCode == ICode::SET){
        // set Motor power (percent)
        motor.setSpeed(message->messageBody.toFloat());
      } else if(message->iCode == ICode::GET) {
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, MOTOR_POWER_PERCENT_ID, "NA");
          Serial.println(outMessage);
      }
      break;
    }

    case RUDDER_ANGLE_ID: {
      if(message->iCode == ICode::SET){
        // set Rudder angle (degrees)
        float angle = message->messageBody.toFloat();
        rudder.setAngle(angle);
      } else if(message->iCode == ICode::GET) {
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, RUDDER_ANGLE_ID, "NA");
          Serial.println(outMessage);
      }
      break;
    }

    case RPM_ID: {
        if (message->iCode == ICode::SET) {
            outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, RPM_ID, "NA");
            Serial.println(outMessage);

        } else if (message->iCode == ICode::GET) {
            // get RPM
            outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, RPM_ID, "NA");
            Serial.println(outMessage);
        }
        break;
    }

    case GPS_HEADING_ID: {
        if (message->iCode == ICode::SET) {
            outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, GPS_HEADING_ID, "NA");
            Serial.println(outMessage);

        } else if (message->iCode == ICode::GET) {
            // get GPS heading
            float heading = gps.getHeading();
            outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, GPS_HEADING_ID, String(heading));
            Serial.println(outMessage);
        }
        break;
    }

    case GPS_SPEED_ID: {
      if (message->iCode == ICode::SET) {
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::ERR, GPS_SPEED_ID, "NA");
          Serial.println(outMessage);

      } else if (message->iCode == ICode::GET) {
          // get GPS speed
          float speed = gps.getSOG();
          outMessage = rasPiSerialInstance.buildOutMessage(ICode::VAL, GPS_SPEED_ID, String(speed));
          Serial.println(outMessage);
      }
      break;
    }

    default: Serial.println("Unknown componentID in the message"); break;
  }

  // dequeue the message from the queue and free the memory assigned to the message
  rasPiSerialInstance.messageQueue.pop();
  delete(message);
}

void updateControl() {
  rc_timeout++;
	int endChannel;
	if((endChannel = rc.available()) > 0) {
    rc_timeout = 0;

		if(rc.read(MANUAL_OVERRIDE_CHANNEL) > 1500) {
			motor.setPeriod(rc.read(MOTOR_CHANNEL));
			rudder.setPeriod(rc.read(RUDDER_CHANNEL));
		} else { //if in autonomous mode release motor and rudder from manual control
      motor.releasePeriod();
      rudder.releasePeriod();
		}

		rc.read(endChannel); //clear ppm buffer until next frame comes in.

	} else if(rc_timeout > 50) { //if rc reception is timed out return control to autonomous
    motor.releasePeriod();
    rudder.releasePeriod();
	}
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting...");

  rc.begin(INPUT_PPM_PIN);
  motor.begin(MOTOR_ESC_PIN);
  rudder.begin(RUDDER_SERVO_PIN);
  gps.begin();

  RCTimer.begin(updateControl, 1000*15);

  Serial.println("Components setup");
  Serial.clear();

  GPSSERIAL.begin(115200, SERIAL_8N1);

}

void loop() {
  if(!rasPiSerialInstance.messageQueue.isEmpty()){
    delegateMessageResponsibility(rasPiSerialInstance.messageQueue.front());
  }
}

void serialEvent() {
  while(Serial.available()) {
	  if((Serialbuf[Serialbuf_pointer++] = Serial.read()) == '*') {
      String temp(Serialbuf);
		  rasPiSerialInstance.readSerial(temp.substring(0,Serialbuf_pointer));
		  Serialbuf_pointer = 0;
	  }
  }
}

void serialEvent1() {
  while(GPSSERIAL.available()) {
	  if((NMEAbuf[NMEAbuf_pointer++] = GPSSERIAL.read()) == '\n') {
      NMEAbuf[NMEAbuf_pointer] = '\0';
		 gps.parseNMEA(NMEAbuf);
		 NMEAbuf_pointer = 0;
	  }
  }
}
