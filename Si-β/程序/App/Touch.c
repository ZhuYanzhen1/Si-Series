#include "System.h"
#include "Touch.h"
#include "SPI2.h"
#include "stm32f10x_it.h"
#include "GUI.h"
#include "LCD.h"
#include "USART.h"
uint8_t TOUCH_PEN=0;
static PosTypeDef TouchAdj;
TouchTypeDef TouchData;
void Touch_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Touch_Init(void)
{
	Touch_GPIO_Init();
	printf("Touch GPIO Init Success \r\n");
	TOUCH_Adjust();
	printf("The X Offset is:%f \r\n",(float)TouchAdj.xOffset);
	printf("The Y Offset is:%f \r\n",(float)TouchAdj.yOffset);
	printf("The X Factor is:%f \r\n",(float)TouchAdj.xFactor);
	printf("The Y Factor is:%f \r\n",(float)TouchAdj.yFactor);
	//TouchAdj.xOffset = 151 ;
  //TouchAdj.yOffset = 0xffffffe3 ;
  //TouchAdj.xFactor =  -0.086366  ;
  //TouchAdj.yFactor = 0.130658 ;
}
uint16_t TOUCH_ReadData(uint8_t cmd)
{
    uint8_t i, j;
    uint16_t readValue[TOUCH_READ_TIMES], value;
    uint32_t totalValue;
    for(i=0; i<TOUCH_READ_TIMES; i++)
    {
        TOUCH_CS_CLR;
        SPI2_WriteReadData(cmd); 
        readValue[i] = SPI2_WriteReadData(0xFF);
        readValue[i] <<= 8;
        readValue[i] |= SPI2_WriteReadData(0xFF);
        readValue[i] >>= 3;
        TOUCH_CS_SET;
    }
    for(i=0; i<(TOUCH_READ_TIMES - 1); i++)
    {
        for(j=i+1; j<TOUCH_READ_TIMES; j++)
        {
            if(readValue[i] < readValue[j])
            {
                value = readValue[i];
								readValue[i] = readValue[j];
								readValue[j] = value;
            }   
        }       
    }
    j = TOUCH_READ_TIMES - 1;
    totalValue = 0;
    for(i=1; i<j; i++) 
    {
        totalValue += readValue[i];
    }
    value = totalValue / (TOUCH_READ_TIMES - 2);   
    return value;
}

uint8_t TOUCH_ReadXY(uint16_t *xValue, uint16_t *yValue)
{
    uint16_t xValue1, yValue1, xValue2, yValue2;
    xValue1 = TOUCH_ReadData(TOUCH_X_CMD);
    yValue1 = TOUCH_ReadData(TOUCH_Y_CMD);
    xValue2 = TOUCH_ReadData(TOUCH_X_CMD);
    yValue2 = TOUCH_ReadData(TOUCH_Y_CMD);
    if(xValue1 > xValue2)
        *xValue = xValue1 - xValue2;
    else
        *xValue = xValue2 - xValue1;
    if(yValue1 > yValue2)
        *yValue = yValue1 - yValue2;
    else
        *yValue = yValue2 - yValue1;
		if((*xValue > TOUCH_MAX+0) || (*yValue > TOUCH_MAX+0))  
		{
			return 0xFF;
		}
    *xValue = (xValue1 + xValue2) / 2;
    *yValue = (yValue1 + yValue2) / 2;
    if((*xValue > TOUCH_X_MAX+0) || (*xValue < TOUCH_X_MIN) 
       || (*yValue > TOUCH_Y_MAX+0) || (*yValue < TOUCH_Y_MIN))
    {                   
        return 0xFF;
    }
    return 0; 
}
void GUI_DrowSign(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;
    LCD_SetWindows(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
        LCD_WR_DATA(color);    
    }
    LCD_SetWindows(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
        LCD_WR_DATA(color);    
    }
    LCD_SetWindows(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
        LCD_WR_DATA(color);    
    }
}
uint8_t TOUCH_ReadAdjust(uint16_t x, uint16_t y, uint16_t *xValue, uint16_t *yValue)
{
    uint8_t i;
    uint32_t timeCont;
    LCD_Clear(WHITE);
    GUI_DrowSign(x,y,RED);
    i = 0;
    while(1)
    {
        if(!TOUCH_ReadXY(xValue, yValue))
        {
            i++;
            if(i > 10)
            {
							printf("Receve Touch \r\n");
                GUI_DrowSign(x, y, BLACK);
                return 0;
            } 
        }
		    timeCont++;
        if(timeCont > 0xFFFFFFFE)
        {   
                GUI_DrowSign(x, y, BLACK); 
                return 0xFF;
        } 
    }       
}
void TOUCH_Adjust(void)
{
    uint16_t px[2], py[2], xPot[4], yPot[4];
    float xFactor, yFactor;
    if(TOUCH_ReadAdjust(LCD_ADJX_MIN, LCD_ADJY_MIN, &xPot[0], &yPot[0]))
    {
        return;
    }   
    Delayms(500);
    if(TOUCH_ReadAdjust(LCD_ADJX_MIN, LCD_ADJY_MAX, &xPot[1], &yPot[1]))
    {
        return;
    }   
    Delayms(500);
    if(TOUCH_ReadAdjust(LCD_ADJX_MAX, LCD_ADJY_MIN, &xPot[2], &yPot[2]))
    {
        return;
    }   
    Delayms(500);
    if(TOUCH_ReadAdjust(LCD_ADJX_MAX, LCD_ADJY_MAX, &xPot[3], &yPot[3]))
    {
        return;
    }   
    Delayms(500);
    px[0] = (xPot[0] + xPot[1]) / 2;
    py[0] = (yPot[0] + yPot[2]) / 2;
    px[1] = (xPot[3] + xPot[2]) / 2;
    py[1] = (yPot[3] + yPot[1]) / 2;
    xFactor = (float)LCD_ADJ_X / (px[1] - px[0]);
    yFactor = (float)LCD_ADJ_Y / (py[1] - py[0]);  
    TouchAdj.xOffset = (int16_t)LCD_ADJX_MAX - ((float)px[1] * xFactor);
    TouchAdj.yOffset = (int16_t)LCD_ADJY_MAX - ((float)py[1] * yFactor);
    TouchAdj.xFactor = xFactor ;
    TouchAdj.yFactor = yFactor ;
    TouchAdj.posState = TOUCH_ADJ_OK;          
}
uint8_t TOUCH_Scan(void)
{  
    //if(TOUCH_PEN == 0)   //查看是否有触摸
    //{
        if(TOUCH_ReadXY(&TouchData.x, &TouchData.y)) //没有触摸
        {
            return 0xFF;    
        }
        /* 根据物理坐标值，计算出彩屏坐标值 */
        TouchData.lcdx = TouchData.x * TouchAdj.xFactor + TouchAdj.xOffset;
        TouchData.lcdy = TouchData.y * TouchAdj.yFactor + TouchAdj.yOffset;
        /* 查看彩屏坐标值是否超过彩屏大小 */
        if(TouchData.lcdx > TFT_XMAX)
        {
            TouchData.lcdx = TFT_XMAX;
        }
        if(TouchData.lcdy > TFT_YMAX)
        {
            TouchData.lcdy = TFT_YMAX;
        }
        return 0; 
    //}
    //return 0xFF;       
}
