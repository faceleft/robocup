#include "settings.h"

const int PREF_STRING_BUFFER_LEN = 20;

const unsigned long PREF_SERIAL_SPEED = 115200;
const int PREF_SERIAL_TIMEOUT = 50;

#ifdef PREF_DISPLAY_BIG_FONT
const int PREF_DISPLAY_KX = 16;
const int PREF_DISPLAY_KY = 20;
const int PREF_DISPLAY_MAX_X = 20;
const int PREF_DISPLAY_MAX_Y = 12;
#else
const int PREF_DISPLAY_KX = 8;
const int PREF_DISPLAY_KY = 15;
const int PREF_DISPLAY_MAX_X = 40;
const int PREF_DISPLAY_MAX_Y = 16;
#endif

const int PREF_MOTORS_SPEED = 2;
