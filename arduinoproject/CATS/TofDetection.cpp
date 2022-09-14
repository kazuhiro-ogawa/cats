#include <Arduino.h>
#include "TofDetection.h"
#include "CATS.h"


TofDetection::TofDetection(int tof_pin1,int tof_pin2){
  m_tof_pin1 = tof_pin1;
  m_tof_pin2 = tof_pin2;
}
