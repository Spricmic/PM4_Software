#include "color_sensor.h"

// define colorsensor initalize as lightsensor
Adafruit_AS7341 lightsensor;

void setup_color_sensor() {
  // initialize the AS7341 sensor
  Serial.begin(115200);
  if (!lightsensor.begin()) {
    Serial.println("Could not find a valid AS7341 sensor, check wiring!");
    while (1) { delay(10); }
  }

  // configure the sensor for calibrated RGB output
  lightsensor.setATIME(100);
  lightsensor.setASTEP(999);
  lightsensor.setGain(AS7341_GAIN_256X);
}

int read_color_sensor() {
  // Read all channels at the same time and store in as7341 object
  if (!lightsensor.readAllChannels()){
    Serial.println("Error reading all channels!");
    return 0; //TODO extend function to give back the dessired values
  }

  // Print out the stored values for each channel
  Serial.print("F1 415nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_415nm_F1));
  Serial.print("F2 445nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_445nm_F2));
  Serial.print("F3 480nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_480nm_F3));
  Serial.print("F4 515nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_515nm_F4));
  Serial.print("F5 555nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_555nm_F5));
  Serial.print("F6 590nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_590nm_F6));
  Serial.print("F7 630nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_630nm_F7));
  Serial.print("F8 680nm : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_680nm_F8));

  Serial.print("Clear    : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_CLEAR));

  Serial.print("Near IR  : ");
  Serial.println(lightsensor.getChannel(AS7341_CHANNEL_NIR));

  Serial.println("");
}

result analyze_data(int color_sensor_reading) {
  // check what is positive / negative / error
  result test_result = READY;
  return test_result;
}