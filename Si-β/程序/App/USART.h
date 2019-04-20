#ifndef _USART_H_
#define _USART_H_
#include "System.h"
#include <stdio.h>
#include "stm32f10x_it.h"
void USART1_Test(void);
void USART1_Init(u32 BaudRate);
int fputc(int ch,FILE *f);
#endif

