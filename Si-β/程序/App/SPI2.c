#include "System.h"
#include "SPI2.h"
#include "USART.h"
void SPI2_Config(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//选择全双工SPI模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;     //主机模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8位SPI
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;       //时钟悬空高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;      //在第二个时钟采集数据
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		  //Nss使用软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//从最高位开始传输
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_16);
	SPI_Cmd(SPI2, ENABLE);
	SPI_Init(SPI2, &SPI_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}
uint8_t SPI2_WriteReadData(uint8_t dat)
{
	uint16_t i = 0;
 	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
	{
		i++;
		if(i > 10000)
		{
			return 0xFF;
		}
	}
  SPI_I2S_SendData(SPI2, dat);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
	{
	}
 	return SPI_I2S_ReceiveData(SPI2);		
}
void SPI2_SetSpeed(uint8_t Speed)
{
	SPI2->CR1 &= 0xFFC7; 
	SPI2->CR1 |= Speed;
	SPI_Cmd(SPI2,ENABLE);	
	printf("Set Speed Success \r\n");
}
