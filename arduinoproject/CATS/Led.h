#pragma once

class Led
{
  private:
    int m_led_pin;

  public:
    Led(int led_pin);
    void on();
    void flicker();
    void off();
};
