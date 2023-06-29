#ifndef ROBOT_MOTORS_H
#define ROBOT_MOTORS_H

#include <Arduino.h>


class Motors
{
public:
  int _speed; //скорость (лучше не трогать)
  Motors(uint8_t pin_rf, uint8_t pin_rb, uint8_t pin_lf, uint8_t pin_lb, int speed); //ненужно

  void SoftWrite(int r, int l); //плавное движение, от -255 до 255
  void byTime(int r, int l, uint32_t _time); //вроде не работает
  void IntWrite(int r, int l); //управление моторами, от -255 до 255
  void RawWrite(uint8_t rf, uint8_t rb, uint8_t lf, uint8_t lb); //прямые значения pwm выходов моторов
  void SetTarget(int r, int l); //аналогично SoftWrite но происходит параллельно программе, нужен task() в void loop()
  void timeout_handler(); //не работает
  void task(); //task() в void loop() для работы SetTarget()

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

extern Motors motors; //единственный нужный экземпляр класса моторов

#endif
