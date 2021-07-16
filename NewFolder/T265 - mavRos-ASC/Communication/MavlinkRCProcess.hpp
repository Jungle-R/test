#pragma once

#include "mavlink.h"
#include "M35_Auto1.hpp"

extern M35_mavlink_message msg_OLED;

//Mavlink消息处理函数表
extern void (*const Mavlink_RC_Process[])( uint8_t Port_index , const mavlink_message_t* msg_sd );
//Mavlink消息处理函数个数
extern const uint16_t Mavlink_RC_Process_Count;

void Mav84_SET_POSITION_TARGET_LOCAL_NED (  M35_mavlink_message msg );
void Mav82_SET_ATTITUDE_TARGET (  M35_mavlink_message msg );

	