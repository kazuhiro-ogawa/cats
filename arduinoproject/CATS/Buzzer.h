#pragma once
#define BUZZER_TIME 2000

class Buzzer
{
  private:
    int m_buzzer_pin;

  public:
    Buzzer(int buzzer_pin);
    void on();
    void off();
};
