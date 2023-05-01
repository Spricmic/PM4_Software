#include "led.h"
#include <Arduino.h>
#include "motor_valve.h"

// Define pins
extern const int SERVO_MOTOR_PIN;
Servo Distribution_Valve_Motor;

void setup() {
  pinMode(SERVO_MOTOR_PIN, OUTPUT);
  Distribution_Valve_Motor.attach(SERVO_MOTOR_PIN);
}

/** 
*This function turns the distribution valve to the fluid channel
*@param state types of enumerator fluid that the distribution valve turn to
*/
void turn_distribution_valve(fluid state) { 
  int degree = convert_input_to_pwm(state);
  Distribution_Valve_Motor.write(degree);
}

/** 
*This function converts the enummerator of the fluid to angle that the distribution valve should turn 
*@param state types of enumerator fluid that the distribution valve turn to
*@return angle of that the motor need to turn to
*/
float convert_input_to_pwm(fluid state) {
  if (state == AIR) {
    return 0.0;  // value for: AIR
  }else if (state == ANTIGEN) {
    return 0.0;  // value for: ANTIGEN
  }else if (state == BLOOD) {
    return 0.0;  // value for: BLOOD
  }else if (state == ROX) {
    return 0.0;  // value for: ROX
  }else if (state == WASHING) {
    return 0.0;  // value for: WASHING 
  }else if (state == CLOSED) {
    return 0.0;  // value for: CLOSED
  }
}
