#pragma once;

class Button
{
  private:
    int m_button_pin;

  public:
    Button(int button_pin);
    int Read();
};
