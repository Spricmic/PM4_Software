#include "led.h"
#include <Servo.h>
#include <Arduino.h>
#include "motor_valve.h"

// Define pins
extern const int SERVO_MOTOR_PIN;
Servo Distribution_Valve_Motor;

void motor_valve_setup() {
  Distribution_Valve_Motor.attach(SERVO_MOTOR_PIN);
  Serial.begin(9600);
}

/** 
*This function turns the distribution valve to the fluid channel
*@param choosen_fluid types of enumerator fluid that the distribution valve turn to
*/
void turn_distribution_valve(fluid choosen_fluid) { 
  float degree = convert_input_to_pwm(choosen_fluid);
  Distribution_Valve_Motor.write(degree);
  delay(15);
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
    return 20.0;  // value for: ANTIGEN
  }else if (state == BLOOD) {
    return 40.0;  // value for: BLOOD
  }else if (state == ROX) {
    return 60.0;  // value for: ROX
  }else if (state == WASHING) {
    return 80.0;  // value for: WASHING 
  }else if (state == CLOSED) {
    return 100.0;  // value for: CLOSED
  }
}
