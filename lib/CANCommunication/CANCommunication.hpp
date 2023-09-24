#include <mbed.h>

class CANCommunication{
public:
        CANCommunication(PinName rd, PinName td, int hz);

        float getAmount(uint8_t MotorNumber);

        //前進がtheta = 0; asin(r)で角度出して、その角度に比例した速度にする。
        void readController(float* jr, float* jtheta, uint8_t* jb);

        void read_msgs();
    private:

        CAN can;

        char msgs[21];

        //最下位バイトが1なら+何周したか、0なら-何周したか、下2byteは2048のうちなんぼか。を４つ分
        char encoder_data[4][4];

        //JoyStick_R : 2byte, JoyStick_theta : 2byte, botton : 1byte
        char ctrler_data[5];
};
