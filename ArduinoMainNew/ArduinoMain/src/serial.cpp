#include "serial_analyser.h"

#include "settings.h"

static void analyse(String text, void (*callback)(String*)) {
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
      } 
      else {
        message[counter] = Word;
        counter++;
        Word = "";
      }
    } else {
      Word += sim;
    }
  }
  //****************
  if (callback != NULL) {
    callback(message);
  }

  if (complited) {
    Serial.println("complited");
  }
}

void serial_task(void (*callback)(String*)) {
    if (Serial.available()) {
        analyse(Serial.readString(), callback);
    }
}