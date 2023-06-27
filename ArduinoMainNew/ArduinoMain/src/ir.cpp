#include "ir.h"

#include <Arduino.h>

uint8_t __ir_pin;

void ir_setup(uint8_t ir_pin) {
  __ir_pin = ir_pin;
  pinMode(__ir_pin, OUTPUT);
  digitalWrite(__ir_pin, HIGH);
}

void ir_on() {
  digitalWrite(__ir_pin, LOW);
}

void ir_off() {
  digitalWrite(__ir_pin, HIGH);
}