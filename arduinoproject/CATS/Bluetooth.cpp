#include <Arduino.h>


Bluetooth::Bluetooth(bluetooth1_pin,bluetooth1_pin){
  m_bluetooth1_pin = bluetooth1_pin
  m_bluetooth2_pin = bluetooth2_pin
     
  Serial1.begin(115200);
  
}
void Bluetooth::receiveData(int tableNumber){                              //受信メソッド　(保留)
  while ( Serial1.available())
  {
    tableNumber =  Serial1.read();
    Serial.write(tableNumber;);
     Serial1.write(tableNumber;);
  }
}
void Bluetooth::sendData(){                                        //送信メソッド
   if(Serial.available()){
    tableNumber = Serial1.write(Serial.read());
  } 
}
