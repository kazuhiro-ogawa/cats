#include <Arduino.h>
#include "ObstacleDetection.h"
#include "CATS.h"

ObstacleDetection::ObstacleDetection(int obs_pin){
  m_obs_pin = obs_pin;
  pinMode(m_obs_pin,INPUT);
}
