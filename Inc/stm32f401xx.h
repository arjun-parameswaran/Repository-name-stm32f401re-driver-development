/*
 * stm32f401xx.h
 *
 *  Created on: Sep 22, 2026
 *      Author: ARJUN
 */

#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_

#include <stddef.h>
#include <stdint.h>

/*Macro for volatile keyword*/
#define __vo volatile

/*-------------------------Memory Base Address------------------------*/
#define FLASH_BASEADDR							0x08000000U
#define ROM_BASEADDR							0x1FFF0000U
#define SRAM_BASEADDR							0x20000000U
/*--------------------Peripheral Base Address (Reference Manual PgNo:51) -------------------------*/


#define PERIPH_BASEADDR							0x40000000U
#define APB1_PERIPH_BASEADDR					PERIPH_BASEADDR
#define APB2_PERIPH_BASEADDR					0x40010000U
#define AHB1_PERIPH_BASEADDR					0x40020000U
#define AHB2_PERIPH_BASEADDR					0x50000000U

/* --------------------AHB1 Peripheral Base Addresses---------------------------*/
#define GPIOA_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x1000U)
#define GPIOH_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x1C00U)
/*Other Peripherals*/
#define CRC_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x3000U)
#define RCC_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x3800U)
#define FLASH_IF_BASEADDR 					(AHB1_PERIPH_BASEADDR + 0x3C00U)
#define DMA1_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x6000U)
#define DMA2_BASEADDR						(AHB1_PERIPH_BASEADDR + 0x6400U)

/*----------------------------APB1 PERIPHERAL Base Address-------------------------------------*/

/*TIMERS*/
#define TIM2_BASEADDR					(APB1_PERIPH_BASEADDR + 0x0000U)
#define TIM3_BASEADDR					(APB1_PERIPH_BASEADDR + 0x0400U)
#define TIM4_BASEADDR					(APB1_PERIPH_BASEADDR + 0x0800U)
#define TIM5_BASEADDR					(APB1_PERIPH_BASEADDR + 0x0C00U)

/*SPI*/
#define SPI2_BASEADDR					(APB1_PERIPH_BASEADDR + 0x3800U)
#define SPI3_BASEADDR					(APB1_PERIPH_BASEADDR + 0x3C00U)

/*USART*/
#define USART2_BASEADDR					(APB1_PERIPH_BASEADDR + 0x4400U)

/*I2C*/
#define I2C1_BASEADDR					(APB1_PERIPH_BASEADDR + 0x5400U)
#define I2C2_BASEADDR					(APB1_PERIPH_BASEADDR + 0x5800U)
#define I2C3_BASEADDR					(APB1_PERIPH_BASEADDR + 0x5C00U)


/*----------------------------APB2 PERIPHERAL Base Address-------------------------------------*/

#define TIM1_BASEADDR					(APB2_PERIPH_BASEADDR + 0x0000U)
#define TIM9_BASEADDR					(APB2_PERIPH_BASEADDR + 0x4000U)
#define TIM10_BASEADDR					(APB2_PERIPH_BASEADDR + 0x4400U)
#define TIM11_BASEADDR					(APB2_PERIPH_BASEADDR + 0x4800U)
/*USART*/
#define USART1_BASEADDR					(APB2_PERIPH_BASEADDR + 0x1000U)
#define USART6_BASEADDR					(APB2_PERIPH_BASEADDR + 0x1400U)

/*SPI*/
#define SPI1_BASEADDR					(APB2_PERIPH_BASEADDR + 0x3000U)
#define SPI4_BASEADDR					(APB2_PERIPH_BASEADDR + 0x3400U)

/*System Configuration*/
#define SYSCFG_BASEADDR					(APB2_PERIPH_BASEADDR + 0x3800U)
#define EXTI_BASEADDR					(APB2_PERIPH_BASEADDR + 0x3C00U)



/*---------------------------Some Generic Macros------------------------*/
#define ENABLE 			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_SET		SET
#define FLAG_RESET		RESET

/* --------------------Peripheral register definition structure for GPIO ---------------------*/
typedef struct
{
	__vo uint32_t MODER;					//offset:
	__vo uint32_t OTYPER;					//offset:
	__vo uint32_t OSPEEDR;					//offset:
	__vo uint32_t PUPDR;					//offset:
	__vo uint32_t IDR;						//offset:
	__vo uint32_t ODR;						//offset:
	__vo uint32_t BSRR;						//offset:
	__vo uint32_t LCKR;						//offset:
	__vo uint32_t AFR[2];					//offset:
}GPIO_RegDef_t;

#define GPIOA 			((GPIO_RegDef_t *)(GPIOA_BASEADDR))
#define GPIOB 			((GPIO_RegDef_t *)(GPIOB_BASEADDR))
#define GPIOC 			((GPIO_RegDef_t *)(GPIOC_BASEADDR))
#define GPIOD 			((GPIO_RegDef_t *)(GPIOD_BASEADDR))
#define GPIOE 			((GPIO_RegDef_t *)(GPIOE_BASEADDR))
#define GPIOH 			((GPIO_RegDef_t *)(GPIOH_BASEADDR))

