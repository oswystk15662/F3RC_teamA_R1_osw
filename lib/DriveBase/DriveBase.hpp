#pragma once

#include "DriveMotor.hpp"
#include "PIDcontroller.hpp"
#include <functional>

using namespace std;

class DriveBase{
    public:
        DriveBase(  DriveMotor* motor_0, DriveMotor* motor_1, DriveMotor* motor_2, DriveMotor* motor_3,
                    float kp_1=DRIVEBASE_KP, float ki_1=DRIVEBASE_KI, float kd_1=DRIVEBASE_KD,
                    float kp_2=DRIVEBASE_ROTATE_KP, float ki_2=DRIVEBASE_ROTATE_KI, float kd_2=DRIVEBASE_ROTATE_KD);

        //各モーターに回転速度を割り当てる
        void AssignSpeed(uint8_t _msgs[21]);

        //移動の停止
        void stopMovement(bool stop=true);

        // 速度に対して移動。元はpublicのメンバ関数で呼ばれるものだった。
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
        uint8_t msgs[21];

        DriveMotor* motors[4];

        PIDController pidController;
        PIDController pidRotateController;

        float targetSpeed_R, last_targetSpeed_R;

        Ticker movementTicker;
        Timer timer;

        function<void(void)> loop;
};