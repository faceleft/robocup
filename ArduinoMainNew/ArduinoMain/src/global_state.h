#ifndef ROBOT_GLOBAL_STATE_H
#define ROBOT_GLOBAL_STATE_H

#include "structures/static_queue.h"

#define GLOBAL_SERIAL_BUFFER_SIZE 100

typedef enum {
  MIRROR,
  FIGHT,
  NONE,
} t_state;

extern static_queue<char, GLOBAL_SERIAL_BUFFER_SIZE> global_serial_buffer;

void set_global_state(t_state state);

t_state get_global_state();

#endif
