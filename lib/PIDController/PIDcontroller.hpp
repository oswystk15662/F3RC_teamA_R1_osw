#pragma once

typedef struct
{
    float KP;   // P制御のゲイン
    float KI;   // I制御のゲイン
    float KD;    // D制御のゲイン
} Gains;

class PIDController {
private:

public:
    float integral; // 積分値
    float prevError; // 前回のエラー

    int FREQUENCY; //制御頻度

    Gains kpid;

    PIDController(int frequency, Gains kpid);
    float calculate(float error);
    void reset();

    void setGain(Gains kpid);
};