#include <Arduino.h>
#include "ObstacleDetection.h"
#include "CATS.h"

ObstacleDetection::ObstacleDetection(int obs_interrupt_pin) {
  m_obs_interrupt_pin = obs_interrupt_pin;
  pinMode(m_obs_interrupt_pin, INPUT);
}
