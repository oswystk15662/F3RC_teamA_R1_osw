#pragma once
#include <mbed.h>
#include "parameters.hpp"

//-----足回り------

//ロータリエンコーダー
#define RE_1_A (PB_4)
#define RE_1_B (PB_5)
#define RE_2_A (PA_1)
#define RE_2_B (PA_0)
#define RE_3_A (PA_11)
#define RE_3_B (PB_12)
#define RE_4_A (PC_10)
#define RE_4_B (PC_12)

//DCモーター
/*
#define PWM_1 (PB_1)
#define DIR_1 (PC_9)
#define PWM_2 (PB_15)
#define DIR_2 (PC_8)
#define PWM_3 (PB_14)
#define DIR_3 (PC_6)
#define PWM_4 (PB_13)
#define DIR_4 (PB_2)
*/



//motor0
#define PWM_1 (PB_1) 
#define DIR_1 (PC_9)

//motor1
#define PWM_3 (PB_14)
#define DIR_3 (PC_6)

//motor2
#define PWM_4 (PB_13)
#define DIR_4 (PB_2)

//motor3
#define PWM_5 (PC_7)
#define DIR_5 (PC_4)

#define LED1 (PA_15)




//#define BUZZER (PA_5)
#define BUZZER (PB_3)

#if USING_R1

//-----アーム-----
//DCモーター
// #define PWM_5 (PB_8)

#define PWM_6 (PB_6)
#define DIR_6 (PB_10)

//サーボ
#define SV_1_SIGNAL (PA_7)
#define SV_2_SIGNAL (PA_6)

//リミットスイッチ
#define LS_1 (PC_11)
#define LS_2 (PD_2) 

//-----レーザー-----

// #define SDA (PC_7)
// #define SCL (PB_6)

#define SDA (PB_9)
#define SCL (PB_8)

#define XSHUT_1 (PC_5)
#define XSHUT_2 (PA_12)
#define XSHUT_3 (PA_6)
#define XSHUT_4 (PC_1)

#define USRBTN1 (PC_0)
#define USRBTN2 (PC_3)

#define SOLENOID (PB_7)


//-----esp32-----

#define ESP_UART_RX (PA_10)
#define ESP_UART_TX (PA_9)

#else


#define PWM_6 (PB_9)
#define DIR_6 (PB_10)

//------レーザー-----

#define LASER_1 (PC_1)
#define LASER_2 (PC_0)
#define LASER_3 (PC_2)

//------esp32-------

#define ESP_UART_RX (PA_10)
#define ESP_UART_TX (PA_9)

//------マイクロスイッチ-------

#define PASS_DETECT (PC_3)

#define LS_1 (PC_11)


#endif