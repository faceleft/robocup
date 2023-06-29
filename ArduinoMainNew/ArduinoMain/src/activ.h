#ifndef ROBOT_ACTIV_H
#define ROBOT_ACTIV_H

namespace mv
{
  struct {
    float rv_hand;
    float lv_hand;
    float rh_hand;
    float lh_hand;
    float angle;
    float dist;
    bool change_flag = false;
    bool rotate_flag = false;
  } mirror_status;

  struct {
    float angle;
    float dist;
    bool change_flag = false;
    bool save_distance_flag = false;
  } fight_status;

  void none();
  void r_huk();
  void l_huk();
  void r_aperkot();
  void l_aperkot();
  void meln();
  void r_MAX();
  void l_MAX();
  void tors();
  void mtrs();
  void set_right();
  void set_left();

  void punch();

  void mirror();
  void mirror_hands();
  void mirror_rotate();
  void mirror_save_distance();

  void fight();
  void fight_rotate();
  void fight_save_distance();
  void fight_delay(unsigned long ms);

}
#endif
