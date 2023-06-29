#ifndef ROBOT_SERVO_H
#define ROBOT_SERVO_H

#include <Adafruit_PWMServoDriver.h>

extern Adafruit_PWMServoDriver pwm;

struct Servo
{
  uint8_t addr;
  uint16_t min;
  uint16_t mean;
  uint16_t max;
  bool invert;
};

extern const Servo servo_belt;
extern const Servo servo_rh;
extern const Servo servo_rv;
extern const Servo servo_lh;
extern const Servo servo_lv;
extern const Servo servo_neck;
extern const Servo servo_neck_like_belt;

void servo_set_float(float angle, const Servo &s);

#endif

// 382
