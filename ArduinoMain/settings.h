#ifndef settings_h
#define settings_h

#define PREF_SERIAL_SPEED 115200
#define PREF_SERIAL_TIMEOUT 50 //ms

#define PREF_VREF 2.5  //Volts

#define PREF_BUTTONS_NUM 6.0
#define PREF_BUTTONS_MAX_LEVEL 1024.0
#define PREF_BUTTONS_ACCURACY 3.0  //%
#define PREF_BUTTONS_DELAY 500.0   //ms

//#define PREF_DISPLAY_BIG_FONT

#ifdef PREF_DISPLAY_BIG_FONT
  #define PREF_DISPLAY_KX 16
  #define PREF_DISPLAY_KY 20
  #define PREF_DISPLAY_MAX_X 20
  #define PREF_DISPLAY_MAX_Y 12
#else
  #define PREF_DISPLAY_KX 8
  #define PREF_DISPLAY_KY 15
  #define PREF_DISPLAY_MAX_X 40
  #define PREF_DISPLAY_MAX_Y 16
#endif

#define PREF_MOTORS_SPEED 2



#endif
