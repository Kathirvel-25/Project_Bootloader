/*
 * I2C_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */


#include "I2C_Driver.h"



void I2C_Init(void)
{
	RCC->AHB1ENR |= (1 << 1);
	RCC->APB1ENR |= (1 << 21);

	GPIOB->MODER &= ~(3U << (SCL * 2U));
	GPIOB->MODER &= ~(3U << (SDA * 2U));

	GPIOB->MODER |= (2U << (SCL * 2U));
	GPIOB->MODER |= (2U << (SDA * 2U));

	GPIOB->PUPDR &= ~(3U << (SCL * 2U));
	GPIOB->PUPDR &= ~(3U << (SDA * 2U));

	GPIOB->PUPDR |= (1U << (SCL * 2U));
	GPIOB->PUPDR |= (1U << (SDA * 2U));

	GPIOB->OTYPER &= ~(1U << SCL);
	GPIOB->OTYPER &= ~(1U << SDA);

	GPIOB->OTYPER |= (1U << SCL);
	GPIOB->OTYPER |= (1U << SDA);

	GPIOB->AFRL &= ~(0xFUL << (SCL * 4U));
	GPIOB->AFRL &= ~(0xFUL << (SDA * 4U));

	GPIOB->AFRL |= (4U << (SCL * 4U));
	GPIOB->AFRL |= (4U << (SDA * 4U));

	I2C1->CR1 &= ~(1U << 0);

	I2C1->CR2 = 16;

	I2C1->CCR = 80;

	I2C1->TRISE = 17;

	I2C1->CR1 |= (1 << 0);
}


void I2C_Transmit(uint8_t addr, uint8_t *data, uint8_t len)
{
   I2C1->CR1 |= (1 << 8);

   while(!(I2C1->SR1 & (1 << 0)));

   I2C1->DR = (addr << 1)|0;

   while(!(I2C1->SR1 & (1 << 1)));

   volatile uint32_t temp;
   temp = I2C1->SR1;
   temp = I2C1->SR2;
   (void)temp;

   while(len--)
   {
	   while(!(I2C1->SR1 & (1 << 7)));
	   I2C1->DR = *data++;
   }

   while(!(I2C1->SR1 & (1 << 2)));

   I2C1->CR1 |= (1 << 9);
}


void I2C_Receive(uint8_t addr, uint8_t *data, uint8_t len)
{
	I2C1->CR1 |= (1 << 8);

	while(!(I2C1->SR1 & (1 << 0)));

	I2C1->DR = (addr << 1)|1;

	while(!(I2C1->SR1 & (1 << 1)));

	uint8_t remain = len;

	if(len == 1)
	{
		I2C1->CR1 &= ~(1 << 10);

		volatile uint32_t temp;
		temp = I2C1->SR1;
		temp = I2C1->SR2;
		(void)temp;

		I2C1->CR1 |= (1 << 9);

		while(!(I2C1->SR1 & (1 << 6)));

		*data = I2C1->DR;

		I2C1->CR1 |= (1 << 10);

		return;
	}

	if(len == 2)
	{

		I2C1->CR1 &= ~(1 << 10);
		I2C1->CR1 |=  (1U << 11);

		volatile uint32_t temp;
		temp = I2C1->SR1;
		temp = I2C1->SR2;
		(void)temp;

		while(!(I2C1->SR1 & (1u << 2)));

		I2C1->CR1 |= (1 << 9);

		data[0] = I2C1->DR;
		data[1] = I2C1->DR;


		I2C1->CR1 &= ~(1U << 11);
		I2C1->CR1 |= (1 << 10);
		return;
	}

		I2C1->CR1 |= (1 << 10);

		volatile uint32_t temp;
		temp = I2C1->SR1;
		temp = I2C1->SR2;
		(void)temp;

		while(remain > 3)
		{
			while(!(I2C1->SR1 & (1 << 6)));
			*data++ = I2C1->DR;
			remain--;
		}

		while(!(I2C1->SR1 & (1 << 2)));

		I2C1->CR1 &= ~(1 << 10);

		*data++ = I2C1->DR;

		I2C1->CR1 |= (1 << 9);


		while (!(I2C1->SR1 & (1U << 6)));
		*data++ = I2C1->DR;

		while (!(I2C1->SR1 & (1U << 6)));
		*data = I2C1->DR;

		I2C1->CR1 |= (1 << 10);
}
