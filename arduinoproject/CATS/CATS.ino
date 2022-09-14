#include <Wire.h>
#include <Arduino.h>
#include "MotorControl.h"
#include "Motor.h"
#include "ServoMotor.h"
#include "Led.h"
#include "Bluetooth.h"
#include "Buzzer.h"
#include "Button.h"
#include "ObstacleDetection.h"
#include "TofDetection.h"
#include "HallSensor.h"
#include "CATS.h"





/* 各クラスをインスタンス化 */
MotorControl motorControl;

/*Motor motorL = Motor(MOTOR_L1_PIN,MOTOR_L2_PIN);
Motor motorR = Motor(MOTOR_R1_PIN,MOTOR_R2_PIN);*/

ServoMotor servoMotor = ServoMotor(SERVO_PIN);
Led led = Led(LED_PIN);
Bluetooth bluetooth = Bluetooth(BLUETOOTH1_PIN, BLUETOOTH2_PIN);
Buzzer buzzer = Buzzer(BUZZER_PIN);
Button callButton = Button(CALL_BUTTON_PIN);
Button cleanButton = Button(CLEAN_BUTTON_PIN);
ObstacleDetection obstacleDetectionL = ObstacleDetection(OBS_INTERRUPT_L_PIN);
ObstacleDetection obstacleDetectionR = ObstacleDetection(OBS_INTERRUPT_R_PIN);
TofDetection tofDetectionL = TofDetection(TOF_SDA_PIN, TOF_SCL_PIN);
TofDetection tofDetectionR = TofDetection(TOF_SDA_PIN, TOF_SCL_PIN);
HallSensor hallSensorL = HallSensor(HALL_SENSOR_L_PIN);
HallSensor hallSensorR = HallSensor(HALL_SENSOR_R_PIN);

MODE g_mode = WAIT;
ACTION_STATE action = ENTRY;

void change_mode(MODE mode) {                       /*アクションを自走してよいか確認*/
  g_mode = mode;
}

boolean flg = false;                                /*仮時装　旋回の向き*/
boolean finishFlg = false;                         /*仮自走　清掃終了フラグ*/
boolean trenFlg = false;                          /*仮自走　検知フラグ*/
int checkFlg = 1;                                 /*段差検知か障害物検知かチェック*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  

}

void loop() {
  /*
    // put your main code here, to run repeatedly:
    if (callButton == LOW) {
    buzzer.on();
    buzzer.off();
    }
  */

  switch (g_mode) {

    /*待機モード   OK*/
    case WAIT:
      switch (action) {
        case ENTRY:
        led.on();
        action = DO;
        break;
        case DO :
        if(30 == HIGH || CALL_BUTTON_PIN == HIGH || CLEAN_BUTTON_PIN == HIGH ){
          action = EXIT;
        }
        if (digitalRead(HALL_SENSOR_L_PIN) == LOW)
  {
    
    Serial.print("OK");
  }
  else
  {
    
    Serial.print("NO");
  }
        break;
        case EXIT:
        if(30 == HIGH){
          change_mode(SETTING_TABLE_NUMBER);
          action = ENTRY;
        }
        else if(CALL_BUTTON_PIN == HIGH){         
          action = ENTRY;
          change_mode(CALL);
          
        }
        else if(CLEAN_BUTTON_PIN == HIGH){ 
          action = ENTRY;
          change_mode(START_CLEANING);
          
        }
        
        break;
      }

    /*テーブル番号設定モード*/
    case SETTING_TABLE_NUMBER:
      switch (action) {
        case ENTRY:
          action = DO;
          break;
        case DO :
        action = EXIT;
          break;
        case EXIT:
  


        
          action = ENTRY;
          change_mode(WAIT);
          break;
      }

    /*呼び出しモード   OK*/
    case CALL:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          buzzer.on();
          buzzer.off();
          change_mode(WAIT);
          break;
      }

    /*清掃開始モード　　OK*/
    case START_CLEANING:
      switch (action) {
        case ENTRY:
          servoMotor.up();
          action = DO;
          break;
        case DO :
        action = EXIT;
          break;
        case EXIT:
          action = ENTRY;
          change_mode(CLEANING);
          break;
      }

    /*清掃モード OK*/
    case CLEANING:
      switch (action) {
        case ENTRY:
         action = DO;
          break;
        case DO:
         motorControl.goStraight();             
         
/*         if(DistanceCheck() <= 4){
          action = EXIT;
          checkFlg = 1;
          }*/
         if(digitalRead(OBS_INTERRUPT_L_PIN == LOW)){
          action = EXIT;
          checkFlg = 2;
         }
                                  
          break;
        case EXIT:
          action = ENTRY;
          if(checkFlg == 1){
            change_mode(STEP);
          }
          else if(checkFlg == 2){
            change_mode(OBSTACLE);
          }
 
          break;
      }

    /*段差定位モード  OK*/
    case STEP:
      switch (action) {
        case ENTRY:
        action = DO;
          break;
        case DO :
        action = EXIT;
          break;
        case EXIT:
        action = ENTRY;
          change_mode(ROTATION);
          break;
      }

    /*障害物定位モード   OK*/
    case OBSTACLE:
      switch (action) {
        case ENTRY:
          action = DO;
          break;
        case DO :
          action = EXIT;
          break;
        case EXIT:
          action = ENTRY;
          change_mode(ROTATION);
          break;
      }

    /*旋回モード*/
    case ROTATION:
      switch (action) {
        case ENTRY:
          action = DO;
          break;
        case DO :
          action = EXIT;
          break;
        case EXIT:
          action = ENTRY;
          motorControl.rotate(flg);
          if(flg == false){
             flg = true;
          }else{
             flg = false;
          }
          change_mode(CLEANING);

          
          /*清掃終了フラグを立てるためのプログラム*/
          if(finishFlg == true){                                
          change_mode(CLEANING_COMPLETED);
          
          }
          break;
      }

    /* 清掃完了モード*/
    case CLEANING_COMPLETED:
      switch (action) {
        case ENTRY:
        action = DO;
        if(flg == false){
          flg = true;
        }
        else{
          flg =false;
        }
          break;
        case DO :
          break;
        case EXIT:
          break;
          change_mode(HOME_BASE);
      }


    /*帰巣モード*/
    case HOME_BASE:
      switch (action) {
        case ENTRY:
        action = DO;
          break;
        case DO :
        action = EXIT;
          break;
        case EXIT:
        action = ENTRY;
          change_mode(HALL_SENSOR);
          change_mode(STOP);
          break;
      }

    /*ホールセンサ検知モード*/
    case HALL_SENSOR:
      switch (action) {
        case ENTRY:
        action = DO;
          break;
        case DO :
        action = EXIT;
          break;
        case EXIT:
        action = ENTRY;
          servoMotor.down();
          change_mode(WAIT);
          break;
      }

    /*強制停止モード*/
    case STOP:
      switch (action) {
        case ENTRY:
          servoMotor.down();
          action = DO;
          break;
        case DO :
        action = EXIT;
          break;
        case EXIT:
        action = ENTRY;
        change_mode(WAIT);
          break;
      }
  }
  }
