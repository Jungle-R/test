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

/*����ϵͳ������*/
 SemaphoreHandle_t T265_Clear = xSemaphoreCreateBinary();
static void T265_server(void* pvParameters)
{
		
    static portTickType xLastWakeTime;  
		static int count_s=0;
    const portTickType xFrequency = pdMS_TO_TICKS(1000);  //1000����ת��Ϊ������
   
    xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		count_s++;
		
		/******���յ���Ϣ����ʱ��0*******/
		 if( xSemaphoreTake( T265_Clear, ( TickType_t ) 0 ) )
					count_s = 0;			 
			/******10s��û�н��յ����ݣ�ʧЧ*******/
		 if(count_s>=10)
		 {
			PositionSensorUnRegister(default_vision_XY_Velocity_index);
			PositionSensorUnRegister(default_vision_Z_Position_index);		
			vTaskDelete(0);   //ɾ������
			 
		 }
			 
		vTaskDelayUntil( &xLastWakeTime,xFrequency ); 
	
	}
}


void init_drv_T265()
{

	//maxi:��ʱĬ��Ϊ0 �ˣ�TIMEOUTĬ�϶���-1�����ȼ���Ϊ0
	PositionSensorRegister( 
			default_vision_XY_Velocity_index ,\
			Position_Sensor_Type_RelativePositioning ,\
			Position_Sensor_DataType_v_xy ,   			 //XY�ٶ�
			Position_Sensor_frame_BodyHeading ,//Position_Sensor_frame_BodyHeading
			0,//0.05f
			0 ,\
			0 
		);
	//maxi:��ʱĬ��Ϊ0 �ˣ�TIMEOUTĬ�϶���-1�����ȼ���Ϊ0
	PositionSensorRegister( 			
			default_vision_Z_Position_index ,\
			Position_Sensor_Type_RangePositioning ,//Position_Sensor_Type_RangePositioning
			Position_Sensor_DataType_s_z ,         //Z �߶�
			Position_Sensor_frame_ENU ,\
			0,//0.05		
			0 ,
			0 
		);	

	//��ʱ����
//	xTaskCreate( T265_server,"T265_server", 2048, NULL, SysPriority_UserTask,NULL);

	
}