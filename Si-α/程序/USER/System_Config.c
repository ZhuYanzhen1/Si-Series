#include "System_Config.h"
#include "User_Program.h"
void Delayms(unsigned int xms)
{
	while(xms--)
	{
		unsigned char i, j;
		_nop_();
		i = 3;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}
void Delayus(unsigned int xus)
{
	while(xus--)
		_nop_();
}
void Show_Analog(bit LE)
{
	if(LE==0)
	{
	  unsigned int A1 = Get_AD_Result(1);
		unsigned int A2 = Get_AD_Result(2);
		unsigned int A3 = Get_AD_Result(3);
		unsigned int A4 = Get_AD_Result(4);
		unsigned char code Table[]="0123456789";
		LCD1602_Writecom(0x80);
		LCD1602_SendString("A1:");
		LCD1602_Writedat(Table[A1/1000]);
		LCD1602_Writedat(Table[A1%1000/100]);
		LCD1602_Writedat(Table[A1%100/10]);
		LCD1602_Writedat(Table[A1%10]);
		LCD1602_SendString("  A2:");
		LCD1602_Writedat(Table[A2/1000]);
		LCD1602_Writedat(Table[A2%1000/100]);
		LCD1602_Writedat(Table[A2%100/10]);
		LCD1602_Writedat(Table[A2%10]);
		LCD1602_Writecom(0x80+0x40);
		LCD1602_SendString("A3:");
		LCD1602_Writedat(Table[A3/1000]);
		LCD1602_Writedat(Table[A3%1000/100]);
		LCD1602_Writedat(Table[A3%100/10]);
		LCD1602_Writedat(Table[A3%10]);
		LCD1602_SendString("  A4:");
		LCD1602_Writedat(Table[A4/1000]);
		LCD1602_Writedat(Table[A4%1000/100]);
		LCD1602_Writedat(Table[A4%100/10]);
		LCD1602_Writedat(Table[A4%10]);
	}
	else
	{
		unsigned int A5 = Get_AD_Result(5);
		unsigned int A6 = Get_AD_Result(6);
		unsigned char code Table[]="0123456789";
		LCD1602_Writecom(0x80);
		LCD1602_SendString("A5:");
		LCD1602_Writedat(Table[A5/1000]);
		LCD1602_Writedat(Table[A5%1000/100]);
		LCD1602_Writedat(Table[A5%100/10]);
		LCD1602_Writedat(Table[A5%10]);
		LCD1602_SendString("  A6:");
		LCD1602_Writedat(Table[A6/1000]);
		LCD1602_Writedat(Table[A6%1000/100]);
		LCD1602_Writedat(Table[A6%100/10]);
		LCD1602_Writedat(Table[A6%10]);
	}
}
void Show_Digital(bit LE)
{
	if(LE==0)
	{
	LCD1602_Writecom(0x80);
	LCD1602_SendString("D1:");
	if(Digital1==1)
	  LCD1602_Writedat('1');
	else
		LCD1602_Writedat('0');
	LCD1602_SendString(" D2:");
	if(Digital2==1)
	  LCD1602_Writedat('1');
	else
		LCD1602_Writedat('0');
	LCD1602_SendString(" D3:");
	if(Digital3==1)
	  LCD1602_Writedat('1');
	else
		LCD1602_Writedat('0');
	LCD1602_Writecom(0x80+0x40);
	LCD1602_SendString("D4:");
	if(Digital4==1)
	  LCD1602_Writedat('1');
	else
		LCD1602_Writedat('0');
	LCD1602_SendString(" D5:");
	if(Digital5==1)
	  LCD1602_Writedat('1');
	else
		LCD1602_Writedat('0');
	LCD1602_SendString(" D6:");
	if(Digital6==1)
	  LCD1602_Writedat('1');
	else
		LCD1602_Writedat('0');
  }
	else
	{
		LCD1602_Writecom(0x80);
		LCD1602_SendString("D7:");
		if(Digital7==1)
			LCD1602_Writedat('1');
		else
			LCD1602_Writedat('0');
		LCD1602_SendString(" D8:");
		if(Digital8==1)
			LCD1602_Writedat('1');
		else
			LCD1602_Writedat('0');
	}
}
void Show_Tempreture(void)
{
	unsigned int Temp = Get_Temp();
	unsigned char code Table[]="0123456789";
	LCD1602_Writecom(0x80);
	LCD1602_SendString("Temperature:");
	LCD1602_Writecom(0x80+0x40);
	LCD1602_Writedat(Table[Temp/100]);
	LCD1602_Writedat(Table[Temp%100/10]);
	LCD1602_Writedat('.');
	LCD1602_Writedat(Table[Temp%10]);
	LCD1602_Writedat(0xdf);
	LCD1602_Writedat('C');
}