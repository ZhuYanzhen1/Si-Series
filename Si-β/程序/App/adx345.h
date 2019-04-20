#ifndef __ADX345_H
#define __ADX345_H


#include "stm32f10x.h"

/* ADX345的I2C地址 */
#define ADX345_ADDR        0x3A   //ADX345的I2C地址

/* ADXL345的指令表 */
#define ADX_DEVID          0x00   //器件ID
#define ADX_DATA_FORMAT    0x31   //数据格式控制
#define ADX_BW_RATE        0x2C   //数据速率及功率模式控制
#define ADX_POWER_CTL      0x2D   //省电特性控制
#define ADX_INT_ENABLE     0x2E   //中断使能控制
#define ADX_OFSX           0x1E   //敲击阈值
#define ADX_OFSY           0x1F   //X轴偏移
#define ADX_OFSZ           0x20   //Y轴偏移


/* 声明全局函数 */
int ADX345_Init(void);
void ADX345_Adjust(void);
void ADX_GetXYZData(int16_t *xValue, int16_t *yValue, int16_t *zValue);
int16_t ADX_GetAngle(float xValue, float yValue, float zValue, uint8_t dir);


#endif
