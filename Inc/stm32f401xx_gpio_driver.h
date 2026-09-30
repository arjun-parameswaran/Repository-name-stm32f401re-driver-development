/*
 * stm32f401xx_gpio_driver.h
 *
 *  Created on: Sep 23, 2026
 *      Author: ARJUN
 */

#ifndef INC_STM32F401XX_GPIO_DRIVER_H_
#define INC_STM32F401XX_GPIO_DRIVER_H_

#include "stm32f401xx.h" //step1: adding MCU specific header.

/*GPIO Configuration Structure*/ //step 2: adding GPIO configurations structure
typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PuPdControl;
	uint8_t GPIO_PinOPtype;
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;

/*GPIO Handle Structure*/
typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;


#define GPIO_SET_PIN 	1U
#define GPIO_CLR_PIN	0U

/*GPIO Pin Numbers*/
#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_PIN_8		8
#define GPIO_PIN_9		9
#define GPIO_PIN_10		10
#define GPIO_PIN_11		11
#define GPIO_PIN_12		12
#define GPIO_PIN_13		13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15


/*GPIO Modes*/
#define GPIO_MODE_IN				0
#define GPIO_MODE_OUT				1
#define GPIO_MODE_ALTFN				2
#define GPIO_MODE_ANALOG			3

/*GPIO Output Type*/
#define GPIO_OP_PP					0
#define GPIO_OP_OD					1
/*GPIO Speed*/
#define GPIO_SPEED_LOW				0
#define GPIO_SPEED_MEDIUM			1
#define GPIO_SPEED_FAST				2
#define GPIO_SPEED_HIGH				3
/*GPIO PUPD*/
#define GPIO_NO_PUPD				0
#define GPIO_PU						1
#define GPIO_PD						2
/*GPIO */
#define GPIO_AF_0					0
#define GPIO_AF_1					1
#define GPIO_AF_2					2
#define GPIO_AF_3					3
#define GPIO_AF_4					4
#define GPIO_AF_5					5
#define GPIO_AF_6					6
#define GPIO_AF_7					7
#define GPIO_AF_8					8
#define GPIO_AF_9					9
#define GPIO_AF_10					10
#define GPIO_AF_11					11
#define GPIO_AF_12					12
#define GPIO_AF_13					13
#define GPIO_AF_14					14
#define GPIO_AF_15					15

/*GPIO API Function Prototypes*/
void GPIO_PeriClockControl(GPIO_RegDef_t *GPIOx, uint8_t EnorDi); //Completed
void GPIO_Init(GPIO_Handle_t *GPIOHandle); //Completed
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);   //Completed

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToOutputPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *GPIOx, uint16_t value);

void GPIO_ToggleOutputPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber);




#endif /* INC_STM32F401XX_GPIO_DRIVER_H_ */
