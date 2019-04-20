#include "LCD1602.h"
#include "Port.h"
void LCD1602_Writecom(unsigned char com)
{
	 unsigned int a=1320;
	 unsigned char Temp_Port = D0;
	 D0=com;
	 LCD1602_RS=0;
	 LCD1602_E=1;
	 while(a--);
	 LCD1602_E=0;
	 D0 = Temp_Port;
}
void LCD1602_Writedat(unsigned char dat)
{
	 unsigned int a=1320;
	 unsigned char Temp_Port = D0;
	 D0=dat;
	 LCD1602_RS=1;
	 LCD1602_E=1;
	 while(a--);
	 LCD1602_E=0;
	 D0 = Temp_Port;
}
void LCD1602_Init()
{
	  unsigned char i=5;
		for(i=5;i>0;i--)
		   LCD1602_Writecom(0x38);
		LCD1602_Writecom(0x06);
		LCD1602_Writecom(0x0c);
		LCD1602_Writecom(0x01);
		LCD1602_E=0;
}
void LCD1602_SendString(unsigned char *s)
{
    while (*s)        
    {
        LCD1602_Writedat(*s++);
    }
}