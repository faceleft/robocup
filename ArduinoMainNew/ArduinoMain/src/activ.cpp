#include "activ.h"

#include "servo.h"
#include "motors.h"
#include "display.h"
#include "tools.h"
#include "global_state.h"

void mv::none()
{
  motors.IntWrite(0, 0);
  motors.SetTarget(0, 0);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_rh);
  servo_set_float(0, servo_rv);
  servo_set_float(0, servo_lh);
  servo_set_float(0, servo_lv);
  servo_set_float(0, servo_neck);
}

void mv::r_huk()
{
  servo_set_float(-0.5, servo_belt);
  servo_set_float(0.5, servo_neck_like_belt);

  servo_set_float(0.85, servo_rh);
  servo_set_float(-1, servo_rv);

  delay(200);
  servo_set_float(0.75, servo_rv);
  servo_set_float(1, servo_belt);
  servo_set_float(-1, servo_neck_like_belt);
  delay(400);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_neck_like_belt);
  servo_set_float(0, servo_rh);
  servo_set_float(0, servo_rv);
}

void mv::l_huk()
{
  servo_set_float(0.5, servo_belt);
  servo_set_float(-0.5, servo_neck_like_belt);
  servo_set_float(0.85, servo_lh);
  servo_set_float(-1, servo_lv);

  delay(200);
  servo_set_float(0.75, servo_lv);
  servo_set_float(-1, servo_belt);
  servo_set_float(1, servo_neck_like_belt);
  delay(400);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_neck_like_belt);
  servo_set_float(0, servo_lh);
  servo_set_float(0, servo_lv);
}

void mv::r_aperkot()
{
  servo_set_float(-1, servo_rv);
  servo_set_float(-0.15, servo_belt);
  servo_set_float(0.15, servo_neck_like_belt);
  delay(100);
  servo_set_float(1, servo_rv);
  servo_set_float(0.6, servo_belt);
  servo_set_float(-0.6, servo_neck_like_belt);
  delay(400);
  servo_set_float(0, servo_rv);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_neck_like_belt);
}

void mv::l_aperkot()
{
  servo_set_float(-1, servo_lv);
  servo_set_float(0.15, servo_belt);
  servo_set_float(-0.15, servo_neck_like_belt);
  delay(100);
  servo_set_float(1, servo_lv);
  servo_set_float(-0.6, servo_belt);
  servo_set_float(0.6, servo_neck_like_belt);
  delay(400);
  servo_set_float(0, servo_lv);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_neck_like_belt);
}

void mv::meln()
{
  servo_set_float(1, servo_rh);
  servo_set_float(1, servo_lh);
  delay(300);
  servo_set_float(-1, servo_belt);
  servo_set_float(1, servo_neck_like_belt);
  delay(300);
  servo_set_float(1, servo_belt);
  servo_set_float(-1, servo_neck_like_belt);
  delay(600);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_neck_like_belt);
  delay(300);
  servo_set_float(0, servo_rh);
  servo_set_float(0, servo_lh);
}

void mv::r_MAX()
{
  motors.IntWrite(64, -64);
  for (float i = 0; i < 200; i++)
  {
    servo_set_float(-(i / 200), servo_belt);
    servo_set_float(3 * (i / 200), servo_rh);
    servo_set_float(-(i / 200), servo_rv);
    delay(5);
  }
  motors.IntWrite(-255, 255);
  servo_set_float(1, servo_rv);
  servo_set_float(1, servo_belt);
  servo_set_float(-1, servo_neck_like_belt);
  delay(400);
  motors.IntWrite(0, 0);
  delay(500);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_neck_like_belt);
  servo_set_float(0, servo_rh);
  servo_set_float(0, servo_rv);
  motors.IntWrite(64, -64);
  delay(1100);
  motors.IntWrite(0, 0);
}

void mv::l_MAX()
{
  motors.IntWrite(-64, 64);
  for (float i = 0; i < 200; i++)
  {
    servo_set_float((i / 200), servo_belt);
    servo_set_float(3 * (i / 200), servo_lh);
    servo_set_float(-(i / 200), servo_lv);
    delay(5);
  }
  motors.IntWrite(255, -255);
  servo_set_float(1, servo_lv);
  servo_set_float(-1, servo_belt);
  servo_set_float(1, servo_neck_like_belt);
  delay(400);
  motors.IntWrite(0, 0);
  delay(500);
  servo_set_float(0, servo_belt);
  servo_set_float(0, servo_neck_like_belt);
  servo_set_float(0, servo_lh);
  servo_set_float(0, servo_lv);
  motors.IntWrite(-64, 64);
  delay(1100);
  motors.IntWrite(0, 0);
}

