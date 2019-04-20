#include "CPU_Temp.h"
#include "System.h"
void CPU_Temp_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M  最大14M 设置ADC时钟（ADCCLK）
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1; 
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);
	ADC_TempSensorVrefintCmd(ENABLE);//打开内部温度传感器使能
	ADC_Cmd(ADC1,ENABLE);	
	ADC_ResetCalibration(ADC1);//重置指定的ADC的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));//获取ADC重置校准寄存器的状态
	ADC_StartCalibration(ADC1);//开始指定ADC的校准状态
	while(ADC_GetCalibrationStatus(ADC1));//获取指定ADC的校准程序
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能或者失能指定的ADC的软件转换启动功能
}
int Get_Temp(void)
{
	float ad;
	char i;
	u32 value;
	for(i=0;i<50;i++)	 //读取50此AD检测速度后求其平均值
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//转换结束标志位
			value=value+ADC_GetConversionValue(ADC1);//返回最近一次ADCx规则组的转换结果	
		}
		value/=50;
		ad=(float)value*0.0008056640625;
		ad=((1.43-ad)/0.0043)+25;
		return (int)(ad*1000);
}
