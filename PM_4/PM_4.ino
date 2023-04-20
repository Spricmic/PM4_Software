#include "Laser.ino"
#include "pressure_sensor.ino"
#include "motor_valve.ino"
#include "LED.ino"
#include "color_sensor.ino"
#include "pump.ino"
#include "check_valve.ino"


extern void blink();


// declare an enumerator for the different fluid in the elisa process.
typedef enum {
  AIR = 0,
  ANTIGEN = 1,
  BLOOD = 2,
  ROX = 3,
  WASHING = 4
}fluid;


void setup() {
  // put your setup code here, to run once:
}


int state;

void loop() {
  // put your main code here, to run repeatedly:
  switch (state)
  {
  // Air flush
  case 1:
    airflush();
    state ++;
    break;
  
  // Antigen
  case 2:
    antigenflush();
    state ++;
    break;

  // air
  case 3:
    airflush();
    state ++;
    break;

  // blood
  case 4:
    blood();
    state ++;
    break;

  // washing
  case 5:
    airflush();
    state ++;
    break;

  //Rox
  case 6:
    roxflush();
    state ++;
    break;

  //analysazion
  case 7:
    analysation();
    state ++;
    break;

  //washing
  case 8:
    washing();
    state ++;
    break;

  // air
  case 9:
    airflush()
    state = 1;
    break;

  default:
    state = 1;
    break;
  }

}

void airflush(){
  float pressure = read_pressure_sensor()       //Read pressure value from the prssure sensor
  IF pressure < "something" {                   //Check if the pressure is high enough
    turn_on_pump();                             //turn on the pump to gain pressure
    
    while pressure < "something" {              //wait until the pressure reaches the wanted value
      float pressure = read_pressure_sensor();
      delay(1000);
    }
  }
  open_checkvalve()                             //open valve after the reaction chamber to let air flow
  turn_distribution_valve("to air channel");    //open distribution valve to let air flow
  delay("some time")                            //wait for the air to flow
  turn_off_pump();                              //stop the flow of the air
  turn_distribution_valve("to off channel");    //close the distribution valve
  close_checkvalve()                            //close the valve after the reaction chamber
}


void antigenflush(){
  float pressure = read_pressure_sensor()       //Read pressure value from the prssure sensor
  IF pressure < "something" {                   //Check if the pressure is high enough
    turn_on_pump();                             //turn on the pump to gain pressure
    
    while pressure < "something" {              //wait until the pressure reaches the wanted value
      float pressure = read_pressure_sensor();
      delay(1000);
    }
  }
  open_checkvalve();                            //open valve after the reaction chamber to let air flow
  turn_distribution_valve("to antigen channel");//open distribution valve to let antigen flow
  delay("some time");                           //wait for the antigen to flow until it reaches reaction chamber
  turn_distribution_valve("to off channel");    //close the distribution valve
  close_checkvalve();                           //close the valve after the reaction chamber
  delay("some time")                            //lets the antigen sit for some time
}


void blood(){
  turn_distribution_valve("to blood channel");  //open the valve to recieve blood sample
  start_filling_blood();                        //sent signal to user to fill in blood sample
  finished_filling_blood();                     //recieved a signal when the blood is filled into the device
  turn_distribution_valve("to off channel");    //close the valve to prevent backflow
}


void roxflush(){
  float pressure = read_pressure_sensor()       //Read pressure value from the prssure sensor
  IF pressure < "something" {                   //Check if the pressure is high enough
    turn_on_pump();                             //turn on the pump to gain pressure
    
    while pressure < "something" {              //wait until the pressure reaches the wanted value
      float pressure = read_pressure_sensor();
      delay(1000);
    }
  }
  open_checkvalve();                            //open valve after the reaction chamber to let air flow
  turn_distribution_valve("to rox channel");    //open distribution valve to let rox flow
  delay("some time");                           //wait for the rox to flow until it reaches reaction chamber
  turn_distribution_valve("to off channel");    //close the distribution valve
  close_checkvalve();                           //close the valve after the reaction chamber
  delay("some time")                            //lets the rox sit for some time
}

// make description of the function
void analysation(){
  turn_on_laser()                               //turns on the green laser in the Reaction chamber
  delay("some time")                            //delay to allow the Fluids to react and to emit light
  int data = read_color_sensor()                //reads the value of the AdaFruit lightsensor
  turn_off_laser()                              //turns off the green laser in the reaction chamber
  int result = analyze_data(data)               //converts data to "readable Values" those to make sense if the sample is positiv or negative 
  write_data_to_led(result)                     //converts positive negativ result to output on the LED 
  wait_button_push()                            //waits until button is pushed to have enough time to read the value.
}


void washing(){
  float pressure = read_pressure_sensor()       //Read pressure value from the prssure sensor
  IF pressure < "something" {                   //Check if the pressure is high enough
    turn_on_pump();                             //turn on the pump to gain pressure
    
    while pressure < "something" {              //wait until the pressure reaches the wanted value
      float pressure = read_pressure_sensor();
      delay(1000);
    }
  }
  open_checkvalve()                             //open valve after the reaction chamber to let washing solution flow
  turn_distribution_valve("to washing channel");//open distribution valve to let washing solution flow
  delay("some time")                            //wait for the washing solution to flow
  turn_off_pump();                              //stop the flow of the washing solution
  turn_distribution_valve("to off channel");    //close the distribution valve
  close_checkvalve()                            //close the valve after the reaction chamber
}


