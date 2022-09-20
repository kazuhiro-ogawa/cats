#include <Arduino.h>
#include "TofDetection.h"

TofDetection::TofDetection(int tof_sda_pin, int m_tof_scl_pin) {
  m_tof_sda_pin = tof_sda_pin;
  m_tof_scl_pin = tof_scl_pin;
}
