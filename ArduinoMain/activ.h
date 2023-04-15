#ifndef activ_h
#define activ_h
#include "servo.h"
#include "motors.h"
#include "display.h"
#include "tools.h"
#define midle(a,b,c) min(max(b,a),c)
namespace mv {

void none() {
  motors.IntWrite(0, 0);
  motors.SetTarget(0, 0);
  servoF(0, servo_belt);
  servoF(0, servo_rh);
  servoF(0, servo_rv);
  servoF(0, servo_lh);
  servoF(0, servo_lv);
  servoF(0, servo_neck);
}
void r_huk() {
  servoF(-0.5, servo_belt);
  servoF(0.85, servo_rh);
  servoF(-1, servo_rv);

  delay(200);
  servoF(0.75, servo_rv);
  servoF(1, servo_belt);
  delay(400);
  servoF(0, servo_belt);
  servoF(0, servo_rh);
  servoF(0, servo_rv);
}
void l_huk() {
  servoF(0.5, servo_belt);
  servoF(0.85, servo_lh);
  servoF(-1, servo_lv);

  delay(200);
  servoF(0.75, servo_lv);
  servoF(-1, servo_belt);
  delay(400);
  servoF(0, servo_belt);
  servoF(0, servo_lh);
  servoF(0, servo_lv);
}
void r_aperkot() {
  servoF(-1, servo_rv);
  servoF(-0.15, servo_belt);
  delay(100);
  servoF(1, servo_rv);
  servoF(0.6, servo_belt);
  delay(400);
  servoF(0, servo_rv);
  servoF(0, servo_belt);
}
void l_aperkot() {
  servoF(-1, servo_lv);
  servoF(0.15, servo_belt);
  delay(100);
  servoF(1, servo_lv);
  servoF(-0.6, servo_belt);
  delay(400);
  servoF(0, servo_lv);
  servoF(0, servo_belt);
}
void meln() {
  servoF(1, servo_rh);
  servoF(1, servo_lh);
  delay(300);
  servoF(-1, servo_belt);
  delay(300);
  servoF(1, servo_belt);
  delay(600);
  servoF(0, servo_belt);
  delay(300);
  servoF(0, servo_rh);
  servoF(0, servo_lh);
}
void r_MAX() {
  motors.IntWrite(64, -64);
  for (float i = 0; i < 200; i++) {
    servoF(-(i / 200), servo_belt);
    servoF(3 * (i / 200), servo_rh);
    servoF(-(i / 200), servo_rv);
    delay(5);
  }
  motors.IntWrite(-255, 255);
  servoF(1, servo_rv);
  servoF(1, servo_belt);
  delay(400);
  motors.IntWrite(0, 0);
  delay(500);
  servoF(0, servo_belt);
  servoF(0, servo_rh);
  servoF(0, servo_rv);
  motors.IntWrite(64, -64);
  delay(1100);
  motors.IntWrite(0, 0);
}
void l_MAX() {
  motors.IntWrite(-64, 64);
  for (float i = 0; i < 200; i++) {
    servoF((i / 200), servo_belt);
    servoF(3 * (i / 200), servo_lh);
    servoF(-(i / 200), servo_lv);
    delay(5);
  }
  motors.IntWrite(255, -255);
  servoF(1, servo_lv);
  servoF(-1, servo_belt);
  delay(400);
  motors.IntWrite(0, 0);
  delay(500);
  servoF(0, servo_belt);
  servoF(0, servo_lh);
  servoF(0, servo_lv);
  motors.IntWrite(-64, 64);
  delay(1100);
  motors.IntWrite(0, 0);
}
void tors() {
  motors.IntWrite(128, -128);
  for (float i = 0; i < 50; i++) {
    servoF((i / 50), servo_belt);
    delay(7);
  }
  motors.IntWrite(0, 0);
  delay(300);

  motors.IntWrite(-128, 128);
  for (float i = 50; i > (-50); i--) {
    servoF((i / 50), servo_belt);
    delay(7);
  }
  motors.IntWrite(0, 0);
  delay(300);

  motors.IntWrite(128, -128);

  for (float i = -50; i < 0; i++) {
    servoF((i / 50), servo_belt);
    delay(7);
  }
  motors.IntWrite(0, 0);
}
void mtrs() {
  motors.SoftWrite(128, 128);
  delay(500);
  motors.SoftWrite(-128, -128);
  delay(1000);
  motors.SoftWrite(128, 128);
  delay(500);
  motors.SoftWrite(0, 0);
}
void mirror() {
  static float kp = 0.1;
  static float ki = 0;
  static float kd = 0;
  static float neck_buff = 0;
  static float tors_buff = 0;
  static float motors_buff = 0;
  Serial.println("#start mirror");
  tft_print("#start mirror");
  /*
    for(uint8_t a = 0; a < 255; a++){
    Serial.print((char)a);
    Serial.print(" ");
    Serial.println(a);
    }*/
  int pe_speed = motors._speed;
  motors._speed = 2;
  char c, r, l, rotate, dist;
  float f, fdist;
  float rotate_buff = 0;
  float step = 0.2;
  int speed = 100;
  while (1) {
    if (Serial.available() >= 5) {
      c = Serial.read();
      if (c == 0)break;
      if (c == 1) {
        r = Serial.read() - 2;
        l = Serial.read() - 2;
        rotate = Serial.read() - 2;
        dist = 125 - (Serial.read() - 2);

        fdist = (float)dist / 125;
        //tft_print(String((int)dist));
     /*
        else {
          if (dist > 100) motors.SetTarget(-100, -100);
          else if (dist < 98) motors.SetTarget(100, 100);
          else motors.SetTarget(0, 0);
        }
*/
        f = ((float)rotate / 125) * (-2) + 1;

        float neck_x = computePID(-f, 0, 0.1, 0, 0, 1, -1, 1, 0);
        neck_buff = constrain(neck_buff + neck_x, -1, 1);

        float tors_x = computePID(-neck_buff, 0, 0.2, 0, 0, 1, -1, 1, 1);
        tors_buff = tors_buff + tors_x;
        if (tors_buff >= 1) {
          //motors.SetTarget(-100, 100);
          tors_buff = 1;
        }
        else if (tors_buff <= -1) {
          //motors.SetTarget(100, -100);
          tors_buff = -1;
        }
        else{
          motors.SetTarget(0, -0);
        }
        
        //float motor_x = computePID(-tors_buff, 0, 10*kp, ki, kd, 1, -100, 100, 2);
        //motors.IntWrite((int)motor_x, -(int)motor_x);

        //rotate_buff += f*step;
        servoF(neck_buff, servo_neck);
        servoF(tors_buff, servo_belt);

        servoF((float)r / 125, servo_rh);
        servoF((float)l / 125, servo_lh);
      }
    }
    motors.Work();
  }
  motors.SetTarget(0, 0);
  motors.IntWrite(0, 0);
  motors._speed = pe_speed;
  Serial.println("#end mirror");
}
}
#endif
