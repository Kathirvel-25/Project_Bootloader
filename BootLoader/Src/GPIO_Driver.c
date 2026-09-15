/*
 * GPIO_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#include "GPIO_Driver.h"

#define LED_PIN 5U
#define Button_Pin 13U


void GPIO_Init(void)
{
	RCC->AHB1ENR |= ((1 << 0) | (1 << 2));

	GPIOA->MODER &= ~(3U << (LED_PIN * 2U));
	GPIOA->MODER |= (1U << (LED_PIN * 2U));

	GPIOC->MODER &= ~(3U << (Button_Pin * 2U));

	GPIOC->PUPDR &= ~(3U << (Button_Pin * 2U));
	GPIOC->PUPDR |= (1U << (Button_Pin * 2U));

}


void Toogle_LED(void)
{
	GPIOA->ODR ^= (1U << LED_PIN);
}


int Button_pressed(void)
{
	return ((GPIOC->IDR & (1U << Button_Pin)) == 0);
}
