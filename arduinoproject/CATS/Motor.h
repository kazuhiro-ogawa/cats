#pragma once                          /*後ほど確認して数値を入力*/
#define NORMAL 50

class Motor{
  private:
  int m_motor1_pin;
  int m_motor2_pin;
  
  
  public:
  Motor(int motor1_pin, int motor2_pin);
  void driveMotor(int motor1_speed,int motor2_speed);
  int getMotor1_Pin(){
    return this,m_motor1_pin;
  }
  
  
  
};
