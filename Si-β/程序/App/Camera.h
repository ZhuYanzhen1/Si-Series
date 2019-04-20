#ifndef _CAMERA_H_
#define _CAMERA_H_
#define Camera_Init_Fail 1
#define Camera_Init_Success 0
uint8_t Camera_Init(unsigned char Light_Mode,unsigned char Effect);
		/**
		* Light_Mode,参数范围[0~5]：       Effect，参数范围[0~6]:
				@arg 0：自动												@arg 0:正常
				@arg 1：晴天												@arg 1:黑白
				@arg 2：多云												@arg 2:偏蓝
				@arg 3：办公室											@arg 3:复古
				@arg 4：家里												@arg 4:偏红
				@arg 5：夜晚												@arg 5:偏绿
																						@arg 6:反相
    */
void FIFO_PREPARE(void);
uint16_t READ_FIFO_PIXEL(void);
void OV7725_Window_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height,uint8_t QVGA_VGA);
#endif
