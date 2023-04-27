#ifndef activ_h
#define activ_h
#include "servo.h"
#include "motors.h"
#include "display.h"
#include "tools.h"
#define midle(a,b,c) min(max(b,a),c)
namespace mv {
struct {
  float r_hand;
  float l_hand;
  float angle;
  float dist;
  bool change_flag = false;
  bool mirror_flag = false;
} mirror_status;

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
  servoF(0.5, servo_neck_like_belt);

  servoF(0.85, servo_rh);
  servoF(-1, servo_rv);

  delay(200);
  servoF(0.75, servo_rv);
  servoF(1, servo_belt);
  servoF(-1, servo_neck_like_belt);
  delay(400);
  servoF(0, servo_belt);
  servoF(0, servo_neck_like_belt);
  servoF(0, servo_rh);
  servoF(0, servo_rv);
}
void l_huk() {
  servoF(0.5, servo_belt);
  servoF(-0.5, servo_neck_like_belt);
  servoF(0.85, servo_lh);
  servoF(-1, servo_lv);

  delay(200);
  servoF(0.75, servo_lv);
  servoF(-1, servo_belt);
  servoF(1, servo_neck_like_belt);
  delay(400);
  servoF(0, servo_belt);
  servoF(0, servo_neck_like_belt);
  servoF(0, servo_lh);
  servoF(0, servo_lv);
}
void r_aperkot() {
  servoF(-1, servo_rv);
  servoF(-0.15, servo_belt);
  servoF(0.15, servo_neck_like_belt);
  delay(100);
  servoF(1, servo_rv);
  servoF(0.6, servo_belt);
  servoF(-0.6, servo_neck_like_belt);
  delay(400);
  servoF(0, servo_rv);
  servoF(0, servo_belt);
  servoF(0, servo_neck_like_belt);
}
void l_aperkot() {
  servoF(-1, servo_lv);
  servoF(0.15, servo_belt);
  servoF(-0.15, servo_neck_like_belt);
  delay(100);
  servoF(1, servo_lv);
  servoF(-0.6, servo_belt);
  servoF(0.6, servo_neck_like_belt);
  delay(400);
  servoF(0, servo_lv);
  servoF(0, servo_belt);
  servoF(0, servo_neck_like_belt);
}
void meln() {
  servoF(1, servo_rh);
  servoF(1, servo_lh);
  delay(300);
  servoF(-1, servo_belt);
  servoF(1, servo_neck_like_belt);
  delay(300);
  servoF(1, servo_belt);
  servoF(-1, servo_neck_like_belt);
  delay(600);
  servoF(0, servo_belt);
  servoF(0, servo_neck_like_belt);
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
  servoF(-1, servo_neck_like_belt);
  delay(400);
  motors.IntWrite(0, 0);
  delay(500);
  servoF(0, servo_belt);
  servoF(0, servo_neck_like_belt);
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
  servoF(1, servo_neck_like_belt);
  delay(400);
  motors.IntWrite(0, 0);
  delay(500);
  servoF(0, servo_belt);
  servoF(0, servo_neck_like_belt);
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

void set_right() {
  servoF(1, servo_neck);
  servoF(1, servo_belt);
}

void set_left() {
  servoF(-1, servo_neck);
  servoF(-1, servo_belt);
}

void save_distance(int dist) {
  float f_dist = ((float)dist / 125) * 5;
  if (f_dist > 1.7) {
    motors.SetTarget(100, 100);
  }
  else if (f_dist < 1.5) {
    motors.SetTarget(-100, -100);
  }
  else {
    motors.SetTarget(0, 0);
  }
}
void rotate() {
  float motors_buff, neck_buff, tors_buff;
  float neck_x = computePID(mirror_status.angle, 0, 0, 1, 0.01, 0.1, -1.1, 1.1, 0);
  neck_buff = constrain(neck_x, -1, 1);
  if (neck_x > 1) {
    motors_buff = 1;
  }
  else if (neck_x < -1) {
    motors_buff = -1;
  }
  else {
    motors_buff = 0;
  }
  servoF(neck_buff, servo_neck);
  servoF(neck_buff, servo_belt);
  motors.IntWrite(-100 * motors_buff, 100 * motors_buff);

}
void hands() {
  servoF(mirror_status.r_hand, servo_rh);
  servoF(mirror_status.l_hand, servo_lh);
}

void mirror() {
  if (!mirror_status.mirror_flag) {
    Serial.println("#start mirror");
    tft_print("#start mirror");
    mirror_status.mirror_flag = true;
  }
  char c, r, l, rotate, dist;
  float f, fdist;
  float rotate_buff = 0;

  if (Serial.available() >= 5) {
    c = Serial.read();
    if (c == 0) {
      mirror_status.mirror_flag = false;
      motors.SetTarget(0, 0);
      motors.IntWrite(0, 0);
      tft_print("#end mirror");
      Serial.println("#end mirror");
      return;
    }
    else if (c == 1) {
      r = Serial.read() - 2;
      l = Serial.read() - 2;
      rotate = Serial.read() - 2;
      dist = (Serial.read() - 2);
      mirror_status.r_hand = (float)r / 125;
      mirror_status.l_hand = (float)l / 125;
      mirror_status.angle = ((float)rotate / 125) * 2 - 1;
      mirror_status.dist = ((float)dist / 125) * 5;
      mirror_status.change_flag = true;
    }
  }
}


}
#endif
