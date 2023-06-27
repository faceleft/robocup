#include "servo.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PWM_ADDRESS);

const Servo servo_belt = {SERVO_BELT_ADDR, SERVO_BELT_MIN, SERVO_BELT_MEAN, SERVO_BELT_MAX, SERVO_BELT_INVERT};
const Servo servo_rh = {SERVO_RH_ADDR, SERVO_RH_MIN, SERVO_RH_MEAN, SERVO_RH_MAX, SERVO_RH_INVERT};
const Servo servo_rv = {SERVO_RV_ADDR, SERVO_RV_MIN, SERVO_RV_MEAN, SERVO_RV_MAX, SERVO_RV_INVERT};
const Servo servo_lh = {SERVO_LH_ADDR, SERVO_LH_MIN, SERVO_LH_MEAN, SERVO_LH_MAX, SERVO_LH_INVERT};
const Servo servo_lv = {SERVO_LV_ADDR, SERVO_LV_MIN, SERVO_LV_MEAN, SERVO_LV_MAX, SERVO_LV_INVERT};
const Servo servo_neck = {8, 200, 340, 530, 0};
const Servo servo_neck_like_belt = {8, 290, 340, 410, 0};
