#pragma once

#include "DriveMotor.hpp"
#include "PIDcontroller.hpp"
#include <functional>

using namespace std;

struct Motors_ptr
{
    DriveMotor* motor0;
    DriveMotor* motor1;
    DriveMotor* motor2;
    DriveMotor* motor3;
};

class DriveBase{
public:
    DriveBase(  CANCommunication _can, Motors_ptr ms_ptr);
                
    DriveBase(  CANCommunication _can, Motors_ptr ms_ptr, Gains _k1,  Gains _k2);

    //各モーターに回転速度を割り当てる
    void AssignSpeed();

    //移動の停止
    void stopMovement(bool stop=true);

    // 速度に対して移動。
    void go(float targetSpeedX, float targetSpeedY, float targetSpeedD, bool absolute=true);

    void resetPID();
    
    //デバッグ用
    void runNoEncoder(float pwmX, float pwmY, float dir, float pwmD, float time);

    bool moving = false;

    int _s1;
    int _s2;

    float lastTargetSpeedX = 0.0f;
    float lastTargetSpeedY = 0.0f;
    float lastTargetSpeedD = 0.0f;

private:
    CANCommunication can;

    DriveMotor* motors[4];

    PIDController pidController;
    PIDController pidRotateController;

    float targetSpeed_R, last_targetSpeed_R;

    Ticker movementTicker;
    Timer timer;

    function<void(void)> loop;
};