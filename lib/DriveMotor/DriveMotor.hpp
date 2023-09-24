#pragma once

#include <mbed.h>
#include "settings.hpp"
#include "parameters.hpp"
#include "CANCommunication.hpp"
#include "PIDcontroller.hpp"
#include <functional>

using namespace std;

struct MDpins
{
    PinName pwm_pin;
    PinName dir_pin;
};

struct MD
{
    PwmOut pwm;
    DigitalOut dir;
};


class DriveMotor{
public:

    bool sign;
    float target = 0.0f, target_speed = 0.0f;
    bool moving = false;


    float lastEncoderAmount = 0.0f;

    float pwm = 0.0f;

    float _s1 = 0;
    float _s2 = 0;

    uint8_t MotorNumber;

    PwmOut pwmOut; //モーター
    DigitalOut dirOut;
    PIDController pidController;
    PIDController pidSpeedController;

    DriveMotor( CANCommunication _can,  uint8_t MoNum, MDpins _MDpins,
                Gains _kpid1, Gains _kpid2, bool _sign = 1);

    void setPWM(float signed_pwm); //PWMの直接書き込み

    void slowStart(float* _target_duty);

    void rotate(float targetSpeed); //速度を指定

    void rotateTo(float target, bool idle=true);

    void rotatePermanent(float speed, bool idle=true);

    void stop();

    void attachLoop(function<void(void)> loop_func);

private:
    
    CANCommunication can;

    void rotateTowardTargetAccDcc(); //target[mm] に向かって動く
    Ticker movementTicker;
    function<void(void)> loop;
};
