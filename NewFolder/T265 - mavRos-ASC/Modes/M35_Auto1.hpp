#pragma once

#include "Modes.hpp"

 struct M35_mavlink_message 
{
	uint8_t msg_num;
	float params[10];
//	uint8_t masi[10];
	uint16_t type_mask;
	uint8_t coordinate_frame;
};


class M35_Auto1:public Mode_Base 
{
	private:
		
	public:
		M35_Auto1();
		virtual ModeResult main_func( void* param1, uint32_t param2 );
};
bool SendMsgToM35( M35_mavlink_message msg, double TIMEOUT );
bool M35ReceiveMsg( M35_mavlink_message* msg, double TIMEOUT);