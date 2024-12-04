#ifndef __OLED_H__
#define __OLED_H__


#include "gpio.h"


//-----------------OLED端口定义---------------- 

// PB8--->SCL	PB9-->SDA

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)		//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)		//SDA
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define OLED_CMD	 1		// 写命令
#define OLED_DATA 	 0		// 写数据







#endif
