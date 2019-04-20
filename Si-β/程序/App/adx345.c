#include "adx345.h"
#include "IIC2.h"
#include "math.h"
#include "system.h"
#include "stm32f10x_it.h"
#define ADX345_DelayMs(x)     {Delayms(x);}  //延时函数

/****************************************************************************
* Function Name  : ADX345_WriteReg
* Description    : 设置ADX345寄存器
* Input          : addr：寄存器地址
*                * dat：吸入数据
* Output         : None
* Return         : None
****************************************************************************/

static int8_t ADX345_WriteReg(uint8_t addr, uint8_t dat)
{
	IIC2_Start();
	IIC2_SendData(ADX345_ADDR); //24C02写地址
    if(IIC2_WaitAck())          //如果无应答，表示发送失败
    {
        return 0xFF;
    }
    IIC2_SendData(addr); 
    if(IIC2_WaitAck())         //如果无应答，表示发送失败
    {
        return 0xFF;
    }
    IIC2_SendData(dat); 
    if(IIC2_WaitAck())
    {
        return 0xFF;
    }
    IIC2_Stop();
    return 0;   
}

/****************************************************************************
* Function Name  : ADX345_ReadReg
* Description    : 读取ADX345寄存器
* Input          : addr：读取地址
* Output         : None
* Return         : 读取到的8位数据
****************************************************************************/

static uint8_t ADX345_ReadReg(uint8_t addr)
{
    uint8_t readValue = 0xFF;

    IIC2_Start();
	  IIC2_SendData(ADX345_ADDR);    //24C02写地址
    if(IIC2_WaitAck())
    {
        return readValue;
    }
    IIC2_SendData(addr); 
    if(IIC2_WaitAck())
    {
        return readValue;
    }

    IIC2_Start();
	IIC2_SendData(ADX345_ADDR + 1); //24C02读地址
    if(IIC2_WaitAck())
    {
        return readValue;       
    }
    readValue = IIC2_ReceiveData(0);
    IIC2_Stop();

    return readValue;
}

/****************************************************************************
* Function Name  : ADX345_ReadXYZ
* Description    : 读取X,Y,Z的AD值
* Input          : xValue：X轴的保存地址
*                * yValue：Y轴的保存地址
*                * zValue：Z轴的保存地址
* Output         : None
* Return         : 0：读取成功。0xFF：读取失败
****************************************************************************/

static int8_t ADX345_ReadXYZ(int16_t *xValue, int16_t *yValue, int16_t *zValue)
{
    uint8_t readValue[6], i;
    IIC2_Start();
	IIC2_SendData(ADX345_ADDR);    //24C02写地址
    if(IIC2_WaitAck())
    {
        return 0xFF;
    }
    IIC2_SendData(0x32);           //发送读地址（X轴首地址）
    if(IIC2_WaitAck())
    {
        return 0xFF;
    }

    IIC2_Start();
	IIC2_SendData(ADX345_ADDR + 1); //24C02读地址
    if(IIC2_WaitAck())
    {
        return 0xFF;       
    }

    /* 读取六个字节数据 */
    for(i=0; i<6; i++)
    {
        
        if(i == 5)        //接收最后一个字节时，发送NACK
        {
            readValue[i] = IIC2_ReceiveData(0);
        }
        else             //发送接收后应答
        {
            readValue[i] = IIC2_ReceiveData(1); 
        }
    }
    IIC2_Stop();
    /* 处理读取到的数据 */
	*xValue = (uint16_t)(readValue[1] << 8) + readValue[0]; 	    
	*yValue = (uint16_t)(readValue[3] << 8) + readValue[2]; 	    
	*zValue = (uint16_t)(readValue[5] << 8) + readValue[4]; 	   

   return 0;
}

/****************************************************************************
* Function Name  : ADX345_Init
* Description    : 初始化ADX345，并核对ADX的ID
* Input          : None
* Output         : None
* Return         : 0：成功。0xFF：失败
****************************************************************************/

