/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "memorymap.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	//1. inicijalizacija
	uint32_t *pAhb1Enr = (uint32_t*)RCC_AHB1ENR;
	*pAhb1Enr |= RCC_AHB1ENR_GPIOGEN;
	*pAhb1Enr |= RCC_AHB1ENR_GPIOAEN;

	// set pg14 to output
	uint32_t * gModer = (uint32_t*)GPIOG_MODER;
	*gModer &= ~(1<<29); // bit 29 to 0
	*gModer |= (1<<28);  // bit 28 to 1

	// set PA0 to input
	uint32_t * aModer = (uint32_t*)GPIOA_MODER;
	// &= ~(3 << 0)
	*aModer &= ~(1<<0); // bit 0 to 0
	*aModer &= ~(1<<1); // bit 1 to 0

	uint32_t *gOdr = (uint32_t*)GPIOG_ODR;
	uint32_t *aIdr = (uint32_t*)GPIOA_IDR;

	//2. neskoncna zanka
    /* Loop forever */
	for (;;) {
		int32_t buttonState = *aIdr & USER_BUTTON_PIN;

		if(buttonState != 0)
			*gOdr |= RED_LED_PIN;
		else
			*gOdr &= ~(RED_LED_PIN);
	}
}
