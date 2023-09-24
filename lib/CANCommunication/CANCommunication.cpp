#include "CANCommunication.hpp"

CANCommunication::SerialCommunication(PinName rd, PinName td, int hz)::can(rd, td, hz)
{
    &encoder_data[0][0] = &msgs;
    &ctrler_data[0] = &msgs + 16;
}

void CANCommunication::read_msgs(){
    can.read(CANMessage(CAN_ID, &msgs, 21));
}

float CANCommunication::getAmmount(uint8_t MotorNumber){
    float ammount;
    ammount = MMPP * encoder_data[MotorNumber][1] * (encoder_data[MotorNumber][2] << 8 +  encoder_data[MotorNumber][2]);
    encoder_data[MotorNumber][0] == 0 ? * ammount *= -1 : ;
    
    return ammount;
}
void CANCommunication::readController(float* jr, float* jtheta, uint8_t* jb){
    *jr = (float)(msg[0]<<8 + msg[1]) / NUM_FLOAT_KETA;
    *jtheta = (float)(msg[2]<<8 + msg[3]) / NUM_FLOAT_KETA;
    *jb = msg[5];
}
