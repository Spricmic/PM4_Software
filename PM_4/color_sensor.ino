#include <Wire.h>

// define device address of pressure sensor and color sensor
const int COLOR_ADDRESS = 0x00;

void setup() {
  Wire.begin();
  // put your setup code here, to run once:
  
}

/**
*This function reads the data from the Adafruit sensor in the raction chamber.
* @return raw data from the color sensor
*/
int read_color_sensor(){
  Wire.beginTransmission(DEVICE_ADDRESS); // start communication with device
  Wire.write(0x00); // set register address to read from
  Wire.endTransmission(); // end transmission

  Wire.requestFrom(DEVICE_ADDRESS, 1); // request 1 byte of data from device

  if (Wire.available()) {
    byte data = Wire.read(); // read the received data
    // process the data as needed
  }
return data
}


/**
* This function converts the read data from the colorsensor into a positiv / negativ
* and returns a int value depending on the result.
* @param data data read from the colorsensor.
*/
int analyze_data(int data){

  return result
}

void loop() {
  // put your code to test the functions of color_sensor here.

}
