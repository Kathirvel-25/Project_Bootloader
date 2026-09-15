/*
 * UART_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */


#include "UART2_Driver.h"

#define Tx  2U
#define Rx  3U

void UART_Init(void)
{
    RCC->APB1ENR |= (1 << 17);
    RCC->AHB1ENR |= (1 << 0);

    GPIOA->MODER &= ~(3U << (Tx * 2U));
    GPIOA->MODER &= ~(3U << (Rx * 2U));

    GPIOA->MODER |= (2U << (Tx * 2U));
    GPIOA->MODER |= (2U << (Rx * 2U));

    GPIOA->AFRL &= ~(0xFUL << (Tx * 4U));
    GPIOA->AFRL &= ~(0xFUL << (Rx * 4U));

    GPIOA->AFRL |= (7U << (Tx * 4U));
    GPIOA->AFRL |= (7U << (Rx * 4U));

    UART2->CR1 =0;
    UART2->CR1 = 0;

	UART2->CR1 &= ~(1U << 15);
	UART2->CR1 &= ~(1U << 12);
	UART2->CR2 &= ~(3U << 12);

	UART2->BRR = (8 << 4)|11;

	UART2->CR1 |= ((1 << 3) | (1 << 2) | (1 << 13));
}

void UART_Transmit_Char(char c)
{
	while(!(UART2->SR & (1U << 7)));
	UART2->DR = (uint8_t)c;
}

void UART_Transmit_u32(uint32_t val)
{
	uint8_t buff[11];
	int index = 0;

	if(val == 0)
	{
		UART_Transmit_Char('0');
		return;
	}

	while(val > 0)
	{
		buff[index++] = '0' + (val % 10);
		val /= 10;
	}

	while(index > 0)
	{
		UART_Transmit_Char(buff[--index]);
	}
}

void UART_Transmit_string(char *str)
{
	while(*str)
	{
		UART_Transmit_Char(*str++);
	}

}

char UART_Receive_char(void)
{
	while(!(UART2->SR & (1 << 5)));

	return (char)UART2->DR;
}


int UART_Receive_Timeout(uint8_t *data, uint32_t timeout)
{
	while(timeout--)
	{
		if(UART2->SR & (1 << 5))
		{
			*data = (uint8_t)(UART2->DR & 0xFFUL);
			 return 1;
		}
	}

	return 0;
}
