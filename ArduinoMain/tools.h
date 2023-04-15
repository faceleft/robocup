#ifndef tools_h
#define tools_h
#include <Arduino.h>

#include "pins.h"
#include "settings.h"
#include "servo.h"

float voltage(uint8_t pin) {
  //return ((float)analogRead(pin) * PREF_VREF) / (float)analogRead(PIN_VREF); //когда будет аппаратно
  return ((float)analogRead(pin) * PREF_VREF) / 512;
}

void servoF(float angle, const Servo& s){
  angle = max(-1, min(1, angle));
  if(s.invert){
    angle = -angle;
  }
  int zn;
  if(angle >= 0){
      zn = s.mean + angle*(s.max-s.mean);
  }
  else{
      zn = s.mean + angle*(s.mean-s.min);
  }
  pwm.setPWM(s.addr, 0, zn);
}

namespace func{
  float sine(float x){return 0.5*(sin((-PI)/2 + PI*x)+1);} 
}

void diodeColor(int red, int green, int blue){
  pwm.setPWM(DIODE_RED_ADDR, 0, red);
  pwm.setPWM(DIODE_GREEN_ADDR, 0, green);
  pwm.setPWM(DIODE_BLUE_ADDR, 0, blue);
}

float computePID(float input, float setpoint, float kp, float ki, float kd, float dt, float minOut, float maxOut, int index) {
  float err = setpoint - input;
  static float integral[5]= {0,0,0,0,0};
  static float prevErr[5]= {0,0,0,0,0};
  integral[index] = constrain(integral[index] + (float)err * dt * ki, minOut, maxOut);
  float D = (err - prevErr[index]) / dt;
  prevErr[index] = err;
  return constrain(err * kp + integral[index] + D * kd, minOut, maxOut);
}

#endif
