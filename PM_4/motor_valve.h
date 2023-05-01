#ifndef MOTOR_VALVE_H
#define MOTOR_VALVE_H

#include "led.h"
#include <Arduino.h>
#include <Servo.h>

// declare an enumerator for the different fluid in the elisa process.
typedef enum {
  AIR = 0,
  ANTIGEN = 1,
  BLOOD = 2,
  ROX = 3,
  WASHING = 4, 
  CLOSED = 5
}fluid;

// makes the setup for the motorvalve
void motorvalve_setup();

/** 
*This function turns the distribution valve to the fluid channel
*@param state types of enumerator fluid that the distribution valve turn to
*/
void turn_distribution_valve(fluid state);

/** 
*This function converts the enummerator of the fluid to angle that the distribution valve should turn 
*@param state types of enumerator fluid that the distribution valve turn to
*@return angle of that the motor need to turn to
*/
float convert_input_to_pwm(fluid state);

#endif