#include "led.h"

// Define LED pins
extern const int START_SWITCH_PIN;
extern const int GREEN_LED_PIN;
extern const int YELLOW_LED_PIN;
extern const int RED_LED_PIN;

/**
* This function writes turns on LED depending on the state of the system.
* @param result positiv or negativ result of the analysis in the reaction chamber.
*/
void write_to_led(result r){
  switch (r) {
    case READY:
      write_ready();
      break;
    case NEGATIVE:
      write_negative();
      break;
    case POSITIVE:
      write_positive();
      break;
    case SOMETHING:
      write_do_something();
      break;
    case WORKING:
      write_work_inprogress();
      break;
    case FAIL:
      write_fail();
      break;
    default:
      break;
  }
}


/**
* turns on green signal to show that the device is ready.
*/
void write_ready(){
  //while (digitalRead(START_SWITCH_PIN) == LOW){
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  //}
}


/**
* green led starts blinking to show negativ result
*/
void write_negative(){
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  //while (digitalRead(START_SWITCH_PIN) == LOW){
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(500);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(500);
  //}
}


/**
* red led starts blinking to show negativ result
*/
void write_positive(){
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  //while (digitalRead(START_SWITCH_PIN) == LOW){
    digitalWrite(RED_LED_PIN, HIGH);
    delay(500);
    digitalWrite(RED_LED_PIN, LOW);
    delay(500);
  //}
}


/**
* yellow led starts blinking to signal, that some step need to be taken.
*/
void write_do_something(){
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  //while (digitalRead(START_SWITCH_PIN) == LOW){
    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(500);
    digitalWrite(YELLOW_LED_PIN, LOW);
    delay(500);
  //}
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
  Serial.println("wait for input function called");
  while (digitalRead(START_SWITCH_PIN) == LOW){
    delay(10);  // small delay to reduce CPU usage
    // wait for input
  }
  // wait until button has been released again.
  while (digitalRead(START_SWITCH_PIN) != LOW){
    delay(10);  // small delay to reduce CPU usage
    // wait for input
  }
}
