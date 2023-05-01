
const int PUMP_PIN = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(PUMP_PIN, OUTPUT); // Set pumpPin as an output
  analogWriteFrequency(PUMP_PIN, 1000); // Set PWM frequency to 1 kHz
}

void turn_on_pump() {
  // this function turn on the pump and control speed of the pump 
  analogWrite(PUMP_PIN,"wanted speed ranging from 0-255"); // Set pump speed
}

void turn_off_pump() {
  // this function turn off the pump
  analogWrite(PUMP_PIN, 0); // Set pump speed
}

void loop() {
  // put your main code here, to run repeatedly:
  turn_on_pump()
  delay(5000)
  turn_off_pump()
  delay(5000)
}