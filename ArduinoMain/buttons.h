#ifndef buttons_h
#define buttons_h
#include <Arduino.h>
#include "pins.h"
#include "settings.h"

uint8_t buttons_click() {
  static uint32_t timer;
  static bool flag = false;

  float input = analogRead(PIN_BUTTONS);
  for (uint8_t i = 0; i <= PREF_BUTTONS_NUM; i++) {
    if (abs(input - (PREF_BUTTONS_MAX_LEVEL / PREF_BUTTONS_NUM) * i) <= ((PREF_BUTTONS_MAX_LEVEL * PREF_BUTTONS_ACCURACY) / 100)) {
      if (i && !flag) {
        flag = true;
        timer = millis();
        return i;
      } else if (!i && flag && millis() - timer >= PREF_BUTTONS_DELAY) {
        flag = false;
      }
    }
  }
  return 0;
}

uint8_t buttons_now() {
  float input = analogRead(PIN_BUTTONS);
  for (uint8_t i = 0; i <= PREF_BUTTONS_NUM; i++) {
    if (abs(input - (PREF_BUTTONS_MAX_LEVEL / PREF_BUTTONS_NUM) * i) <= ((PREF_BUTTONS_MAX_LEVEL * PREF_BUTTONS_ACCURACY) / 100)) {
      return i;
    }
  }
return 0;
}

#endif
