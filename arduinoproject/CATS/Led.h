#pragma once

class Led{
  private:
  int m_led_pin;                //ピン番号

  public:
  
  Led(int led_pin);
  void on();
  void blink();
  void off();
}
