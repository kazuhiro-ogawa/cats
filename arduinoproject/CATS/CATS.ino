#include <Arduino.h>
#include "Brain.h"
#include "MotorControl.h"
#include "Motor.h"
#include "ServoMotor.h"
#include "Led.h"
#include "Bluetooth.h"
#include "Buzzer.h"
#include "Button.h"
#include "ObstacleDetection.h"
#include "TofDetection.h"
#include "SHallSensor.h"

/* 各クラスをインスタンス化 */
Brain brain;
MotorControl motorControl;
Motor motorL = Motor(MOTOR_L1_PIN,MOTOR_L2_PIN);
Motor motorR = Motor(MOTOR_R1_PIN,MOTOR_R2_PIN);
ServoMotor servoMotor = ServoMotor(SERVO_PIN);
Led led = Led(LED_PIN);
Bluetooth bluetooth = Bluetooth(BLUETOOTH1_PIN, BLUETOOTH2_PIN);
Buzzer buzzer = Buzzer(BUZZER_PIN);
Button callButton = Button(CALL_BUTTON_PIN);
Button cleanButton = Button(CLEAN_BUTTON_PIN);
ObstacleDetection obstacleDetectionL = ObstacleDetection(OBS_INTERRUPT_L_PIN);
ObstacleDetection obstacleDetectionR = ObstacleDetection(OBS_INTERRUPT_R_PIN);
TofDetection tofDetectionL = TofDetection(TOF_SDA_PIN, TOF_SCL_PIN);
TofDetection tofDetectionR = TofDetection(BUZZER_PIN);
HallSensor hallSensorL = HallSensor(HALL_SENSOR_L_PIN);
HallSensor hallSensorR = HallSensor(HALL_SENSOR_R_PIN);

MODE g_mode = WAIT;
ACTION_STATE action = ENTRY;

void change_mode(MODE mode) {
  g_mode = mode;
}


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

    // 待機モード
    case WAIT:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(SETTING_TABLE_NUMBER);
          change_mode(CALL);
          change_mode(START_CLEANING);
          break;
      }

    // テーブル番号設定モード
    case SETTING_TABLE_NUMBER:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(WAIT);
          break;
      }

    // 呼び出しモード
    case CALL:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(CALL);
          break;
      }

    // 清掃開始モード
    case START_CLEANING:
      switch (action) {
        case ENTRY:
          servoMotor.up();
          action = DO;
          break;
        case DO :
          break;
        case EXIT:
          change_mode(CLEANING);
          break;
      }

    // 清掃モード
    case CLEANING:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(STEP);
          change_mode(OBSTACLE);
          break;
      }

    // 段差定位モード
    case STEP:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(ROTATION);
          break;
      }

    // 障害物定位モード
    case OBSTACLE:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(ROTATION);
          break;
      }

    // 旋回モード
    case ROTATION:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(CLEANING);
          change_mode(CLEANING_COMPLETED);
          break;
      }

    // 清掃完了モード
    case CLEANING_COMPLETED:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          break;
          change_mode(HOME_BASE);
      }


    // 帰巣モード
    case HOME_BASE:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          change_mode(HALL_SENSOR);
          change_mode(STOP);
          break;
      }

    // ホールセンサ検知モード
    case HALL_SENSOR:
      switch (action) {
        case ENTRY:
          break;
        case DO :
          break;
        case EXIT:
          servoMotor.down();
          change_mode(WAIT);
          break;
      }

    // 強制停止モード
    case STOP:
      switch (action) {
        case ENTRY:
          servoMotor.down();
          break;
        case DO :
          break;
        case EXIT:
          break;
      }








    case INIT:
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
  }
}
