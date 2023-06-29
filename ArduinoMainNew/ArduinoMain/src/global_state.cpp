#include "global_state.h"

#include "error.h"
#include "servo.h"
#include "tools.h"
#include "motors.h"
#include "ir.h"

t_state __global_state;

static_queue<char, GLOBAL_SERIAL_BUFFER_SIZE> global_serial_buffer(error);

t_state get_global_state() {
  return __global_state;
}

void set_global_state(t_state state)
{
  __global_state = state;
  switch (state)
  {
  case NONE:
  {
    global_serial_buffer.clear();
    diodeColor(0, 0, 512);
    // Serial.println("#wait");
    tft_print("#start wait");
    servo_set_float(0, servo_rh);
    servo_set_float(0, servo_rv);
    servo_set_float(0, servo_lh);
    servo_set_float(0, servo_lv);
    ir_off();
    break;
  }
  case MIRROR:
  {
    global_serial_buffer.clear();
    diodeColor(0, 512, 0);
    // Serial.println("#start mirror");
    tft_print("#start mirror");
    servo_set_float(0, servo_rh);
    servo_set_float(0, servo_rv);
    servo_set_float(0, servo_lh);
    servo_set_float(0, servo_lv);
    ir_off();
    break;
  }
  case FIGHT:
  {
    global_serial_buffer.clear();
    diodeColor(512, 0, 0);
    // Serial.println("#start fight");
    tft_print("#start fight");
    motors.IntWrite(0, 0);
    servo_set_float(0, servo_belt);
    servo_set_float(0, servo_rh);
    servo_set_float(0, servo_rv);
    servo_set_float(0, servo_lh);
    servo_set_float(0, servo_lv);
    servo_set_float(0, servo_neck);
    ir_on();
    break;
  }
  }
}