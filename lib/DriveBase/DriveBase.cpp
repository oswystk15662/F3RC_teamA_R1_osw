#include <math.h>
#include <chrono>
#include "DriveBase.hpp"
#include "parameters.hpp"
//#include "simpleFunctions.hpp"


inline bool limit_filter(float* value, float minValue, float maxValue){
    if(*value < minValue || *value > maxValue){
        *value = minValue;
        return 1;
    }else{
        return 0;
    }
}

//初期化
DriveBase::DriveBase(   CANCommunication _can,
                        DriveMotor* motor_0, DriveMotor* motor_1, DriveMotor* motor_2, DriveMotor* motor_3,)
                        :   can(&_can),
                            pidController(SPEED_ADJUSTMENT_FREQUENCY, DRIVEBASE_KP, DRIVEBASE_KI, DRIVEBASE_KD),
                            pidRotateController(SPEED_ADJUSTMENT_FREQUENCY, DRIVEBASE_ROTATE_KP, DRIVEBASE_ROTATE_KI, DRIVEBASE_ROTATE_KD)
{
    motors[0] = motor_0;
    motors[1] = motor_1;
    motors[2] = motor_2;
    motors[3] = motor_3;

    moving = false;
    loop = [this] {return;};
}

DriveBase::DriveBase(   CANCommunication _can,
                        DriveMotor* motor_0, DriveMotor* motor_1, DriveMotor* motor_2, DriveMotor* motor_3,
                        float kp_1, float ki_1, float kd_1, float kp_2, float ki_2, float kd_2)
                        :   can(&_can),
                            pidController(SPEED_ADJUSTMENT_FREQUENCY, kp_1, ki_1, kd_1),
                            pidRotateController(SPEED_ADJUSTMENT_FREQUENCY, kp_2, ki_2, kd_2)
{
    motors[0] = motor_0;
    motors[1] = motor_1;
    motors[2] = motor_2;
    motors[3] = motor_3;

    moving = false;
    loop = [this] {return;};
}

void DriveBase::resetPID(){
    for (int i=0;i<4;i++){
        motors[i]->pidController.reset();
    }
    pidController.reset();
    pidRotateController.reset();
}

void DriveBase::AssignSpeed(){
    float jr, jtheta;
    uint8_t jb;//ここでは使わない

    can.readController(&jr, &jtheta, &jb);

    (targetSpeed_R - last_targetSpeed_R) * SPEED_ADJUSTMENT_FREQUENCY  > MAX_ACCELERATION 
        ? targetSpeed_R = MAX_ACCELERATION / SPEED_ADJUSTMENT_FREQUENCY : targetSpeed_R = MAX_SPEED * asinf(jr) * 2 / M_PI;

    motors[0]->rotate(targetSpeed_R * cos(theta + 45));
    motors[1]->rotate(targetSpeed_R * sin(theta + 45));
    motors[2]->rotate(targetSpeed_R * cos(theta + 45) * -1);
    motors[3]->rotate(targetSpeed_R * sin(theta + 45) * -1);
}

//モーターの停止
void DriveBase::stopMovement(bool stop){
    movementTicker.detach();
    moving = false;
    if(stop){
        for(int i=0;i<4;i++){
            motors[i]->stop();
        }
    }
}

