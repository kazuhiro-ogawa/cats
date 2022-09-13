#pragma once



class Bluetooth{
  private :
  int m_bluetooth1_pin;　　　　　　　
  int m_bluetooth2_pin;
  int tableNumber =1;         //bluetoothに保存しておく番号(初期の値を入れておかないといけないので仮に1)　モジュール仕様書未記入の為確認
  public :
  BlueTooth();                           //コンストラクタ
  void Bluetooth::sendData();            //データ送信
  void Bluetooth::receiveData();         //データ受信
};
