#include "PWM.h"
#include "Port.h"
void PWM1_Duty(unsigned char Duty)
{
	if(Duty==0)
			CCAP0H = CCAP0L = 0;
	else
	{
		unsigned char Temp=0xff-(2.55*Duty)/1;
		CCAP0H = CCAP0L = Temp;
	}
}
void PWM2_Duty(unsigned char Duty)
{
	if(Duty==0)
			CCAP1H = CCAP1L = 0;
	else
	{
		unsigned char Temp=0xff-(2.55*Duty)/1;
		CCAP1H = CCAP1L = Temp;
	}
}
void Init_PWM()
{    
    CCON = 0;                       //清除标志位
    CL = 0;                         //重置PCA基础时钟
    CH = 0;													//重置PCA基础时钟
    CMOD = 0x02;                    //设置时钟频率是主频的二分之一                           
    CCAP0H = CCAP0L = 0xff;         //设置PWM0口占空比为100%
    CCAPM0 = 0x42;                  //PCA0工作在8位模式，值域为(0x00~0xff)，查询模式
    CCAP1H = CCAP1L = 0xff;         //设置PWM1口占空比为100%
    CCAPM1 = 0x42;                  //PCA1工作在8位模式，值域为(0x00~0xff)，查询模式
    CR = 1;                         //PCA启动
}