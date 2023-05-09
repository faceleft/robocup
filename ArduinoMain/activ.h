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
  bool rotate_flag = false;
} mirror_status;

struct {
  float angle;
  float dist;
  bool change_flag = false;
  bool save_distance_flag = false;
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
void mirror_save_distance() {
  if (mirror_status.dist > 0.5) {
    motors.IntWrite(-160, -160);
  }
  else if (mirror_status.dist < 0.3) {
    motors.IntWrite(160, 160);
  }
  else {
    motors.IntWrite(0, 0);
  }
}
void mirror_rotate() {
  float neck_x = computePID(mirror_status.angle, 0, 0, 0.8, 0.01, 0.1, -1, 1, 0);
  float neck_buff = constrain(neck_x, -1, 1);
  if (neck_x > 0.7) {
    //motors.IntWrite(-100, 100);
  }
  else if (neck_x < -0.7) {
    //motors.IntWrite(100, -100);
  }
  else {
    //motors.IntWrite(0, 0);
  }
  //tft_print(String(neck_x));
  servoF(neck_buff, servo_neck);
  servoF(neck_buff, servo_belt);

  if (mirror_status.rotate_flag) {
    float motors_x = computePID(neck_buff, 0, 200, 1, 0, 0.1, -100, 100, 1);
    motors.IntWrite(motors_x, -motors_x);
  }
}

void mirror_hands() {
  servoF(mirror_status.rh_hand * 2, servo_rh);
  servoF(mirror_status.lh_hand * 2, servo_lh);

  servoF(mirror_status.rv_hand, servo_rv);
  servoF(mirror_status.lv_hand, servo_lv);

  if (mirror_status.lh_hand * 160 + 20 >= 130) {
    //mirror_status.rotate_flag = 1;
  }
  else {
    mirror_status.rotate_flag = 0;
  }
}

void fight_rotate() {
  if (fight_status.save_distance_flag == false) {
    float neck_x = computePID(fight_status.angle, 0, 3, 0, 0, 0.1, -1, 1, 2);
    motors.IntWrite(-100 * neck_x, 100 * neck_x);
  }
}

void punch() {
  static int i = 0;
  void (*mvs[])(void) = {
    r_huk,
    l_aperkot,
    l_huk,
    r_aperkot,
    r_MAX,
    l_aperkot,
    l_huk,
  };
  mvs[i]();
  i = (i + 1) % (sizeof(mvs) / sizeof(mvs[0]));
}

void fight_delay(uint32_t ms);
void fight_save_distance() {
  if (fight_status.dist > 0.5) {
    motors.IntWrite(-160, -160);
    fight_status.save_distance_flag = true;
  }
  else if (fight_status.dist < 0.3) {
    motors.IntWrite(160, 160);
    fight_status.save_distance_flag = true;
  }
  else {

    if (fight_status.save_distance_flag) {
      motors.IntWrite(0, 0);
      punch();
      fight_delay(1000);
      fight_status.save_distance_flag = false;
    }
  }
}



void mirror() {
  if (Serial.available()) {
    char b = Serial.read();
    if (b == 0) {
      set_global_state(FIGHT);
      return;
    }
    global_serial_buffer.add(b);
  }


  if (global_serial_buffer.len()) {
    if (global_serial_buffer.check_top() != 1) {
      global_serial_buffer.get();
    }
  }

  if (global_serial_buffer.len() >= 7) {
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
  if (Serial.available()) {
    char b = Serial.read();
    if (b == 0) {
      return;
    }
    global_serial_buffer.add(b);
  }


  if (global_serial_buffer.len()) {
    if (global_serial_buffer.check_top() != 1) {
      global_serial_buffer.get();
    }
  }

  if (global_serial_buffer.len() >= 3) {
    global_serial_buffer.get();
    fight_status.angle = Byte2Val(global_serial_buffer.get(), -1, 1);
    fight_status.dist = Byte2Val(global_serial_buffer.get(), 0, 1);
    fight_status.change_flag = true;
  }
}
void fight_delay(uint32_t ms) {
  uint32_t time = millis();
  while (millis() - time < ms) {
    fight();
  }
}

}
#endif
