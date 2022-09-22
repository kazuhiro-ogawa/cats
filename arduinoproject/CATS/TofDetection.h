#pragma once

class TofDetection {
  private:
    int m_tof_sda_pin;
    int m_tof_scl_pin;

  public:
    TofDetection(int tof_sda_pin, int tof_scl_pin);
    float tofDetection();
    boolean isStep();
};
