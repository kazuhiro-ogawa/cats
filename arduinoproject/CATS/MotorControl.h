#pragma once


class MotorControl{
  public :
  void goStraight();
  void stops();                   /*メソッド名変更有？*/
  void rotate(bool turn);
  void back();
  void returnHome();
};
