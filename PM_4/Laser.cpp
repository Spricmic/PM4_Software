#include "Laser.h"
#include <Arduino.h>

extern const int LASER_DIODE_PIN;
extern const int LASER_DIODE_OUTPUT_MODE;

void turn_on_laser(){
  digitalWrite(LASER_DIODE_PIN, HIGH);
}

void turn_off_laser(){
  digitalWrite(LASER_DIODE_PIN, LOW);
}