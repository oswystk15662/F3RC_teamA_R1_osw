#include "CANCommunication.hpp"

CANCommunication::CANCommunication(PinName rd, PinName td, int hz):can(rd, td, hz)
{
    
}

void CANCommunication::copyData(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            encoder_data[i][j] = msgs[i*4 + j];
        }
    }
    for(int i = 0; i < 5; i++){
        ctrler_data[i] = msgs[16 + i];
    }
}

void CANCommunication::read_msgs(){
    can.read(CANMessage(CAN_ID, &msgs[0], 21));
}

float CANCommunication::getAmmount(uint8_t MotorNumber){
    this->copyData();
    float amount;
    amount = MMPP * encoder_data[MotorNumber][1] * (encoder_data[MotorNumber][2] << 8 +  encoder_data[MotorNumber][2]);
    encoder_data[MotorNumber][0] == 0 ? * amount *= -1 : ;
    
    return amount;
}
void CANCommunication::readController(float* jr, float* jtheta, uint8_t* jb){
    this->copyData();
    *jr = (float)(ctrler_data[0]<<8 + ctrler_data[1]) / NUM_FLOAT_KETA;
    *jtheta = (float)(ctrler_data[2]<<8 + ctrler_data[3]) / NUM_FLOAT_KETA;
    *jb = ctrler_data[5];
}
