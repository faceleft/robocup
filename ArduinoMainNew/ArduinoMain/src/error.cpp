#include "error.h"

#include <Arduino.h>
#include "display.h"


void error(int num) {
    tft_print("!!!!!!!!!!!!!!", 1, 255, 0, 0);
    tft_print("ERROR: ", 0, 255, 0, 0);
    tft_print(String(num), 1, 255, 0, 0);
    for (;;);
}