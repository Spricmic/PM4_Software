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

}


void antigenflush(){

}


void blood(){

}


void roxflush(){

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

}


 **this may not be a function cuz it iisnt 't related to any component