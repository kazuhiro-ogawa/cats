/* インクルードガード */
#pragma once

/* pin管理 */
#define MOTOR_L1_PIN 10
#define MOTOR_L2_PIN 11
#define MOTOR_R1_PIN 12
#define MOTOR_R2_PIN 13
#define SERVO_PIN 8
#define LED_PIN 50
#define BLUETOOTH1_PIN 2
#define BLUETOOTH2_PIN 3
#define BUZZER_PIN 52
#define CALL_BUTTON_PIN 0
#define CLEAN_BUTTON_PIN 4
#define OBS_INTERRUPT_L_PIN 19
#define OBS_INTERRUPT_R_PIN 18
#define TOF_SDA_PIN 20
#define TOF_SCL_PIN 21
#define HALL_SENSOR_L_PIN 46
#define HALL_SENSOR_R_PIN 44

/* mode */
typedef enum {
  WAIT,                   /*待機モード*/
  SETTING_TABLE_NUMBER,   /*テーブル番号設定モード*/
  CALL,                   /*呼び出しモード*/
  START_CLEANING,         /*清掃開始モード*/
  CLEANING,               /*清掃モード*/
  STEP,                   /*段差定位モード*/
  OBSTACLE,               /*障害物定位モード*/
  ROTATION,               /*旋回モード*/
  HOME_BASE,              /*帰巣モード*/
  HALL_SENSOR,            /*ホールセンサ検知モード*/
  STOP,                   /*強制停止モード*/
  CLEANING_COMPLETED,     /*清掃完了モード*/
} MODE;

typedef enum {
  ENTRY,                  /*エントリー*/
  DO,                     /*ドゥー*/
  EXIT,                   /*イグジット*/
} ACTION_STATE;
