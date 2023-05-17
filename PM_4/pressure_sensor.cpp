#include "pressure_sensor.h"

Adafruit_MPRLS pressure_sensor = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

/**
* creats the set up to use the pressure sensor.
*/
void pressure_sensor_setup(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!pressure_sensor.begin()) {
    Serial.print("Failed to communicate with MPRLS sensor, check wiring?");
    while (1) {
      delay(10);
    }
  }
  Serial.println("Found MPRLS sensor");
}



/** 
*This function read pressure from the pressure sensor
*@return pressure value in hPa
*/
float read_pressure_sensor() {
  Serial.print("Called from pressure_sensor.cpp pressure: ");
  Serial.println(pressure_sensor.readPressure());
  return pressure_sensor.readPressure();
} 