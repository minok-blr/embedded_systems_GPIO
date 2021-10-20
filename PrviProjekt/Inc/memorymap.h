/*
 * memorymap.h
 *
 *  Created on: Oct 20, 2021
 *      Author: luka.jeraminok
 */

#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (RCC_BASE + 0x30)
#define RCC_AHB1ENR_GPIOGEN (1<<6)
#define RCC_AHB1ENR_GPIOAEN (1<<0)

#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (GPIOA_BASE + 0x00)
#define GPIOA_IDR (GPIOA_BASE + 0x10)

#define GPIOG_BASE 0x40021800
#define GPIOG_MODER (GPIOG_BASE + 0X00)
#define GPIOG_ODR (GPIOG_BASE + 0x14)

#define RED_LED_PIN (1 << 14)
#define USER_BUTTON_PIN (1 << 0)

#endif /* MEMORYMAP_H_ */
