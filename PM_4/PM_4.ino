#include "Laser.ino"
#include "pressure_sensor.ino"
#include "motor_valve.ino"
#include "LED.ino"
#include "color_sensor.ino"
#include "pump.ino"
#include "check_valve.ino"
#include <Servo.h>
#include <Wire.h>

Servo Distribution_Valve_Motor;


extern void blink();


// declare an enumerator for the different fluid in the elisa process.
typedef enum {
  AIR = 0,
  ANTIGEN = 1,
  BLOOD = 2,
  ROX = 3,
  WASHING = 4
  CLOSED = 5
}fluid;


// declare Pin modes
const int START_SWITCH_PIN = 5; //start button
const int GREEN_LED_PIN = 6;  // green led
const int YELLOW_LED_PIN = 7;  // yellow led
const int RED_LED_PIN = 8;  // red led
const int LASER_DIODE_PIN = 9;
const int VALVE_PIN = 10;
const int PUMP_PIN = 11;
const int SERVO_MOTOR_PIN = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(START_SWITCH_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(LASER_DIODE_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  Distribution_Valve_Motor.attach(SERVO_MOTOR_PIN)
}


int state;

void loop() {
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
    flush(AIR)
    state = 1;
    break;

  default:
    state = 1;
    break;
  }
}


void flush(int fluid){
  if (fluid == BLOOD){
    turn_distribution_valve(fluid);               //open the valve to recieve blood sample
    start_filling_blood();                        //sent signal to user to fill in blood sample
    finished_filling_blood();                     //recieved a signal when the blood is filled into the device
    turn_distribution_valve(CLOSED);              //close the valve to prevent backflow
  }

  else{
    float pressure = read_pressure_sensor()       //Read pressure value from the prssure sensor
    IF pressure < "something" {                   //Check if the pressure is high enough
      turn_on_pump();                             //turn on the pump to gain pressure
    
      while pressure < "something" {              //wait until the pressure reaches the wanted value
        float pressure = read_pressure_sensor();
        delay(1000);
      }
    }
    
    open_checkvalve()
    turn_distribution_valve(fluid);               //open distribution valve to let air flow
    delay("some time")                            //wait for the air to flow
    turn_off_pump();                              //stop the flow of the air
    turn_distribution_valve(CLOSED);              //close the distribution valve
    close_checkvalve()                            //close the valve after the reaction chamber
  }
  
}


/**
* function analyzes the fluorescent in the reaction chamber and 
* controlls the LED to show the result
*/
void analysation(){
  turn_on_laser();                               //turns on the green laser in the Reaction chamber
  delay("some time");                            //delay to allow the Fluids to react and to emit light
  int data = read_color_sensor();                //reads the value of the AdaFruit lightsensor
  turn_off_laser();                             //turns off the green laser in the reaction chamber
  int result = analyze_data(data);               //converts data to "readable Values" those to make sense if the sample is positiv or negative 
  write_data_to_led(result);                     //converts positive negativ result to output on the LED 
  wait_button_push();                            //waits until button is pushed to have enough time to read the value.
}

