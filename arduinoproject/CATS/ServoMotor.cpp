#include <Servo.h>
#include <Arduino.h>


Servo servo;

ServoMotor::ServoMotor(int servo_pin){
  m_servo_pin = servo_pin;
}
void ServoMotor::up(){
  servo.write(SERVO_ANGLE);
  
}
void ServoMotor::down(){
  servo.write(0);
}
void ServoMotor::init(){
  servo.attach(m_servo_pin);
  servo.write(0);
}
