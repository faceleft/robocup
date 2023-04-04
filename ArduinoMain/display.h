#ifndef display_h
#define display_h
#include "pins.h"
#include "settings.h"
#include <UTFT.h>
UTFT display(TFT01_22SP,
             PIN_LED_MOSI,
             PIN_LED_SCK,
             PIN_LED_CS,
             PIN_LED_RESET,
             PIN_LED_DC);

#ifdef PREF_DISPLAY_BIG_FONT
extern uint8_t BigFont[];
#else
extern uint8_t SmallFont[];
#endif

void tft_print(String s = "", bool ln = 1, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) {
  static int n = 0;
  static int m = 0;
  int l = s.length();
  display.setColor(r, g, b);
  for (int i = 0; i < l; i++) {
      if (m >= PREF_DISPLAY_MAX_X) {
        n++;
        m = 0;
      }
      if (n >= PREF_DISPLAY_MAX_Y) {
        //display.clrScr();
        n = 0;
      } 
      display.print(String(s[i]), m * PREF_DISPLAY_KX, n * PREF_DISPLAY_KY);
          
      m++;
      
  }
  if (ln == 1) {
      n++;
      m = 0;
  }
  display.setColor(255, 255, 255);
}

#endif
