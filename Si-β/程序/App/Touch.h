#ifndef _TOUCH_H_
#define _TOUCH_H_
#define TOUCH_READ_TIMES 6
#define TOUCH_CS_CLR GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define TOUCH_CS_SET GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define TOUCH_X_CMD      0xD0  //读取X轴命令
#define TOUCH_Y_CMD      0x90  //读取Y轴命令
#define TOUCH_MAX        20    //预期差值
#define TOUCH_X_MAX      4000  //X轴最大值
#define TOUCH_X_MIN      100   //X轴最小值
#define TOUCH_Y_MAX      4000  //Y轴最大值
#define TOUCH_Y_MIN      100   //Y轴最小值
#define TFT_XMAX 319	
#define TFT_YMAX 479
#define LCD_ADJX_MIN (10)                      //读取四个点的最小X值
#define LCD_ADJX_MAX (TFT_XMAX - LCD_ADJX_MIN) //读取四个点的最大X值
#define LCD_ADJY_MIN (10)                      //读取四个点的最小Y值
#define LCD_ADJY_MAX (TFT_YMAX - LCD_ADJY_MIN) //读取四个点的最大Y值
#define LCD_ADJ_X (LCD_ADJX_MAX - LCD_ADJY_MIN)//读取方框的宽度
#define LCD_ADJ_Y (LCD_ADJY_MAX - LCD_ADJY_MIN)//读取方框的高度
typedef struct{
    uint8_t posState;   
    int16_t xOffset;
    int16_t yOffset; 
    float xFactor;
    float yFactor;
} PosTypeDef;
typedef struct 
{
	uint16_t x;
	uint16_t y;
    uint16_t lcdx;
    uint16_t lcdy;
} TouchTypeDef;
#define TOUCH_ADJ_OK  'Y' 
uint8_t TOUCH_Scan(void);
void Touch_Init(void);
void TOUCH_Adjust(void);
uint8_t TOUCH_ReadXY(uint16_t *xValue, uint16_t *yValue);
#endif
