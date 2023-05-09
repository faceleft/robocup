#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H
#include "structures/static_queue.h"
#include "error.h"

typedef enum {
  MIRROR,
  FIGHT,
  NONE,
} t_state;

t_state __global_state;

static_queue<char, 100> global_serial_buffer(error);

void set_global_state(t_state state) {
  __global_state = state;
  switch (state) {
    case NONE: {
        global_serial_buffer.clear();
        diodeColor(0, 0, 512);
        //Serial.println("#wait");
        tft_print("#start wait");
        servoF(0, servo_rh);
        servoF(0, servo_rv);
        servoF(0, servo_lh);
        servoF(0, servo_lv);
        digitalWrite(IR, HIGH);
        break;
      }
    case MIRROR: {
        global_serial_buffer.clear();
        diodeColor(0, 512, 0);
        //Serial.println("#start mirror");
        tft_print("#start mirror");
        servoF(0, servo_rh);
        servoF(0, servo_rv);
        servoF(0, servo_lh);
        servoF(0, servo_lv);
        digitalWrite(IR, HIGH);
        break;
      }
    case FIGHT: {
        global_serial_buffer.clear();
        diodeColor(512, 0, 0);
        //Serial.println("#start fight");
        tft_print("#start fight");
        motors.IntWrite(0, 0);
        servoF(0, servo_belt);
        servoF(0, servo_rh);
        servoF(0, servo_rv);
        servoF(0, servo_lh);
        servoF(0, servo_lv);
        servoF(0, servo_neck);
        digitalWrite(IR, LOW);
        break;
      }
  }
}

#define get_global_state() (__global_state)




#endif
