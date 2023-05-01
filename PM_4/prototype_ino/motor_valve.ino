
#include <Servo.h>

Servo Distribution_Valve_Motor

const int SERVO_MOTOR_PIN = 12;

// declare an enumerator for the different fluid in the elisa process.
typedef enum {
  AIR = 0,
  ANTIGEN = 1,
  BLOOD = 2,
  ROX = 3,
  WASHING = 4
  CLOSED = 5
}fluid;

void setup() {
  pinMode(SERVO_MOTOR_PIN, OUTPUT);
  Distribution_Valve_Motor.attach(SERVO_MOTOR_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  turn_distribution_valve(AIR);
  delay(1000)
  turn_distribution_valve(ANTIGEN);
  delay(2000)
}

/** 
*This function turns the distribution valve to the fluid channel
*@param state types of enumerator fluid that the distribution valve turn to
*/
void turn_distribution_valve(fluid state) { 
  int degree = convert_input_to_pwm(fluid state);
  Distribution_Valve_Motor.write(degree);
}

/** 
*This function converts the enummerator of the fluid to angle that the distribution valve should turn 
*@param state types of enumerator fluid that the distribution valve turn to
*@return angle of that the motor need to turn to
*/
float convert_input_to_pwm(fluid state) {
  if (state == AIR) {
    return "degree of motor to air channel";
  }else if (state == ANTIGENT) {
    return "degree of motor to antigent channel";
  }else if (state == BLOOD) {
    return "degree of motor to blood channel";
  }else if (state == ROX) {
    return "degree of motor to ROX channel";
  }else if (state == WASHING) {
    return "degree of motor to washing solution channel";
  }else if (state == CLOSED) {
    return "degree of motor to close channel";
  }
}