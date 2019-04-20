#include "User_Program.h"
#include "Startup.h"
void main()
{
	unsigned char Press_Num=0;
	Init_System();
	while(1)
	{
		unsigned int Count_Down=0x6fff;
		while(Count_Down--)
		{
			if(KEY==0)
			{
				Delayms(20);
				if(KEY==0)
				{
					unsigned long Key_Time=0;
					while(!KEY)
					{
						Key_Time++;
					}
					if(Key_Time>100000)
					{
						LCD1602_Writecom(0x01);
						User_Program();
						while(1);
					}
					else
					{
						LCD1602_Writecom(0x01);
						Press_Num++;
					}
				}
			}
		}
		switch(Press_Num)
		{
			case 0:
				Show_Analog(0);
				break;
			case 1:
				Show_Analog(1);
				break;
			case 2:
				Show_Digital(0);
				break;
			case 3:
				Show_Digital(1);
				break;
			case 4:
				Show_Tempreture();
				break;
			case 5:
				Press_Num=0;
				break;
		}
	}
}