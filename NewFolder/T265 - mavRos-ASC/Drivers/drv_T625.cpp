#include "drv_T625.hpp"
#include "Basic.hpp"
#include "SensorsBackend.hpp"
#include "Sensors.hpp"
#include "MeasurementSystem.hpp"
#include "drv_Uart1.hpp"
#include "timers.h"
#include "task.h"
#include "Modes.hpp"
#include "FreeRTOS.h"
#include "task.h"

/*控制系统互斥锁*/
 SemaphoreHandle_t T265_Clear = xSemaphoreCreateBinary();
static void T265_server(void* pvParameters)
{
		
    static portTickType xLastWakeTime;  
		static int count_s=0;
    const portTickType xFrequency = pdMS_TO_TICKS(1000);  //1000毫秒转化为节拍数
   
    xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		count_s++;
		
		/******接收到信息，计时清0*******/
		 if( xSemaphoreTake( T265_Clear, ( TickType_t ) 0 ) )
					count_s = 0;			 
			/******10s内没有接收到数据，失效*******/
		 if(count_s>=10)
		 {
			PositionSensorUnRegister(default_vision_XY_Velocity_index);
			PositionSensorUnRegister(default_vision_Z_Position_index);		
			vTaskDelete(0);   //删除任务
			 
		 }
			 
		vTaskDelayUntil( &xLastWakeTime,xFrequency ); 
	
	}
}


void init_drv_T265()
{

	//maxi:延时默认为0 了，TIMEOUT默认都是-1，优先级都为0
	PositionSensorRegister( 
			default_vision_XY_Velocity_index ,\
			Position_Sensor_Type_RelativePositioning ,\
			Position_Sensor_DataType_v_xy ,   			 //XY速度
			Position_Sensor_frame_BodyHeading ,//Position_Sensor_frame_BodyHeading
			0,//0.05f
			0 ,\
			0 
		);
	//maxi:延时默认为0 了，TIMEOUT默认都是-1，优先级都为0
	PositionSensorRegister( 			
			default_vision_Z_Position_index ,\
			Position_Sensor_Type_RangePositioning ,//Position_Sensor_Type_RangePositioning
			Position_Sensor_DataType_s_z ,         //Z 高度
			Position_Sensor_frame_ENU ,\
			0,//0.05		
			0 ,
			0 
		);	

	//定时采样
//	xTaskCreate( T265_server,"T265_server", 2048, NULL, SysPriority_UserTask,NULL);

	
}