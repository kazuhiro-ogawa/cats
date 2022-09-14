#pragma once
#define BUZZER_TIME 2000

class Buzzer{
  private:
  int buzzer_time;
  int m_buzzer_pin;  /*ピン番号を入力*/
  public:
  Buzzer(int buzzer_pin);
  void on();
  void off();
  void init(); 
};
