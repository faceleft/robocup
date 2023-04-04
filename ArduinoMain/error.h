#ifndef error_h
#define error_h

#include <Arduino.h>
#include "display.h"

const char* ErrorNames[] = {
  "Alloc Error",
  "Pointer Error"
  };

enum Errors{
  ALLOC_ERROR,
  POINTER_ERROR
};

void error(Errors num){
        
    tft_print("!!!!!!!!!!!!!!", 1, 255, 0, 0);
    Serial.print("!!!!!!!!!!!!!!");
    
    tft_print("ERROR: ", 0, 255, 0, 0);
    Serial.print("ERROR: ");
    
    tft_print(ErrorNames[num], 1, 255, 0, 0);
    Serial.println(ErrorNames[num]);

    tft_print("at ", 0, 255, 0, 0);
    Serial.print("at ");
    
    tft_print(String((float)millis()/1024), 0, 255, 0, 0);
    Serial.print(String((float)millis()/1024));
    
    tft_print(" seconds", 0, 255, 0, 0);
    Serial.print(" seconds");
    
    for(;;);
}

#endif
