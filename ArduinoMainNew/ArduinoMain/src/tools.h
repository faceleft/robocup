#ifndef ROBOT_TOOLS_H
#define ROBOT_TOOLS_H

#include <Arduino.h>

#include "display.h"
#define try(func) {tft_print("!try '" #func "'", 0, 255, 128, 255); func; tft_print(" DONE", 1, 128, 255, 128);}

float voltage(uint8_t pin);

float Byte2Val(byte val, float min_, float max_);

void diodeColor(int red, int green, int blue);

float computePID(float input, float setpoint, float kp, float ki, float kd, float dt, float minOut, float maxOut, int index);

#endif
