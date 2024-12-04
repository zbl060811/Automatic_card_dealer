//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-0101
//  ����޸�   : 
//  ��������   : STM32L151AC8T6���������OLED��ʾ��ʵ��
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  3.3v��Դ
//              D0   PA0��SCL��
//              D1   PA1��SDA��
//              RES  PA2��SPIģ��ĳ�IICģ����Ҫ�Ӵ����ţ�IICģ���û�����ԣ�
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018
//All rights reserved
//******************************************************************************/

#include "main.h"
#include "stm32l1xx_hal.h"
#include "oled.h"
#include "bmp.h"
void SystemClock_Config(void);
int main()
{
	u8 t=' ';
	HAL_Init();
	SystemClock_Config();
	OLED_Init();
	LED_ON;
	while(1)
	{
		OLED_ShowPicture(0,0,128,32,BMP1,1);
		OLED_Refresh();
		HAL_Delay(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);//��
		OLED_ShowChinese(18,0,1,16,1);//��
		OLED_ShowChinese(36,0,2,16,1);//԰
		OLED_ShowChinese(54,0,3,16,1);//��
		OLED_ShowChinese(72,0,4,16,1);//��
		OLED_ShowChinese(90,0,5,16,1);//��
		OLED_ShowChinese(108,0,6,16,1);//��
		OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
		OLED_Refresh();
		HAL_Delay(500);
		OLED_Clear();
		OLED_ShowString(20,0,"2014/05/01",16,1);
		OLED_ShowString(0,16,"ASCII:",16,1);  
		OLED_ShowString(63,16,"CODE:",16,1);
		OLED_ShowChar(48,16,t,16,1);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,16,t,3,16,1);
		OLED_Refresh();
		HAL_Delay(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1); //16*16 ��
		OLED_ShowChinese(16,0,0,24,1);//24*24 ��
		OLED_ShowChinese(40,0,0,32,1);//32*32 ��
		OLED_Refresh();
	  HAL_Delay(500);
  	OLED_Clear();
		OLED_ShowString(0,7,"A",8,1);
		OLED_ShowString(18,4,"B",12,1);
		OLED_ShowString(36,2,"C",16,1);
		OLED_ShowString(56,0,"D",24,1);
	  OLED_Refresh();
		HAL_Delay(500);
		OLED_ScrollDisplay(11,4,1);
	}
}

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