/*Peripheral Register Definition Structure for RCC*/
typedef struct
{
	__vo uint32_t CR;					//offset: 0x00
	__vo uint32_t PLLCFGR;				//offset: 0x04
	__vo uint32_t CFGR;					//offset: 0x08
	__vo uint32_t CIR;					//offset: 0x0C

	__vo uint32_t AHB1RSTR;				//offset: 0x10
	__vo uint32_t AHB2RSTR;				//offset: 0x14

	uint32_t RESERVED_0[2];		//offset: 0x18, 0x1C -Reserved

	__vo uint32_t APB1RSTR;				//offset: 0x20
	__vo uint32_t APB2RSTR;				//offset: 0x24

	uint32_t RESERVED_1[2];		//offset: 0x28 ,0x2C - Reserved

	__vo uint32_t AHB1ENR;				//offset: 0x30
	__vo uint32_t AHB2ENR;				//offset: 0x34

	uint32_t RESERVED_2[2];		//offset: 0x38, 0x3C - Reserved

	__vo uint32_t APB1ENR;				//offset: 0x40
	__vo uint32_t APB2ENR;				//offset: 0x44

	 uint32_t RESERVED_3[2];		//offset: 0x48, 0x4C - Reserved

	__vo uint32_t AHB1LPENR;			//offset: 0x50
	__vo uint32_t AHB2LPENR;			//offset: 0x54

	uint32_t RESERVED_4[2];		//offset: 0x58, 0x5C - Reserved

	__vo uint32_t APB1LPENR;			//offset: 0x60
	__vo uint32_t APB2LPENR;			//offset: 0x64

	uint32_t RESERVED_5[2];			//offset: 0x68, 0x6C -Reserved

	__vo uint32_t BDCR;					//offset: 0x70
	__vo uint32_t CSR;					//offset: 0x74

	 uint32_t RESERVED_6[2];		//offset: 0x78, 0x7C

	__vo uint32_t SSCGR;				//offset: 0x80
	__vo uint32_t PLLI2SCFGR;			//offset: 0x84

	uint32_t RESERVED_7;			//offset: 0x88	- Reserved

	__vo uint32_t DCKCFGR;				//offset: 0x8C
	//why no volatile for RESERVED?
}RCC_RegDef_t;


#define RCC	((RCC_RegDef_t *) (RCC_BASEADDR))

/* GPIO Clock Enable */
#define GPIOA_PCLK_EN()   (RCC->AHB1ENR |= (1U << 0))
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR |= (1U << 1))
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR |= (1U << 2))
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR |= (1U << 3))
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR |= (1U << 4))
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR |= (1U << 7))

/* GPIO Clock Disable */
#define GPIOA_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 0))
#define GPIOB_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 1))
#define GPIOC_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 2))
#define GPIOD_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 3))
#define GPIOE_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 4))
#define GPIOH_PCLK_DI()   (RCC->AHB1ENR &= ~(1U << 7))




/*------------------------ Peripheral register definition structure for SPI------------------ */
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;

}SPI_RegDef_t;


#define SPI1		((SPI_RegDef_t *) (SPI1_BASEADDR))
#define SPI2		((SPI_RegDef_t *) (SPI2_BASEADDR))
#define SPI3		((SPI_RegDef_t *) (SPI3_BASEADDR))
#define SPI4		((SPI_RegDef_t *) (SPI4_BASEADDR))


/*SPI Enable functions*/
#define SPI1_PCLK_EN()			RCC->APB2ENR |= (1 << 12)
#define SPI2_PCLK_EN()			RCC->APB1ENR |= (1 << 14)
#define SPI3_PCLK_EN()			RCC->APB1ENR |= (1 << 15)
#define SPI4_PCLK_EN()			RCC->APB2ENR |= (1 << 13)
/*SPI Disable Function*/
#define SPI1_PCLK_DI()			RCC->APB2ENR &= ~(1 << 12)
#define SPI2_PCLK_DI()			RCC->APB1ENR &= ~(1 << 14)
#define SPI3_PCLK_DI()			RCC->APB1ENR &= ~(1 << 15)
#define SPI4_PCLK_DI()			RCC->APB2ENR &= ~(1 << 13)

/*SPI CR1 Bit Positions*/
#define SPI_CR1_CPHA				0
#define SPI_CR1_CPOL				1
#define SPI_CR1_MSTR				2
#define SPI_CR1_BR					3
#define SPI_CR1_SPE					6
#define SPI_CR1_LSBFIRST			7
#define SPI_CR1_SSI					8
#define SPI_CR1_SSM					9
#define SPI_CR1_RXONLY				10
#define SPI_CR1_DFF					11
#define SPI_CR1_CRCNEXT				12
#define SPI_CR1_CRCEN				13
#define SPI_CR1_BIDIOE				14
#define SPI_CR1_BIDIMODE			15

/*SPI SR Bit Positions*/
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_OVR			5
#define SPI_SR_BSY			6
#define SPI_SR_FRE			7
/* Peripheral Register Definition Structure for I2C
*/


#endif /* INC_STM32F401XX_H_ */
