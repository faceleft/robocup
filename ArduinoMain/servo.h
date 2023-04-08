#ifndef servo_h
#define servo_h

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

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PWM_ADDRESS);

struct Servo{
  uint8_t addr;
  uint16_t min;
  uint16_t mean;
  uint16_t max;
  bool invert;
  };
extern const Servo servo_belt = {SERVO_BELT_ADDR, SERVO_BELT_MIN, SERVO_BELT_MEAN, SERVO_BELT_MAX, SERVO_BELT_INVERT};
extern const Servo servo_rh = {SERVO_RH_ADDR, SERVO_RH_MIN, SERVO_RH_MEAN, SERVO_RH_MAX, SERVO_RH_INVERT};
extern const Servo servo_rv = {SERVO_RV_ADDR, SERVO_RV_MIN, SERVO_RV_MEAN, SERVO_RV_MAX, SERVO_RV_INVERT};
extern const Servo servo_lh = {SERVO_LH_ADDR, SERVO_LH_MIN, SERVO_LH_MEAN, SERVO_LH_MAX, SERVO_LH_INVERT};
extern const Servo servo_lv = {SERVO_LV_ADDR, SERVO_LV_MIN, SERVO_LV_MEAN, SERVO_LV_MAX, SERVO_LV_INVERT};
extern const Servo servo_neck = {8, 128, 320, 512, 0};


#endif

//382
