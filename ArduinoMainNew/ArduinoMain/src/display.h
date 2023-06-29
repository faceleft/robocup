#ifndef ROBOT_DISPLAY_H
#define ROBOT_DISPLAY_H

#include "pins.h"
#include "settings.h"
#include "Arduino.h"

void display_setup();

void tft_print(String s = "", bool ln = 1, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255);

#endif
