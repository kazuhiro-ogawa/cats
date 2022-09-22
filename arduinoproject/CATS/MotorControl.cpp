#include <Arduino.h>
#include "Motor.h"
#include "MotorControl.h"
#include "CATS.h"

Motor motorL(MOTOR_L1_PIN, MOTOR_L2_PIN);
Motor motorR(MOTOR_R1_PIN, MOTOR_R2_PIN);

/*void goStraight() {
  motorL.driveMotor(NORMAL, STOP);
  motorR.driveMotor(NORMAL, STOP);
}

void brakes() {
  motorL.driveMotor(STOP, STOP);
  motorR.driveMotor(STOP, STOP);
}*/

void MotorControl::goStraight() {                   //digitalWrite()   digitalWriteをつけて動かす？
  analogWrite(MOTOR_L1_PIN, NORMAL);
  analogWrite(MOTOR_L2_PIN, STOP);
  analogWrite(MOTOR_R1_PIN, NORMAL);
  analogWrite(MOTOR_R2_PIN, STOP);
  motorL.driveMotor(HIGH, LOW);
  motorR.driveMotor(HIGH, LOW);
}

void MotorControl::brakes() {
  analogWrite(MOTOR_L1_PIN, STOP);
  analogWrite(MOTOR_L2_PIN, STOP);
  analogWrite(MOTOR_R1_PIN, STOP);
  analogWrite(MOTOR_R2_PIN, STOP);
  motorL.driveMotor(LOW, LOW);
  motorR.driveMotor(LOW, LOW);
}

void MotorControl::rotate(bool turn) {
  if (turn == true) {                               //左右の旋回の判定のtrue/falseを決める、dealy時間で正確に回れるかチェック
    analogWrite(MOTOR_L1_PIN, NORMAL);
    analogWrite(MOTOR_L2_PIN, STOP);
    analogWrite(MOTOR_R1_PIN, STOP);
    analogWrite(MOTOR_R2_PIN, STOP);
    motorL.driveMotor(HIGH, LOW);
    motorR.driveMotor(LOW, LOW);
  } else {
    analogWrite(MOTOR_L1_PIN, STOP);
    analogWrite(MOTOR_L2_PIN, STOP);
    analogWrite(MOTOR_R1_PIN, NORMAL);
    analogWrite(MOTOR_R2_PIN, STOP);
    motorL.driveMotor(LOW, LOW);
    motorR.driveMotor(HIGH, LOW);
  }
  delay(0);                                         //時間確認   検知モードを把握するためdelayの時間を2回に分ける（仮に１度目で９０度旋回するとしてそこで段差検知を行う）
  goStraight();                                     //直進に戻る
}

void MotorControl::back() {
  analogWrite(MOTOR_L1_PIN, STOP);
  analogWrite(MOTOR_L2_PIN, NORMAL);
  analogWrite(MOTOR_R1_PIN, STOP);
  analogWrite(MOTOR_R2_PIN, NORMAL);
  motorL.driveMotor(LOW, HIGH);                     //バックのスピードを変える必要がある？あと途中で止まる動作が必要？
  motorR.driveMotor(LOW, HIGH);
}

void MotorControl::returnHome() {                   //処理が難しい、保留
}
