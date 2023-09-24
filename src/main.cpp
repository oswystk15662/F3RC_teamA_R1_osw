#include <mbed.h>
#include "DriveMotor.hpp"
#include "settings.hpp"
#include "parameters.hpp"
#include "DriveBase.hpp"
#include "pins.hpp"

int main() {

    MDpins m0_pins = {PWM_1, DIR_1};
    MDpins m1_pins = {PWM_3, DIR_3};
    MDpins m2_pins = {PWM_4, DIR_4};
    MDpins m3_pins = {PWM_5, DIR_5};

    Gains m0_k1 = {MOTOR_0_KP_1, MOTOR_0_KI_1, MOTOR_0_KD_1};
    Gains m1_k1 = {MOTOR_1_KP_1, MOTOR_1_KI_1, MOTOR_1_KD_1};
    Gains m2_k1 = {MOTOR_2_KP_1, MOTOR_2_KI_1, MOTOR_2_KD_1};
    Gains m3_k1 = {MOTOR_3_KP_1, MOTOR_3_KI_1, MOTOR_3_KD_1};

    Gains m0_k2 = {MOTOR_0_KP_2, MOTOR_0_KI_2, MOTOR_0_KD_2};
    Gains m1_k2 = {MOTOR_1_KP_2, MOTOR_1_KI_2, MOTOR_1_KD_2};
    Gains m2_k2 = {MOTOR_2_KP_2, MOTOR_2_KI_2, MOTOR_2_KD_2};
    Gains m3_k2 = {MOTOR_3_KP_2, MOTOR_3_KI_2, MOTOR_3_KD_2};

  //CAN can(CAN_RD, CAN_TD, CAN_HZ);

  CANCommunication cancan(CAN_RD, CAN_TD, CAN_HZ);

  DriveMotor m0(cancan, 0, m0_pins, m0_k1, m0_k2, true);
  DriveMotor m1(cancan, 1, m1_pins, m1_k1, m1_k2, true);
  DriveMotor m2(cancan, 2, m2_pins, m2_k1, m2_k2, true);
  DriveMotor m3(cancan, 3, m3_pins, m2_k1, m3_k2, true);

    Motors_ptr m_ptr = {&m0, &m1, &m2, &m3};
  

  DriveBase db(cancan, m_ptr);
  
  cancan.can.attach(cancan.read_msgs(), RxIrq);
}