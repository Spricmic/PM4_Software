#include "pump.h"

void setupPump() {
  
  pinMode(PUMP_PIN, OUTPUT); // Set pumpPin as an output
  
}

void turn_on_pump(uint8_t speed) {
  
  // this function turn on the pump and control speed of the pump 
  analogWrite(PUMP_PIN, speed); // Set pump speed
  
}

void turn_off_pump() {
  // this function turn off the pump
  
  analogWrite(PUMP_PIN, 0); // Set pump speed

}
