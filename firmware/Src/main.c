/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "config.h"
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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/



LED_TypeDef LED_R;
LED_TypeDef LED_G;

volatile Packet_TypeDef RX;
volatile Packet_TypeDef TX;

volatile uint32_t Global_Error = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void LED_Routine();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
	
	/*Initialize UART*/
	
	HAL_UART_DeInit(&HUART_PC);
	HAL_UART_DeInit(&HUART_MOTOR);
	
	/* Change baudrate based on dip switch position */
	if (BAUD_SW)
	{
		LED_R.Pattern=2;
		HUART_PC.Init.BaudRate = 8000000;
		HUART_MOTOR.Init.BaudRate = 8000000;
	}
	else
	{
		LED_R.Pattern=3;
		HUART_PC.Init.BaudRate = 3000000;
		HUART_MOTOR.Init.BaudRate = 3000000;
	}
	
	LED_R.Cycles=1;
	
	/* UART1 from PC */
	HAL_UART_Init(&HUART_PC);
	/* UART2 from motors */
	HAL_UART_Init(&HUART_MOTOR);
	
	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	SET_BIT(USART_PC->CR3, USART_CR3_EIE);
	/* Enable the UART Parity Error interrupt and Data Register Not Empty interrupt */
	SET_BIT(USART_PC->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	
	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	SET_BIT(USART_MOTOR->CR3, USART_CR3_EIE);
	/* Enable the UART Parity Error interrupt and Data Register Not Empty interrupt */
	SET_BIT(USART_MOTOR->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	
	
	LED_G_ON();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		/*Watchdog*/
		//HAL_IWDG_Refresh(&hiwdg);
		
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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 3000000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_8;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 3000000;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_8;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DCD_GPIO_Port, DCD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_G_Pin|LED_R_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA5 PA6 PA7
                           PA8 PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DCD_Pin */
  GPIO_InitStruct.Pin = DCD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DCD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SW_Pin */
  GPIO_InitStruct.Pin = SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_G_Pin LED_R_Pin */
  GPIO_InitStruct.Pin = LED_G_Pin|LED_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PH3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/**
 * @brief Turn on specific LED
 *
 * @param LED pointer to LED type define
 */
inline static void LED_ON(LED_TypeDef *LED)
{
	if (LED == (&LED_G))
		LED_G_ON();
	else
		LED_R_ON();
}

/**
 * @brief Turn off specific LED
 *
 * @param LED pointer to LED type define
 */
inline static void LED_OFF(LED_TypeDef *LED)
{
	if (LED == (&LED_G))
		LED_G_OFF();
	else
		LED_R_OFF();
}

/**
 * @brief LED routine to handle LED flash patterns.
 *
 * @param LED pointer to LED type define
 */
void LED_Routine(LED_TypeDef *LED)
{

	if (LED->Pattern)
	{
		/* has pattern */

		if (Pattern_State[LED->Pattern - 1][LED->Pattern_Step])
			LED->CT = 1;	//LED_ON(LED);
//		else
//			LED_OFF(LED);

		LED->Pattern_CT++;

		if (LED->Pattern_CT
				> Pattern_Delay[LED->Pattern - 1][LED->Pattern_Step])
		{
			/* Next step */
			LED->Pattern_CT = 0;

			LED->Pattern_Step++;
			if (LED->Pattern_Step >= Pattern_Length[LED->Pattern - 1])
			{
				/*over the length limit*/
				LED->Pattern_Step = 0;
				if (LED->Cycles)
					LED->Cycles--;
				if (LED->Cycles == 0)
				{
					/*done pattern cycles*/
					LED->Pattern = 0;
				}
			}
		}

	}

	if (LED->CT)
	{
		LED_ON(LED);
		LED->CT--;
	}
	else
		LED_OFF(LED);

}

/**
 * @brief routine called at systick, 1kHz
 *
 */
void HAL_SYSTICK_Callback(void)
{

	/* if not idle -> count up */
	if (RX.Packet_Stat != IDLE)
		RX.Idle_CT++;
	else
		RX.Idle_CT = 0;

	if (RX.Idle_CT > RX_NON_IDLE_LIMIT)
	{
		//RX timeout
		Global_Error |= ERR_PACKET_TIMEOUT;
		RX.Packet_Stat = IDLE;
	}

	/* if not idle -> count up */
	if (TX.Packet_Stat != IDLE)
		TX.Idle_CT++;
	else
		TX.Idle_CT = 0;
	if (TX.Idle_CT > TX_NON_IDLE_LIMIT)
	{
		//TX timeout
		Global_Error |= ERR_PACKET_TIMEOUT;
		TX.Packet_Stat = IDLE;
	}

	/* Error handling */
	if (Global_Error & ERR_UART)
	{
		LED_G.Pattern = 3;
		LED_G.Cycles = 5;
		Global_Error &= (~ERR_UART);
	}
	else if (Global_Error & ERR_CHECKSUM)
	{
		LED_G.Pattern = 2;
		LED_G.Cycles = 5;
		Global_Error &= (~ERR_CHECKSUM);
	}
	else if (Global_Error & ERR_PACKET_TIMEOUT)
	{
		LED_G.Pattern = 1;
		LED_G.Cycles = 5;
		Global_Error &= (~ERR_PACKET_TIMEOUT);
	}

	/* Green LED normally always on */
	if (LED_G.Cycles == 0)
		LED_G_FLASH();

	LED_Routine(&LED_R);
	LED_Routine(&LED_G);
}

/**
 * @brief UART Error callback
 *
 * @param huart
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

	if (huart == &HUART_MOTOR)
	{
		Global_Error |= ERR_UART;
		//HAL_UART_GetError(huart);

		RX.Packet_Stat = IDLE;
		/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
		SET_BIT(HUART_MOTOR.Instance->CR3, USART_CR3_EIE);
		/* Enable the UART Parity Error interrupt and Data Register Not Empty interrupt */
		SET_BIT(HUART_MOTOR.Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	}
	else if (huart == &HUART_PC)
	{
		Global_Error |= ERR_UART;

		TX.Packet_Stat = IDLE;
		/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
		SET_BIT(HUART_PC.Instance->CR3, USART_CR3_EIE);
		/* Enable the UART Parity Error interrupt and Data Register Not Empty interrupt */
		SET_BIT(HUART_PC.Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);

	}

}





/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while(1) 
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
