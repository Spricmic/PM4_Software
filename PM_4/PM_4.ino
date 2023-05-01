#include "pins_setup.h"
#include "Laser.h"
#include "led.h"
#include "pressure_sensor.h"
#include "motor_valve.h"
#include "color_sensor.h"
#include "pump.h"
#include "check_valve.h"
#include <Servo.h>
#include <Wire.h>


// define const
const float MAX_PRESSURE = 10.0; // input max pressure



// enumerator to spezifie which part of the process to activate.
typedef enum {
  FULL,
  LED,
  LASER,
  CHECK_VALVE,
  COLOR_SENSOR,
  MOTOR_VALVE,
  PRESSURE_SENSOR,
  PUMP
}mode;

void setup() {
  // put your setup code here, to run once:
  setup_pins();
  pressure_sensor_setup();
  setupPump();
}


int state;
int choosen_mode = LED;  // defines in which mode the void loop runes for different testing setups


void loop(){
  if (choosen_mode == FULL) {
  work_loop();
} else if (choosen_mode == LED) {
  LED_loop();
} else if (choosen_mode == LASER) {
  laser_loop();
} else if (choosen_mode == CHECK_VALVE) {
  check_valve_loop();
} else if (choosen_mode == COLOR_SENSOR) {
  color_sensor_loop();
} else if (choosen_mode == MOTOR_VALVE) {
  motor_valve_loop();
} else if (choosen_mode == PRESSURE_SENSOR) {
  pressure_sensor_loop();
} else if (choosen_mode == PUMP) {
  pump_loop();
} else {
  // handle invalid mode
  
}

}

void work_loop() {
  // put your main code here, to run repeatedly:
  switch (state)
  {
  // Air flush
  case 1:
    flush(AIR);
    state ++;
    break;
  
  // Antigen
  case 2:
    flush(ANTIGEN);
    state ++;
    break;

  // air
  case 3:
    flush(AIR);
    state ++;
    break;

  // blood
  case 4:
    flush(BLOOD);
    state ++;
    break;

  // washing
  case 5:
    flush(AIR);
    state ++;
    break;

  //Rox
  case 6:
    flush(ROX);
    state ++;
    break;

  //analysazion
  case 7:
    analysation();
    state ++;
    break;

  //washing
  case 8:
    flush(WASHING);
    state ++;
    break;

  // air
  case 9:
    flush(AIR);
    state = 1;
    break;

  default:
    state = 1;
    break;
  }
}

/**
* loop to test the  functions.
*/
void LED_loop(){
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


/**
* loop to test the laser functions.
*/
void laser_loop(){
  turn_on_laser();
  delay(500);
  turn_off_laser();
  delay(500);
}


/**
* loop to test the laser functions.
*/
void check_valve_loop(){
  open_checkvalve();
  delay(10000);
  close_checkvalve();
}


/**
* loop to test the laser functions.
*/
void color_sensor_loop(){
  // put your code to test the functions of color_sensor here.
  float red, green, blue = read_color_sensor();
  // print the RGB values to the serial monitor
  Serial.print("Red:   ");
  Serial.println(red);
  Serial.print("Green: ");
  Serial.println(green);
  Serial.print("Blue:  ");
  Serial.println(blue);
  delay(500);
}


/**
* loop to test the laser functions.
*/
void motor_valve_loop(){
  // put your main code here, to run repeatedly:
  turn_distribution_valve(AIR);
  delay(1000);
  turn_distribution_valve(ANTIGEN);
  delay(2000);
}


/**
* loop to test the laser functions.
*/
void pressure_sensor_loop(){
  float pressure_hPa = read_pressure_sensor();
  Serial.print("Pressure (hPa): "); Serial.println(pressure_hPa);
  Serial.print("Pressure (PSI): "); Serial.println(pressure_hPa / 68.947572932);
  delay(1000);
}


/**
* loop to test the laser functions.
*/
void pump_loop(){
  // put your main code here, to run repeatedly:
  turn_on_pump(128); // set pump speed to 50%
  delay(5000);
  turn_off_pump();
  delay(5000);
}


void flush(fluid fluid_type){
  if (fluid_type == BLOOD){
    turn_distribution_valve(fluid_type);          //open the valve to recieve blood sample
    write_do_something();                        //sent signal to user to fill in blood sample
    turn_distribution_valve(CLOSED);              //close the valve to prevent backflow
  }

  else{
    float pressure = read_pressure_sensor();       //Read pressure value from the prssure sensor
    if (pressure < MAX_PRESSURE) {                   //Check if the pressure is high enough
      turn_on_pump(128);                             //turn on the pump to gain pressure
    
      while (pressure < MAX_PRESSURE) {              //wait until the pressure reaches the wanted value
        float pressure = read_pressure_sensor();
        delay(1000);
      }
    }
    
    open_checkvalve();
    turn_distribution_valve(fluid_type);               //open distribution valve to let air flow
    delay(50);                            //wait for the air to flow
    turn_off_pump();                              //stop the flow of the air
    turn_distribution_valve(CLOSED);              //close the distribution valve
    close_checkvalve();                            //close the valve after the reaction chamber
  }
  
}


/**
* function analyzes the fluorescent in the reaction chamber and 
* controlls the LED to show the result
*/
void analysation(){
  turn_on_laser();                               //turns on the green laser in the Reaction chamber
  delay(50);                            //delay to allow the Fluids to react and to emit light
  int data = read_color_sensor();                //reads the value of the AdaFruit lightsensor
  turn_off_laser();                             //turns off the green laser in the reaction chamber
  result result_type = analyze_data(data);               //converts data to "readable Values" those to make sense if the sample is positiv or negative 
  write_to_led(result_type);                     //converts positive negativ result to output on the LED 
  wait_for_input();                            //waits until button is pushed to have enough time to read the value.
}

