#include "Motor.h"

Motor motorL;
Motor motorR;

void MotorControl::goStraight(){
  motorL.driveMotor(NORMAL,STOP);
  motorR.driveMotor(NORMAL,STOP);
  
}
void MotorControl::stop(){
  motorL.driveMotor(STOP,STOP);
  motorR.driveMotor(STOP,STOP);
  
}
void MotorControl::rotate(boolean turn){
  if(turn == true){                   //左右の旋回の判定のtrue/falseを決める、dealy時間で正確に回れるかチェック//
    motorL.driveMotor(NORMAL,STOP);
    motorR.driveMotor(STOP,STOP);
    
  }else{
    motorL.driveMotor(STOP,STOP);
    motorR.driveMotor(NORMAL,STOP);
  }
  delay(2000);                         //時間確認   検知モードを把握するためdelayの時間を2回に分ける（仮に１度目で９０度旋回するとしてそこで段差検知を行う）
                          
} 
void MotorControl::back(){
    motorL.driveMotor(STOP,NORMAL);        //バックのスピードを変える必要がある？あと途中で止まる動作が必要？
    motorR.driveMotor(STOP,NORMAL);
}
void returnHome(){
    　　　　　　　　　　　　　　　　　　　　　　　//処理が難しい、保留
}
