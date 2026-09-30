/*
 * stm32f401xx_gpio_driver.c
 *
 *  Created on: Sep 23, 2026
 *      Author: ARJUN
 */
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
	}

}

void GPIO_Init(GPIO_Handle_t *pGPIO_Handle)
{
	uint32_t temp = 0;
	//1. Enabling GPIO Peripheral CLock
	GPIO_PeriClockControl(pGPIO_Handle->pGPIOx, ENABLE);
	//2. GPIO Mode
	if(pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//storing the configuration inside a temporary variable, x2 because each pin contains 2 bits.
		temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
		//clearing the MODER
		pGPIO_Handle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
		//now were writing the actual mode into MODER Address.
		pGPIO_Handle->pGPIOx->MODER |= temp;
		//resetting/clearing variable 'temp' for next use


	}
	else //Interrupt Code
	{
		//Interrupt Mode - Code to be written.
	}
	//3.SPEED
	temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIO_Handle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIO_Handle->pGPIOx->OSPEEDR |= temp;

	//4.PUPD : Configuring Pull-Up / Pull-Down

	temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PuPdControl <<(2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
	//Clearing the Bits.
	pGPIO_Handle->pGPIOx->PUPDR &= ~(0x03 << 2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	//writing to the Register
	pGPIO_Handle->pGPIOx->PUPDR |= temp;
	temp = 0; //Clearing

	//5. TYPE

	temp = (pGPIO_Handle->GPIO_PinConfig.GPIO_PinOPtype << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	//clearing the type
	pGPIO_Handle->pGPIOx->OTYPER &= ~(0x1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_Handle->pGPIOx->OTYPER |= temp;
	temp = 0; //Clearing

	//ALT Function
	if(pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t index, value;
		//to get the index H or L
		index = (pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNumber) / 8;

		value = (pGPIO_Handle -> GPIO_PinConfig.GPIO_PinNumber) % 8;

		//clearing the bits of the required position
		pGPIO_Handle->pGPIOx->AFR[index] &= ~((0xF) << (4 * value));
		//writing to the register
		pGPIO_Handle->pGPIOx->AFR[index] |= (pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * value));

	}
}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{

	}
}

/*********************************************************************
 * @function  				- GPIO_ReadFromInputPin
 *
 * @brief   	       	  	- This function is used to read the value in GPIO pin.
 *
 * @parameters[in]        	- pGPIOx: base address of the GPIO peripheral(GPIOA, GPIOB, .....GPIOH)
 * @parameters[in]          - PinNumber
 * @return      	      	- uint7_t value (returns the value inside that pin.
 *
 * @Note            	  	- refer macros for
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t) (((pGPIOx->IDR) >> PinNumber) & 0x00000001);
	return value;
}

/*********************************************************************
 * @function  				- GPIO_ReadFromInputPin
 *
 * @brief   	       	  	- This function is used to read the value in GPIO pin.
 *
 * @parameters[in]        	- pGPIOx: base address of the GPIO peripheral(GPIOA, GPIOB, .....GPIOH)
 * @parameters[in]          - PinNumber
 * @return      	      	- uint7_t value (returns the value inside that pin.)
 *
 * @Note            	  	- refer macros for
 */


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t) (pGPIOx->IDR);
	return value;
}


/*********************************************************************
 * @function  				- GPIO_ReadFromInputPin
 *
 * @brief   	       	  	- This function is used to read the value in GPIO pin.
 *
 * @parameters[in]        	- pGPIOx: base address of the GPIO peripheral(GPIOA, GPIOB, .....GPIOH)
 * @parameters[in]          - PinNumber
 * @return      	      	- uint7_t value (returns the value inside that pin.
 *
 * @Note            	  	- refer macros for
 */

void GPIO_WritToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
	if(value == GPIO_SET_PIN)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

/*********************************************************************
 * @function  				- GPIO_ReadFromInputPin
 *
 * @brief   	       	  	- This function is used to read the value in GPIO pin.
 *
 * @parameters[in]        	- pGPIOx: base address of the GPIO peripheral(GPIOA, GPIOB, .....GPIOH)
 * @parameters[in]          - PinNumber
 * @return      	      	- uint7_t value (returns the value inside that pin.
 *
 * @Note            	  	- refer macros for
 */


void GPIO_WritToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}
/*********************************************************************
 * @function  				- GPIO_ToggleOutputPin
 *
 * @brief   	       	  	- This function is used to Toggle the a specific output pin.
 *
 * @parameters[in]        	- pGPIOx: base address of the GPIO peripheral(GPIOA, GPIOB, .....GPIOH)
 * @parameters[in]          - PinNumber
 * @return      	      	- N
 *
 * @Note            	  	- refer macros for
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx -> ODR ^= (1 << PinNumber);
}

