#include <Arduino.h>
#include"Buzzer.h"
#include "CATS.h"

Buzzer::Buzzer(int buzzer_pin){
  buzzer_time = BUZZER_TIME;
  m_buzzer_pin = buzzer_pin;
  pinMode(m_buzzer_pin,INPUT);
}
void Buzzer::on(){
  digitalWrite(m_buzzer_pin,HIGH);
  delay(buzzer_time);
}
void Buzzer::off(){
  digitalWrite(m_buzzer_pin,LOW);
}
