#include "motor.h"
#include "rudder.h"
#include "pins.h"
#include "rasPiSerial.h"
#include "gps.h"

//#define GPSSERIAL Serial1

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
  delay(1000);
  Serial.println("Starting...");

  rasPiSerialInstance = new RasPiSerial();

  motor.begin(MOTOR_ESC_PIN);
  rudder.begin(RUDDER_SERVO_PIN);
  gps.begin();

   Serial.println("Components setup");
   Serial.clear();
   

  //GPSSERIAL.begin(115200, SERIAL_8N1);

}

void loop() {
  if(!rasPiSerialInstance->messageQueue.isEmpty()){
    delegateMessageResponsibility(rasPiSerialInstance->messageQueue.front());
  }
  delay(1500);
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

void serialEvent() {
  
  if(Serial.available()) {
    rasPiSerialInstance->readSerial(Serial.readString());
  }
  
  Serial.clear();
}

/**
 * Depending on the message contents, delegate responsibility
 * to the appropriate part of the system
 */
void delegateMessageResponsibility(RasPiMessage* message){  
  if(message->iCode == ICode::ERR){
    Serial.println("$ERR0RinInputMessage*");
    rasPiSerialInstance->messageQueue.pop();
    delete(message);
    return;
  }

  String outMessage = "";

  switch(message->id){

    case GPS_LATITUDE_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Cannot set GPS Latitude");
      } else if(message->iCode == ICode::GET) {
        // get GPS latitude
        float latitude = gps.getLatitude();
        outMessage = rasPiSerialInstance->buildOutMessage(ICode::VAL, 1, String(latitude));
        Serial.println(outMessage);
      }
      break;
    }

    case GPS_LONGITUDE_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Cannot set longitude");
      } else if(message->iCode == ICode::GET) {
          // get GPS longitude
        float longitude = gps.getLongitude();
        outMessage = rasPiSerialInstance->buildOutMessage(ICode::VAL, 2, String(longitude));
        Serial.println(outMessage);
      }
      break;
    }

    case MOTOR_POWER_WATTS_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Motor power (watts)");
      } else if(message->iCode == ICode::GET) {
          // get Motor power (Watts)
        Serial.println("Getting Motor power (Watts) not yet implemented, tempVal=5");
        outMessage = rasPiSerialInstance->buildOutMessage(ICode::VAL, 3, "5");
        Serial.println(outMessage);
      }
      break;
    }

    case BATTERY_LEVEL_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Battery level (percent)");
      } else if(message->iCode == ICode::GET) {
          // get Battery level (percent)
        Serial.println("Getting Battery level (percent) not yet implemented, tempVal=65");
        outMessage = rasPiSerialInstance->buildOutMessage(ICode::VAL, 4, "65");
        Serial.println(outMessage);
      }
      break;
    }

    case MOTOR_TEMPERATURE_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Motor temperature (Kelvin)");
      } else if(message->iCode == ICode::GET) {
          // get Motor temperature (Kelvin)
        Serial.println("Getting Motor temperature (Kelvin) not yet implemented, tempVal=130");
        outMessage = rasPiSerialInstance->buildOutMessage(ICode::VAL, 5, "130");
        Serial.println(outMessage);
      }
      break;
    }

    case BATTERY_VOLTAGE_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Battery volatage");
      } else if(message->iCode == ICode::GET) {
          // get Battery voltage
        Serial.println("Getting Battery voltage not yet implemented, tempVal=3.3");
        outMessage = rasPiSerialInstance->buildOutMessage(ICode::VAL, 6, "3.3");
        Serial.println(outMessage);
      }
      break;
    }

    case MOTOR_POWER_PERCENT_ID: {
      if(message->iCode == ICode::SET){
        // set Motor power (percent)
        motor.setSpeed(message->messageBody.toFloat());
      } else if(message->iCode == ICode::GET) {
        Serial.println("Shouldn't have to get Motor power (percent)");
      }
      break;
    }

    case RUDDER_ANGLE_ID: {
      if(message->iCode == ICode::SET){
        // set Rudder angle (degrees)
        float angle = message->messageBody.toFloat();
        rudder.setAngle(angle);
      } else if(message->iCode == ICode::GET) {
        Serial.println("Shouldn't have to get Rudder angle (degrees)");
      }
      break;
    }

    default: Serial.println("Unknown componentID in the message"); break;
  }

  // dequeue the message from the queue and free the memory assigned to the message
  rasPiSerialInstance->messageQueue.pop();
  delete(message);
}
