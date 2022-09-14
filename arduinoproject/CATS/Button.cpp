#include <Arduino.h>
#include "Button.h"
#include "CATS.h"

Button::Button(int button_pin){
  m_button_pin = button_pin;
  pinMode(m_button_pin,INPUT);
}
