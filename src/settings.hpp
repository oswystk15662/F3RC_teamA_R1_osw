#pragma once

#include <mbed.h>

constexpr int CAN_ID = 1337;
constexpr PinName CAN_RD = PB_8;
constexpr PinName CAN_TD = PB_9;
constexpr int CAN_HZ = 1000;
constexpr uint8_t NUM_FLOAT_KETA = 4;

constexpr bool ENABLE_SPEED_LIMIT = true;
constexpr bool ENABLE_ACCEL_LIMIT = true;

constexpr bool USING_R1 = true;