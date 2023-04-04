#include "pins.h"
#include "settings.h"
#include "buttons.h"
#include "tools.h"
#include "motors.h"
#include "list.h"
#include "servo.h"
#include "activ.h"
#include "display.h"
#include "error.h"
#include <SoftwareSerial.h>

#include <Wire.h>




void functionManager(const list<String>&);
void analyse(String text) {

  list<String> message;
  String Word;
  int len = text.length();
  const char sep = '|';
  bool complited = false;
  text[len - 1] = sep;
  //*****************
  for (int i = 0; i < len; i++) {
    char sim = text[i];

    if (sim == sep) {
      if (Word == "-c") {
        complited = true;
        Word = "";
      } else {
        message.append(Word);
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
  message.clear();
}

void functionManager(list<String>& message) {
  String command = message.at(0);
  if (command == "heartbeat") {
    tft_print("heartbeat", 1, 220, 220, 255);
    Serial.println("heartbeat");
  } else if (command == "print") {
    tft_print("Jetson: ", 0, 255, 220, 255);
    tft_print(message.at(1));
  } else if (command == "motors") {
    motors.SetTarget((message.at(1)).toInt(), (message.at(2)).toInt());
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
  tft_print("#Serial: Speed=" + String(PREF_SERIAL_SPEED) + " Timeout=" + String(PREF_SERIAL_TIMEOUT), 1, 220, 255, 220);
  pwm.setPWM(SERVO_BELT_ADDR, 0 ,SERVO_BELT_MEAN);
  
}

void loop() {
  static int j = SERVO_RH_MEAN;
  static int k = SERVO_RV_MEAN;
  //print("test ");
  if (Serial.available()) {
    analyse(Serial.readString());
  }
  uint8_t a = buttons_click();
  if (a) {
    String s = "Button " + String(a);
    tft_print(s + " " + String(j), 1, 220, 220, 255);
    Serial.println(s);
  }
  if(a==1){
    diodeColor(1024, 0, 0);
    //mv::r_huk();
  }
  if(a==2){
    diodeColor(0, 1024, 0);
    //mv::l_huk();
  }
  if(a==3){
    diodeColor(0, 0, 1024);
    //mv::r_MAX();
  }
  if(a==4){
    diodeColor(1024, 1024, 1024);
    //mv::l_MAX();
  }
  if(a==5){
    diodeColor(0, 0, 0);
    //mv::tors();
  }
  if(a==6){
    diodeColor(1024, 0, 1024);
    //mv::mtrs();
  }
}
