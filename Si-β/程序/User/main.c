#include "Picture.h"
#include "System.h"
#include "USART.h"
#include "LCD.h"
#include "GUI.h"
#include "sram.h"
#include "Camera.h"
#include "Touch.h"
#include "SPI3.h"
#include "SPI2.h"
#include "SPI1.h"
#include "W25Q64.h"
#include "DAC.h"
#include "DS18B20.h"
#include "adx345.h"
#include "Beep.h"
#include "User.h"
#include "FreeRTOS.h"
#include "task.h"
TaskHandle_t User_Programe_Handler;
TaskHandle_t List_Handler;
TaskHandle_t Beep_Handler;
uint8_t Ov7725_vsync = 0;
extern TouchTypeDef TouchData;
void ImagDisp(void);
void Beep(void *Par)
{
	while(1)
	{
		Beep_On;
		vTaskDelay(200);
		Beep_Off;
		vTaskDelay(1000);
	}
}
void List(void *Par)
{
	while(1)
	{
		char Buffer[400];
		vTaskGetRunTimeStats(Buffer);
		printf(" %s \r\n",Buffer);
		vTaskDelay(5000);
	}
}
int main()
{
	char Counter=0;
	SystemInit();
	GPIO_Config();
	Beep_Init();
	//ADX345_Init();
	USART1_Init(115200);
  SPI2_Config();
	FLASH_Init();
	Ds18b20_init();
	LCD_Init();
	LCD_Clear(BLACK);
	Gui_Drawbmp16(10,90,gImage_Develope,300,300);
	while(1)
	{
		Delayms(30);
		TIM_SetCompare3(TIM4,Counter);
		Counter++;
		if(Counter==60)
			break;
	}
	Delayms(3000);
	LCD_Clear(0xefff);
	DAC_Config();
	if(Camera_Init(0,0)==Camera_Init_Success)
		printf("Camera Init Success! \r\n");
	else
		printf("Camera Init Fail! \r\n");
	Ov7725_vsync = 0;
	Gui_Drawbmp16(0,300,gImage_Bottom,320,180);
	xTaskCreate((TaskFunction_t)User,
							(const char *)"User",
							(configSTACK_DEPTH_TYPE)128,
							(void *)NULL,
							(UBaseType_t)2,
							(TaskHandle_t *)&User_Programe_Handler);
	xTaskCreate((TaskFunction_t)List,
							(const char *)"List",
							(configSTACK_DEPTH_TYPE)256,
							(void *)NULL,
							(UBaseType_t)4,
							(TaskHandle_t *)&List_Handler);
	xTaskCreate((TaskFunction_t)Beep,
							(const char *)"Beep",
							(configSTACK_DEPTH_TYPE)128,
							(void *)NULL,
							(UBaseType_t)2,
							(TaskHandle_t *)&Beep_Handler);
	vTaskStartScheduler();
  //User();
}
void ImagDisp(void)
{
	uint16_t i, j; 
	uint16_t Camera_Data;
	LCD_SetWindows(0,0,320,240);	
	for(i = 0; i < 320; i++)
	{
		for(j = 0; j < 240; j++)
		{
			Camera_Data = READ_FIFO_PIXEL();		/* 从FIFO读出一个rgb565像素到Camera_Data变量 */
			LCD_WR_DATA(Camera_Data);
		}
	}
}
