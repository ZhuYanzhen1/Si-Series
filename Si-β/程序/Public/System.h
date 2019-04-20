#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include "stm32f10x.h"
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    
#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //?? 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //?? 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //?? 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //?? 
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //?? 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //?? 
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //?? 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //?? 
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //?? 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //??
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //?? 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //??
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //?? 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //??
#define PA0 PAout(0)
#define PA1 PAout(1)
#define PA2 PAout(2)
#define PA3 PAout(3)
#define PA4 PAout(4)
#define PA5 PAout(5)
#define PA6 PAout(6)
#define PA7 PAout(7)
#define PA8 PAout(8)
#define PA9 PAout(9)
#define PA10 PAout(10)
#define PA11 PAout(11)
#define PA12 PAout(12)
#define PA13 PAout(13)
#define PA14 PAout(14)
#define PA15 PAout(15)
#define PB0 PBout(0)
#define PB1 PBout(1)
#define PB2 PBout(2)
#define PB3 PBout(3)
#define PB4 PBout(4)
#define PB5 PBout(5)
#define PB6 PBout(6)
#define PB7 PBout(7)
#define PB8 PBout(8)
#define PB9 PBout(9)
#define PB10 PBout(10)
#define PB11 PBout(11)
#define PB12 PBout(12)
#define PB13 PBout(13)
#define PB14 PBout(14)
#define PB15 PBout(15)
#define PC0 PCout(0)
#define PC1 PCout(1)
#define PC2 PCout(2)
#define PC3 PCout(3)
#define PC4 PCout(4)
#define PC5 PCout(5)
#define PC6 PCout(6)
#define PC7 PCout(7)
#define PC8 PCout(8)
#define PC9 PCout(9)
#define PC10 PCout(10)
#define PC11 PCout(11)
#define PC12 PCout(12)
#define PC13 PCout(13)
#define PC14 PCout(14)
#define PC15 PCout(15)
#define PD0 PDout(0)
#define PD1 PDout(1)
#define PD2 PDout(2)
#define PD3 PDout(3)
#define PD4 PDout(4)
#define PD5 PDout(5)
#define PD6 PDout(6)
#define PD7 PDout(7)
#define PD8 PDout(8)
#define PD9 PDout(9)
#define PD10 PDout(10)
#define PD11 PDout(11)
#define PD12 PDout(12)
#define PD13 PDout(13)
#define PD14 PDout(14)
#define PD15 PDout(15)
#define PE0 PEout(0)
#define PE1 PEout(1)
#define PE2 PEout(2)
#define PE3 PEout(3)
#define PE4 PEout(4)
#define PE5 PEout(5)
#define PE6 PEout(6)
#define PE7 PEout(7)
#define PE8 PEout(8)
#define PE9 PEout(9)
#define PE10 PEout(10)
#define PE11 PEout(11)
#define PE12 PEout(12)
#define PE13 PEout(13)
#define PE14 PEout(14)
#define PE15 PEout(15)
#define PF0 PFout(0)
#define PF1 PFout(1)
#define PF2 PFout(2)
#define PF3 PFout(3)
#define PF4 PFout(4)
#define PF5 PFout(5)
#define PF6 PFout(6)
#define PF7 PFout(7)
#define PF8 PFout(8)
#define PF9 PFout(9)
#define PF10 PFout(10)
#define PF11 PFout(11)
#define PF12 PFout(12)
#define PF13 PFout(13)
#define PF14 PFout(14)
#define PF15 PFout(15)
#define PG0 PGout(0)
#define PG1 PGout(1)
#define PG2 PGout(2)
#define PG3 PGout(3)
#define PG4 PGout(4)
#define PG5 PGout(5)
#define PG6 PGout(6)
#define PG7 PGout(7)
#define PG8 PGout(8)
#define PG9 PGout(9)
#define PG10 PGout(10)
#define PG11 PGout(11)
#define PG12 PGout(12)
#define PG13 PGout(13)
#define PG14 PGout(14)
#define PG15 PGout(15)
void GPIO_Config(void);
#endif
