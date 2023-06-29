#ifndef ROBOT_GLOBAL_STATE_H
#define ROBOT_GLOBAL_STATE_H

#include "structures/static_queue.h"

//размер буффера, уменьшить при нежватки памяти
//если размера буффера не хватит будет вызвана error()
#define GLOBAL_SERIAL_BUFFER_SIZE 100

typedef enum { //состояния
  MIRROR,
  FIGHT,
  NONE,
} t_state;

//очередь serial для передачи данных
extern static_queue<char, GLOBAL_SERIAL_BUFFER_SIZE> global_serial_buffer;

//установить режим работы
void set_global_state(t_state state);

//посмотреть режим работы
t_state get_global_state();

#endif
