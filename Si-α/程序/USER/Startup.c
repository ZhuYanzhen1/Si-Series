#include "Startup.h"
#include "User_Program.h"
void Init_System(void)
{
	Digital1=1;
	Digital2=1;
	Digital3=1;
	Digital4=1;
	Digital5=1;
	Digital6=1;
	Digital7=1;
	Digital8=1;
	Beep_Off;
	Delayus(100);
	EepromWriteByte(0X00,0X51);
	EepromReadByte(0x00);
	EepromWriteByte(0X00,0X00);
	P4M1=0x00;//P4.1 P4.4 P4.5 P4.6??
	P4M0=0x72;	
	P4SW=0x70;//P4.4=I/O P4.5=I/O P4.6=I/O	
	P0M1 = BinToHex(0,0,0,0,0,0,0,0);
	P0M0 = BinToHex(0,0,0,0,0,0,0,0);
	P1M1 = BinToHex(1,1,1,0,0,1,1,1);
	P1M0 = BinToHex(0,0,0,0,0,0,0,0);
	P2M1 = BinToHex(0,0,0,0,0,0,0,0);
	P2M0 = BinToHex(0,0,0,0,0,0,0,0);
	P3M1 = BinToHex(0,0,0,0,0,0,0,0);
	P3M0 = BinToHex(0,0,0,0,0,0,0,0);
	Serial_Init();
	printf("Initing......");
	LCD1602_Init();
	InitADC();
	Init_PWM();
	PWM1_Duty(50);
	PWM2_Duty(90);
	Set_Pin(1,0);
	P0=0xff;
	HC573_LE=1;
	Delayms(1);
	HC573_LE=0;
	LCD1602_Writedat('a');
	LCD1602_SendString("Hello");
	LCD1602_Writecom(0x01);
	Get_AD_Result(1);
	Get_Temp();
	Beep_On;
	Delayms(300);
	Beep_Off;
}