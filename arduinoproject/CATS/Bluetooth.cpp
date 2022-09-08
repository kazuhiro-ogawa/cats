#include <Arduino.h>
#include <SoftwareSerial.h>

Bluetooth::Bluetooth(bluetooth1_pin,bluetooth1_pin){
  m_bluetooth1_pin = bluetooth1_pin
  m_bluetooth2_pin = bluetooth2_pin
  SoftwareSerial BTserial(bluetooth1_pin,bluetooth2_pin);     //bluetoothのピン登録
  BTserial.begin(115200);
  
}
void Bluetooth::sendData(int tableNumber){                              //送信メソッド　(保留)
  while (BTserial.available())
  {
    bluetoothNo = BTserial.read();
    Serial.write(bluetoothNo;);
    BTserial.write(bluetoothNo;);
  }
}
void Bluetooth::receiveData(){                                        //受信メソッド
   if(Serial.available()){
    bluetoothNo = Serial.write(Serial.read());
  } 
}
