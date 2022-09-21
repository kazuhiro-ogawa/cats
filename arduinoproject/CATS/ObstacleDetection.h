#pragma once

class ObstacleDetection
{
  private:
    int m_obs_interrupt_pin;

  public:
    ObstacleDetection(int obs_interrupt_pin);
    int putOn();
};
