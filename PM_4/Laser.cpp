#include "Laser.h"
#include "pins_setup.h"

void laser_setup(){
  pinMode(LASER_DIODE_PIN, OUTPUT);
}

void turn_on_laser(){
  digitalWrite(LASER_DIODE_PIN, HIGH);
}

void turn_off_laser(){
  digitalWrite(LASER_DIODE_PIN, LOW);
}