/*uint16_t DistanceCheck()                  TOFセンサの距離を返す
{
  uint16_t distance;
  uint16_t distance_tmp;
  uint8_t data_cnt;

  digitalWrite(25, LOW);
  delay(5);
  Serial.print("distance = ");

  Wire.beginTransmission(0x52);
  Wire.write(0xD3);
  Wire.endTransmission(false);
  Wire.requestFrom(0x52, 2);
  
  distance = 0;
  distance_tmp = 0;
  while(Wire.available())
  {
    distance_tmp = Wire.read();
    distance = (distance << (data_cnt*8)) | distance_tmp;
    
  }

  Serial.print(distance);
  Serial.println(" mm");
  digitalWrite(25, HIGH);
  delay(45);
  return distance;
}*/






    /*下はウォータースライダー*/

   /* case INIT:
      switch (action) {
        case ENTRY:
          action = DO;
          break;
        case DO :
          if (!button.Read()) {
            action = EXIT;
          }
          break;
        case EXIT:
          change_mode(COUNTDOWN);
          action = ENTRY;
          break;
      }
      break;

    case COUNTDOWN :
      switch (action) {
        case ENTRY:
          MsTimer2::start();
          action = DO;
          break;
        case DO:
          lcd.lcd_print(countdown_print[g_count]);
          if (g_count < 0) {
            MsTimer2::stop();
            action = EXIT;
          }
          break;
        case EXIT:
          change_mode(GATE);
          action = ENTRY;
          g_count = 6;
          break;
      }
      break;

    case GATE :
      switch (action) {
        case ENTRY:
          gate.gate_opn();
          action = DO;
          break;
        case DO:
          delay(3000);
          action = EXIT;
          break;
        case EXIT:
          gate.gate_cls();
          change_mode(WAIT);
          action = ENTRY;
          break;
      }
      break;

    case WAIT :
      switch (action) {
        case ENTRY:
          lcd.lcd_print(countdown_print[g_count]);
          action = DO;
          break;
        case DO :
          if (sensor.check_passing() || !button.Read()) {
            action = EXIT;
          }
          break;
        case EXIT:
          change_mode(COUNTDOWN);
          action = ENTRY;
          break;
      }
      break;
  }}*/
