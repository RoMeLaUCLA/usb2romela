/**
 * @file 	config.h
 * @brief 	All configurations and macros related to the project.
 *
 * @author 	Tym Zhu
 */
#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32l4xx_hal.h"

/* Macros for GPIOs */
#define LED_R_ON()			LED_R_GPIO_Port->BSRR=(uint32_t)LED_R_Pin //SET
#define LED_R_OFF()			LED_R_GPIO_Port->BRR=(uint32_t)LED_R_Pin //RESET
#define LED_R_TOGGLE()		LED_R_GPIO_Port->ODR ^= LED_R_Pin //Toggle

#define LED_G_ON()			LED_G_GPIO_Port->BSRR=(uint32_t)LED_G_Pin //SET
#define LED_G_OFF()			LED_G_GPIO_Port->BRR=(uint32_t)LED_G_Pin //RESET
#define LED_G_TOGGLE()		LED_G_GPIO_Port->ODR ^= LED_G_Pin //Toggle

#define DCD_ON()			DCD_GPIO_Port->BSRR=((uint32_t)DCD_Pin)<<16U //SET
#define DCD_OFF()			DCD_GPIO_Port->BSRR=DCD_Pin //RESET

#define BAUD_SW				(((SW_GPIO_Port->IDR & SW_Pin) != 0) ? 1:0)

/* Macros for LED */
#define LED_DELAY			2
#define LED_R_FLASH()		LED_R.CT=LED_DELAY
#define LED_G_FLASH()		LED_G.CT=LED_DELAY

/* HUART definition */
#define HUART_PC			huart1
#define USART_PC			USART1
#define HUART_MOTOR			huart2
#define USART_MOTOR			USART2

/* Error definition */
#define ERR_PACKET_TIMEOUT	0x01
#define ERR_CHECKSUM		0x02
#define ERR_UART			0x04

/* communication non-idle time limit */
#define RX_NON_IDLE_LIMIT	20 //ms
#define TX_NON_IDLE_LIMIT	20 //ms


/** Buffer structure */
typedef struct
{
	uint16_t Pt;
	uint16_t Done;
	uint8_t Buffer[256];
} Buffer_TypeDef;

/** Packet status structure */
typedef enum
{
	IDLE = 0,
	HEADER0,
	HEADER1,
	HEADER2,
	RESERVED,
	ID,
	LEN_L,
	LEN_H,
	PAYLOAD,
	ID_10,

} Packet_Stat_TypeDef;

/** Data packet type define */
typedef struct
{
	Packet_Stat_TypeDef Packet_Stat;
	uint16_t Packet_Size;
	uint8_t CheckSum;
	uint8_t Bulk_Read_Num;
	uint8_t Type;
	uint32_t Idle_CT;
	Buffer_TypeDef Buff;

	uint8_t BEAR_Bulk_Header;

} Packet_TypeDef;

/** LED structure */
typedef struct
{
	uint32_t CT;
	uint8_t Pattern;
	uint8_t Pattern_Step;
	uint32_t Pattern_CT;
	uint8_t Cycles;

} LED_TypeDef;

/* LED flash patterns */
static const uint8_t Pattern_Length[] =
{ 3, 5, 7, 9 };
static const uint32_t Pattern_Delay[4][9] =
{
{ 1, 100, 2000 },
{ 1, 100, 500, 100, 2000 },
{ 1, 100, 500, 100, 500, 100, 2000 },
{ 1, 100, 500, 100, 500, 100, 500, 100, 2000 } };
static const uint8_t Pattern_State[4][9] =
{
{ 0, 1, 0 },
{ 0, 1, 0, 1, 0 },
{ 0, 1, 0, 1, 0, 1, 0 },
{ 0, 1, 0, 1, 0, 1, 0, 1, 0 } };

#endif 
