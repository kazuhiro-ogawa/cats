#include <Arduino.h>

Led::Led(int led_pin){
  m_led_pin = led_pin;
  pinMode(m_led_pin,HIGH);
  
}
void Led::on(){
  digitalWrite(m_led_pin,HIGH);                  //LED点灯
}
void Led::blink(){
  digitalWrite(m_led_pin,LOW);                  //テーブル番号変更時にLED点滅
  delay(2000);                                  //時間後ほど確認// 
  digitalWrite(m_led_pin,HIGH);
  delay(2000);
}
void Led::off(){
  digitalWrite(m_led_pin,LOW);                   //LED消灯
}
