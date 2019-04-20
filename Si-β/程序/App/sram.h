#ifndef __SRAM_H
#define __SRAM_H


#include"stm32f10x.h"

/* 定义FSMC的地址 */
#define Bank1_SRAM3_ADDR    ((uint32_t)(0x68000000))		

/* 声明全局函数 */
void SRAM_Config(void);
void SRAM_WriteBuffer(uint16_t *writeBuf, uint32_t writeAddr, uint32_t length);
void SRAM_ReadBuffer(uint16_t* readBuff, uint32_t readAddr, uint32_t length);

#endif
