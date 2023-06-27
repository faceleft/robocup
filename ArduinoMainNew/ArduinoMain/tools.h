#ifndef tools_h
#define tools_h
#include <Arduino.h>

#include "pins.h"
#include "settings.h"
#include "servo.h"

float voltage(uint8_t pin);

void servoF(float angle, const Servo &s);

namespace func
{
  float sine(float x);
}

float Byte2Val(byte val, float min_, float max_);

void diodeColor(int red, int green, int blue);

float computePID(float input, float setpoint, float kp, float ki, float kd, float dt, float minOut, float maxOut, int index);

#endif
