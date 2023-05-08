#include "pins_setup.h"
#include "Laser.h"
#include "led.h"
#include "pressure_sensor.h"
#include "motor_valve.h"
#include "color_sensor.h"
#include "pump.h"
#include "check_valve.h"
#include <Servo.h>
#include <Wire.h>


const float MAX_PRESSURE = 10.0; // input max pressure


void setup();
void loop();
void flush(fluid fluid_type);
void analysation();