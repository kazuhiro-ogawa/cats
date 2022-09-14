#include <Arduino.h>
#include "Motor.h"
#include "MotorControl.h"
#include "CATS.h"

Motor motorL(MOTOR_L1_PIN,MOTOR_L2_PIN);
Motor motorR(MOTOR_R1_PIN,MOTOR_R2_PIN);

void MotorControl::goStraight(){
  motorL.driveMotor(NORMAL,0);
  motorR.driveMotor(NORMAL,0);
  
}
void MotorControl::stops(){
  motorL.driveMotor(0,0);
  motorR.driveMotor(0,0);
  
}
void MotorControl::rotate(bool turn){
  if(turn == true){                   /*左右の旋回の判定のtrue/falseを決める、dealy時間で正確に回れるかチェック*/
    motorL.driveMotor(NORMAL,0);
    motorR.driveMotor(0,0);
    
  }else{
    motorL.driveMotor(0,0);
    motorR.driveMotor(NORMAL,0);
  }
  delay(2000);                         /*時間確認   検知モードを把握するためdelayの時間を2回に分ける（仮に１度目で９０度旋回するとしてそこで段差検知を行う）*/
                          
} 
void MotorControl::back(){
    motorL.driveMotor(0,NORMAL);       /*バックのスピードを変える必要がある？あと途中で止まる動作が必要？*/
    motorR.driveMotor(0,NORMAL);
}
/*void returnHome(){
}    　　　　　　　　　　　　　　　　　　　　　　　/*処理が難しい、保留*/  
