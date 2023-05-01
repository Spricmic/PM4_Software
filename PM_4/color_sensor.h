#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Wire.h>
#include <Adafruit_AS7341.h>
#include <Arduino.h>

// define colorsensor initalize as lightsensor
extern Adafruit_AS7341 lightsensor;

void setup_color_sensor();
int read_color_sensor();
int analyze_data(int result);

#endif // COLOR_SENSOR_H