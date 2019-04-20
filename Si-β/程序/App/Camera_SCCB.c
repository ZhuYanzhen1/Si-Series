#include "System.h"
#include "Camera_SCCB.h"
#include "USART.h"
void SCCB_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
  GPIO_InitStructure.GPIO_Pin =  OV7725_SIO_C_GPIO_PIN ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(OV7725_SIO_C_GPIO_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =  OV7725_SIO_D_GPIO_PIN ;
  GPIO_Init(OV7725_SIO_D_GPIO_PORT, &GPIO_InitStructure);
}
static void SCCB_delay(void)
{	
   uint16_t i = 400; 
   while(i) 
   { 
     i--; 
   } 
}
static int SCCB_Start(void)
{
	SDA_H;
	SCL_H;
	SCCB_delay();
	if(!SDA_read)
	return DISABLE;	
	SDA_L;
	SCCB_delay();
	if(SDA_read) 
	return DISABLE;
	SDA_L;
	SCCB_delay();
	return ENABLE;
}
static void SCCB_Stop(void)
{
	SCL_L;
	SCCB_delay();
	SDA_L;
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	SDA_H;
	SCCB_delay();
}
static void SCCB_Ack(void)
{	
	SCL_L;
	SCCB_delay();
	SDA_L;
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	SCL_L;
	SCCB_delay();
}
static void SCCB_NoAck(void)
{	
	SCL_L;
	SCCB_delay();
	SDA_H;
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	SCL_L;
	SCCB_delay();
}
static int SCCB_WaitAck(void) 	
{
	SCL_L;
	SCCB_delay();
	SDA_H;			
	SCCB_delay();
	SCL_H;
	SCCB_delay();
	if(SDA_read)
	{
      SCL_L;
      return DISABLE;
	}
	SCL_L;
	return ENABLE;
}
static void SCCB_SendByte(uint8_t SendByte) 
{
    uint8_t i=8;
    while(i--)
    {
        SCL_L;
        SCCB_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        SCCB_delay();
		SCL_H;
        SCCB_delay();
    }
    SCL_L;
}
static int SCCB_ReceiveByte(void)  
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      SCCB_delay();
	  SCL_H;
      SCCB_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
}        
int SCCB_WriteByte( uint16_t WriteAddress , uint8_t SendByte)
{		
    if(!SCCB_Start())
	{
		printf("SCCB Write Fail \r\n");
	    return DISABLE;
	}
    SCCB_SendByte( DEV_ADR );            
    if( !SCCB_WaitAck() )
	{
		SCCB_Stop(); 
		printf("SCCB Write Fail \r\n");
		return DISABLE;
	}
    SCCB_SendByte((uint8_t)(WriteAddress & 0x00FF));     
    SCCB_WaitAck();	
    SCCB_SendByte(SendByte);
    SCCB_WaitAck();   
    SCCB_Stop(); 
    return ENABLE;
}       
int SCCB_ReadByte(uint8_t* pBuffer, uint16_t length, uint8_t ReadAddress)
{	
    if(!SCCB_Start())
	{
	    return DISABLE;
	}
    SCCB_SendByte( DEV_ADR );       
    if( !SCCB_WaitAck() )
	{
		SCCB_Stop(); 
		return DISABLE;
	}
    SCCB_SendByte( ReadAddress );    
    SCCB_WaitAck();	
    SCCB_Stop(); 
    if(!SCCB_Start())
	{
		return DISABLE;
	}
    SCCB_SendByte( DEV_ADR + 1 );    
    if(!SCCB_WaitAck())
	{
		SCCB_Stop(); 
		return DISABLE;
	}
    while(length)
    {
      *pBuffer = SCCB_ReceiveByte();
      if(length == 1)
	  {
		  SCCB_NoAck();
	  }
      else
	  {
		SCCB_Ack(); 
	  }
      pBuffer++;
      length--;
    }
    SCCB_Stop();
    return ENABLE;
}