int ADX345_Init(void)
{
    IIC2_Config();
    if(ADX345_ReadReg(ADX_DEVID) == 0xE5)
    {
        ADX345_WriteReg(ADX_DATA_FORMAT,0x2B);//13位全分辨率,输出数据右对齐,16g量程 
		ADX345_WriteReg(ADX_BW_RATE,0x0A);	  //数据输出速度为100Hz
		ADX345_WriteReg(ADX_POWER_CTL,0x28);  //链接使能,测量模式
		ADX345_WriteReg(ADX_INT_ENABLE,0x00); //不使用中断		 
	 	ADX345_WriteReg(ADX_OFSX,0x00);       //敲击阀值
		ADX345_WriteReg(ADX_OFSY,0x00);       //X轴偏移
		ADX345_WriteReg(ADX_OFSZ,0x00);       //Y轴偏移
        return 0;
    }
   
    return 0xFF; //返回初始化失败
}

/****************************************************************************
* Function Name  : ADX345_Adjust
* Description    : ADX345进行校正。
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

void ADX345_Adjust(void)
{
    int32_t offx = 0, offy = 0, offz = 0;
    int16_t xValue, yValue, zValue;
    uint8_t i;

	ADX345_WriteReg(ADX_POWER_CTL, 0x00);	 //先进入休眠模式.
	ADX345_DelayMs(100);
	ADX345_Init(); 
    ADX345_DelayMs(20);
    
    /* 读取十次数值 */
    for(i=0; i<10; i++)
    {
        ADX345_ReadXYZ(&xValue, &yValue, &zValue);
        offx += xValue;
        offy += yValue;
        offz += zValue;
        ADX345_DelayMs(10);   //才样频率在100HZ，10ms采样一次最好         
    }
    
    /* 求出平均值 */
    offx /= 10;
    offy /= 10;
    offz /= 10;
    
    /* 全分辨率下，每个输出LSB为3.9 mg或偏移寄存器LSB的四分之一，所以除以4 */
    xValue = -(offx / 4);
	yValue = -(offy / 4);
	zValue = -((offz - 256) / 4);
    
    /* 设置偏移量 */
	ADX345_WriteReg(ADX_OFSX, xValue);
	ADX345_WriteReg(ADX_OFSY, yValue);
	ADX345_WriteReg(ADX_OFSZ, zValue); 
            
}

/****************************************************************************
* Function Name  : ADX_GetXYZData
* Description    : 读取ADX的XYZ轴的值（进行过数据处理）
* Input          : xValue：X轴的保存地址
*                * yValue：Y轴的保存地址
*                * zValue：Z轴的保存地址
* Output         : None
* Return         : None
****************************************************************************/

void ADX_GetXYZData(int16_t *xValue, int16_t *yValue, int16_t *zValue)
{
    int32_t xTotal = 0, yTotal = 0, zTotal = 0;
    uint8_t i;
    
    *xValue = 0;
    *yValue = 0;
    *zValue = 0;

    /* 读取十次采样值 */
    for(i=0; i<10; i++)
    {
        ADX345_ReadXYZ(xValue, yValue, zValue);
        xTotal += *xValue;
        yTotal += *yValue;
        zTotal += *zValue;
        ADX345_DelayMs(10);  //才样频率在100HZ，10ms采样一次最好 
    }
    
    /* 求出平均值 */
    *xValue = xTotal / 10;
    *yValue = yTotal / 10;
    *zValue = zTotal / 10;       
}

/****************************************************************************
* Function Name  : ADX_GetAngle
* Description    : 将AD值转换成角度值
* Input          : xValue：x的值
*                * yValue：y的值
*                * zValue：z的值
*                * dir：0：与Z轴的角度;1：与X轴的角度;2：与Y轴的角度.
* Output         : None
* Return         : None
****************************************************************************/

int16_t ADX_GetAngle(float xValue, float yValue, float zValue, uint8_t dir)
{
	float temp;
 	float res = 0;

	switch(dir)
	{   
        /* 与自然Z轴的角度 */
		case 0:
 			temp = sqrt((xValue * xValue + yValue * yValue)) / zValue;
 			res = atan(temp);
 			break;
        
        /* 与自然X轴的角度 */
		case 1:
 			temp = xValue / sqrt((yValue * yValue + zValue * zValue));
 			res = atan(temp);
 			break;

        /* 与自然Y轴的角度 */
 		case 2:
 			temp = yValue / sqrt((xValue * xValue + zValue * zValue));
 			res = atan(temp);
 			break;

        default:
            break;
 	}

    res = res * 1800 / 3.14; 

	return res;
}

