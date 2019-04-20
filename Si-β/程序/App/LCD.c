#include "lcd.h"
#include "stdlib.h"
#include "stm32f10x_it.h"
//=======================================液晶屏数据线接线==========================================//
//DB0       接PD14 
//DB1       接PD15 
//DB2       接PD0 
//DB3       接PD1 
//DB4~DB12  依次接PE7~PE15
//DB13      接PD8 
//DB14      接PD9
//DB15      接PD10  
//=======================================液晶屏控制线接线==========================================//
//LCD_CS	接PG12	//片选信号
//LCD_RS	接PG0	//寄存器/数据选择信号
//LCD_WR	接PD5	//写信号
//LCD_RD	接PD4	//读信号
//LCD_RST	接PD7	//复位信号
//LCD_LED	接PD6	//背光控制信号(高电平点亮)
_lcd_dev lcddev;
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	 

void LCD_WR_REG(u16 data)
{ 
	LCD->LCD_REG=data;	 	
}
void LCD_WR_DATA(u16 data)
{
	LCD->LCD_RAM=data;
}
void LCD_DrawPoint_16Bit(u16 color)
{
	LCD_WR_DATA(color); 
}
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;	
	LCD->LCD_RAM = LCD_RegValue;     		 
}		   
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);
	LCD_WR_DATA(POINT_COLOR); 
}
void LCD_Clear(u16 Color) //清屏LCD_Clear(屏幕颜色);
{	
	u32 index=0,i=0;   
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
	for(i=0;i<960;i++)
	{
		for(index=0;index<160;index++)
		{
			LCD->LCD_RAM=Color;		
		}
  }
} 
void LCD_GPIOInit(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOB,GPIO_Pin_8);
	//背光调节
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9
	|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12
	|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//使能FSMC时钟
		readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //地址建立时间（ADDSET）为2个HCLK 1/36M=27ns
    readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
    readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // 数据保存时间为16个HCLK,因为液晶驱动IC的读数据的时候，速度不能太快，尤其对1289这个IC。
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
    

		writeTiming.FSMC_AddressSetupTime = 0x02;	 //0x01 地址建立时间（ADDSET）为1个HCLK  
    writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
    writeTiming.FSMC_DataSetupTime = 0x05;		 ////0x03 数据保存时间为4个HCLK	
    writeTiming.FSMC_BusTurnAroundDuration = 0x00;
    writeTiming.FSMC_CLKDivision = 0x00;
    writeTiming.FSMC_DataLatency = 0x00;
    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 

 
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
		FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置
   	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
		
		TIM_TimeBaseInitStructure.TIM_Period=999;
		TIM_TimeBaseInitStructure.TIM_Prescaler=0;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
		
		TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse=500;
		TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
		TIM_OC3Init(TIM4,&TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
		TIM_ARRPreloadConfig(TIM4,ENABLE);
		TIM_Cmd(TIM4,ENABLE);
		
		TIM_SetCompare3(TIM4,0);
}
void LCD_RESET(void)
{
	LCD_RST_CLR;
	Delayms(10);
	LCD_RST_SET;
	Delayms(10);
}
void LCD_Init(void)
{  									 
	LCD_GPIOInit();
 	LCD_RESET();
	//液晶屏初始化
	LCD_WR_REG(0XF1);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0X0F);
	LCD_WR_DATA(0x8F);
	LCD_WR_REG(0XF2);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0xA3);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0XB2);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0XF8);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x04);
	LCD_WR_REG(0XF9);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x08);
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x08);
	LCD_WR_REG(0xB4);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x22);
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x41);
	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x18);
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x1F);
	LCD_WR_DATA(0x1C);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x48);
	LCD_WR_DATA(0x98);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x2E);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x47);
	LCD_WR_DATA(0x75);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x24);
	LCD_WR_DATA(0x20);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);
	LCD_WR_REG(0x11);
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0xC8);
	Delayms(100);
	LCD_WR_REG(0x29);
	LCD_SetParam();//设置LCD参数	  
	LCD_Clear(BLACK);
}
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);
	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd);
	LCD_WriteRAM_Prepare();	
}   
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(Xpos>>8);
	LCD_WR_DATA(0x00FF&Xpos);		
	LCD_WR_DATA((Xpos+1)>>8);
	LCD_WR_DATA((Xpos+1));
	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(Ypos>>8);
	LCD_WR_DATA(0x00FF&Ypos);		
	LCD_WR_DATA((Ypos+1)>>8);
	LCD_WR_DATA((Ypos+1));
	LCD_WriteRAM_Prepare();	
} 
void LCD_SetParam(void)
{ 
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//使用横屏	  
	lcddev.dir=1;//横屏
	lcddev.width=480;
	lcddev.height=320;			
	LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
#else//竖屏
	lcddev.dir=0;//竖屏				 	 		
	lcddev.width=320;
	lcddev.height=480;	
	LCD_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
#endif
}	  

 

