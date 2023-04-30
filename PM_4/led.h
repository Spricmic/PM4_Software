#ifndef LED_H
#define LED_H

#include <Arduino.h>

// define an enum 
typedef enum{
  READY,
  NEGATIVE,
  POSITIVE,
  SOMETHING,
  WORKING,
  FAIL
}result;


// takes an input and writes a corrresponding signal to the led
void write_to_led(result input);

// turns on green signal to show that the device is ready.
void write_ready();

// green led starts blinking to show negativ result
void write_negativ();

// yellow led starts blinking to signal, that some step need to be taken.
void write_positiv();

// Turn off all LEDs
void write_do_something();

// yellow light is constantly on to show that the system is progressing
void write_work_inprogress()

// turn on all the lights to signal a malfunction.
void write_fail()

// waits for button input until programm is continued.
void wait_for_input()

#endif