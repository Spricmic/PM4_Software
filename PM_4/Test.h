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

extern const float MAX_PRESSURE;
extern int state;

void test_setup();
void test_loop();
void test_flush(fluid fluid_type);
void test_analysation();