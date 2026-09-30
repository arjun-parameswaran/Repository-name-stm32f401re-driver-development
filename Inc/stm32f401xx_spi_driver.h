/*
 * stm32f401xx_spi_driver.h
 *
 *  Created on: Sep 29, 2026
 *      Author: ARJUN
 */

#ifndef INC_STM32F401XX_SPI_DRIVER_H_
#define INC_STM32F401XX_SPI_DRIVER_H_

#include "stm32f401xx.h"

/*1. Configuration Structure for a SPIx Peripheral*/
typedef struct
{
	uint8_t SPI_DeviceMode;			/*Master or Slave*/
	uint8_t SPI_BusConfig;			/*Full-Duplex, Half-Duplex, Simplex, etc*/
	uint8_t SPI_SclkSpeed;			/*Baud rate pre-scaler*/
	uint8_t SPI_DFF;				/*Data frame format (8-Bit / 16-Bit)*/
	uint8_t SPI_CPOL;				/*Clock Polarity*/
	uint8_t SPI_CPHA;				/*Clock Phase*/
	uint8_t SPI_SSM;				/*Software Slave Management*/

} SPI_Config_t;

/*SPI Device Mode*/
#define SPI_DEVICE_MODE_MASTER	1
#define SPI_DEVICE_MODE_SLAVE	0

/*SPI Bus Configuration*/
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3

/*SPI Clock Speed*/
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

/*
 *SPI Data Frame Format
 */
#define SPI_DFF_8BITS					0
#define SPI_DFF_16BITS					1

/*SPI CPOL*/
#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0
/**SPI CPOH*/
#define SPI_CPHA_HIGH	1
#define SPI_CPHA_LOW	0

/*SPI SSM*/
#define SPI_SSM_EN	1
#define SPI_SSM_DI  0


/*SPI FLAGS*/
#define SPI_TXE_FLAG				(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG				(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG				(1 << SPI_SR_BSY)


/*3. Handle Structure for a SPIx peripheral*/
typedef struct
{
	SPI_RegDef_t *pSPIx;			/*for Base Addresses SPI1, SPI2, SPI3, SP4*/
	SPI_Config_t SPIConfig;			/*SPI Configuration settings*/

} SPI_Handle_t;

/*
 * SPI Function Definitions
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);

/*
 * Data Send and Receive (Blocking / Polling based)
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer,uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);





#endif /* INC_STM32F401XX_SPI_DRIVER_H_ */
