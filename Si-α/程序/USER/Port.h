#ifndef _PORT_H_
#define _PORT_H_
#include "STC12.h"
#include "stdio.h"
#include "intrins.h"
#define D0 P0
#define Beep_On Beep=0
#define Beep_Off Beep=1
sbit Digital1=P2^6;
sbit Digital2=P2^7;
sbit Digital3=P3^2;
sbit Beep=P4^4;
sbit Digital4=P3^3;
sbit Digital5=P3^4;
sbit Digital6=P3^5;
sbit Digital7=P3^6;
sbit Digital8=P3^7;
sbit KEY=P2^4;
sbit HC573_LE=P2^3;
sbit LED0=P2^5;
sbit LCD1602_E=P2^2;
sbit LCD1602_RS=P2^1;	
sbit DS18B20=P2^0;
#endif