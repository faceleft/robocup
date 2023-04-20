#ifndef motors_h
#define motors_h
#include <Arduino.h>
#include "settings.h"
#include "pins.h"

class Motors {
  public:
    int _speed;
    Motors(uint8_t pin_rf, uint8_t pin_rb, uint8_t pin_lf, uint8_t pin_lb, int speed) {
      _pin_rf = pin_rf;
      _pin_rb = pin_rb;
      _pin_lf = pin_lf;
      _pin_lb = pin_lb;
      _speed = speed;
    }

    void SoftWrite(int r, int l) {
      int zn_r = 1;
      int zn_l = 1;
      if (this->r_state - r > 0) {
        zn_r = -1;
      }
      if (this->l_state - l > 0) {
        zn_l = -1;
      }
      int steps = max(abs(this->r_state - r), abs(this->l_state - l));
      for(int i = 0; i<steps; i++){
        //this->IntWrite(zn_r * min((this->r_state + zn_r)*zn_r, zn_r * r), zn_l * min((this->l_state + zn_l)*zn_l, zn_l * l));
        //this->IntWrite((r_state == r) ? (r_state + zn_r) : (r_state), (l_state == l) ? (l_state + zn_l) : (l_state));
        if(r_state == r){
          zn_r = 0;
        }
        if(l_state == l){
          zn_l = 0;
        }
        this->IntWrite(r_state + zn_r, l_state + zn_l);
        
        delay(this->_speed);
      }
    }

    void IntWrite(int r, int l) {
      this->RawWrite(max(0, r), abs(min(0, r)), max(0, l), abs(min(0, l)));
    }

    void RawWrite(uint8_t rf, uint8_t rb, uint8_t lf, uint8_t lb) {
      analogWrite(_pin_rf, min(255, rf));
      analogWrite(_pin_rb, min(255, rb));
      analogWrite(_pin_lf, min(255, lf));
      analogWrite(_pin_lb, min(255, lb));
      this->r_state = (int)rf - (int)rb;
      this->l_state = (int)lf - (int)lb;
    }

    void SetTarget(int r, int l) {
      this->r_target = r;
      this->l_target = l;
      millis_buff = millis();

    }
    void Work() {
      int times = millis() - this->millis_buff;
      if (times >= this->_speed) {
        this->millis_buff = millis();
        int k =  min(times/this->_speed, 10);
        
        if (this->r_state != r_target || this->l_state != l_target) {
          int zn_r = 1;
          int zn_l = 1;
          if (this->r_state - r_target > 0) {
            zn_r = -1;
          } 
          if (this->l_state - l_target > 0) {
            zn_l = -1;
          }
          this->IntWrite(zn_r * min((this->r_state + zn_r*k)*zn_r, zn_r * r_target), zn_l * min((this->l_state + zn_l*k)*zn_l, zn_l * l_target));
        }
      }
    }
  private:
    uint8_t _pin_rf;
    uint8_t _pin_rb;
    uint8_t _pin_lf;
    uint8_t _pin_lb;
    
    int r_state = 0;
    int l_state = 0;
    int r_target = 0;
    int l_target = 0;
    
    unsigned long millis_buff;

};

Motors motors(PIN_MOTOR_RIGHT_FORWARD,
              PIN_MOTOR_RIGHT_BACK,
              PIN_MOTOR_LEFT_FORWARD,
              PIN_MOTOR_LEFT_BACK,
              PREF_MOTORS_SPEED);
              
#endif
