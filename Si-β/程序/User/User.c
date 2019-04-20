#include "System.h"
#include "User.h"
#include "LCD.h"
#include "GUI.h"
#include "Camera.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"
#define R_Threshold 7
#define G_Threshold 7
#define B_Threshold 7
extern uint8_t Ov7725_vsync;
static unsigned char Point_X[4800];
static unsigned char Point_Y[4800];
float a=0,b=0;
void float2str(float val, uint8_t Decimal, char *buf)
{
 char fmt[]="%.3f";
 fmt[2]=Decimal+0x30;
 sprintf(buf, fmt, val);
}
void SquareLinear(unsigned int num)
{
		long sum_x2 = 0,sum_x=0,sum_y=0,sum_xy=0;
	  int i;
		for (i = 0; i < num; ++i) 
		{
			sum_x2 += Point_X[i]*Point_X[i];
			sum_y += Point_Y[i];
			sum_x += Point_X[i];
			sum_xy += Point_X[i]*Point_Y[i];
		}
		a = (float)((num*sum_xy) - (sum_x*sum_y))/(float)((num*sum_x2) - (sum_x*sum_x));
		b = (float)((sum_x2*sum_y) - (sum_x*sum_xy))/(float)((num*sum_x2)-(sum_x*sum_x));
}
void User(void)
{
	float Rotation=0;
	static char Buffer[22];
	static unsigned char Pooling_R[4800];
	static unsigned char Pooling_G[4800];
	static unsigned char Pooling_B[4800];
	unsigned int Double_Counter = 0,Possition_Counter=0;
	memset((unsigned long *)Point_X, 0, sizeof(Point_X));
	memset((unsigned long *)Point_Y, 0, sizeof(Point_Y));
	while(1)
	{
		if(Ov7725_vsync == 2)
		{
			static unsigned char Temp_R[1280];
			static unsigned char Temp_G[1280];
			static unsigned char Temp_B[1280];
			static unsigned char Row_Counter=0;
			static unsigned int Polling_Counter=0;
			static unsigned char R_Average=0,G_Average=0,B_Average=0;
			static unsigned int RGB565=0;
			static unsigned int RGB_Average=0,Temp1_Address,Temp2_Address;
			static unsigned int Temp3_Address,Temp4_Address;
			static unsigned int Line_Counter=0,Data_Address=0;
			static unsigned int R_Sum,G_Sum,B_Sum;
			FIFO_PREPARE();
			while(1)
			{
				LCD_SetWindows(0,Row_Counter*4,319,Row_Counter*4+3);
				while(1)
				{
					RGB565 = READ_FIFO_PIXEL();
					Temp_R[Line_Counter] = RGB565>>11;
					Temp_G[Line_Counter] = (RGB565>>5)&0x003F;
					Temp_B[Line_Counter] = RGB565&0x001F;
					LCD_WR_DATA(RGB565);
					Line_Counter++;
					if(Line_Counter==1280)
						break;
				}
				Line_Counter=0;
				LCD_SetWindows(0,240+Row_Counter,80,240+Row_Counter);
				while(1)
				{
					Temp1_Address=Polling_Counter;
					Temp2_Address=Temp1_Address +320;
					Temp3_Address=Temp1_Address +640;
					Temp4_Address=Temp1_Address +960;
					R_Sum+=Temp_R[Temp1_Address];
					R_Sum+=Temp_R[Temp1_Address+1];
					R_Sum+=Temp_R[Temp1_Address+2];
					R_Sum+=Temp_R[Temp1_Address+3];
					R_Sum+=Temp_R[Temp2_Address];
					R_Sum+=Temp_R[Temp2_Address+1];
					R_Sum+=Temp_R[Temp2_Address+2];
					R_Sum+=Temp_R[Temp2_Address+3];
					R_Sum+=Temp_R[Temp3_Address];
					R_Sum+=Temp_R[Temp3_Address+1];
					R_Sum+=Temp_R[Temp3_Address+2];
					R_Sum+=Temp_R[Temp3_Address+3];
					R_Sum+=Temp_R[Temp4_Address];
					R_Sum+=Temp_R[Temp4_Address+1];
					R_Sum+=Temp_R[Temp4_Address+2];
					R_Sum+=Temp_R[Temp4_Address+3];
					G_Sum+=Temp_G[Temp1_Address];
					G_Sum+=Temp_G[Temp1_Address+1];
					G_Sum+=Temp_G[Temp1_Address+2];
					G_Sum+=Temp_G[Temp1_Address+3];
					G_Sum+=Temp_G[Temp2_Address];
					G_Sum+=Temp_G[Temp2_Address+1];
					G_Sum+=Temp_G[Temp2_Address+2];
					G_Sum+=Temp_G[Temp2_Address+3];
					G_Sum+=Temp_G[Temp3_Address];
					G_Sum+=Temp_G[Temp3_Address+1];
					G_Sum+=Temp_G[Temp3_Address+2];
					G_Sum+=Temp_G[Temp3_Address+3];
					G_Sum+=Temp_G[Temp4_Address];
					G_Sum+=Temp_G[Temp4_Address+1];
					G_Sum+=Temp_G[Temp4_Address+2];
					G_Sum+=Temp_G[Temp4_Address+3];
					B_Sum+=Temp_B[Temp1_Address];
					B_Sum+=Temp_B[Temp1_Address+1];
					B_Sum+=Temp_B[Temp1_Address+2];
					B_Sum+=Temp_B[Temp1_Address+3];
					B_Sum+=Temp_B[Temp2_Address];
					B_Sum+=Temp_B[Temp2_Address+1];
					B_Sum+=Temp_B[Temp2_Address+2];
					B_Sum+=Temp_B[Temp2_Address+3];
					B_Sum+=Temp_B[Temp3_Address];
					B_Sum+=Temp_B[Temp3_Address+1];
					B_Sum+=Temp_B[Temp3_Address+2];
					B_Sum+=Temp_B[Temp3_Address+3];
					B_Sum+=Temp_B[Temp4_Address];
					B_Sum+=Temp_B[Temp4_Address+1];
					B_Sum+=Temp_B[Temp4_Address+2];
					B_Sum+=Temp_B[Temp4_Address+3];
					R_Average= R_Sum/16;
					G_Average= G_Sum/16;
					B_Average= B_Sum/16;
					Pooling_R[Data_Address] = R_Average;
					Pooling_G[Data_Address] = R_Average;
					Pooling_B[Data_Address] = R_Average;
					Data_Address++;
					Polling_Counter+=4;
					RGB_Average = R_Average<<11;
					RGB_Average |= G_Average<<5;
					RGB_Average |= B_Average;
					LCD_WR_DATA(RGB_Average);
					R_Sum=0;
					G_Sum=0;
					B_Sum=0;
					R_Average=0;
					G_Average=0;
					B_Average=0;
					if (Polling_Counter==320)
							break;
         }
				Polling_Counter=0;
				Row_Counter++;
				 if(Row_Counter ==60)
					 break;
			}
			Data_Address =0;
			Row_Counter=0;		
			LCD_SetWindows(80,240,159,299);
			while(1)
			{
				if(Pooling_R[Double_Counter] <= R_Threshold && Pooling_G[Double_Counter] <= G_Threshold && Pooling_B[Double_Counter] <= B_Threshold)
				{
						Point_X[Possition_Counter]=Double_Counter%80;
						Point_Y[Possition_Counter]=60-(Double_Counter/80);
						Possition_Counter++;
						LCD_WR_DATA(0x07ff);
				}
				else
					LCD_WR_DATA(BLACK);
				Double_Counter++;
				if(Double_Counter==4801)
					break;
			}
			Double_Counter=0;
			SquareLinear(Possition_Counter);
			Possition_Counter=0;
			LCD_Fill(160,240,240,300,0xefff);
			if(a>1.0)
				LCD_DrawLine(160,300,(unsigned int)(((60-b)/a)+160),240);
			else
				LCD_DrawLine(160,300,240,(unsigned int)(300-(80*a+b)));
			 LCD_ShowString(240,245,16,"Rotation:",0);
			 Rotation=(float)(atan(a) * 180.0/3.1416);
			 float2str(Rotation,4,Buffer);
			 LCD_ShowString(240,265,16,(unsigned char *)Buffer,0);
			Ov7725_vsync = 0;	
	}
 }
}
