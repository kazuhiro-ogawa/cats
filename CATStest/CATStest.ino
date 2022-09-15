// Bluetoothモジュール HC-05(HC-06) ATモード設定用スケッチ
// シリアルモニタを使用した通信スケッチになります
// https://burariweb.info
//
// HC-05はスイッチを押しながら電源投入でATモードに入ります。
// HC-06は電源投入と同時にATモードに入ります。
//
// デフォルトのボーレートは HC-05（34800bps)・HC-06(9600bps)となっています。
// HC-05は［NL+CR］、HC-06は［改行なし］でコマンドを送信！
//
 int no;
 int SW;
 void setup() 
{
     Serial.begin(9600);
     Serial.println("AT コマンドを入力 :");
     pinMode(7,INPUT);
    
// HC-05のデフォルトでのボーレートは38400
// HC-06のデフォルトのボーレートは9600
     Serial1.begin(9600);
}
 
 void loop()
{
// HC-05(HC-06)から読み取りシリアルモニタに送信する
  if (Serial1.available())
  {  
    Serial.write(Serial1.read());
  }
 
  // シリアルモニタからのデータを読み取りHC-05(HC-06)に送信する
  if (Serial.available()){
    Serial1.write(Serial.read());
    Serial.print("ok");
  }
     
  SW = digitalRead(7);
  if(SW == HIGH){
    
    Serial1.println("1");
    Serial1.write(Serial.read()); 
    
    
  }
  
}
