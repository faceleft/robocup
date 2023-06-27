#ifndef SERIAL_ANALYSER_H
#define SERIAL_ANALYSER_H
#include <Arduino.h>

void serial_init(unsigned long speed, int timeout);

void serial_task(void (*callback)(String*));

#endif
