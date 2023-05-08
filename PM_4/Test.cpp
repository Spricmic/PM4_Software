#include "Test.h"


void setup() {
// put your setup code here, to run once:
  setup_pins();
  pressure_sensor_setup();
  setup_color_sensor();
  setupPump();
}

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
    flush(AIR);
    state = 1;
    break;

  default:
    state = 1;
    break;
  }
}

void flush(fluid fluid_type){
  if (fluid_type == BLOOD){
    turn_distribution_valve(fluid_type);          //open the valve to recieve blood sample
    delay(3000);                                  // check if the valve is turned
    write_do_something();                        //sent signal to user to fill in blood sample
    turn_distribution_valve(CLOSED);              //close the valve to prevent backflow
  }

  else{
    float pressure = read_pressure_sensor();       //Read pressure value from the prssure sensor
    println(pressure);
    if (pressure < MAX_PRESSURE) {                   //Check if the pressure is high enough
      turn_on_pump(128);                             //turn on the pump to gain pressure
      delay(3000);                                  //Check if pump is on
    
      while (pressure < MAX_PRESSURE) {             //wait until the pressure reaches the wanted value
        float pressure = read_pressure_sensor();
        println(pressure);
        delay(2000);
      }
    }
    
    open_checkvalve();
    delay(3000);                                  //Check if the checkvale is turned
    turn_distribution_valve(fluid_type);          //open distribution valve to let air flow
    delay(3000);                                  //wait for the air to flow
    turn_off_pump();                              //stop the flow of the air
    delay(3000);                                  //Check if the pump is off
    turn_distribution_valve(CLOSED);              //close the distribution valve
    delay(3000);                                  //Check if the valve is close
    close_checkvalve();                           //close the valve after the reaction chamber
    delay(3000);                                  //Check if the valve is close
  }
  
}


/**
* function analyzes the fluorescent in the reaction chamber and 
* controlls the LED to show the result
*/
void analysation(){
  turn_on_laser();                               //turns on the green laser in the Reaction chamber
  delay(3000);                                   //Check that the laser is turn on before the data is taken
  int data = read_color_sensor();                //reads the value of the AdaFruit lightsensor
  dalay(3000);                                   //Check if the data is read before the laser is off
  turn_off_laser();                             //turns off the green laser in the reaction chamber
  result result_type = analyze_data(data);               //converts data to "readable Values" those to make sense if the sample is positiv or negative 
  dalay(3000);                                    //ensure that the data is analysed before LED is on
  write_to_led(result_type);                     //converts positive negativ result to output on the LED 
  wait_for_input();                            //waits until button is pushed to have enough time to read the value.
}

