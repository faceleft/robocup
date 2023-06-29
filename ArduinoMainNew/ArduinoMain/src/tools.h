#ifndef ROBOT_TOOLS_H
#define ROBOT_TOOLS_H

#include <Arduino.h>

#include "display.h"

/*
Выыод выполнения фунции
"try(func());" сначала напишет имя функции, 
потом попытается выполнить, и после выполнения 
напишет DONE
*/
#define try(func) {tft_print("!try '" #func "'", 0, 255, 128, 255); func; tft_print(" DONE", 1, 128, 255, 128);}

/*
перевод значения из байта 2-255 (0 и 1 управляющие значения)
в float с указанным диапазоном
примеры:
Byte2Val(2,0,1) -> 0.0
Byte2Val(255,0,1) -> 1.0
Byte2Val(127,0,1) -> 0.49
Byte2Val(127,0,2) -> 0.99
нужно для передачи движения рук, моторов, пояса и головы
*/
float Byte2Val(byte val, float min_, float max_);

/*
установить цвет светодиода в глазу
RGB от 0 до 1024
*/
void diodeColor(int red, int green, int blue);

/*
PID регулятор, последний аргумент index (0-9) нужен для одновременного использования в нескольких местах
*/
float computePID(float input, float setpoint, float kp, float ki, float kd, float dt, float minOut, float maxOut, int index);

#endif
