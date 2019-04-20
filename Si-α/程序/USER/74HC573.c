#include "74HC573.h"
#include "Port.h"
sbit PP1=P0^0;
sbit PP2=P0^1;
sbit PP3=P0^2;
sbit PP4=P0^3;
sbit PP5=P0^4;
sbit PP6=P0^5;
sbit PP7=P0^6;
sbit PP8=P0^7;
void Set_Pin(unsigned char Port,bit Statue)
{
	unsigned char Temp=0xff;
	if(Statue==1)
	{
		switch(Port)
		{
			case 1:
				PP1=1;
				break;
			case 2:
				PP2=1;
				break;
			case 3:
				PP3=1;
				break;
			case 4:
				PP4=1;
				break;
			case 5:
				PP5=1;
				break;
			case 6:
				PP6=1;
				break;
			case 7:
				PP7=1;
				break;
			case 8:
				PP8=1;
				break;
		}
	}
	else
	{
		switch(Port)
		{
			case 1:
				PP1=0;
				break;
			case 2:
				PP2=0;
				break;
			case 3:
				PP3=0;
				break;
			case 4:
				PP4=0;
				break;
			case 5:
				PP5=0;
				break;
			case 6:
				PP6=0;
				break;
			case 7:
				PP7=0;
				break;
			case 8:
				PP8=0;
				break;
		}
	}
	Temp=0xff;
	HC573_LE=1;
	while(Temp--);
	HC573_LE=0;
}