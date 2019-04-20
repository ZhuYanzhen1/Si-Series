#ifndef _IIC2_H_
#define _IIC2_H_
#define IIC2_SDA_SET {GPIOB->BSRR = 1 << 11;}
#define IIC2_SDA_CLR {GPIOB->BRR = 1 << 11;}
#define IIC2_SDA     (GPIOB->IDR & (1 << 11))
#define IIC2_SCL_SET {GPIOB->BSRR = 1 << 10;}
#define IIC2_SCL_CLR {GPIOB->BRR = 1 << 10;}
char IIC2_WaitAck(void);
void IIC2_Start(void);
void IIC2_Config(void);
void IIC2_Stop(void);
void IIC2_SendData(unsigned char dat);
unsigned char IIC2_ReceiveData(unsigned char ack);
#endif
