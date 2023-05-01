#include <Wire.h>
#include "Adafruit_MPRLS.h"

// You dont *need* a reset and EOC pin for most uses, so we set to -1 and don't connect
#define RESET_PIN  -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN    -1  // set to any GPIO pin to read end-of-conversion by pin
Adafruit_MPRLS pressure_sensor = Adafruit_MPRLS(RESET_PIN, EOC_PIN);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!pressure_sensor.begin()) {
    Serial.print("Failed to communicate with MPRLS sensor, check wiring?");
    while (1) {
      delay(10);
    }
  }
  Serial.print("Found MPRLS sensor");
}


/** 
*This function read pressure from the pressure sensor
*@return pressure value in hPa
*/
float read_pressure_sensor() {
  Serial.print(pressure_sensor.readPressure());
  return pressure_sensor.readPressure()
} 

void loop() {
  // put your main code here, to run repeatedly:

}
