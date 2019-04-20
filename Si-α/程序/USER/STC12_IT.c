#include "STC12_IT.h"
#include "User_Program.h"
void USART_IT_Confguration(unsigned char Return)
{
	if(Return=='^')
		LED0=~LED0;
}