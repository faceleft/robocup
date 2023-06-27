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

#endif

// 382
