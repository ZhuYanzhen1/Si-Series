#include"sram.h"
void SRAM_Config(void)
{  	
	/* 初始化函数 */
	FSMC_NORSRAMInitTypeDef        FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTiming;
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5
	                            | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 
								| GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;					
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7 | GPIO_Pin_8
	                            | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 
								| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;						
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
	                            | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 
								| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
    GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 
	                            | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10; 
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	//SRAM初始化
	
/* ------------------------------------------------------------------------------ */
/* ------------ FSMC Config ----------------------------------------------------- */
/* ------------------------------------------------------------------------------ */
	/* 设置读写时序，给FSMC_NORSRAMInitStructure调用 */
	/* 地址建立时间，1个HCLK周期, 1/36M = 27ns */
	FSMC_NORSRAMTiming.FSMC_AddressSetupTime = 0x00;

	/* 地址保持时间，1个HCLK周期 */
	FSMC_NORSRAMTiming.FSMC_AddressHoldTime = 0x00;

	/* 数据建立时间，63个HCLK周期 4/72 = 55ns */
	FSMC_NORSRAMTiming.FSMC_DataSetupTime = 0x03;

	/* 数据保持时间，1个HCLK周期 */
	FSMC_NORSRAMTiming.FSMC_DataLatency = 0x00;

	/* 总线恢复时间设置 */
	FSMC_NORSRAMTiming.FSMC_BusTurnAroundDuration = 0x00;
	
	/* 时钟分频设置 */
	FSMC_NORSRAMTiming.FSMC_CLKDivision = 0x00;

	/* 设置模式，如果在地址/数据不复用时，ABCD模式都区别不大 */
	FSMC_NORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_A;

	/* 设置FSMC_NORSRAMInitStructure的数据 */
	/* FSMC有四个存储块（bank），我们使用第一个（bank1） */
	/* 同时我们使用的是bank里面的第 3个RAM区 */
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;

	/* 这里我们使用SRAM模式 */
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;

	/* 使用的数据宽度为16位 */
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	
	// FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;	 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;

	/* 设置写使能打开 */
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;

	/* 选择拓展模式使能，即设置读和写用相同的时序 */
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	
	/* 设置地址和数据复用使能不打开 */
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	
	/* 设置读写时序 */
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTiming;
	
	/* 设置写时序 */
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTiming;

	/* 打开FSMC的时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	 
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	/*!< Enable FSMC Bank1_SRAM Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
}

/****************************************************************************
* Function Name  : SRAM_WriteBuffer
* Description    : 向SRAM里面写入一定长度的数据
* Input          : writeBuf：写入缓存
*                * writeAddr：写入起始地址
*                * length：写入数据长度
* Output         : None
* Return         : None
****************************************************************************/

void SRAM_WriteBuffer(uint16_t *writeBuf, uint32_t writeAddr, uint32_t length)
{
  while(length--) /*!< while there is data to write */
  {
    /*!< Transfer data to the memory */
    *(uint16_t *) (Bank1_SRAM3_ADDR + writeAddr) = *writeBuf++;
    
    /*  十六位长度的是地址+2 */  
    writeAddr += 2;
  }   
}

/****************************************************************************
* Function Name  : SRAM_ReadBuffer
* Description    : 读取SRAM数据
* Input          : readBuff：读取缓存
*                * readAddr：读取起始地址
*                * length：读取数据长度
* Output         : None
* Return         : None
****************************************************************************/

void SRAM_ReadBuffer(uint16_t* readBuff, uint32_t readAddr, uint32_t length)
{
  while(length--) /*!< while there is data to read */
  {
    /*!< Read a half-word from the memory */
    *readBuff++ = *(__IO uint16_t*) (Bank1_SRAM3_ADDR + readAddr);

    /*  十六位长度的是地址+2 */  
    readAddr += 2;
  }  
}
