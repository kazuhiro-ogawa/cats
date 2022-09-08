#include <Arduino.h>

Motor::Motor(int motor1_pin,int motor2_pin;){               //左か右かちゃんと確認する//
  m_motor1_pin = motor1_pin;
  m_motor2_pin = motor2_pin;
}
void Motor::driveMotor(int motorOutput1,int motorOutput2){
  analogWrite(m_motor1_pin,motorOutput1);
  analogWrite(m_motor2_pin,motorOutput2);
}
