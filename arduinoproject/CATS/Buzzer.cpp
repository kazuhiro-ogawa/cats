#include <Arduino.h>
#include "Buzzer.h"

Buzzer::Buzzer(int buzzer_pin) {
  m_buzzer_pin = buzzer_pin;
  pinMode(m_buzzer_pin, INPUT);
}

void Buzzer::on() {
  digitalWrite(m_buzzer_pin, HIGH);
  tone(m_buzzer_pin,200,BUZZER_TIME);       //ブザーピン、ブザーの周波数、ブザーの時間
  delay(BUZZER_TIME);
}

void Buzzer::off() {
  digitalWrite(m_buzzer_pin, LOW);
}
