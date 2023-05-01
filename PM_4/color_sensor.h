#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Wire.h>
#include <Adafruit_AS7341.h>
#include <Arduino.h>
#include "led.h"

// define colorsensor initalize as lightsensor
extern Adafruit_AS7341 lightsensor;

void setup_color_sensor();
int read_color_sensor();
result analyze_data(int color_sensor_reading);

#endif // COLOR_SENSOR_H