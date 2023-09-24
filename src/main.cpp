#include "settings.hpp"
#include "parameters.hpp"
#include "DriveBase.hpp"
#include "pins.hpp"

int main() {

  //CAN can(CAN_RD, CAN_TD, CAN_HZ);
  uint8_t msgs[21];

  CANCommunication cancan(CAN_RD, CAN_TD, CAN_HZ);
  DriveMotor m0(&msgs[0], 0, PWM_1, DIR_1, MOTOR_0_KP_1, MOTOR_0_KI_1, MOTOR_0_KD_1, MOTOR_0_KP_2, MOTOR_0_KI_2, MOTOR_0_KD_2, true);
  DriveMotor m1(&msgs[0], 1, PWM_3, DIR_3, MOTOR_1_KP_1, MOTOR_1_KI_1, MOTOR_1_KD_1, MOTOR_1_KP_2, MOTOR_1_KI_2, MOTOR_1_KD_2, true);
  DriveMotor m2(&msgs[0], 0, PWM_4, DIR_4, MOTOR_2_KP_1, MOTOR_2_KI_1, MOTOR_2_KD_1, MOTOR_2_KP_2, MOTOR_2_KI_2, MOTOR_2_KD_2, true);
  DriveMotor m3(&msgs[0], 0, PWM_5, DIR_5, MOTOR_3_KP_1, MOTOR_3_KI_1, MOTOR_3_KD_1, MOTOR_3_KP_2, MOTOR_3_KI_2, MOTOR_3_KD_2, true);

  DriveBase db(&msgs[0], &m0, &m1, &m2, &m3);
  
  cancan.can.attach(cancan.read_msgs(), IrqType::RxIrq)
  
}