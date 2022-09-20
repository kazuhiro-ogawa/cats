#include <Arduino.h>
#include "Motor.h"

Motor::Motor(int motor1_pin, int motor2_pin) {
  m_motor1_pin = motor1_pin;
  m_motor2_pin = motor2_pin;
  pinMode(m_motor1_pin, OUTPUT);
  pinMode(m_motor2_pin, OUTPUT);
}

void Motor::driveMotor(int motorOutput1, int motorOutput2) {
  analogWrite(m_motor1_pin, motorOutput1);
  analogWrite(m_motor2_pin, motorOutput2);
}
