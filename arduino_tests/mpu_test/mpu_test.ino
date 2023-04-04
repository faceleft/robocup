#include "cartask.h"

#define leftMotorForward 3
#define leftMotorBack 5
#define rightMotorForward 6
#define rightMotorBack 9

const float leftFC = 1;
const float leftBC = 1;
const float rightFC = 1;
const float rightBC = 1;
unsigned long curMil, prevMil;

void Calc_CompensatorZ(float mill_sec);

void setup() {
  Serial.begin(115200);
  Serial.println("Theatre of Robots");
  delay(1000);

  if (!mpu.begin()) {
    Serial.println("MPU not found");
    delay(1000);
    return;
  }

  Serial.println("MPU6050 Found");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Calc_CompensatorZ(5000);

  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBack, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBack, OUTPUT);

  t0 = micros();
}

void loop() {
  curMil = millis();
  if (Serial.available() > 0)
  {
    String rec = Serial.readStringUntil('\n');

    if (rec == "f") {
      analogWrite(leftMotorForward, 150);
      analogWrite(rightMotorForward, 150);
    }
    else if (rec == "b") {
      analogWrite(leftMotorBack, 150);
      analogWrite(rightMotorBack, 150);
    }
    else if (rec == "l") {
      analogWrite(leftMotorBack, 150);
      analogWrite(rightMotorForward, 150);
    }
    else if (rec == "r") {
      analogWrite(leftMotorForward, 150);
      analogWrite(rightMotorBack, 150);
    }
    else if (rec == "s") {
      analogWrite(leftMotorForward, 0);
      analogWrite(rightMotorForward, 0);
      analogWrite(leftMotorBack, 0);
      analogWrite(rightMotorBack, 0);
    }
    else if (rec == "t") {
      analogWrite(leftMotorForward, 70);
    }
  }
  if (curMil - prevMil >= 5) {
    TaskCarPosition();
    Serial.println(imu[2] * RAD_TO_DEG);
    prevMil = curMil;
  }

}
