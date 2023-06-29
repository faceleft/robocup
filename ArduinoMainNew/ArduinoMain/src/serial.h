#ifndef ROBOT_SERIAL_H
#define ROBOT_SERIAL_H
#include <Arduino.h>

void serial_init(); //инициализация

#define serial_print(...) Serial.print(__VA_ARGS__)

#define serial_println(...) Serial.println(__VA_ARGS__)

//запустить в void loop()
//будет вызывать callback(message) при получении сообщение
void serial_task(void (*callback)(String*)); 

#endif
