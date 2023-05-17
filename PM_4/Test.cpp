#include "Test.h"


void test_setup() {
// put your setup code here, to run once:
  setup_pins();
  pressure_sensor_setup();
  setup_color_sensor();
  setupPump();
  motor_valve_setup();
}


void test_loop() {
  // put your main code here, to run repeatedly:
  Serial.print("state: ");
  Serial.println(state);
  switch (state)
  {
  // Air flush
  case 1:
    
    test_flush(AIR);
    wait_for_input();
    state ++;
    break;
  
  // Antigen
  case 2:
    test_flush(ANTIGEN);
    wait_for_input();
    state ++;
    break;

  // air
  case 3:
    test_flush(AIR);
    wait_for_input();
    state ++;
    break;

  // blood
  case 4:
    test_flush(BLOOD);
    wait_for_input();
    state ++;
    break;

  // washing
  case 5:
    test_flush(AIR);
    wait_for_input();
    state ++;
    break;

  //Rox
  case 6:
    test_flush(ROX);
    wait_for_input();
    state ++;
    break;

  //analysazion
  case 7:
    test_analysation();
    wait_for_input();
    state ++;
    break;

  //washing
  case 8:
    test_flush(WASHING);
    wait_for_input();
    state ++;
    break;

  // air
  case 9:
    test_flush(AIR);
    wait_for_input();
    state = 1;
    break;

  default:
    Serial.println("!!! default case !!!");
    state = 1;
    break;
  }
}


void test_flush(fluid fluid_type){
  if (fluid_type == BLOOD){
    turn_distribution_valve(fluid_type);          //open the valve to recieve blood sample
    delay(3000);                                  // check if the valve is turned
    write_do_something();                        //sent signal to user to fill in blood sample waits till button is presed.
    turn_distribution_valve(CLOSED);              //close the valve to prevent backflow
  }

  else{
    float pressure = read_pressure_sensor();       //Read pressure value from the prssure sensor
    if (pressure < MAX_PRESSURE) {                   //Check if the pressure is high enough
      turn_on_pump(128);                             //turn on the pump to gain pressure
      delay(3000);                                  //Check if pump is on
    
      while (pressure < MAX_PRESSURE) {             //wait until the pressure reaches the wanted value
        float pressure = read_pressure_sensor();
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
void test_analysation(){
  turn_on_laser();                               //turns on the green laser in the Reaction chamber
  delay(3000);                                   //Check that the laser is turn on before the data is taken
  int data = read_color_sensor();                //reads the value of the AdaFruit lightsensor
  delay(3000);                                   //Check if the data is read before the laser is off
  turn_off_laser();                             //turns off the green laser in the reaction chamber
  result result_type = analyze_data(data);        //converts data to "readable Values" those to make sense if the sample is positiv or negative 
  delay(3000);                                    //ensure that the data is analysed before LED is on
  write_to_led(result_type);                     //converts positive negativ result to output on the LED 
  wait_for_input();                            //waits until button is pushed to have enough time to read the value.
}

