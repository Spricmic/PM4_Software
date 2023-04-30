#ifndef PINS_SETUP_H
#define PINS_SETUP_H

// Pin definitions
const int START_SWITCH_PIN = 5; // start button
const int GREEN_LED_PIN = 6;  // green led
const int YELLOW_LED_PIN = 7;  // yellow led
const int RED_LED_PIN = 8;  // red led
const int LASER_DIODE_PIN = 9;
const int VALVE_PIN = 10;
const int PUMP_PIN = 11;
const int SERVO_MOTOR_PIN = 12;

// Function prototypes
void setup_pins();

#endif
