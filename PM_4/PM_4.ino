#include "Laser.ino"
#include "pressure_sensor.ino"
#include "motor_valve.ino"
#include "LED.ino"
#include "color_sensor.ino"
#include "pump.ino"
#include "check_valve.ino"


extern void blink();


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
  read_light_sensor()
}


void washing(){

}


