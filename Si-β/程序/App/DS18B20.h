#ifndef _DS18B20_H_
#define _DS18B20_H_
#define DS18B20_Pin GPIO_Pin_13 //PG11
#define DS18B20_Port GPIOA
#define ds18b20_dq_H GPIO_SetBits(DS18B20_Port,DS18B20_Pin)
#define ds18b20_dq_L GPIO_ResetBits(DS18B20_Port,DS18B20_Pin)
void Ds18b20_init(void);
void DQOUTINT(void);	
void DQININT(void);	 
void ds18b20init(void);
void ds18b20wr(unsigned char dat);
unsigned char DS18b20rd(void);
double readtemp(void);
#endif
