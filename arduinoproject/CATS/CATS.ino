#include <Wire.h>
#include <Arduino.h>
//#include "Brain.h"
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
int checkFlg = 1;                                 // 段差検知か障害物検知かチェック


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
          break;
        case DO:
          if (callButton.Read()) {                // 呼び出しボタン押下
            callBtnflg = true;
            action = EXIT;
          }
          if (cleanButton.Read()) {               // 清掃開始ボタン押下
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


    /*待機モード   OK
        if(30 == HIGH || CALL_BUTTON_PIN == HIGH || CLEAN_BUTTON_PIN == HIGH ){
          action = EXIT;
        }
        int base = 2500;
        float voltage1 =(analogRead(A0) / 1024.0) * 5.0 * 1000;
        float voltage2 =(analogRead(A1) / 1024.0) * 5.0 * 1000;
        if (base<=voltage1||base<=voltage2)
      {

      Serial.print("OK");
      Serial.print((voltage1 - base)/5.0);
      }
      else
      {

      Serial.print("NO");
      Serial.print((base - voltage2)/5);
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
    */

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
          buzzer.on();                             // ブザー鳴動・Android端末へテーブル番号送信？？？
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
          motorControl.goStraight();               // 直進走行
          action = DO;
          break;
        case DO:
          callBtnflg = true;
          if (callButton.Read()) {
            callBtnflg = true;
            checkFlg = 1;
            action = EXIT;
          }
          if (digitalRead(OBS_INTERRUPT_L_PIN == LOW)) {
            callBtnflg = true;
            checkFlg = 2;
            action = EXIT;
          }
          break;
        case EXIT:
          if (checkFlg == 1) {
            change_mode(STEP);                    // 段差定位モードへ
            action = ENTRY;
          } else if (checkFlg == 2) {
            change_mode(OBSTACLE);                // 障害物定位モードへ
            action = ENTRY;
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
          break;
      }


    case ROTATION:                                // 旋回モード
      switch (action) {
        case ENTRY:
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
          /*清掃終了フラグを立てるためのプログラム*/
          if (finishFlg == true) {
            change_mode(CLEANING_COMPLETED);      // 清掃完了モードへ
            action = ENTRY;
          }
          break;
      }


    case CLEANING_COMPLETED:                      // 清掃完了モード
      switch (action) {
        case ENTRY:
          if (flg == false) {
            flg = true;
          }
          else {
            flg = false;
          }
          break;
          motorControl.returnHome();               // 旋回停止・方向転換
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


    case HOME_BASE:                               // 帰巣モード
      switch (action) {
        case ENTRY:
          motorControl.goStraight();               // 直進走行
          action = DO;
          break;
        case DO:                                  // 元のルートを逆に走行（障害物・段差・ホールセンサ検知）？？？
          if (cleanButton.Read()) {               // 清掃開始ボタン押下
            cleanBtnflg = true;
            action = EXIT;
          }
          break;
        case EXIT:
          change_mode(HALL_SENSOR);
          if (cleanButton.Read()) {               // 清掃開始ボタン押下
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
          action = ENTRY;
          change_mode(WAIT);                      // 待機モードへ
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


      /*下はウォータースライダー
                case INIT:
                  switch (action) {
                    case ENTRY:
                      action = DO;
                      break;
                    case DO:
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
                    case DO:
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
      */
  }
}
