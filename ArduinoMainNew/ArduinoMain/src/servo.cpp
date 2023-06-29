#include "servo.h"

#define PWM_ADDRESS 0x40

#define SERVO_BELT_MIN 282
#define SERVO_BELT_MEAN 352
#define SERVO_BELT_MAX 427
#define SERVO_BELT_ADDR 0
#define SERVO_BELT_INVERT 0

#define SERVO_RH_MIN 207
#define SERVO_RH_MEAN 377
#define SERVO_RH_MAX 377
#define SERVO_RH_ADDR 3
#define SERVO_RH_INVERT 1

#define SERVO_RV_MIN 147
#define SERVO_RV_MEAN 227
#define SERVO_RV_MAX 537
#define SERVO_RV_ADDR 4
#define SERVO_RV_INVERT 0

#define SERVO_LH_MIN 187
#define SERVO_LH_MEAN 347
#define SERVO_LH_MAX 347
#define SERVO_LH_ADDR 1
#define SERVO_LH_INVERT 1

#define SERVO_LV_MIN 192
#define SERVO_LV_MEAN 452
#define SERVO_LV_MAX 512
#define SERVO_LV_ADDR 2
#define SERVO_LV_INVERT 1

#define SERVO_NECK_MIN 200
#define SERVO_NECK_MEAN 340
#define SERVO_NECK_MAX 530
#define SERVO_NECK_ADDR 8
#define SERVO_NECK_INVERT 0

#define SERVO_NECK_LIKE_BELT_MIN 290
#define SERVO_NECK_LIKE_BELT_MEAN 340
#define SERVO_NECK_LIKE_BELT_MAX 410
#define SERVO_NECK_LIKE_BELT_ADDR 8
#define SERVO_NECK_LIKE_BELT_INVERT 0

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PWM_ADDRESS);

const Servo servo_belt = {SERVO_BELT_ADDR, SERVO_BELT_MIN, SERVO_BELT_MEAN, SERVO_BELT_MAX, SERVO_BELT_INVERT};
const Servo servo_rh = {SERVO_RH_ADDR, SERVO_RH_MIN, SERVO_RH_MEAN, SERVO_RH_MAX, SERVO_RH_INVERT};
const Servo servo_rv = {SERVO_RV_ADDR, SERVO_RV_MIN, SERVO_RV_MEAN, SERVO_RV_MAX, SERVO_RV_INVERT};
const Servo servo_lh = {SERVO_LH_ADDR, SERVO_LH_MIN, SERVO_LH_MEAN, SERVO_LH_MAX, SERVO_LH_INVERT};
const Servo servo_lv = {SERVO_LV_ADDR, SERVO_LV_MIN, SERVO_LV_MEAN, SERVO_LV_MAX, SERVO_LV_INVERT};
const Servo servo_neck = {SERVO_NECK_ADDR, SERVO_NECK_MIN, SERVO_NECK_MEAN, SERVO_NECK_MAX, SERVO_NECK_INVERT};
const Servo servo_neck_like_belt = {SERVO_NECK_LIKE_BELT_ADDR, SERVO_NECK_LIKE_BELT_MIN,\
                                    SERVO_NECK_LIKE_BELT_MEAN, SERVO_NECK_LIKE_BELT_MAX, SERVO_NECK_LIKE_BELT_INVERT};

void servo_set_float(float angle, const Servo &s)
{
  angle = max(-1, min(1, angle));
  if (s.invert)
  {
    angle = -angle;
  }
  int zn;
  if (angle >= 0)
  {
    zn = s.mean + angle * (s.max - s.mean);
  }
  else
  {
    zn = s.mean + angle * (s.mean - s.min);
  }
  pwm.setPWM(s.addr, 0, zn);
}