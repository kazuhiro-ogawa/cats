#pragma once
#define SERVO_ANGLE 90     /*サーボモーターの回転角度仮*/


class ServoMotor{
  private :  
  int m_servo_pin;  

            
  public :
  ServoMotor(int servo_pin);
  void up();
  void down();
  void init();
  
    
  
};
