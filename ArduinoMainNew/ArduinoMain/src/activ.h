#ifndef ROBOT_ACTIV_H
#define ROBOT_ACTIV_H

namespace mv
{
  struct { //состояние mirror
    float rv_hand;
    float lv_hand;
    float rh_hand;
    float lh_hand;
    float angle;
    float dist;
    bool change_flag = false;
    bool rotate_flag = false;
  } mirror_status;

  struct { //состояние fight
    float angle;
    float dist;
    bool change_flag = false;
    bool save_distance_flag = false;
  } fight_status;

  void none(); //начальное положение
  void r_huk(); //удар правой
  void l_huk(); //удар левой
  void r_aperkot(); //удар правой
  void l_aperkot(); //удар левой
  void meln(); //руки в стороны и врашение корпусом
  void r_MAX(); //сильный удар правой
  void l_MAX(); //сильный удар левой
  void tors(); //непомню, выяснить и доложить
  void mtrs(); //вперёд назад поездить
  void set_right(); //голову вправо
  void set_left(); //голову влево

  void punch(); //чередующиеся удары

  void mirror(); //обновление положения робота в режиме mirror
  void mirror_hands(); //повторение движения рук
  void mirror_rotate(); //поворот за человеком
  void mirror_save_distance(); //движение вслед за человеком

  void fight(); //обновление положения робота в режиме fight
  void fight_rotate(); //движение за целью и удары по ней
  void fight_delay(unsigned long ms); //вмесо delay при режиме fight

}
#endif
