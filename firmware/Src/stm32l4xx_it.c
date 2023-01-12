/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include "config.h"
	  
extern LED_TypeDef LED_R;
extern LED_TypeDef LED_G;

extern volatile Packet_TypeDef RX;
extern volatile Packet_TypeDef TX;
extern volatile uint32_t Global_Error;

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  //HAL_SYSTICK_Callback();
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	uint8_t temp;

	/*  HUART_PC   */

	if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET))
	{
		/* Get the received byte */
		temp = (USART1->RDR);

		LED_R_FLASH();	//flash red led

		switch (TX.Packet_Stat) //Last packet status
		{
		default:
		case IDLE:
			if (temp == 0xFF)
				TX.Packet_Stat = HEADER0;
			break;

		case HEADER0:
			if (temp == 0xFF)
				TX.Packet_Stat = HEADER1;
			else
				TX.Packet_Stat = IDLE;
			break;

		case HEADER1:
			if (temp == 0xFD)
			{
				/* 2.0 */
				TX.Packet_Stat = HEADER2;
				TX.Type = 2;
			}
			else
			{
				/* 1.0 */
				TX.Packet_Stat = ID_10;
				TX.Type = 1;
				TX.CheckSum = temp;	// start checksum calculation
			}
			break;

		case ID_10:
			TX.Packet_Stat = LEN_H;
			TX.Packet_Size = temp;
			TX.CheckSum += temp;
			break;

		case HEADER2:
			TX.Packet_Stat = RESERVED;
			break;

		case RESERVED:
			TX.Packet_Stat = ID;
			break;

		case ID:
			TX.Packet_Stat = LEN_L;
			TX.Packet_Size = temp;
			break;

		case LEN_L:
			TX.Packet_Stat = LEN_H;
			TX.Packet_Size += ((uint16_t) temp * 0x100);
			break;

		case LEN_H:
			TX.Packet_Stat = PAYLOAD;
			if ((TX.Type == 1) && (temp == 0x92))
			{
				/* 1.0 Bulk Read, set number of expected return packets */
				RX.Bulk_Read_Num = (TX.Packet_Size - 3) / 3;
			}
			else if ((TX.Type == 1) && (temp == 0x12))
			{
				/* BEAR Bulk Stat */
				RX.BEAR_Bulk_Header = 2;
			}

		case PAYLOAD:
			TX.CheckSum += temp;
			TX.Packet_Size--;

			/* getting number of expected return packets for BEAR */
			if (RX.BEAR_Bulk_Header != 0)
			{
				RX.BEAR_Bulk_Header--;
				if (RX.BEAR_Bulk_Header == 0)
				{
					/* # of motor */
					RX.Bulk_Read_Num = temp;
				}
			}

			if (TX.Packet_Size == 0)
			{
				/* Done */
				if ((TX.Type == 1) && (TX.CheckSum != 0xFF))
				{
					Global_Error |= ERR_CHECKSUM;
				}
				//TODO: 2.0 checksum

				TX.Idle_CT = 0;			// reset idle counter
				TX.Packet_Stat = IDLE;	// status back to idle
			}
			break;
		}
		return;
	}

	if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_NE) != RESET))
	{
		// UART noise error

		//Global_Error|=ERR_UART;
		//TX.Packet_Stat=IDLE;
		__HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_NE);
		return;
	}
	
	
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
	
  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	uint8_t temp;
	
	
	/*  HUART_MOTOR  */

	if ((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET))
	{
		/* Get the received byte */
		temp = (USART2->RDR);

		LED_R_FLASH();	//flash red led

		switch (RX.Packet_Stat) //Last packet stat
		{
		default:
		case IDLE:
			if (temp == 0xFF)
				RX.Packet_Stat = HEADER0;
			break;

		case HEADER0:
			if (temp == 0xFF)
				RX.Packet_Stat = HEADER1;
			else
				RX.Packet_Stat = IDLE;
			break;

		case HEADER1:
			if (temp == 0xFD)
			{
				/* 2.0 */
				RX.Packet_Stat = HEADER2;
				RX.Type = 2;
			}
			else
			{
				/* 1.0 */
				RX.Packet_Stat = ID_10;
				RX.Type = 1;
				RX.CheckSum = temp;	// start checksum calculation
			}
			break;

		case ID_10:
			RX.Packet_Stat = LEN_H;
			RX.Packet_Size = temp;
			RX.CheckSum += temp;
			break;

		case HEADER2:
			RX.Packet_Stat = RESERVED;
			break;

		case RESERVED:
			RX.Packet_Stat = ID;
			break;

		case ID:
			RX.Packet_Stat = LEN_L;
			RX.Packet_Size = temp;
			break;

		case LEN_L:
			RX.Packet_Stat = LEN_H;
			RX.Packet_Size += ((uint16_t) temp * 0x100);
			break;

		case LEN_H:
			RX.Packet_Stat = PAYLOAD;
		case PAYLOAD:
			RX.CheckSum += temp;
			RX.Packet_Size--;
			if (RX.Packet_Size == 0)
			{
				/* Done with one packet */
				if (RX.Bulk_Read_Num <= 1)
				{
					/* Done with all return packets */
					/* Send back to PC immediately */
					DCD_ON();			// pulse ---> DCD_OFF()
					RX.Idle_CT = 0;		// reset idle counter
				}
				else
					RX.Bulk_Read_Num--;

				if ((RX.Type == 1) && (RX.CheckSum != 0xFF))
				{
					Global_Error |= ERR_CHECKSUM;
				}
				//TODO: 2.0 checksum

				RX.Packet_Stat = IDLE;	// status back to idle
				DCD_OFF();
			}
			break;
		}

		return;
	}

	if ((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_NE) != RESET))
	{
		// UART noise error

		//Global_Error|=ERR_UART;
		//TX.Packet_Stat=IDLE;
		__HAL_UART_CLEAR_FLAG(&huart2, UART_FLAG_NE);
		return;
	}
	
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
