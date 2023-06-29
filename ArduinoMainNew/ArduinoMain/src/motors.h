#ifndef ROBOT_MOTORS_H
#define ROBOT_MOTORS_H

#include <Arduino.h>


class Motors
{
public:
  int _speed;
  Motors(uint8_t pin_rf, uint8_t pin_rb, uint8_t pin_lf, uint8_t pin_lb, int speed);
  void SoftWrite(int r, int l);
  void byTime(int r, int l, uint32_t _time);
  void IntWrite(int r, int l);
  void RawWrite(uint8_t rf, uint8_t rb, uint8_t lf, uint8_t lb);
  void SetTarget(int r, int l);
  void timeout_handler();
  void task();

private:
  uint8_t _pin_rf;
  uint8_t _pin_rb;
  uint8_t _pin_lf;
  uint8_t _pin_lb;

  int r_state = 0;
  int l_state = 0;
  int r_target = 0;
  int l_target = 0;

  uint32_t millis_buff;

  bool stop_flag = false;
  uint32_t stop_time;
  uint32_t stop_timeout;
};

extern Motors motors;

#endif
