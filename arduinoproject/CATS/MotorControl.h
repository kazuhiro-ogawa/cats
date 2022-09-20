#pragma once

class MotorControl
{
  public:
    void goStraight();
    void brakes();
    void rotate(boolean turn);
    void back();
    void returnHome();
};