#if 1
//速度を指定して移動
void DriveBase::go(float targetSpeedX, float targetSpeedY, float targetSpeedD, bool absolute){

    float targetSpeedR = sqrtf(targetSpeedX*targetSpeedX + targetSpeedY*targetSpeedY);

    //速度を制限する
    if(targetSpeedR > MAX_SPEED){
        targetSpeedX = MAX_SPEED*(targetSpeedX/targetSpeedR);
        targetSpeedY = MAX_SPEED*(targetSpeedY/targetSpeedR);
        pidController.reset();
    }

    if(targetSpeedD > MAX_ROTATE_SPEED){
        targetSpeedD = MAX_ROTATE_SPEED;
        pidRotateController.reset();
    }else if(targetSpeedD < -MAX_ROTATE_SPEED){
        targetSpeedD = -MAX_ROTATE_SPEED;
        pidRotateController.reset();
    }

    #if 0 //どっちにしようかな〜
    float targetAccX = (targetSpeedX - localization.speedX) * SPEED_ADJUSTMENT_FREQUENCY;
    float targetAccY = (targetSpeedY - localization.speedY) * SPEED_ADJUSTMENT_FREQUENCY;
    float targetAccD = (targetSpeedD - localization.rotateSpeed) * SPEED_ADJUSTMENT_FREQUENCY;
    #else
    float targetAccX = (targetSpeedX - lastTargetSpeedX) * SPEED_ADJUSTMENT_FREQUENCY;
    float targetAccY = (targetSpeedY - lastTargetSpeedY) * SPEED_ADJUSTMENT_FREQUENCY;
    float targetAccD = (targetSpeedD - lastTargetSpeedD) * SPEED_ADJUSTMENT_FREQUENCY;
    #endif

    
    float targetAccR = sqrtf(targetAccX*targetAccX + targetAccY*targetAccY);

    //加速度を制限する
    if(targetAccR > MAX_ACCELERATION){
        targetAccX = MAX_ACCELERATION*(targetAccX/targetAccR);
        targetAccY = MAX_ACCELERATION*(targetAccY/targetAccR);
        //targetSpeedX = localization.speedX + targetAccX/SPEED_ADJUSTMENT_FREQUENCY;
        //targetSpeedY = localization.speedY + targetAccY/SPEED_ADJUSTMENT_FREQUENCY;
    }
    /*
    if(targetAccD > MAX_ROTATE_ACCELERATION){
        targetSpeedD = localization.rotateSpeed + MAX_ROTATE_ACCELERATION / SPEED_ADJUSTMENT_FREQUENCY;
    }else if(targetAccD < -MAX_ROTATE_ACCELERATION){
        targetSpeedD = localization.rotateSpeed - MAX_ROTATE_ACCELERATION / SPEED_ADJUSTMENT_FREQUENCY;
    }
    */

    //デバッグ用
    _s1 = int(targetSpeedX);
    _s2 = int(targetSpeedY);

    lastTargetSpeedX = targetSpeedX;
    lastTargetSpeedY = targetSpeedY;
    lastTargetSpeedD = targetSpeedD;

    /*
    float vx, vy;

    if(absolute){
        //X, Yに回転行列をかける
        vx = cos(localization.direction)*targetSpeedX + sin(localization.direction)*targetSpeedY;
        vy = -sin(localization.direction)*targetSpeedX + cos(localization.direction)*targetSpeedY;
    }else{
        vx = targetSpeedX;
        vy = targetSpeedY;
    }
    */

    //各モーターの速度
    float speeds[4]; //モーターの速度
    speeds[0] = SQRT2/2 * (- vx + vy) + TRED_RADIUS * targetSpeedD;
    speeds[1] = SQRT2/2 * (- vx - vy) + TRED_RADIUS * targetSpeedD;
    speeds[2] = SQRT2/2 * (+ vx - vy) + TRED_RADIUS * targetSpeedD;
    speeds[3] = SQRT2/2 * (+ vx + vy) + TRED_RADIUS * targetSpeedD;
    
    
    for (int i=0;i<4;i++){
        motors[i]->rotate(speeds[i]);
    }

}

#else
//成分ごとに制限をかける場合．おそらく使用しない．（計算量は減るが方向によって最高速度が違うのは不自然なので)
//速度を指定して移動
void DriveBase::go(float targetSpeedX, float targetSpeedY, float targetSpeedD){
    if(limit_filter(&targetSpeedX, -MAX_SPEED, +MAX_SPEED)){
        pidController.reset();
    }
    if(limit_filter(&targetSpeedY, -MAX_SPEED, +MAX_SPEED)){
        pidController.reset();
    }
    if(limit_filter(&targetSpeedD, -MAX_ROTATE_SPEED, +MAX_ROTATE_SPEED)){
        pidRotateController.reset();
    }

    limit_filter(&targetSpeedX, lastTargetSpeedX-MAX_ACCELERATION/SPEED_ADJUSTMENT_FREQUENCY, lastTargetSpeedX+MAX_ACCELERATION/SPEED_ADJUSTMENT_FREQUENCY);
    limit_filter(&targetSpeedY, lastTargetSpeedY-MAX_ACCELERATION/SPEED_ADJUSTMENT_FREQUENCY, lastTargetSpeedY+MAX_ACCELERATION/SPEED_ADJUSTMENT_FREQUENCY);
    limit_filter(&targetSpeedD, lastTargetSpeedD-MAX_ROTATE_ACCELERATION/SPEED_ADJUSTMENT_FREQUENCY, lastTargetSpeedD+MAX_ROTATE_ACCELERATION/SPEED_ADJUSTMENT_FREQUENCY);

    _s1 = int(targetSpeedX);
    _s2 = int(targetSpeedY);

    lastTargetSpeedX = targetSpeedX;
    lastTargetSpeedY = targetSpeedY;
    lastTargetSpeedD = targetSpeedD;

    //X, Yに回転行列をかける
    float vx = cos(localization.direction)*targetSpeedX + sin(localization.direction)*targetSpeedY;
    float vy = -sin(localization.direction)*targetSpeedX + cos(localization.direction)*targetSpeedY;

    //各モーターの速度
    float speeds[4]; //モーターの速度
    speeds[0] = SQRT2/2 * (- vx + vy) + TRED_RADIUS * targetSpeedD;
    speeds[1] = SQRT2/2 * (- vx - vy) + TRED_RADIUS * targetSpeedD;
    speeds[2] = SQRT2/2 * (+ vx - vy) + TRED_RADIUS * targetSpeedD;
    speeds[3] = SQRT2/2 * (+ vx + vy) + TRED_RADIUS * targetSpeedD;
    
    
    for (int i=0;i<4;i++){
        motors[i]->rotate(speeds[i]);
    }

}
#endif