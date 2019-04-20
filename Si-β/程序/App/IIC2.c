#include "IIC2.h"
#include "System.h"
#include "stm32f10x_it.h"
#define IIC2_DelayUs(x) {Delayus(x);}
static void IIC2_SendAck(void);
static void IIC2_NoAck(void);
void IIC2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	PBout(10)=1;
	PBout(11)=1;
}
void IIC2_Start(void)
{
	IIC2_SDA_SET;
	IIC2_SCL_SET;
	IIC2_DelayUs(5);	
	IIC2_SDA_CLR;	//START:when CLK is high,DATA change form high to low
	IIC2_DelayUs(5);	//保持时间>4us
	IIC2_SCL_CLR;    //钳住IIC2总线，准备发送或接收数据					
}
void IIC2_Stop(void)
{
	IIC2_SCL_CLR;
	IIC2_SDA_CLR;	//SCL在低电平期间，SDA变化无效
	IIC2_SCL_SET;
	IIC2_DelayUs(5);	//保持时间>4us
	IIC2_SDA_SET;    //STOP:when CLK is high DATA change form low to high
	IIC2_DelayUs(5);	//保持时间>4.7us
}
void IIC2_SendData(unsigned char dat)
{
	uint8_t i;
	IIC2_SCL_CLR;
	for(i=0; i<8; i++)//要发送8位，从最高位开始
	{
		if((dat & 0x80) == 0x80)
		{
			IIC2_SDA_SET;
		}
		else
		{
			IIC2_SDA_CLR;
		}
		dat <<= 1;
		IIC2_DelayUs(2);
		IIC2_SCL_SET;
		IIC2_DelayUs(5);  //保持时间>4.7us
		IIC2_SCL_CLR;
		IIC2_DelayUs(2);
	}	
}
unsigned char IIC2_ReceiveData(unsigned char ack)
{
	uint8_t i, readValue;
	IIC2_SDA_SET;	
	IIC2_SCL_CLR;
	for(i=0; i<8; i++)	 //接收8个字节,从高到低
	{
		IIC2_SCL_SET;
		IIC2_DelayUs(2);
		readValue <<= 1;
		if(IIC2_SDA != 0)
		{
			readValue |= 0x01;
		}		
		IIC2_DelayUs(1);
		
		IIC2_SCL_CLR;
		IIC2_DelayUs(5);			
	}
	if(ack)		 //是否应答
	{
		IIC2_SendAck();
	}
	else
	{
		IIC2_NoAck();
	}

	return readValue;
}
char IIC2_WaitAck(void)
{
	uint32_t i;
	IIC2_SDA_SET;
	IIC2_DelayUs(1);
	IIC2_SCL_SET;
	while(IIC2_SDA)//在SCL高电平的情况下，SDA产生一个下降沿
	{
		 i++;
		 if(i > 0xFFFF)
		 {
		 	return 0xFF;
		 }
	}
	IIC2_SCL_CLR;
	IIC2_DelayUs(2);
	return 0;	
}
static void IIC2_SendAck(void)
{	
	IIC2_SCL_CLR;
	IIC2_SDA_CLR;
	IIC2_DelayUs(2);
	IIC2_SCL_SET;
	IIC2_DelayUs(2);
	IIC2_SCL_CLR;		
}
static void IIC2_NoAck(void)
{	
	IIC2_SCL_CLR;
	IIC2_SDA_SET;
	IIC2_DelayUs(2);
	IIC2_SCL_SET;
	IIC2_DelayUs(2);
	IIC2_SCL_CLR;		
}
