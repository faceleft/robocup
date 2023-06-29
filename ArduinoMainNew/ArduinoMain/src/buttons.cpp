#include "buttons.h"

#include <Arduino.h>
#include "pins.h"

const float PREF_BUTTONS_NUM = 6;
const float PREF_BUTTONS_MAX_LEVEL = 1024;
const float PREF_BUTTONS_ACCURACY = 3; //%
const float PREF_BUTTONS_DELAY = 500;  // ms

typedef enum
{
  NO_BUTTON = 0,
  BUTTON_1 = 1,
  BUTTON_2 = 2,
  BUTTON_3 = 3,
  BUTTON_4 = 4,
  BUTTON_5 = 5,
  BUTTON_6 = 6,
} button_t;

static button_t buttons_click()
{
  static uint32_t timer;
  static bool flag = false;

  float input = analogRead(PIN_BUTTONS);
  for (uint8_t i = 0; i <= PREF_BUTTONS_NUM; i++)
  {
    if (abs(input - (PREF_BUTTONS_MAX_LEVEL / PREF_BUTTONS_NUM) * i) <= ((PREF_BUTTONS_MAX_LEVEL * PREF_BUTTONS_ACCURACY) / 100))
    {
      if (i && !flag)
      {
        flag = true;
        timer = millis();
        return (button_t)i;
      }
      else if (!i && flag && millis() - timer >= PREF_BUTTONS_DELAY)
      {
        flag = false;
      }
    }
  }
  return NO_BUTTON;
}

void buttons_task(
    void (*button1_handler)(void),
    void (*button2_handler)(void),
    void (*button3_handler)(void),
    void (*button4_handler)(void),
    void (*button5_handler)(void),
    void (*button6_handler)(void))
{
  button_t button = buttons_click();

  switch (button)
  {
  case NO_BUTTON:
    break;

  case BUTTON_1:
  {
    if (button1_handler != NULL)
    {
      button1_handler();
    }
  }
  break;

  case BUTTON_2:
  {
    if (button2_handler != NULL)
    {
      button2_handler();
    }
  }
  break;

  case BUTTON_3:
  {
    if (button3_handler != NULL)
    {
      button3_handler();
    }
  }
  break;

  case BUTTON_4:
  {
    if (button4_handler != NULL)
    {
      button4_handler();
    }
  }
  break;

  case BUTTON_5:
  {
    if (button5_handler != NULL)
    {
      button5_handler();
    }
  }
  break;

  case BUTTON_6:
  {
    if (button6_handler != NULL)
    {
      button6_handler();
    }
  }
  break;
  }
}
