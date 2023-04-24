void setup() {
  // put your setup code here, to run once:
}

/**
* This Function turns on the laser
*/
void turn_on_laser(){
 digitalWrite(LASER_DIODE_PIN, HIGH)
}


/**
* This Function turns off the laser
*/
void turn_off_laser(){
  digitalWrite(LASER_DIODE_PIN, LOW)
}


void loop() {
  // Code for testing of the Laser functions
}
