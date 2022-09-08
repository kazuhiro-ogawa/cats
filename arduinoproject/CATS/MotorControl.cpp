#include "Moter.h"

Moter motorL;
moter motorR;

void goStraight(){
  motorL.driveMotor(NORMAL,STOP);
  MotorR.driveMotor(NORMAL,STOP);
  
}
void stop(){
  motorL.driveMotor(STOP,STOP);
  motorR.driveMotor(STOP,STOP);
  
}
void rotate(boolean turn){
  if(turn == true){                   //左右の旋回の判定のtrue/falseを決める、dealy時間で正確に回れるかチェック//
    motorL.driveMotor(NORMAL,STOP);
    motorR.driveMotor(STOP,STOP);
    
  }else{
    motorL.driveMotor(STOP,STOP);
    motorR.driveMotor(NORMAL,STOP);
  }
  delay(2000);                         //時間確認
  goStraight();                        //直進に戻る
} 
void back(){
    motorL.driveMotor(STOP,NORMAL);        //バックのスピードを変える必要がある？あと途中で止まる動作が必要？
    motorR.driveMotor(STOP,NORMAL);
}
void returnHome(){
    　　　　　　　　　　　　　　　　　　　　　　　//処理が難しい、保留
}
