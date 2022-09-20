/*#include <SoftwareSerial.h>
#include <Arduino.h>
#include "Bluetooth.h"
#include "CATS.h"

Bluetooth::Bluetooth(int bluetooth1_pin, int bluetooth2_pin) {
  m_bluetooth1_pin = bluetooth1_pin;
  m_bluetooth2_pin = bluetooth2_pin;
  Serial1.begin(115200);
}

void Bluetooth::receiveData(int tableNumber) {            // 受信メソッド　(保留)
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}

void Bluetooth::sendData(int tableNumber) {               // 送信メソッド
  while (Serial1.available()) {
    tableNumber = Serial1.read();
    Serial.write(tableNumber);
    Serial1.write(tableNumber);
  }
}*/
