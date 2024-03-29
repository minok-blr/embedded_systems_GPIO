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
	*pAhb1Enr |= RCC_AHB1ENR_GPIOFEN;

	// set pg14 to output
	uint32_t * gModer = (uint32_t*)GPIOG_MODER;
	*gModer &= ~(1<<29); // bit 29 to 0
	*gModer |= (1<<28);  // bit 28 to 1

	// set pf0 to output
	uint32_t *fModer = (uint32_t*)GPIOF_MODER;
	//*fModer &= ~(1<<29); // bit 29 to 0
	//*fModer |= (1<<28);  // bit 28 to 1

	//*fModer &= ~(1<<1); // bit 29 to 0
	//*fModer |= (1<<0);  // bit 28 to 1


	for (int var = 0; var < 30; var=var+2) {
		*fModer &= ~(1<<(var + 1)); // set odd bit to 0
		*fModer |= (1<<var);  // set even bit to 1
	}

	// set PA0 to input
	uint32_t * aModer = (uint32_t*)GPIOA_MODER;
	// &= ~(3 << 0)
	*aModer &= ~(1<<0); // bit 0 to 0
	*aModer &= ~(1<<1); // bit 1 to 0

	//uint32_t *gOdr = (uint32_t*)GPIOG_ODR;
	uint32_t *aIdr = (uint32_t*)GPIOA_IDR;

	uint32_t *fOdr = (uint32_t*)GPIOF_ODR;

	// create array of fOdr values
	volatile int arrLED[13];
	arrLED[0] = 0;
	arrLED[1] = 1<<0;
	arrLED[2] = 1<<0 | 1<<1;
	arrLED[3] = 1<<0 | 1<<1 | 1<<2;
	arrLED[4] = 1<<1 | 1<<2 | 1<<3;
	arrLED[5] = 1<<2 | 1<<3 | 1<<4;
	arrLED[6] = 1<<3 | 1<<4 | 1<<5;
	arrLED[7] = 1<<4 | 1<<5 | 1<<6;
	arrLED[8] = 1<<5 | 1<<6 | 1<<7;
	arrLED[9] = 1<<6 | 1<<7 | 1<<8;
	arrLED[10] = 1<<7 | 1<<8 | 1<<9;
	arrLED[11] = 1<<8 | 1<<9;
	arrLED[12] = 1<<9;

	uint8_t pos = 0;
	uint8_t speedSelect = 0;
	uint32_t speed[3];
	speed[0] = 10000;
	speed[1] = 25000;
	speed[2] = 50000;

	uint8_t confidence = 0;
	uint8_t threshold = 2;
	uint8_t buttonSwitch = 0;
	uint8_t prevButtonState = 0;

    /* Loop forever */
	for (;;) {

		// get button state
		int32_t buttonState = *aIdr & USER_BUTTON_PIN;

		if (confidence > threshold && buttonState == 0) {
			buttonSwitch = 1;
		}

		if (buttonState != 0 && prevButtonState != 0) {
			confidence++;
		}
		else {
			confidence = 0;
		}

		if (buttonSwitch == 1) {
			speedSelect++;
			if(speedSelect == 3) speedSelect = 0;
			confidence = 0;
			buttonSwitch = 0;
			prevButtonState = 0;
		}

		prevButtonState = buttonState;

		// change LED speed
//		if(buttonState != 0)
//		{
//			speedSelect++;
//			if(speedSelect == 3) speedSelect = 0;
//		}

		// set output on port F to saved array values
		*fOdr |= arrLED[pos];

		// delay for speed modes
		for (int var = 0; var < speed[speedSelect]; ++var) {}

		// turn off previously lit LED bar and check array positioning
		*fOdr &= ~arrLED[pos];
		pos++;
		if(pos == 13) pos = 0;

/*
		if(buttonState != 0)
		{
			*gOdr |= RED_LED_PIN;
			//*fOdr |= 1;
			//*fOdr |= 1<<1;
				}

		else
		{
			*gOdr &= ~(RED_LED_PIN);
			//*fOdr &= ~1;
			//*fOdr &= ~(1<<1);
				}
*/
	}
}
