#include "CONV.h"
#include "System.h"
const char Filter1[3][3]={{-1,-1,-1},
													{-1,8,-1},
													{-1,-1,-1}};
int Result[10][10];
char Input_Image[10][10];
unsigned char CONV_Calculate(void)
{
	while(1)
	{
		unsigned char Line=0,Row=0;
		int Sum=0;
		while(1)
		{
			unsigned char Temp_L=0,Temp_R=0;
			Sum += Input_Image[Line+Temp_L][Row+Temp_R]*Filter1[Temp_L][Temp_R];
			if(Temp_L==2&&Temp_R==2)	break;
			if(Temp_R==2)	{  Temp_R=-1;Temp_L++;  }
			Temp_R++;
		}
		Result[Line][Row]=Sum;
		Sum=0;   Row++;
		if(Row==8){  Row=0;Line++;  }
		if(Line==8&&Row==8)
			break;
	}
	return 1;
}
