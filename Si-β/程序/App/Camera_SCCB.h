#ifndef _CAMERA_SCCB_H_
#define _CAMERA_SCCB_H_

#define OV7725_SIO_C_GPIO_PORT GPIOG
#define OV7725_SIO_C_GPIO_PIN GPIO_Pin_6

#define OV7725_SIO_D_GPIO_PORT GPIOG
#define OV7725_SIO_D_GPIO_PIN GPIO_Pin_7

#define ADDR_OV7725 0x42
#define DEV_ADR ADDR_OV7725

#define SCL_H         GPIO_SetBits(OV7725_SIO_C_GPIO_PORT , OV7725_SIO_C_GPIO_PIN) 
#define SCL_L         GPIO_ResetBits(OV7725_SIO_C_GPIO_PORT , OV7725_SIO_C_GPIO_PIN) 
#define SDA_H         GPIO_SetBits(OV7725_SIO_D_GPIO_PORT , OV7725_SIO_D_GPIO_PIN) 
#define SDA_L         GPIO_ResetBits(OV7725_SIO_D_GPIO_PORT , OV7725_SIO_D_GPIO_PIN) 
#define SCL_read      GPIO_ReadInputDataBit(OV7725_SIO_C_GPIO_PORT , OV7725_SIO_C_GPIO_PIN) 
#define SDA_read      GPIO_ReadInputDataBit(OV7725_SIO_D_GPIO_PORT , OV7725_SIO_D_GPIO_PIN) 
#define ADDR_OV7725   0x42
void SCCB_GPIO_Config(void);
int SCCB_WriteByte(u16 WriteAddress,u8 SendByte);
int SCCB_ReadByte(u8* pBuffer,u16 length,u8 ReadAddress);
#endif
