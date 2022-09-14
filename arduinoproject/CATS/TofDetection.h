#pragma once

class TofDetection{
  private :
  int m_tof_pin1;
  int m_tof_pin2;
  public :
  TofDetection(int tof_pin1,int tof_pin2);
  float tofDetection();
  boolean isStep();
};
