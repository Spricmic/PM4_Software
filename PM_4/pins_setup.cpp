#include "pins_setup.h"
// Create a Servo object for the distribution valve motor
Servo Distribution_Valve_Motor;

void setup_pins() {
  // Set pin modes
  pinMode(START_SWITCH_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(LASER_DIODE_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  // Attach the servo motor to its pin
  Distribution_Valve_Motor.attach(SERVO_MOTOR_PIN);
}