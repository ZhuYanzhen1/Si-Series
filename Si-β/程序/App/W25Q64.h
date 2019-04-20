#ifndef _W25Q64_H_
#define _W25Q64_H_

#define EN25Q64 	 0Xc816
#define W25Q80     0XEF13    
#define W25Q16     0XEF14
#define W25Q32     0XEF15
#define W25Q64     0XEF16
#define W25Q128    0XEF17

#define EN25X_WriteStatusReg    0x01   //Ð´×´Ì¬¼Ä´æÆ÷
#define EN25X_PageProgram		0x02   //Ò³±à¼­
#define EN25X_ReadData          0x03   //¶ÁÊý¾Ý
#define EN25X_WriteDisable		0x04   //Ð´Ê§ÄÜ
#define EN25X_ReadStatusReg		0x05   //¶ÁÈ¡×´Ì¬¼Ä´æÆ÷
#define EN25X_WriteEnable		0x06   //Ð´Ê¹ÄÜ
#define EN25X_SectorErase		0x20   //²Á³ý¿é
#define EN25X_ChipErase			0xC7   //²Á³ýÆ¬

#define FLASH_CS_SET GPIO_SetBits(FLASH_CS_PORT,FLASH_CS_PIN)
#define FLASH_CS_CLR {GPIO_ResetBits(FLASH_CS_PORT,FLASH_CS_PIN);\
GPIO_SetBits(GPIOG, GPIO_Pin_14);GPIO_SetBits(GPIOB, GPIO_Pin_12);}

#define FLASH_CS_PIN   GPIO_Pin_13
#define FLASH_CS_PORT  GPIOB

uint16_t FLASH_ReadID(void);
uint16_t FLASH_Init(void);
void FLASH_ChipErase(void);
void FLASH_ReadData(uint8_t *readBuff, uint32_t readAddr, uint16_t readByteNum);
void FLASH_WriteData(uint8_t *writeBuff, uint32_t writeAddr, uint16_t writeByteNum);

#endif
