#include "CANCommunication.hpp"

CANCommunication::SerialCommunication(PinName rd, PinName td, int hz)::can(rd, td, hz)
{
    
}

float CANCommunication::getAmmount(uint8_t MotorNumber){
    uint8_t msgs[21];
    can.read(CANMessage(CAN_ID, &msgs, 21));
    &encoder_data[0][0] = &msgs;
    
    float ammount;
    ammount = MMPP * encoder_data[MotorNumber][1] * (encoder_data[MotorNumber][2] << 8 +  encoder_data[MotorNumber][2]);
    encoder_data[MotorNumber][0] == 0 ? * ammount *= -1 : ;
    
    return ammount;
}
void CANCommunication::readController(float* jr, float* jtheta, uint8_t* jb){
    uint8_t msgs[21];
    can.read(CANMessage(CAN_ID, msgs, 21));

    &msg[0] = &msgs + 16;
    *jr = (float)(msg[0]<<8 + msg[1]) / NUM_FLOAT_KETA;
    *jtheta = (float)(msg[2]<<8 + msg[3]) / NUM_FLOAT_KETA;
    *jb = msg[5];
}
