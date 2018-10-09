#include "motor.h"
#include "rudder.h"
#include "pins.h"
#include "rasPiSerial.h"

//#define GPSSERIAL Serial1

Motor motor;
Rudder rudder;

// GPS code
// =========================================

char tmp;
char NMEAbuf[82];
//char NMEAbuf = 0;

RasPiSerial* rasPiSerialInstance;

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Starting...");

  rasPiSerialInstance = new RasPiSerial();

  motor.begin(MOTOR_ESC_PIN);
  rudder.begin(RUDDER_SERVO_PIN);

  //GPSSERIAL.begin(115200, SERIAL_8N1);

}

void loop() {
  if(!rasPiSerialInstance->messageQueue.isEmpty()){
    delegateMessageResponsibility(rasPiSerialInstance->messageQueue.front());
  }
  delay(2500);

  Serial.println("loop iteration");
}

void serialEvent1() {
  // while(GPSSERIAL.available()) {
  //   if(NMEAbuf[NMEAbuf_pointer++] = GPSSERIAL.read())
  //     parseNMEA();
  // }
}

void serialEvent() {
  Serial.println("serialEvent");
  if(Serial.available()) {
    rasPiSerialInstance->readSerial(Serial.readString());
  }
}

void parseNMEA() {
  // sscanf(NMEAbuf, "%[$!]%2s%3s%*[^*]*%2x", start_delimiter, message_talker, message_id, checksum);

  // switch(message_id) {
  //   case "GLL": sscanf(NMEAbuf, "$GPGLL%lf,%c,%lf,%c,%2i%2i%5f,%*[AV],%c*%x",); break; //read NMEA 0183 GLL string
  //   default:
  // }
}

/**
 * Depending on the message contents, delegate responsibility
 * to the appropriate part of the system
 */
void delegateMessageResponsibility(RasPiMessage* message){
  if(message->iCode == ICode::ERR){
    Serial.println("Error in input message");
    rasPiSerialInstance->messageQueue.pop();
    delete(message);
    return;
  }

  switch(message->id){

    case GPS_LATITUDE_ID: {
      if(message->iCode == ICode::SET){
        // set GPS latitude
        Serial.println("Setting GPS latitude not yet implemented");
      } else if(message->iCode == ICode::GET) {
        // get GPS latitude
        Serial.println("Getting GPS latitude not yet implemented");
      }
      break;
    }

    case GPS_LONGITUDE_ID: {
      if(message->iCode == ICode::SET){
        // set GPS longitude
        Serial.println("Setting GPS longitude not yet implemented");
      } else if(message->iCode == ICode::GET) {
          // get GPS longitude
        Serial.println("Getting GPS longitude not yet implemented");
      }
      break;
    }

    case MOTOR_POWER_WATTS_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Motor power (watts)");
      } else if(message->iCode == ICode::GET) {
          // get Motor power (Watts)
        Serial.println("Getting Motor power (Watts) not yet implemented");
      }
      break;
    }

    case BATTERY_LEVEL_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Battery level (percent)");
      } else if(message->iCode == ICode::GET) {
          // get Battery level (percent)
        Serial.println("Getting Battery level (percent) not yet implemented");
      }
      break;
    }

    case MOTOR_TEMPERATURE_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Motor temperature (Kelvin)");
      } else if(message->iCode == ICode::GET) {
          // get Motor temperature (Kelvin)
        Serial.println("Getting Motor temperature (Kelvin) not yet implemented");
      }
      break;
    }

    case BATTERY_VOLTAGE_ID: {
      if(message->iCode == ICode::SET){
        Serial.println("Can't set Battery volatage");
      } else if(message->iCode == ICode::GET) {
          // get Battery voltage
        Serial.println("Getting Battery voltage not yet implemented");
      }
      break;
    }

    case MOTOR_POWER_PERCENT_ID: {
      if(message->iCode == ICode::SET){
        // set Motor power (percent)
        Serial.println("Setting Motor power (percent) not yet implemented");
      } else if(message->iCode == ICode::GET) {
        Serial.println("Shouldn't have to get Motor power (percent)");
      }
      break;
    }

    case RUDDER_ANGLE_ID: {
      if(message->iCode == ICode::SET){
        // set Rudder angle (degrees)
        Serial.println("Setting Rudder angle (degrees) not yet implemented");
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