void mv::tors()
{
  motors.IntWrite(128, -128);
  for (float i = 0; i < 50; i++)
  {
    servo_set_float((i / 50), servo_belt);
    delay(7);
  }
  motors.IntWrite(0, 0);
  delay(300);

  motors.IntWrite(-128, 128);
  for (float i = 50; i > (-50); i--)
  {
    servo_set_float((i / 50), servo_belt);
    delay(7);
  }
  motors.IntWrite(0, 0);
  delay(300);

  motors.IntWrite(128, -128);

  for (float i = -50; i < 0; i++)
  {
    servo_set_float((i / 50), servo_belt);
    delay(7);
  }
  motors.IntWrite(0, 0);
}

void mv::mtrs()
{
  motors.SoftWrite(128, 128);
  delay(500);
  motors.SoftWrite(-128, -128);
  delay(1000);
  motors.SoftWrite(128, 128);
  delay(500);
  motors.SoftWrite(0, 0);
}

void mv::set_right()
{
  servo_set_float(1, servo_neck);
  servo_set_float(1, servo_belt);
}

void mv::set_left()
{
  servo_set_float(-1, servo_neck);
  servo_set_float(-1, servo_belt);
}

void mv::mirror_save_distance()
{
  if (mirror_status.dist > 0.4)
  {
    motors.IntWrite(-160, -160);
  }
  else if (mirror_status.dist < 0.3)
  {
    motors.IntWrite(160, 160);
  }
  else
  {
    motors.IntWrite(0, 0);
  }
}

void mv::mirror_rotate()
{
  float neck_x = computePID(mirror_status.angle, 0, 0, 0.8, 0.01, 0.1, -1, 1, 0);
  float neck_buff = constrain(neck_x, -1, 1);
  if (neck_x > 0.7)
  {
    // motors.IntWrite(-100, 100);
  }
  else if (neck_x < -0.7)
  {
    // motors.IntWrite(100, -100);
  }
  else
  {
    // motors.IntWrite(0, 0);
  }
  // tft_print(String(neck_x));
  servo_set_float(neck_buff, servo_neck);
  servo_set_float(neck_buff, servo_belt);

  if (mirror_status.rotate_flag)
  {
    float motors_x = computePID(neck_buff, 0, 200, 1, 0, 0.1, -100, 100, 1);
    motors.IntWrite(motors_x, -motors_x);
  }
}

void mv::mirror_hands()
{
  servo_set_float(mirror_status.rh_hand * 2, servo_rh);
  servo_set_float(mirror_status.lh_hand * 2, servo_lh);

  servo_set_float(mirror_status.rv_hand, servo_rv);
  servo_set_float(mirror_status.lv_hand, servo_lv);

  if (mirror_status.lh_hand * 160 + 20 >= 130)
  {
    // mirror_status.rotate_flag = 1;
  }
  else
  {
    mirror_status.rotate_flag = 0;
  }
}

void mv::fight_rotate()
{
  int k;
  static uint32_t timer = millis();

  if (fight_status.dist > 0.1)
  {
    k = -130;
  }
  else
  {
    k = 0;
    if (millis() - timer > 3000)
    {
      motors.IntWrite(0, 0);
      punch();
      fight_delay(500);
      timer = millis();
    }
  }

  float neck_x = computePID(fight_status.angle, 0, 4, 0, 0, 0.1, -1, 1, 2);

  motors.IntWrite(k + (neck_x * -100), k + (neck_x * 100));
}

void mv::punch()
{
  static int i = 0;
  void (*mvs[])(void) = {
      r_huk,
      l_aperkot,
      l_huk,
      r_aperkot,
      // hjjjjjgr_MAX,
      l_aperkot,
      l_huk,
  };
  mvs[i]();
  i = (i + 1) % (sizeof(mvs) / sizeof(mvs[0]));
}

void mv::mirror()
{
  if (Serial.available())
  {
    char b = Serial.read();
    if (b == 0)
    {
      set_global_state(FIGHT);
      return;
    }
    global_serial_buffer.add(b);
  }

  if (global_serial_buffer.len())
  {
    if (global_serial_buffer.check_top() != 1)
    {
      global_serial_buffer.get();
    }
  }

  if (global_serial_buffer.len() >= 7)
  {
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

void mv::fight()
{
  if (Serial.available())
  {
    char b = Serial.read();
    if (b == 0)
    {
      return;
    }
    global_serial_buffer.add(b);
  }

  if (global_serial_buffer.len())
  {
    if (global_serial_buffer.check_top() != 1)
    {
      global_serial_buffer.get();
    }
  }

  if (global_serial_buffer.len() >= 3)
  {
    global_serial_buffer.get();
    fight_status.angle = Byte2Val(global_serial_buffer.get(), -1, 1);
    fight_status.dist = Byte2Val(global_serial_buffer.get(), 0, 1);
    fight_status.change_flag = true;
  }
}

void mv::fight_delay(unsigned long ms)
{
  unsigned long time = millis();
  while (millis() - time < ms)
  {
    fight();
  }
}
