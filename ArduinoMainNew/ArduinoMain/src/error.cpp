#include "error.h"

void error(int num)
{

    tft_print("!!!!!!!!!!!!!!", 1, 255, 0, 0);
    Serial.print("!!!!!!!!!!!!!!");

    tft_print("ERROR: ", 0, 255, 0, 0);
    Serial.print("ERROR: ");

    tft_print(String(num), 1, 255, 0, 0);
    Serial.println(num);
    for (;;)
        ;
}