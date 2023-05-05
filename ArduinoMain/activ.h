#include "HardwareSerial.h"
#ifndef activ_h
#define activ_h
#include "servo.h"
#include "motors.h"
#include "display.h"
#include "tools.h"
#include "global_state.h"


namespace mv {
struct {
  float rv_hand;
  float lv_hand; 
  float rh_hand;
  float lh_hand;
  float angle;
  float dist;
  bool change_flag = false;
} mirror_status;

struct {
  float angle;
  float dist;
  bool change_flag = false;
} fight_status;

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
void mirrot_save_distance(int dist) {
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
void mirror_rotate() {
  float motors_buff, neck_buff, tors_buff;
  float neck_x = computePID(mirror_status.angle, 0, 0, 1, 0.01, 0.1, -1.01, 1.01, 0);
  neck_buff = constrain(neck_x, -1, 1);
  if (neck_x > 1) {
    //motors.byTime(-100, 100, 2000);
  }
  else if (neck_x < -1) {
    motors.byTime(100, -100, 2000);
  }
  tft_print(String(neck_x));
  servoF(neck_buff, servo_neck);
  servoF(neck_buff, servo_belt);
}
void mirror_hands() {
  servoF(mirror_status.rh_hand * 2, servo_rh);
  servoF(mirror_status.lh_hand * 2, servo_lh);
  
  servoF(mirror_status.rv_hand, servo_rv);
  servoF(mirror_status.lv_hand, servo_lv);
}
void fight_rotate() {
  float motors_buff, neck_buff, tors_buff;
  float neck_x = computePID(fight_status.angle, 0, 0, 1, 0.01, 0.1, -1.1, 1.1, 0);
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
void fight_hands() {
}
void mirror() {
  if(Serial.available()){
    char b = Serial.read();
    if(b==0){
      set_global_state(FIGHT);
      return;
    }
    global_serial_buffer.add(B);
  }
  while(global_serial_buffer.check_top()!=1) global_serial_buffer.get();

  if (global_serial_buffer.len()>=7) {
      global_serial_buffer.get();
      mirror_status.rv_hand = Byte2Val(global_serial_buffer.get(), 0, 1);
      mirror_status.lv_hand = Byte2Val(global_serial_buffer.get(), 0, 1);
      mirror_status.rh_hand = Byte2Val(global_serial_buffer.get(), 0, 1);
      mirror_status.lh_hand = Byte2Val(global_serial_buffer.get(), 0, 1);
      mirror_status.angle = Byte2Val(global_serial_buffer.get(), -1, 1);
      mirror_status.dist = Byte2Val(global_serial_buffer.get(), 0, 1);
      mirror_status.change_flag = true;
  }
}
void fight() {
  if(Serial.available()){
    char b = Serial.read();
    if(b==0){
      set_global_state(FIGHT);
      return;
    }
    global_serial_buffer.add(B);
  }
  while(global_serial_buffer.check_top()!=1) global_serial_buffer.get();

  if (global_serial_buffer.len()>=3) {
      global_serial_buffer.get();
      fight_status.angle = Byte2Val(global_serial_buffer.get(), -1, 1);
      fight_status.dist = Byte2Val(global_serial_buffer.get(), 0, 1);
      fight_status.change_flag = true;
  }
}
}
#endif
