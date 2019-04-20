#include "USART.h"
void USART1_Test(void)
{
	int i=0;
	USART1_Init(115200);
	while(1)
	{
			i++;
			printf("Send A Success Message!\r\n");
			printf("尝试发送中文字符!\r\n");
			printf("尝试返回数据! %i \r\n",i);
			Delayms(1000);
	}
}
void USART1_Init(u32 BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitStructure.USART_BaudRate=BaudRate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
}
int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(unsigned char) ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	return ch;
}
