#include <Wire.h>
#include <Adafruit_AS7341.h>
// import adafruit ad7341 with library manager


// define colorsensor initalize as lightsensor
Adafruit_AS7341 lightsensor;

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  // initialize the AS7341 sensor
  if (!lightsensor.begin()) {
    Serial.println("Could not find a valid AS7341 sensor, check wiring!");
    while (1);
  }

  // configure the sensor for calibrated RGB output
  lightsensor.setMeasurementMode(AS7341_MEAS_MODE_2);
  
}

/**
*This function reads the data from the Adafruit sensor in the raction chamber.
* @return raw data from the color sensor
*/
int read_color_sensor(){
  float red, green, blue;
  lightsensor.getCalibratedRed(&red);
  lightsensor.getCalibratedGreen(&green);
  lightsensor.getCalibratedBlue(&blue);
  return red, green, blue
}


/**
* This function converts the read data from the colorsensor into a positiv / negativ
* and returns a int value depending on the result.
* @param data data read from the colorsensor.
*/
int analyze_data(int data_red, data_green, data_blue){
  // check what is positiv / negativ / error
  return result
}

void loop() {
  // put your code to test the functions of color_sensor here.
  float red, green, blue = read_color_sensor()
  // print the RGB values to the serial monitor
  Serial.print("Red:   ");
  Serial.println(red);
  Serial.print("Green: ");
  Serial.println(green);
  Serial.print("Blue:  ");
  Serial.println(blue);
  delay(500);
}
