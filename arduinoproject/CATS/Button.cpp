#include <Arduino.h>

Button::Button(int button_pin){
  M_button_pin = button_pin;
  pinMode(m_button_pin,INPUT_PULLUP);
}
