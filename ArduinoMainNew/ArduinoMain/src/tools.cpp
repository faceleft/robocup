#include "tools.h"

#include "pins.h"
#include "settings.h"
#include "servo.h"

float voltage(uint8_t pin)
{
  // return ((float)analogRead(pin) * PREF_VREF) / (float)analogRead(PIN_VREF); //когда будет аппаратно
  return ((float)analogRead(pin) * PREF_VREF) / 512;
}

float Byte2Val(byte val, float min_, float max_)
{
  return (((float)(val - 2)) / 253) * (max_ - min_) + min_;
}

void diodeColor(int red, int green, int blue)
{
  pwm.setPWM(DIODE_RED_ADDR, 0, red);
  pwm.setPWM(DIODE_GREEN_ADDR, 0, green);
  pwm.setPWM(DIODE_BLUE_ADDR, 0, blue);
}

float computePID(float input, float setpoint, float kp, float ki, float kd, float dt, float minOut, float maxOut, int index)
{
  float err = setpoint - input;
  static float integral[10] = {0};
  static float prevErr[10] = {0};
  integral[index] = constrain(integral[index] + (float)err * dt * ki, minOut, maxOut);
  float D = (err - prevErr[index]) / dt;
  prevErr[index] = err;
  return constrain(err * kp + integral[index] + D * kd, minOut, maxOut);
}