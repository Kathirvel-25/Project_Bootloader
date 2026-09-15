/*
 * UART_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */


#include "UART_Driver.h"


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

 	 UART2->CR1 |= ((1 << 3) | (1 << 13));
}


void UART_Tarnsmit_Char(char c)
{

	while(!(UART2->SR & (1 << 7)));
	UART2->DR = (uint8_t)c;

}


void UART_Transmit_String(char *str)
{

	while(*str)
	{
		UART_Tarnsmit_Char(*str++);
	}
}


void UART_Transmit_Hex(uint8_t data)
{
    const char hex[] = "0123456789ABCDEF";

    UART_Tarnsmit_Char(hex[(data >> 4) & 0x0F]);
    UART_Tarnsmit_Char(hex[data & 0x0F]);
}

void UART_Transmit_Int(int32_t value)
{
    char buff[12];
    int i = 0;

    if(value == 0)
    {
        UART_Tarnsmit_Char('0');
        return;
    }

    if(value < 0)
    {
        UART_Tarnsmit_Char('-');
        value = -value;
    }

    while(value > 0)
    {
        buff[i++] = (value % 10) + '0';
        value /= 10;
    }

    while(i > 0)
    {
        UART_Tarnsmit_Char(buff[--i]);
    }
}


void UART_Transmit_Float(float value)
{
    int32_t integer;
    uint32_t decimal;

    if(value < 0)
    {
        UART_Tarnsmit_Char('-');
        value = -value;
    }

    integer = (int32_t)value;

    decimal = (uint32_t)((value - integer) * 100.0f);

    UART_Transmit_Int(integer);

    UART_Tarnsmit_Char('.');

    UART_Tarnsmit_Char((decimal / 10) + '0');
    UART_Tarnsmit_Char((decimal % 10) + '0');
}
