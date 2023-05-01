const int VALVE_PIN = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(VALVE_PIN, OUTPUT);
}

void open_checkvalve() {
  //This function open the check valve to let fluid flow
  digitalWrite(VALVE_PIN,HIGH);
}

void close_checkvalve() {
  //This function close check valve to stop fluid from flowing through
  digitalWrite(VALVE_PIN,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  open_checkvalve();
  delay(10000);
  close_checkvalve();
}
