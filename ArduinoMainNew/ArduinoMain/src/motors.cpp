#include "motors.h"

#include "settings.h"
#include "pins.h"
#include "display.h"

Motors::Motors(uint8_t pin_rf, uint8_t pin_rb, uint8_t pin_lf, uint8_t pin_lb, int speed)
{
    _pin_rf = pin_rf;
    _pin_rb = pin_rb;
    _pin_lf = pin_lf;
    _pin_lb = pin_lb;
    _speed = speed;
}

void Motors::SoftWrite(int r, int l)
{
    int zn_r = 1;
    int zn_l = 1;
    if (this->r_state - r > 0)
    {
        zn_r = -1;
    }
    if (this->l_state - l > 0)
    {
        zn_l = -1;
    }
    int steps = max(abs(this->r_state - r), abs(this->l_state - l));
    for (int i = 0; i < steps; i++)
    {
        // this->IntWrite(zn_r * min((this->r_state + zn_r)*zn_r, zn_r * r), zn_l * min((this->l_state + zn_l)*zn_l, zn_l * l));
        // this->IntWrite((r_state == r) ? (r_state + zn_r) : (r_state), (l_state == l) ? (l_state + zn_l) : (l_state));
        if (r_state == r)
        {
            zn_r = 0;
        }
        if (l_state == l)
        {
            zn_l = 0;
        }
        this->IntWrite(r_state + zn_r, l_state + zn_l);

        delay(this->_speed);
    }
}
void Motors::byTime(int r, int l, uint32_t _time)
{
    stop_flag = true;
    stop_time = millis();
    stop_timeout = _time;
    SetTarget(r, l);
}

void Motors::IntWrite(int r, int l)
{
    this->RawWrite(max(0, min(r,255)), -min(0, max(r,-255)), max(0, min(l,255)), -min(0, max(l, -255)));
}

void Motors::RawWrite(uint8_t rf, uint8_t rb, uint8_t lf, uint8_t lb)
{
    analogWrite(_pin_rf, rf);
    analogWrite(_pin_rb, rb);
    analogWrite(_pin_lf, lf);
    analogWrite(_pin_lb, lb);
    this->r_state = (int)rf - (int)rb;
    this->l_state = (int)lf - (int)lb;
}

void Motors::SetTarget(int r, int l)
{
    this->r_target = r;
    this->l_target = l;
    millis_buff = millis();
}
void Motors::timeout_handler()
{
    if (stop_flag == true && (stop_timeout >= millis() - stop_time))
    {
        stop_flag = false;
        SetTarget(0, 0);
        tft_print("STOP_BY_TIME");
    }
}
void Motors::task()
{
    // timeout_handler();
    int times = millis() - this->millis_buff;
    if (times >= this->_speed)
    {
        this->millis_buff = millis();
        int k = min(times / this->_speed, 10);

        if (this->r_state != r_target || this->l_state != l_target)
        {
            int zn_r = 1;
            int zn_l = 1;
            if (this->r_state - r_target > 0)
            {
                zn_r = -1;
            }
            if (this->l_state - l_target > 0)
            {
                zn_l = -1;
            }
            this->IntWrite(zn_r * min((this->r_state + zn_r * k) * zn_r, zn_r * r_target), zn_l * min((this->l_state + zn_l * k) * zn_l, zn_l * l_target));
        }
    }
}

Motors motors(PIN_MOTOR_RIGHT_FORWARD,
              PIN_MOTOR_RIGHT_BACK,
              PIN_MOTOR_LEFT_FORWARD,
              PIN_MOTOR_LEFT_BACK,
              PREF_MOTORS_SPEED);