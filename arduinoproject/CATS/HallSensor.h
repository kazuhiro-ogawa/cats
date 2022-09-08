#pragma once
#define SERCH_TIME 2000  //いったん保留//

class HallSensor{
  private :
  int m_hall_sensor_pin;         
  public :
  HallSensor(int hall_sensor_pin);
  boolean checkHall();   //磁気検知
 
}
