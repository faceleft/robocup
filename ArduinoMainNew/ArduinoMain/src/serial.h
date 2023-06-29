#ifndef ROBOT_SERIAL_H
#define ROBOT_SERIAL_H
#include <Arduino.h>

void serial_init();

#define serial_print(...) Serial.print(__VA_ARGS__)

#define serial_println(...) Serial.println(__VA_ARGS__)

void serial_task(void (*callback)(String*));

#endif
