#pragma once

class TofDetection{
  private :
  int m_tof_pin;
  public :
  TofDetection(int tof_pin);
  float tofDetection();
  boolean isStep();
}
