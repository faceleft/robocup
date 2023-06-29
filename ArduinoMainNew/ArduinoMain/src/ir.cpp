#include "ir.h"

#include "pins.h"
#include <Arduino.h>

void ir_setup() {
  pinMode(PIN_IR, OUTPUT);
  digitalWrite(PIN_IR, HIGH);
}

void ir_on() {
  digitalWrite(PIN_IR, LOW);
}

void ir_off() {
  digitalWrite(PIN_IR, HIGH);
}