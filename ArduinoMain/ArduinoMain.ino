#include "pins.h"
#include "settings.h"
#include "buttons.h"
#include "tools.h"
#include "motors.h"
#include "servo.h"
#include "activ.h"
#include "display.h"
#include "error.h"
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
      if (message[i] != "") tft_print(message[i]+" ", 0);
    }
    tft_print(String(""), 1);

  } else if (command == "motors") {
    motors.SetTarget((message[1]).toInt(), (message[2]).toInt());
  } else if (command == "mirror") {
    mv::mirror();
  }
  else {
    tft_print("!unknown command: ", 0, 255, 0, 0);
    tft_print(command, 1);
  }
}

void setup() {
  Serial.begin(PREF_SERIAL_SPEED);
  Serial.setTimeout(PREF_SERIAL_TIMEOUT);

  display.InitLCD();
  display.clrScr();
  display.setFont(SmallFont);
  display.setColor(VGA_GREEN);
  pwm.begin();

  pwm.setPWMFreq(60);
  tft_print("#Start!", 1, 220, 255, 220);
  //tft_print("#Serial: Speed=" + String(PREF_SERIAL_SPEED) + " Timeout=" + String(PREF_SERIAL_TIMEOUT), 1, 220, 255, 220);
  pwm.setPWM(SERVO_BELT_ADDR, 0 , SERVO_BELT_MEAN);
  mv::none();
  mv::set_left();

}

void loop() {
  //print("test ");
  char s;
  if (Serial.available()) {
    analyse(Serial.readString());
  }
  uint8_t a = buttons_click();
  if (a) {
    sprintf(&s, "%d", a);
    tft_print("Button " + s, 1, 220, 220, 255);
    Serial.println(s);
  }
  if (a == 1) {
    diodeColor(1024, 0, 0);

    //mv::r_huk();
  }
  if (a == 2) {
    diodeColor(0, 1024, 0);

    //mv::l_huk();
  }
  if (a == 3) {
    diodeColor(0, 0, 1024);

    //mv::r_MAX();
  }
  if (a == 4) {
    diodeColor(1024, 1024, 1024);

  } 
  if (a == 5) {
    diodeColor(0, 0, 0);

    //mv::tors();
  }
  if (a == 6) {
    diodeColor(1024, 0, 1024);

    //mv::mtrs();
  }

}
