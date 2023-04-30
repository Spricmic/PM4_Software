

const int LASER_DIODE_PIN = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_DIODE_PIN, OUTPUT);
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
  turn_on_laser()
  delay(500);
  turn_off_laser()
  delay(500);
}
