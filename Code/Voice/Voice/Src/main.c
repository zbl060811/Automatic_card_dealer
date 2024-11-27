	/* USER CODE BEGIN Header */
	/**
	  ******************************************************************************
	  * @file           : main.c
	  * @brief          : Main program body
	  ******************************************************************************
	  * @attention
	  *
	  * Copyright (c) 2024 STMicroelectronics.
	  * All rights reserved.
	  *
	  * This software is licensed under terms that can be found in the LICENSE file
	  * in the root directory of this software component.
	  * If no LICENSE file comes with this software, it is provided AS-IS.
	  *
	  ******************************************************************************
	  */
	/* USER CODE END Header */
	/* Includes ------------------------------------------------------------------*/
	#include "main.h"
	#include "adc.h"
	#include "tim.h"
	#include "usart.h"
	#include "gpio.h"

	/* Private includes ----------------------------------------------------------*/
	/* USER CODE BEGIN Includes */
	#include <stdio.h>
	/* USER CODE END Includes */

	/* Private typedef -----------------------------------------------------------*/
	/* USER CODE BEGIN PTD */

	/* USER CODE END PTD */

	/* Private define ------------------------------------------------------------*/
	/* USER CODE BEGIN PD */
	/* USER CODE END PD */

	/* Private macro -------------------------------------------------------------*/
	/* USER CODE BEGIN PM */

	/* USER CODE END PM */

	/* Private variables ---------------------------------------------------------*/

	/* USER CODE BEGIN PV */

	/* USER CODE END PV */

	/* Private function prototypes -----------------------------------------------*/
	void SystemClock_Config(void);
	/* USER CODE BEGIN PFP */

	/* USER CODE END PFP */

	/* Private user code ---------------------------------------------------------*/
	/* USER CODE BEGIN 0 */
	int fputc(int ch, FILE * f)
	{
		HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,1000);
		return ch;
	}

	uint16_t  ADC_Value;	// 未滤波前的ADC采样值
	uint16_t adc_value;		// 低通滤波后的adc采样值

	float ADC_v;			// 未滤波前的ADC电压
	float adc_v;			// 低通滤波后的adc电压
	float percentage;		// 电池电量百分比
	unsigned int lowV( unsigned int com )	
	{
		static unsigned int iLastData;    //上一次值
		unsigned int iData;               //本次计算值
		float dPower = 0.4;               //滤波系数
		iData = ( com * dPower ) + ( 1 - dPower ) * iLastData; //计算
		iLastData = iData;                                     //存贮本次数据
		return iData;                                         //返回数据
	}

	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
		if(htim->Instance == TIM2)
		{
			if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1) , HAL_ADC_STATE_REG_EOC))	// 转换完成
			{
				ADC_Value = HAL_ADC_GetValue(&hadc1);	// 获取ADC采样值
				adc_value = lowV(ADC_Value);
				
				ADC_v = 3.3 * ADC_Value / 4096.0;
				adc_v = 3.3 * adc_value / 4096.0;
				
				ADC_v = ADC_v * (10.0 + 20.0) / 10.0;
				adc_v = adc_v * (10.0 + 20.0) / 10.0;
				
				percentage = (adc_v - 6.4) / (8.4 - 6.4)*100;		// 电池容量百分比
				
				if(percentage > 100)		// 限幅
					percentage = 100;
				if(percentage < 0)
					percentage = 0;
				
				printf("ADC_Sample_value:%f,%.2f%%\r\n",adc_v,percentage);
				HAL_ADC_Start_IT(&hadc1);		//  中断回调函数中或主程序中要重新开启ADC中断，否则ADC不能连续工作
			}
		}
	}

	/* USER CODE END 0 */

	/**
	  * @brief  The application entry point.
	  * @retval int
	  */
	int main(void)
	{
	  /* USER CODE BEGIN 1 */

	  /* USER CODE END 1 */

	  /* MCU Configuration--------------------------------------------------------*/

	  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	  HAL_Init();

	  /* USER CODE BEGIN Init */

	  /* USER CODE END Init */

	  /* Configure the system clock */
	  SystemClock_Config();

	  /* USER CODE BEGIN SysInit */

	  /* USER CODE END SysInit */

	  /* Initialize all configured peripherals */
	  MX_GPIO_Init();
	  MX_ADC1_Init();
	  MX_USART1_UART_Init();
	  MX_TIM2_Init();
	  /* USER CODE BEGIN 2 */
	  HAL_ADCEx_Calibration_Start(&hadc1);			// ADC校准函数，校准ADC1
	  HAL_ADC_Start_IT(&hadc1);
	  HAL_TIM_Base_Start_IT(&htim2);
	  /* USER CODE END 2 */

	  /* Infinite loop */
	  /* USER CODE BEGIN WHILE */
	  while (1)
	  {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		  
			
	  }
	  /* USER CODE END 3 */
	}

	/**
	  * @brief System Clock Configuration
	  * @retval None
	  */
	void SystemClock_Config(void)
	{
	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
		Error_Handler();
	  }

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	  {
		Error_Handler();
	  }
	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	  {
		Error_Handler();
	  }
	}

	/* USER CODE BEGIN 4 */

	/* USER CODE END 4 */

	/**
	  * @brief  This function is executed in case of error occurrence.
	  * @retval None
	  */
	void Error_Handler(void)
	{
	  /* USER CODE BEGIN Error_Handler_Debug */
	  /* User can add his own implementation to report the HAL error return state */
	  __disable_irq();
	  while (1)
	  {
	  }
	  /* USER CODE END Error_Handler_Debug */
	}

	#ifdef  USE_FULL_ASSERT
	/**
	  * @brief  Reports the name of the source file and the source line number
	  *         where the assert_param error has occurred.
	  * @param  file: pointer to the source file name
	  * @param  line: assert_param error line source number
	  * @retval None
	  */
	void assert_failed(uint8_t *file, uint32_t line)
	{
	  /* USER CODE BEGIN 6 */
	  /* User can add his own implementation to report the file name and line number,
		 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	  /* USER CODE END 6 */
	}
	#endif /* USE_FULL_ASSERT */
