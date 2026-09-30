/*
 * stm32f401xx_spi_driver.c
 *
 *  Created on: Sep 29, 2026
 *      Author: ARJUN
 */

/* SPI Init and De-init
 */

#include "stm32f401xx.h"
#include "Stm32f401xx_spi_driver.h"

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	//Enable
	if (EnorDi == ENABLE)
	{
		if(pSPIx ==  SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx ==  SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx ==  SPI3)
		{
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4)
		{

		}
	}
	else //Disable
	{
		if(pSPIx ==  SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSPIx ==  SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if(pSPIx ==  SPI3)
		{
			SPI3_PCLK_DI();
		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_DI();
		}
	}
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	uint32_t tempReg = 0;
	//device mode master or slave
	tempReg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR; //Configuring the Device Mode.
	//full-duplex or half-duplex mode
	if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//need to be cleared from Reference Manual
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tempReg |= (1 << SPI_CR1_BIDIMODE);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		tempReg &= ~(1 << SPI_CR1_BIDIOE);		//0 - Read Only Mode
		tempReg |= (1 << SPI_CR1_BIDIMODE);
	}
	//Clock Speed
	tempReg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//CPOL
	tempReg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//CPHA
	tempReg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	//DFF
	tempReg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	//SSM
	tempReg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	if(pSPIHandle->SPIConfig.SPI_SSM == SPI_SSM_EN)
	{
			tempReg |= (1 << SPI_CR1_SSI);
	}

	pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	//Writing into tempReg
	pSPIHandle->pSPIx->CR1 = tempReg;
	//Enabling SPI
	pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SPE);
}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{


}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if (pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	else
	{
		return FLAG_RESET;
	}
}


void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		// Wait until the TXE Flag is SET
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// Checking if Data Frame Format is 8-Bit or 16-Bit
		if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16-bit transfer
			pSPIx->DR = *((uint16_t *)pTxBuffer);
			Len--;
			Len--;
			pTxBuffer += 2; // Fixed pointer arithmetic
		}
		else
		{
			// 8-bit transfer
			pSPIx->DR = *pTxBuffer; // Fixed missing dereference
			Len--;
			pTxBuffer++;
		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		// Wait until the RXNE Flag is SET (Fixed comment)
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

		// Checking if Data Frame Format is 8-Bit or 16-Bit
		if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16-bit receive (Fixed read direction and pointer casting)
			*((uint16_t *)pRxBuffer) = pSPIx->DR;
			Len--;
			Len--;
			pRxBuffer += 2;
		}
		else
		{
			// 8-bit receive (Fixed read direction and missing dereference)
			*pRxBuffer = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}
