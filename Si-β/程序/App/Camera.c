#include "System.h"
#include "Camera.h"
#include "Camera_SCCB.h"
#include "Camera_REGISTER.h"
#include "USART.h"
void FIFO_GPIO_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_InitStructure.GPIO_Pin = OV7725_OE_GPIO_PIN;
		GPIO_Init(OV7725_OE_GPIO_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = OV7725_WRST_GPIO_PIN;
		GPIO_Init(OV7725_WRST_GPIO_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = OV7725_RRST_GPIO_PIN;
		GPIO_Init(OV7725_RRST_GPIO_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = OV7725_RCLK_GPIO_PIN;
		GPIO_Init(OV7725_RCLK_GPIO_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = OV7725_WE_GPIO_PIN;	
		GPIO_Init(OV7725_WE_GPIO_PORT, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = 	  GPIO_Pin_0 | GPIO_Pin_1 |
																			GPIO_Pin_2 | GPIO_Pin_3 |
																			GPIO_Pin_4 | 	GPIO_Pin_5 |
																			GPIO_Pin_6 | 	GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(OV7725_DATA_GPIO_PORT, &GPIO_InitStructure);
	  FIFO_OE_L();
    FIFO_WE_H(); 
}
void VSYNC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin =  OV7725_VSYNC_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OV7725_VSYNC_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(OV7725_VSYNC_EXTI_SOURCE_PORT, OV7725_VSYNC_EXTI_SOURCE_PIN);
  EXTI_InitStructure.EXTI_Line = OV7725_VSYNC_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(OV7725_VSYNC_EXTI_LINE);		
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = OV7725_VSYNC_EXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void Camera_GPIO_Init(void)
{
	SCCB_GPIO_Config();
	FIFO_GPIO_Config();
	VSYNC_Config();
}
ErrorStatus OV7725_Init(void)
{
	uint16_t i = 0;
	uint8_t Sensor_IDCode = 0;	
	printf("ov7725 Register Config Start...... \r\n");
	if( 0 == SCCB_WriteByte ( 0x12, 0x80 ) ) /*复位sensor */
	{
		printf("sccb write data error \r\n");		
		return ERROR ;
	}	
	if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, 0x0b ) )	 /* 读取sensor ID号*/
	{
		printf("read id faild");		
		return ERROR;
	}
	printf("Sensor ID is 0x%x \r\n", Sensor_IDCode);	
	if(Sensor_IDCode == OV7725_ID)
	{
		for( i = 0 ; i < OV7725_REG_NUM ; i++ )
		{
			if( 0 == SCCB_WriteByte(Sensor_Config[i].Address, Sensor_Config[i].Value) )
			{                
				printf("write reg faild: %x", Sensor_Config[i].Address);
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}
	printf("ov7725 Register Config Success \r\n");
	return SUCCESS;
}
void OV7725_Light_Mode(uint8_t mode)
{
	switch(mode)
	{
		case 0:	//Auto，自动模式
			SCCB_WriteByte(0x13, 0xff); //AWB on 
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;
		case 1://sunny，晴天
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x5a);
			SCCB_WriteByte(0x02, 0x5c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 2://cloudy，多云
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x58);
			SCCB_WriteByte(0x02, 0x60);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 3://office，办公室
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x84);
			SCCB_WriteByte(0x02, 0x4c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 4://home，家里
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x96);
			SCCB_WriteByte(0x02, 0x40);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		
		case 5://night，夜晚
			SCCB_WriteByte(0x13, 0xff); //AWB on
			SCCB_WriteByte(0x0e, 0xe5);
			break;	
		default:
			 printf("Light Mode parameter error! \r\n"); 
			break;
	}
}			


/**
  * @brief  设置饱和度
  * @param  sat:饱和度,参数范围[-4 ~ +4]             	
  * @retval 无
  */
void OV7725_Color_Saturation(int8_t sat)
{
 	if(sat >=-4 && sat<=4)
	{	
		SCCB_WriteByte(REG_USAT, (sat+4)<<4); 
		SCCB_WriteByte(REG_VSAT, (sat+4)<<4);
	}
	else
	{
		printf("Color Saturation parameter error! \r\n");
	}
}			


/**
  * @brief  设置光照度
	* @param  bri:光照度，参数范围[-4~+4]
  * @retval 无
  */
void OV7725_Brightness(int8_t bri)
{
	uint8_t BRIGHT_Value,SIGN_Value;	
	
	switch(bri)
	{
		case 4:
				BRIGHT_Value = 0x48;
				SIGN_Value = 0x06;
			break;
		
		case 3:
				BRIGHT_Value = 0x38;
				SIGN_Value = 0x06;		
		break;	
		
		case 2:
				BRIGHT_Value = 0x28;
				SIGN_Value = 0x06;			
		break;	
		
		case 1:
				BRIGHT_Value = 0x18;
				SIGN_Value = 0x06;			
		break;	
		
		case 0:
				BRIGHT_Value = 0x08;
				SIGN_Value = 0x06;			
		break;	
		
		case -1:
				BRIGHT_Value = 0x08;
				SIGN_Value = 0x0e;		
		break;	
		
		case -2:
				BRIGHT_Value = 0x18;
				SIGN_Value = 0x0e;		
		break;	
		
		case -3:
				BRIGHT_Value = 0x28;
				SIGN_Value = 0x0e;		
		break;	
		
		case -4:
				BRIGHT_Value = 0x38;
				SIGN_Value = 0x0e;		
		break;	
		default:
			printf("Brightness parameter error! \r\n");
			break;
	}
		SCCB_WriteByte(REG_BRIGHT, BRIGHT_Value); //AWB on
		SCCB_WriteByte(REG_SIGN, SIGN_Value);
}		

/**
  * @brief  设置对比度
	* @param  cnst:对比度，参数范围[-4~+4]
  * @retval 无
  */
void OV7725_Contrast(int8_t cnst)
{
	if(cnst >= -4 && cnst <=4)
	{
		SCCB_WriteByte(REG_CNST, (0x30-(4-cnst)*4));
	}
	else
	{
		printf("Contrast parameter error! \r\n");
	}
}		


/**
  * @brief  设置特殊效果
	* @param  eff:特殊效果，参数范围[0~6]:
			@arg 0:正常
			@arg 1:黑白
			@arg 2:偏蓝
			@arg 3:复古
			@arg 4:偏红
			@arg 5:偏绿
			@arg 6:反相
  * @retval 无
  */
void OV7725_Special_Effect(uint8_t eff)
{
	switch(eff)
	{
		case 0://正常
			SCCB_WriteByte(0xa6, 0x06);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0x80);
		break;
		
		case 1://黑白
			SCCB_WriteByte(0xa6, 0x26);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0x80);
		break;	
		
		case 2://偏蓝
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0xa0);
			SCCB_WriteByte(0x61, 0x40);	
		break;	
		
		case 3://复古
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x40);
			SCCB_WriteByte(0x61, 0xa0);	
		break;	
		
		case 4://偏红
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0xc0);		
		break;	
		
		case 5://偏绿
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x60);
			SCCB_WriteByte(0x61, 0x60);		
		break;	
		
		case 6://反相
			SCCB_WriteByte(0xa6, 0x46);
		break;	
		default:
			printf("Special Effect error! \r\n");
			break;
	}
}		
uint8_t Camera_Init(unsigned char Light_Mode,unsigned char Effect)
{
	uint8_t retry = 0;
	Camera_GPIO_Init();
	while(OV7725_Init() != SUCCESS)
	{
		retry++;
		if(retry==5)
			break;
	}
	if(retry==5)
		return Camera_Init_Fail;
	else
	{
		OV7725_Special_Effect(Effect);  //正常模式
		OV7725_Light_Mode(Light_Mode);      //自动光照模式
		OV7725_Color_Saturation(0);//饱和度为0
		OV7725_Brightness(0);      //亮度为0
		OV7725_Contrast(0);        //对比度为0
		OV7725_Special_Effect(Effect);  //正常模式
		OV7725_Window_Set(0,0,320,240,0);
		return Camera_Init_Success;
	}
}
uint16_t READ_FIFO_PIXEL(void)
{	
		 uint16_t RGB565;
	   RGB565=0;
	   FIFO_RCLK_L();
	   RGB565 = ((GPIOC->IDR)&0x00ff)<<8;
	   FIFO_RCLK_H();
     FIFO_RCLK_L();
	   RGB565 |= ((GPIOC->IDR)&0x00ff);
	   FIFO_RCLK_H();
	   return RGB565;
}
void FIFO_PREPARE(void)
{
	   FIFO_RRST_L();
	   FIFO_RCLK_L();
	   FIFO_RCLK_H();
	   FIFO_RRST_H();
	   FIFO_RCLK_L();
	   FIFO_RCLK_H();
}
void OV7725_Window_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height,uint8_t QVGA_VGA)
{
	uint8_t reg_raw,cal_temp;
	if(QVGA_VGA == 0)
		SCCB_WriteByte(REG_COM7,0x46); 
	else
		SCCB_WriteByte(REG_COM7,0x06); 
	SCCB_ReadByte(&reg_raw,1,REG_HSTART);
	cal_temp = (reg_raw + (sx>>2));	
	SCCB_WriteByte(REG_HSTART,cal_temp ); 
	SCCB_WriteByte(REG_HSIZE,width>>2);
	SCCB_ReadByte(&reg_raw,1,REG_VSTRT);	
	cal_temp = (reg_raw + (sy>>1));	
	SCCB_WriteByte(REG_VSTRT,cal_temp);
	SCCB_WriteByte(REG_VSIZE,height>>1);
	SCCB_ReadByte(&reg_raw,1,REG_HREF);	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2)|((sx&0x03)<<4)|((sy&0x01)<<6));	
	SCCB_WriteByte(REG_HREF,cal_temp);
	SCCB_WriteByte(REG_HOutSize,width>>2);
	SCCB_WriteByte(REG_VOutSize,height>>1);
	SCCB_ReadByte(&reg_raw,1,REG_EXHCH);	
	cal_temp = (reg_raw |(width&0x03)|((height&0x01)<<2));	
	SCCB_WriteByte(REG_EXHCH,cal_temp);	
}
