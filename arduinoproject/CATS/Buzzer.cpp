#include <Arduino.h>
#include"Buzzer.h"

Buzzer::Buzzer(int buzzer_pin){
  buzzer_time = BUZZER_TIME;
  m_buzzer_pin = buzzer_pin;
  pinMode(buzzer_pin,INPUT_PULLUP);
}
void Buzzer::on(){
  digitalWrite(buzzer_pin,HIGH);
  delay(Buzzer_time);
}
void Buzzer::off(){
  digitalWrite(buzzer_pin,LOW);
}
