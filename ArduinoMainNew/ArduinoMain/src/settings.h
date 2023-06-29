#ifndef ROBOT_SETTINGS_H
#define ROBOT_SETTINGS_H

//#define PREF_DISPLAY_BIG_FONT //раскоментировать для крупного шрифта дисплея

extern const int PREF_STRING_BUFFER_LEN; //макс. количество слов в комманде получаемой по serial

extern const unsigned long PREF_SERIAL_SPEED; //скорость serial
extern const int PREF_SERIAL_TIMEOUT; //время ожидания Serial.readString()

extern const int PREF_DISPLAY_KX; 
extern const int PREF_DISPLAY_KY;
extern const int PREF_DISPLAY_MAX_X;
extern const int PREF_DISPLAY_MAX_Y;

extern const int PREF_MOTORS_SPEED;

#endif
