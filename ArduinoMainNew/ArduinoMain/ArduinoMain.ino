#include "robot.h"

void functionManager(String message[]) {
  String& command = message[0];
  if (command == "heartbeat") {
    tft_print("heartbeat", 1, 220, 220, 255);
    Serial.println("heartbeat");
  } else if (command == "print") {
    tft_print("Jetson: ", 0, 255, 220, 255);
    for (int i = 1; i < PREF_STRING_BUFFER_LEN; i++) {
      if (message[i] != "") tft_print(message[i] + " ", 0);
    }
    tft_print(String(""), 1);
  } else if (command == "motors") {
    motors.SetTarget((message[1]).toInt(), (message[2]).toInt());
  } else if (command == "mirror") {
    set_global_state(MIRROR);
  } else if (command == "fight") {
    set_global_state(FIGHT);
  } else if (command == "flash") {
    diodeColor(1024, 1024, 1024);
    delay(100);
    diodeColor(0, 0, 512);
  } else {
    tft_print("!unknown command: ", 0, 255, 0, 0);
    tft_print(command, 1);
  }
}

void setup() {
  try(serial_init());
  try(ir_setup());
  try(display_setup());
  try(pwm.begin());
  pwm.setPWMFreq(60);
  mv::none();
  set_global_state(NONE);

  tft_print("End of setup");
}

void button1_handler() {
  delay(2000);
  Serial.println("mirror");
}
void button2_handler() {
  Serial.println("fight");
}
void button3_handler() {
  Serial.println("reset");
  set_global_state(NONE);
}
void button4_handler() {
  mv::punch();
}
void button5_handler() {
  Serial.println("screenshot");
  tft_print("screenshot");
}
void button6_handler() {
  Serial.println("heartbeat");
}


void loop() {
  motors.task();

  buttons_task(\
    button1_handler,\
    button2_handler,\
    button3_handler,\
    button4_handler,\
    button5_handler,\
    button6_handler\
  );

  switch (get_global_state()) {
    case MIRROR: {
        mv::mirror();
        if (mv::mirror_status.change_flag) {
          //mv::mirror_save_distance(); //раскомментировать чтобы держал дистанцию
          mv::mirror_rotate();
          mv::mirror_hands();
          mv::mirror_status.change_flag = false;
        }
    } break;

    case FIGHT: {
        mv::fight();
        if (mv::fight_status.change_flag) {
          mv::fight_rotate();
          mv::fight_status.change_flag = false;
        }
    } break;

    case NONE: {
        serial_task(functionManager);
    } break;
  }
}
