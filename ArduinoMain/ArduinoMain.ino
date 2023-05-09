#include "pins.h"
#include "settings.h"
#include "buttons.h"
#include "tools.h"
#include "motors.h"
#include "servo.h"
#include "activ.h"
#include "display.h"
#include "error.h"
#include "global_state.h"
#include <SoftwareSerial.h>

#include <Wire.h>


void functionManager(String *message);

void analyse(String text) {
  String message[PREF_STRING_BUFFER_LEN];
  String Word;
  int len = text.length();
  const char sep = ' ';
  bool complited = false;
  text[len - 1] = sep;
  int counter = 0;
  //*****************
  for (int i = 0; i < len; i++) {
    char sim = text[i];

    if (sim == sep) {
      if (Word == "-c") {
        complited = true;
        Word = "";
      } else {
        message[counter] = Word;
        counter++;
        Word = "";
      }
    } else {
      Word += sim;
    }
  }
  //****************

  functionManager(message);
  if (complited) {
    Serial.println("complited");
  }
}

void functionManager(String *message) {
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
  }
  else {
    tft_print("!unknown command: ", 0, 255, 0, 0);
    tft_print(command, 1);
  }
}

void setup() {
  Serial.begin(PREF_SERIAL_SPEED);
  Serial.setTimeout(PREF_SERIAL_TIMEOUT);
  pinMode(IR, OUTPUT);
  digitalWrite(IR, HIGH);
  display_init();
  pwm.begin();

  pwm.setPWMFreq(60);
  tft_print("#Start!", 1, 220, 255, 220);
  pwm.setPWM(SERVO_BELT_ADDR, 0 , SERVO_BELT_MEAN);
  mv::none();
  set_global_state(NONE);
}

void loop() {
  motors.Work();
  
  //buttons
  uint8_t a = buttons_click();
  if (a) {
    tft_print("Button " + String(a), 1, 220, 220, 255);
  }
  switch (a) {
    case 0: break;

    case 1: {
        Serial.println("mirror");
      } break;

    case 2: {
        Serial.println("fight");
      } break;

    case 3: {
        Serial.println("reset");
        set_global_state(NONE);      
      } break;

    case 4: {
        mv::punch();
      } break;

    case 5: {
        mv::r_MAX();
      } break;

    case 6: {
        mv::l_MAX();
      } break;
  }
  //end_buttons
  
  switch (get_global_state()) {
    case MIRROR: {
        mv::mirror();
        if (mv::mirror_status.change_flag) {
          mv::mirror_save_distance();
          mv::mirror_rotate();
          mv::mirror_hands();
          mv::mirror_status.change_flag = false;
        }
      } break;

    case FIGHT: {
        mv::fight();
        if (mv::fight_status.change_flag) {
          mv::fight_rotate();
          mv::fight_save_distance();
          mv::fight_status.change_flag = false;
        }
      } break;

    case NONE: {
        if (Serial.available()) {
          analyse(Serial.readString());
        }
      } break;
  }

}
