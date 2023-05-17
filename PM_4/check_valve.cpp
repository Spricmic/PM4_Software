#include "Laser.h"
#include "pins_setup.h"

extern const int VALVE_PIN;

void open_checkvalve() {
  //This function open the check valve to let fluid flow
  Serial.println("open checkvalve");
  digitalWrite(VALVE_PIN,HIGH);
}

void close_checkvalve() {
  //This function close check valve to stop fluid from flowing through
  Serial.println("close checkvalve");
  digitalWrite(VALVE_PIN,LOW);
}