#include "Port.h"
#include "AnalogToDigital.h"
sfr ADC_LOW2 = 0xBE; 
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDHH 0x60            //70 clocks
unsigned int Get_AD(unsigned char ch);
unsigned int Get_AD_Result(unsigned char chunnel)
{
	unsigned int Result = 0x00;
	switch(chunnel)
	{
		case 1:
			Result = Get_AD(0);
			break;
		case 2:
			Result = Get_AD(1);
			break;
		case 3:
			Result = Get_AD(2);
			break;
		case 4:
			Result = Get_AD(5);
			break;
		case 5:
			Result = Get_AD(6);
			break;
		case 6:
			Result = Get_AD(7);
			break;
	}
	return Result;
}
unsigned int Get_AD(unsigned char ch)
{
	  ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ch | ADC_START;
    _nop_();_nop_();_nop_();_nop_();
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
    return (unsigned int)((ADC_RES<<2)|ADC_LOW2);                 //Return ADC result
}
void InitADC()
{
    P1ASF = 0xe7;            
    ADC_RES = 0;               
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    //Delay(2);                    
}