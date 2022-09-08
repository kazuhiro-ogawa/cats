#pragma once
#define m_buzzer_pin
#define BUZZER_TIME 2000

class Buzzer{
  private :
  int buzzer_time;
  void init(); 
  int buzzer_pin  //ピン番号を入力
  public :
  Buzzer(int buzzer_pin);
  void on();
  void off();
  
};
