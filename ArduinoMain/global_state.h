#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H
typedef enum {
  MIRROR,
  FIGHT,
  NONE,
} t_state;

t_state __global_state;

void set_global_state(t_state state) {
  __global_state = state;
  switch (state) {
    case NONE: {
        diodeColor(0, 0, 512);
        //Serial.println("#wait");
        tft_print("#start wait");
        motors.IntWrite(0, 0);
        motors.SetTarget(0, 0);
        servoF(0, servo_belt);
        servoF(0, servo_rh);
        servoF(0, servo_rv);
        servoF(0, servo_lh);
        servoF(0, servo_lv);
        servoF(0, servo_neck);
        break;
      }
    case MIRROR: {
        diodeColor(0, 512, 0);
        //Serial.println("#start mirror");
        tft_print("#start mirror");
        break;
      }
    case FIGHT: {
        diodeColor(512, 0, 0);
        //Serial.println("#start fight");
        tft_print("#start fight");
        break;
      }
  }
}

#define get_global_state() __global_state

#endif
