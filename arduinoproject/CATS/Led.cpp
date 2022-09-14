#include <Arduino.h>
#include "Led.h"
#include "CATS.h"

Led::Led(int led_pin){
  m_led_pin = led_pin;
  pinMode(m_led_pin,OUTPUT);
  
}
void Led::on(){
  digitalWrite(m_led_pin,HIGH);                  
}
void Led::blink(){
  digitalWrite(m_led_pin,LOW);                  
  delay(2000);                                  
  digitalWrite(m_led_pin,HIGH);
  delay(2000);
}
void Led::off(){
  digitalWrite(m_led_pin,LOW);                   /*LED消灯*/
}
