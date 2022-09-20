#include <Arduino.h>
#include "Led.h"

Led::Led(int led_pin) {
  m_led_pin = led_pin;
  pinMode(m_led_pin, OUTPUT);
}

void Led::on() {                        //LED点灯
  digitalWrite(m_led_pin, HIGH);
}

void Led::flicker() {                   //LED点滅
  digitalWrite(m_led_pin, HIGH);
  delay(500);
  digitalWrite(m_led_pin, LOW);
  delay(500);
}

void Led::off() {                       //LED消灯
  digitalWrite(m_led_pin, LOW);
}
