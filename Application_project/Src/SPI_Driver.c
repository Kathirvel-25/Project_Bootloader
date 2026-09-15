/*
 * SPI_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */


#include "SPI_Driver.h"


void SPI_Init(void)
{
    RCC->AHB1ENR |= (1 << 1);
    RCC->APB1ENR |= (1 << 14);

    GPIOB->MODER &= ~(3U << (SCK * 2U));
    GPIOB->MODER &= ~(3U << (MISO * 2U));
    GPIOB->MODER &= ~(3U << (MOSI * 2U));
    GPIOB->MODER &= ~(3U << (CS * 2U));

    GPIOB->MODER |= (2U << (MISO * 2U));
    GPIOB->MODER |= (2U << (MOSI * 2U));
    GPIOB->MODER |= (2U << (SCK * 2U));
    GPIOB->MODER |= (1U << (CS * 2U));

    GPIOB->AFRH &= ~(0xFUL << 20);
    GPIOB->AFRH &= ~(0xFUL << 24);
    GPIOB->AFRH &= ~(0xFUL << 28);

    GPIOB->AFRH |= (5UL << 20);
    GPIOB->AFRH |= (5UL << 24);
    GPIOB->AFRH |= (5UL << 28);

    GPIOB->PUPDR &= ~(3U << (CS * 2U));
    GPIOB->PUPDR |= (1U << (CS * 2U));

    GPIOB->OTYPER &= ~(1U << CS);

    SPI2->CR1 = 0;

    SPI2->CR1 &= ~(1U << 15);

    SPI2->CR1 &= ~(1U << 11);

    SPI2->CR1 &= ~(1U << 10);

    SPI2->CR1 |= (1 << 9);
    SPI2->CR1 |= (1 << 8);

    SPI2->CR1 &= ~(1U << 7);

    SPI2->CR1 &= ~(1U << 1);
    SPI2->CR1 &= ~(1U << 0);

    SPI2->CR1 |= (1U << 2);
    SPI2->CR1 |= (1U << 6);
}

void CS_LOW(void)
{
	GPIOB->BSRR = (1U << (CS + 16U));
}


void CS_HIGH(void)
{
	GPIOB->BSRR = (1U << CS);
}

uint8_t SPI_Transfer(uint8_t data)
{
	while(!(SPI2->SR & (1U << 1)));
	   SPI2->DR = data;

	 while(!(SPI2->SR & (1U << 0)));
	  return (uint8_t)SPI2->DR;
}

void SPI_Transmit(const uint8_t *data, uint8_t size)
{

	while(size--)
	{
		 (void)SPI_Transfer(*data++);
	}

	while(SPI2->SR & (1 << 7));
}


void SPI_receive(uint8_t *data, uint8_t size)
{

	while(size--)
	{
        *data++ = SPI_Transfer(0xFF);
	}
	while(SPI2->SR & (1 << 7));
}
