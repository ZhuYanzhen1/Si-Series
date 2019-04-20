/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
//#include "USART.h"
extern uint8_t Ov7725_vsync;
#define      OV7725_OE_GPIO_PORT                      GPIOE	
#define      OV7725_OE_GPIO_PIN                       GPIO_Pin_2
#define      OV7725_WRST_GPIO_PORT                    GPIOE
#define      OV7725_WRST_GPIO_PIN                     GPIO_Pin_3
#define      OV7725_RRST_GPIO_PORT                    GPIOE
#define      OV7725_RRST_GPIO_PIN                     GPIO_Pin_4
#define      OV7725_RCLK_GPIO_PORT                    GPIOE
#define      OV7725_RCLK_GPIO_PIN                     GPIO_Pin_5
#define      OV7725_WE_GPIO_PORT                      GPIOE
#define      OV7725_WE_GPIO_PIN                       GPIO_Pin_6
#define      OV7725_VSYNC_GPIO_PORT                   GPIOF
#define      OV7725_VSYNC_GPIO_PIN                    GPIO_Pin_11
#define      OV7725_VSYNC_EXTI_SOURCE_PORT            GPIO_PortSourceGPIOF
#define      OV7725_VSYNC_EXTI_SOURCE_PIN             GPIO_PinSource11
#define      OV7725_VSYNC_EXTI_LINE                   EXTI_Line11
#define      OV7725_VSYNC_EXTI_IRQ                    EXTI15_10_IRQn
#define      OV7725_VSYNC_EXTI_INT_FUNCTION           EXTI15_10_IRQHandler
#define FIFO_OE_H()     OV7725_OE_GPIO_PORT->BSRR = OV7725_OE_GPIO_PIN	  
#define FIFO_OE_L()     OV7725_OE_GPIO_PORT->BRR  = OV7725_OE_GPIO_PIN
#define FIFO_WRST_H()   OV7725_WRST_GPIO_PORT->BSRR = OV7725_WRST_GPIO_PIN
#define FIFO_WRST_L()   OV7725_WRST_GPIO_PORT->BRR  = OV7725_WRST_GPIO_PIN
#define FIFO_RRST_H()   OV7725_RRST_GPIO_PORT->BSRR = OV7725_RRST_GPIO_PIN
#define FIFO_RRST_L()   OV7725_RRST_GPIO_PORT->BRR  = OV7725_RRST_GPIO_PIN
#define FIFO_RCLK_H()   OV7725_RCLK_GPIO_PORT->BSRR = OV7725_RCLK_GPIO_PIN	  
#define FIFO_RCLK_L()   OV7725_RCLK_GPIO_PORT->BRR  = OV7725_RCLK_GPIO_PIN
#define FIFO_WE_H()     OV7725_WE_GPIO_PORT->BSRR = OV7725_WE_GPIO_PIN
#define FIFO_WE_L()     OV7725_WE_GPIO_PORT->BRR  = OV7725_WE_GPIO_PIN
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
void DebugMon_Handler(void)
{
}
u32 TimingDelay=0;
void Delayus(__IO u32 xus)
{
	u32 i=0;
	for(i=0;i<xus;i++){
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}
void Delayms(__IO u32 xms)
{
	u32 i=1000*xms;
	Delayus(i);
}
void EXTI15_10_IRQHandler(void)
{
    if ( EXTI_GetITStatus(OV7725_VSYNC_EXTI_LINE) != RESET ) 	//检查EXTI_Line10线路上的中断请求是否发送到了NVIC 
    {
        if( Ov7725_vsync == 0 )
        {
            FIFO_WRST_L(); 	                      //拉低使FIFO写(数据from摄像头)指针复位
            FIFO_WE_H();	                        //拉高使FIFO写允许
            Ov7725_vsync = 1;
            FIFO_WE_H();                          //使FIFO写允许
            FIFO_WRST_H();                        //允许使FIFO写(数据from摄像头)指针运动
        }
        else if(Ov7725_vsync == 1)
        {
            FIFO_WE_L();                          //拉低使FIFO写暂停
            Ov7725_vsync = 2;
					  //printf("Receve NVIC Requests \r\n");
        }        
        EXTI_ClearITPendingBit(OV7725_VSYNC_EXTI_LINE);		    //清除EXTI_Line0线路挂起标志位        
    }    
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
