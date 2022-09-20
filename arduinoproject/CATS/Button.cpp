#include <Arduino.h>
#include "Button.h"

Button::Button(int button_pin) {
  m_button_pin = button_pin;
  pinMode(m_button_pin, INPUT_PULLUP);
}

int Button::Read() {
  return digitalRead(m_button_pin);
}
