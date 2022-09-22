#include <Wire.h>
#include <Arduino.h>
#include "CATS.h"
#include "MotorControl.h"
#include "Motor.h"
#include "ServoMotor.h"
#include "Led.h"
//#include "Bluetooth.h"
#include "Buzzer.h"
#include "Button.h"
#include "ObstacleDetection.h"
#include "TofDetection.h"
#include "HallSensor.h"

/* 各クラスをインスタンス化 */
//Brain brain;
MotorControl motorControl;
//Motor motorL = Motor(MOTOR_L1_PIN, MOTOR_L2_PIN);
//Motor motorR = Motor(MOTOR_R1_PIN, MOTOR_R2_PIN);
ServoMotor servoMotor = ServoMotor(SERVO_PIN);
Led led = Led(LED_PIN);
//Bluetooth bluetooth = Bluetooth(BLUETOOTH1_PIN, BLUETOOTH2_PIN);
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

boolean callBtnflg;
boolean cleanBtnflg;

void change_mode(MODE mode) {                     // アクションを自走してよいか確認
  g_mode = mode;
}

boolean flg = false;                              // 仮時装　旋回の向き
boolean finishFlg = false;                        // 仮自走　清掃終了フラグ
boolean trenFlg = false;                          // 仮自走　検知フラグ
int checkFlg = 0;                                 // 段差検知か障害物検知かチェック


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void loop() {
  switch (g_mode) {
    case WAIT:                                    // 待機モード
      switch (action) {
        case ENTRY:
          led.on();                               // LED点灯
          action = DO;
          break;
        case DO:
          if (callButton.putOn()) {               // 呼び出しボタン押下
            callBtnflg = true;
            action = EXIT;
          }
          if (cleanButton.putOn()) {              // 清掃開始ボタン押下
            cleanBtnflg = true;
            action = EXIT;
          }
          break;
        case EXIT:
          if (callBtnflg == true) {
            callBtnflg = false;
            change_mode(CALL);                    // 呼び出しモードへ
            action = ENTRY;
          }
          else if (cleanBtnflg == true) {
            cleanBtnflg = false;
            change_mode(START_CLEANING);          // 清掃開始モードへ
            action = ENTRY;
          }
          break;
      }


    case SETTING_TABLE_NUMBER:                    // テーブル番号設定モード
      switch (action) {
        case ENTRY:
          action = DO;
          break;
        case DO:
          action = EXIT;
          break;
        case EXIT:
          led.flicker();                          // LED点滅
          change_mode(WAIT);                      // 待機モードへ
          action = ENTRY;
          break;
      }


    case CALL:                                    // 呼び出しモード
      switch (action) {
        case ENTRY:
          buzzer.on();                            // ブザー鳴動・Android端末へテーブル番号送信？？？
          action = DO;
          break;
        case DO:
          action = EXIT;
          break;
        case EXIT:
          buzzer.off();                           // ブザー停止
          change_mode(WAIT);                      // 待機モードへ
          action = ENTRY;
          break;
      }


    case START_CLEANING:                          // 清掃開始モード
      switch (action) {
        case ENTRY:
          servoMotor.init();
          servoMotor.up();                        // サーボモータUP
          action = DO;
          break;
        case DO:
          action = EXIT;
          break;
        case EXIT:
          change_mode(CLEANING);                  // 清掃モードへ
          action = ENTRY;
          break;
      }


    case CLEANING:                                // 清掃モード
      switch (action) {
        case ENTRY:
          motorControl.goStraight();              // 直進走行
          action = DO;
          break;
        case DO:
          callBtnflg = true;
          if (callButton.putOn()) {               //段差検知をメモ帳に記載
            callBtnflg = true;
            checkFlg = 1;
            action = EXIT;
          }
          if (obstacleDetectionL.putOn() || obstacleDetectionR.putOn()) {
            callBtnflg = true;
            checkFlg = 2;
            action = EXIT;
          }
          break;
        case EXIT:
          if (checkFlg == 1) {
            change_mode(STEP);                    // 段差定位モードへ
            action = ENTRY;
            checkFlg = 0;
          } else if (checkFlg == 2) {
            change_mode(OBSTACLE);                // 障害物定位モードへ
            action = ENTRY;
            checkFlg = 0;
          }
          break;
      }


    case STEP:                                    // 段差定位モード
      switch (action) {
        case ENTRY:
          motorControl.brakes();                  // 走行停止
          action = DO;
          break;
        case DO:                                  // 漸進的旋回・（反対側の）段差検知？？？
          action = EXIT;
          break;
        case EXIT:
          change_mode(ROTATION);                  // 旋回モードへ
          action = ENTRY;
          break;
      }


    case OBSTACLE:                                // 障害物定位モード
      switch (action) {
        case ENTRY:
          motorControl.brakes();                  // 走行停止
          action = DO;
          break;
        case DO:                                  // 漸進的旋回・（反対側の）障害物検知？？？
          action = EXIT;
          break;
        case EXIT:
          change_mode(ROTATION);                  // 旋回モードへ
          action = ENTRY;
          break;
      }


    case ROTATION:                                // 旋回モード
      switch (action) {
        case ENTRY:
          action = DO;
          break;
        case DO:
          action = EXIT;
          break;
        case EXIT:                                // 旋回中に段差または障害物検知？？？
          motorControl.rotate(flg);
          if (flg == false) {
            flg = true;
          } else {
            flg = false;
          }
          change_mode(CLEANING);                  // 清掃モードへ
          action = ENTRY;
          if (finishFlg == true) {                // 清掃終了フラグを立てるためのプログラム
            change_mode(CLEANING_COMPLETED);      // 清掃完了モードへ
            action = ENTRY;
          }
          break;
      }


    case HOME_BASE:                               // 帰巣モード
      switch (action) {
        case ENTRY:
          motorControl.goStraight();              // 直進走行
          action = DO;
          break;
        case DO:                                  // 元のルートを逆に走行（障害物・段差・ホールセンサ検知）？？？
          if (cleanButton.putOn()) {              // 清掃開始ボタン押下
            cleanBtnflg = true;
            action = EXIT;
          }
                                                  //ホールセンサ検知モードを入れる
          break;
        case EXIT:
          change_mode(HALL_SENSOR);
          if (cleanButton.putOn()) {              // 清掃開始ボタン押下
            cleanBtnflg = true;
            change_mode(FORCE_STOP);              // 強制停止モードへ
            action = ENTRY;
            cleanButton = false;
          }
          break;
      }


    case HALL_SENSOR:                             // ホールセンサ検知モード
      switch (action) {
        case ENTRY:
          motorControl.returnHome();              // ホームベース帰還動作？？？
          action = DO;
          break;
        case DO:
          action = EXIT;
          break;
        case EXIT:
          servoMotor.down();                      // サーボモータDOWN
          change_mode(WAIT);                      // 待機モードへ
          action = ENTRY;
          finishFlg = false;
          break;
      }


    case FORCE_STOP:                              // 強制停止モード
      switch (action) {
        case ENTRY:
          motorControl.brakes();                  // 走行停止
          servoMotor.down();                      // サーボモータDOWN
          action = DO;
          break;
        case DO:
          led.flicker();                          // LED点滅
          action = EXIT;
          break;
        case EXIT:
          finishFlg = false;
          change_mode(WAIT);                      // 待機モードへ
          action = ENTRY;
          break;
      }


    case CLEANING_COMPLETED:                      // 清掃完了モード
      switch (action) {
        case ENTRY:
          if (flg == false) {
            flg = true;
          } else {
            flg = false;
          }
          break;
          motorControl.returnHome();              // 旋回停止・方向転換
          action = DO;
          break;
        case DO:
          action = EXIT;
          break;
        case EXIT:
          change_mode(HOME_BASE);                 // 帰巣モードへ
          action = ENTRY;
          break;
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
  
  
  
  }
  
}
int tofsensor()                       //TOFセンサー検知 
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
  data_cnt = 0;
  distance = 0;
  distance_tmp = 0;
  while(Wire.available())
  {
    distance_tmp = Wire.read();
    distance = (distance << (data_cnt*8)) | distance_tmp;
    data_cnt++;
  }

  Serial.print(distance);
  Serial.println(" mm");
  digitalWrite(25, HIGH);
  delay(45);
  return distance;
}
