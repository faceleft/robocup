#include <MadgwickAHRS.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "giromath.h"

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

//=================================

void TaskCarPosition()
{
  // Опрос гироприбора MPU6050 (Adafruit_MPU6050)
  mpu.getEvent(&a, &g, &temp);
  micros_ = micros();
  dt = micros_ - t0; // Длительность предыдущего периода регулирования.
  t0 = micros_; //Точка начала нового периода регулирования.
  double Dt = double(dt) * 0.000001;

  GyroZ =  g.gyro.z - CompensatorZ;
  //Расчет текущего положения робота фильтром Маджвика
  MadgwickAHRSupdateIMU(Dt, g.gyro.x - CompensatorX , g.gyro.y - CompensatorY, GyroZ, a.acceleration.x, a.acceleration.y, a.acceleration.z);

  quat[0] = q0; quat[1] = q1; quat[2] = q2; quat[3] = q3;
  // преобразуем кватернион в углы Эйлера
  quat2Euler(&quat[0], &imu[0]);
}

//=============================================
void Calc_CompensatorZ(float mill_sec)
{
  uint32_t ms = mill_sec;
  double i = 0;
  CompensatorZ = 0;
  CompensatorX = 0;
  CompensatorY = 0;
  uint32_t  timer = millis();
  uint32_t endtime = millis() + ms;
  while (endtime > timer) {
    timer = millis();
    mpu.getEvent(&a, &g, &temp);

    CompensatorZ += g.gyro.z;
    CompensatorX += g.gyro.x;
    CompensatorY += g.gyro.y;
    delay(2);
    i++;
  }
  CompensatorZ /= i;
  CompensatorX /= i;
  CompensatorY /= i;
}
