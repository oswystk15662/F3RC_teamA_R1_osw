#include "PIDcontroller.hpp"

PIDController::PIDController(int _frequency, Gains _kpid) : FREQUENCY(_frequency), kpid({_kpid.KP, _kpid.KI / _frequency, _kpid.KD / _frequency}) {
    prevError = 0.0f;
    integral = 0.0f;
}

float PIDController::calculate(float error) {
    float output = kpid.KP * error + kpid.KI * integral + kpid.KD * (error - prevError);
    prevError = error;
    integral += error;

    return output;
}

void PIDController::reset(){
    integral = 0.0;
}

void PIDController::setGain(Gains _kpid){
    kpid.KP = _kpid.KP;
    kpid.KI = _kpid.KI / FREQUENCY;
    kpid.KD = _kpid.KD * FREQUENCY;
}