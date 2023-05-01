#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>

extern const int PUMP_PIN;

void setupPump();
void turn_on_pump(uint8_t speed);
void turn_off_pump();

#endif // PUMP_H