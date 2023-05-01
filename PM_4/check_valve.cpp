#include "Laser.h"
#include "pins_setup.h"

extern const int VALVE_PIN;

void open_checkvalve() {
  //This function open the check valve to let fluid flow
  digitalWrite(VALVE_PIN,HIGH);
}

void close_checkvalve() {
  //This function close check valve to stop fluid from flowing through
  digitalWrite(VALVE_PIN,LOW);
}