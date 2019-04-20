#ifndef _BEEP_H_
#define _BEEP_H_
void Beep_Init(void);
#define Beep_On GPIO_SetBits(GPIOG,GPIO_Pin_8)
#define Beep_Off GPIO_ResetBits(GPIOG,GPIO_Pin_8)
#endif
