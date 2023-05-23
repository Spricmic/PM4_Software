#include "pins_setup.h"
#include "Laser.h"
#include "led.h"
#include "pressure_sensor.h"
#include "motor_valve.h"
#include "color_sensor.h"
#include "pump.h"
#include "check_valve.h"
#include "test.h"
#include <Servo.h>
#include <Wire.h>


// enumerator to spezifie which part of the process to activate (for testing purposes).
typedef enum {
  FULL,
  TEST_FULL,
  LED,
  LASER,
  CHECK_VALVE,
  COLOR_SENSOR,
  MOTOR_VALVE,
  PUMP
} mode;


// define const
const mode choosen_mode = COLOR_SENSOR;  // defines in which mode the void loop runes for different testing setups
int state = 0;                    // keeps track of the State the process is in. see motor_valve.h enum fluid


void setup() {
  // put your setup code here, to run once:
  switch (choosen_mode) {
    case FULL:
      // Call function for FULL mode
      setup_pins();
      setup_color_sensor();
      motor_valve_setup();
      setupPump();
      break;
    case TEST_FULL:
      // Call function for the full process in test mode
      test_setup();
      break;
    case LED:
      // Call function for LED mode
      Serial.begin(115200);
      setup_pins();
      break;
    case LASER:
      // Call function for LASER mode
      Serial.begin(115200);
      setup_pins();
      break;
    case CHECK_VALVE:
      // Call function for CHECK_VALVE mode
      Serial.begin(115200);
      setup_pins();
      break;
    case COLOR_SENSOR:
      // Call function for COLOR_SENSOR mode
      setup_pins();
      setup_color_sensor();
      break;
    case MOTOR_VALVE:
      // Call function for MOTOR_VALVE mode
      setup_pins();
      motor_valve_setup();
      break;
    case PUMP:
      // Call function for PUMP mode
      setup_pins();
      Serial.begin(115200);
      setupPump();
      break;
    default:
      // Handle invalid mode
      break;
  }
}


void loop() {
  switch (choosen_mode) {
    case FULL:
      work_loop();
      break;
    case TEST_FULL:
      // Call function for the full process in test mode
      test_loop();
      break;
    case LED:
      LED_loop();
      break;
    case LASER:
      laser_loop();
      break;
    case CHECK_VALVE:
      check_valve_loop();
      break;
    case COLOR_SENSOR:
      color_sensor_loop();
      break;
    case MOTOR_VALVE:
      motor_valve_loop();
      break;
    case PUMP:
      pump_loop();
      break;
    default:
      // handle invalid mode
      break;
  }
}

void work_loop() {
  // put your main code here, to run repeatedly:
  switch (state) {
    // Air flush
    case 1:
      flush(AIR);
      delay(1000);
      state++;
      break;

    // Antigen
    case 2:
      flush(ANTIGEN);
      delay(1000);
      state++;
      break;

    // air
    case 3:
      flush(AIR);
      delay(1000);
      state++;
      break;

    // blood
    case 4:
      flush(BLOOD);
      delay(1000);
      state++;
      break;

    // washing
    case 5:
      flush(AIR);
      delay(1000);
      state++;
      break;

    //Rox
    case 6:
      flush(ROX);
      delay(1000);
      state++;
      break;

    //analysazion
    case 7:
      analysation();
      delay(1000);
      state++;
      break;

    //washing
    case 8:
      flush(WASHING);
      delay(1000);
      state++;
      break;

    // air
    case 9:
      flush(AIR);
      delay(1000);
      break;

    default:
      state = 1;
      break;
  }
}

/**
* loop to test the  functions.
*/
void LED_loop() {
  /*
  * The following function is for testing and debugging purposses only and should not run in the acctual ELISA Process.
  */
  Serial.println("!!! start Led loop !!!");
  Serial.println("READY");
  write_to_led(READY);
  delay(5000);

  Serial.println("NEGATIV");
  write_to_led(NEGATIVE);
  delay(5000);

  Serial.println("POSITIV");
  write_to_led(POSITIVE);
  delay(5000);

  Serial.println("SOMETHING");
  write_to_led(SOMETHING);
  delay(5000);

  Serial.println("WORKING");
  write_to_led(WORKING);
  delay(5000);

  Serial.println("FAIL");
  write_to_led(FAIL);
  delay(5000);
}


/**
* loop to test the laser functions.
*/
void laser_loop() {
  turn_on_laser();
  delay(5000);
  turn_off_laser();
  delay(5000);
}


/**
* loop to test the che checkvalve functions.
*/
void check_valve_loop() {
  open_checkvalve();
  delay(5000);
  close_checkvalve();
  delay(5000);
}


/**
* loop to test the color sensor functions.
*/
void color_sensor_loop() {
  // put your code to test the functions of color_sensor here.
  turn_on_laser();
  float red, green, blue = read_color_sensor();
  // print the RGB values to the serial monitor
  delay(1000);
}


/**
* loop to test the valve turning motor functions.
*/
void motor_valve_loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("AIR");
  //turn_distribution_valve(AIR);
  //delay(5000);

  Serial.println("ANTIGEN");
  turn_distribution_valve(ANTIGEN);
  delay(5000);

  Serial.println("BLOOD");
  //turn_distribution_valve(BLOOD);
  delay(5000);

  Serial.println("ROX");
  //turn_distribution_valve(ROX);
  delay(5000);

  Serial.println("WASHING");
  //turn_distribution_valve(WASHING);
  delay(5000);

  Serial.println("CLOSED");
  //turn_distribution_valve(CLOSED);
  delay(5000);
}


/**
* loop to test the pump functions.
*/
void pump_loop() {
  // put your main code here, to run repeatedly:
  turn_on_pump(255);  // set pump speed to 50%
}


void flush(fluid fluid_type) {
  if (fluid_type == BLOOD) {
    turn_distribution_valve(fluid_type);  //open the valve to recieve blood sample
    write_do_something();                 //sent signal to user to fill in blood sample
    turn_distribution_valve(CLOSED);      //close the valve to prevent backflow
  }

  else {
    turn_on_pump(255);
    delay(500);
    open_checkvalve();
    turn_distribution_valve(fluid_type);  //open distribution valve to let air flow
    delay(5000);                          //wait for the air to flow
    turn_off_pump();                      //stop the flow of the air
    turn_distribution_valve(CLOSED);      //close the distribution valve
    close_checkvalve();                   //close the valve after the reaction chamber
  }
}


/**
* function analyzes the fluorescent in the reaction chamber and 
* controlls the LED to show the result
*/
void analysation() {
  turn_on_laser();                          //turns on the green laser in the Reaction chamber
  delay(500);                               //delay to allow the Fluids to react and to emit light
  int data = read_color_sensor();           //reads the value of the AdaFruit lightsensor
  turn_off_laser();                         //turns off the green laser in the reaction chamber
  result result_type = analyze_data(data);  //converts data to "readable Values" those to make sense if the sample is positiv or negative
  write_to_led(result_type);                //converts positive negativ result to output on the LED
  wait_for_input();                         //waits until button is pushed to have enough time to read the value.
}
