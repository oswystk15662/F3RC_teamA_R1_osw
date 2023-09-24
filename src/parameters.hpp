//パラメーター

#pragma once

#include <mbed.h>
#include <math.h>
#include "settings.hpp"

//固定値
constexpr int ENC_RES_MAX = 2048 * 2; //ロータリエンコーダーの分解能
constexpr float TRED_RADIUS = 125.4f; //中心からオムニホイールの距離[mm]
constexpr float WHEEL_DIAMETER = 100.0f;	//オムニホイールの直径	[mm]
constexpr float WHEEL_RADIUS = WHEEL_DIAMETER / 2.0f; //オムニホイールの半径	[mm]
constexpr float MMPP = WHEEL_DIAMETER * M_PI / ENC_RES_MAX;	//エンコーダ1パルスあたりに進む距離[mm]
constexpr float RADPP = MMPP / TRED_RADIUS;	//エンコーダ1パルスあたりの回転角[rad]



//モーターのPIDゲイン

#if (USING_R1)

constexpr float MOTOR_0_KP_1 = 1.3f;
constexpr float MOTOR_0_KI_1 = 0.06f;
constexpr float MOTOR_0_KD_1 = 0.0f;

constexpr float MOTOR_1_KP_1 = 1.3f;
constexpr float MOTOR_1_KI_1 = 0.06f;
constexpr float MOTOR_1_KD_1 = 0.0f;

constexpr float MOTOR_2_KP_1 = 1.3f;
constexpr float MOTOR_2_KI_1 = 0.06f;
constexpr float MOTOR_2_KD_1 = 0.0f;

constexpr float MOTOR_3_KP_1 = 1.3f;
constexpr float MOTOR_3_KI_1 = 0.06f;
constexpr float MOTOR_3_KD_1 = 0.0f;

constexpr float MOTOR_0_KP_2 = 0.00016f;
constexpr float MOTOR_0_KI_2 = 0.000000f;
constexpr float MOTOR_0_KD_2 = 0.00000f;

constexpr float MOTOR_1_KP_2 = 0.00016f * 1.17f;
constexpr float MOTOR_1_KI_2 = 0.00000f;
constexpr float MOTOR_1_KD_2 = 0.000000f;

constexpr float MOTOR_2_KP_2 = 0.00016f;
constexpr float MOTOR_2_KI_2 = 0.00000f;
constexpr float MOTOR_2_KD_2 = 0.00000f;

constexpr float MOTOR_3_KP_2 = 0.00016f * 1.17f;
constexpr float MOTOR_3_KI_2 = 0.000000f;
constexpr float MOTOR_3_KD_2 = 0.0f;

constexpr float DRIVEBASE_KP = 1.3f;
constexpr float DRIVEBASE_KI = 0.08f;
constexpr float DRIVEBASE_KD = 0.0f;

constexpr float DRIVEBASE_ROTATE_KP = DRIVEBASE_KP;
constexpr float DRIVEBASE_ROTATE_KI = DRIVEBASE_KI;
constexpr float DRIVEBASE_ROTATE_KD = DRIVEBASE_KD;

#else

constexpr float MOTOR_0_KP_1 = 1.3f;
constexpr float MOTOR_0_KI_1 = 0.06f;
constexpr float MOTOR_0_KD_1 = 0.0f;

constexpr float MOTOR_1_KP_1 = 1.3f;
constexpr float MOTOR_1_KI_1 = 0.06f;
constexpr float MOTOR_1_KD_1 = 0.0f;

constexpr float MOTOR_2_KP_1 = 1.3f;
constexpr float MOTOR_2_KI_1 = 0.06f;
constexpr float MOTOR_2_KD_1 = 0.0f;

constexpr float MOTOR_3_KP_1 = 1.3f;
constexpr float MOTOR_3_KI_1 = 0.06f;
constexpr float MOTOR_3_KD_1 = 0.0f;

constexpr float MOTOR_0_KP_2 = 0.00016f * 1.17f;
constexpr float MOTOR_0_KI_2 = 0.000000f;
constexpr float MOTOR_0_KD_2 = 0.00000f;

constexpr float MOTOR_1_KP_2 = 0.00016f * 1.17f;
constexpr float MOTOR_1_KI_2 = 0.00000f;
constexpr float MOTOR_1_KD_2 = 0.000000f;

constexpr float MOTOR_2_KP_2 = 0.00016f * 1.17f;
constexpr float MOTOR_2_KI_2 = 0.00000f;
constexpr float MOTOR_2_KD_2 = 0.00000f;

constexpr float MOTOR_3_KP_2 = 0.00016f * 1.17f;
constexpr float MOTOR_3_KI_2 = 0.000000f;
constexpr float MOTOR_3_KD_2 = 0.0f;

constexpr float DRIVEBASE_KP = 1.3f;
constexpr float DRIVEBASE_KI = 0.08f;
constexpr float DRIVEBASE_KD = 0.0f;

constexpr float DRIVEBASE_ROTATE_KP = DRIVEBASE_KP;
constexpr float DRIVEBASE_ROTATE_KI = DRIVEBASE_KI;
constexpr float DRIVEBASE_ROTATE_KD = DRIVEBASE_KD;
#endif

//移動パラメータ
constexpr int MAX_ACCELERATION = 20000; //最大加速度 [mm/s^2]
constexpr int MAX_SPEED = 500; //最高速度  [mm/s]
constexpr float MAX_ROTATE_ACCELERATION = MAX_ACCELERATION/TRED_RADIUS; //最大回転速度  [rad/s^2]
constexpr float MAX_ROTATE_SPEED = MAX_SPEED/TRED_RADIUS; //最大回転加速度  [rad/s]

//制御周期など
constexpr int ENCODER_LOCALIZATION_FREQUENCY = 200; //エンコーダーによる自己位置推定の頻度[Hz]
constexpr int SPEED_ADJUSTMENT_FREQUENCY = 20; //速度調整の頻度[Hz]
constexpr int MOTOR_CTRL_FREQUENCY = 50;

//目的地到着を判定する閾値
constexpr int MOVEMENT_THRESHOLD = 10; //目的地に到着したとみなす半径[mm]
constexpr float MOVEMENT_THRESHOLD_RAD = 0.1f; //目的地に到着したとみなす角度の誤差[rad]


constexpr float MOVEMENT_SWITCH_THRESHOLD = MAX_SPEED/DRIVEBASE_KP;

constexpr float MAX_DELTA_R = MAX_SPEED / SPEED_ADJUSTMENT_FREQUENCY;
constexpr float MAX_DELTA_D = MAX_ROTATE_SPEED / SPEED_ADJUSTMENT_FREQUENCY;

//コントローラー等
constexpr float ADJUSTMENT_SPEED_LEFT = 500.0f;
constexpr float ADJUSTMENT_SPEED_RIGHT = 100.0f;
constexpr float ADJUSTMENT_ROTATE_SPEED = 0.5f;

constexpr float HAND_SPEED_LEFT = 800.0f;
constexpr float HAND_SPEED_RIGHT = 200.0f;
constexpr float HAND_ROTATE_SPEED = 1.0f;


//フィールドパラメーター
constexpr int SOUTH_WALL_Y = 38;
constexpr int NORTH_WALL_Y = 2400-38;
constexpr int WEST_WALL_X = 38;
constexpr int EAST_WALL_X = 4500-38;

constexpr int ROBOTSIZE = 165;