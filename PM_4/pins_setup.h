 #ifndef PINS_SETUP_H
#define PINS_SETUP_H

#include <Arduino.h>
#include <Servo.h>

// Pin definitions
const int START_SWITCH_PIN = 5; // start button
const int GREEN_LED_PIN = 6;  // green led
const int YELLOW_LED_PIN = 7;  // yellow led
const int RED_LED_PIN = 8;  // red led
const int LASER_DIODE_PIN = 9; // outputpin to controll the Laser
const int VALVE_PIN = 10;  // outputpin to controll the valve
const int PUMP_PIN = 11;  // output pin to controll the Pump with PWM
const int SERVO_MOTOR_PIN = 12;  // outputpin to controlle the Selected chanell with a servo.

// Function prototypes
void setup_pins();

#endif
