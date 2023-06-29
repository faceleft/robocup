#ifndef ROBOT_SERVO_H
#define ROBOT_SERVO_H

#include <Adafruit_PWMServoDriver.h>

extern Adafruit_PWMServoDriver pwm; //pwm для всех 

struct Servo
{
  uint8_t addr;
  uint16_t min;
  uint16_t mean;
  uint16_t max;
  bool invert;
};

extern const Servo servo_belt; //серво на поясе
extern const Servo servo_rh; //правая рука вбок
extern const Servo servo_rv; //правая рука вперёд
extern const Servo servo_lh; //левая рука вбок
extern const Servo servo_lv; //левая рука вперёд
extern const Servo servo_neck; //шея
extern const Servo servo_neck_like_belt; //шея с ограничениями пояся (для синхронного движения)

//установка положения от -1 - минимум до 1 - максимум, 0 -стандартное положение
void servo_set_float(float angle, const Servo &s); 

#endif

// 382
