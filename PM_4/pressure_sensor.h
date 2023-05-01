#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <Wire.h>
#include "Adafruit_MPRLS.h"
#include <Arduino.h>

#define RESET_PIN  -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN    -1  // set to any GPIO pin to read end-of-conversion by pin

void pressure_sensor_setup();
float read_pressure_sensor();

#endif // PRESSURE_SENSOR_H