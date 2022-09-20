#include <Wire.h>
#include <Arduino.h>
#include "HallSensor.h"

HallSensor::HallSensor(int hall_sensor_pin) {
  m_hall_sensor_pin = hall_sensor_pin;
  pinMode(m_hall_sensor_pin, OUTPUT);
}

boolean HallSensor::checkHall() {
  if (digitalRead(m_hall_sensor_pin) == LOW ) {
    return true;
  } else {
    return false;
  }
}
