const int START_SWITCH_PIN = 5; // button
const int GREEN_LED_PIN = 6;  // green led
const int YELLOW_LED_PIN = 7;  // yellow led
const int RED_LED_PIN = 8;  // red led


enum Result {
  READY,
  NEGATIVE,
  POSITIVE,
  SOMETHING,
  WORKING,
  FAIL
};


void setup() {
  // put your setup code here, to run once:
  pinMode(START_SWITCH_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}


/**
* This function writes turns on LED depending on the state of the system.
* @param result positiv or negativ result of the analysis in the reaction chamber.
*/
void write_to_led(int result){
  if (result == READY){
    write_ready();
  }
  else if(result == NEGATIV){
    write_negative();
  }
  else if (result == POSITIV){
    write_positive();
  }
  else if (result == SOMETHING){
    write_do_something();
  }
  else if (result == WORKING){
    write_work_inprogress();
  }
  else{
    write_fail();
  }
}


/**
* turns on green signal to show that the device is ready.
*/
void write_ready(){
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}


/**
* green led starts blinking to show negativ result
*/
void write_negativ(){
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  delay(500);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(500);
}


/**
* red led starts blinking to show negativ result
*/
void write_positiv(){
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(500);
  digitalWrite(RED_LED_PIN, LOW);
  delay(500);
}


/**
* yellow led starts blinking to signal, that some step need to be taken.
*/
void write_do_something(){
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  delay(500);
  digitalWrite(YELLOW_LED_PIN, LOW);
  delay(500);
  wait_for_input();
}


/**
* yellow light is constantly on to show that the system is progressing
*/
void write_work_inprogress(){
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
}


/**
* turn on all the lights to signal a malfunction.
*/
void write_fail(){
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
}

/**
* waits for button input until programm is continued.
*/
void wait_for_input(){
  while (digitalRead(START_SWITCH_PIN) == 0){
    // wait for input
  }
}


void loop() {
  // put your main code here, to run repeatedly:

  /*
  * The following function is for testing and debugging porposses only and should not run in the acctual ELISA Process.
  */
  wait_for_input();
  write_to_led(READY);

  wait_for_input();
  write_to_led(NEGATIVE);

  wait_for_input();
  write_to_led(POSITIVE);

  wait_for_input();
  write_to_led(SOMETHING);

  wait_for_input();
  write_to_led(WORKING);

  wait_for_input();
  write_to_led(FAIL);

}
