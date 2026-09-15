/*
 * GPS_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */


#include "GPS_Driver.h"


#define nmeaBuffSize  256

char nmeaBuff[nmeaBuffSize];
uint8_t nmeaIdx  = 0;



static void Get_RequiredData(const char *nmeaBuff, logdata_t *logg)
{
	if (strncmp(nmeaBuff, "$GPRMC", 6) != 0) return;

	char Buff[nmeaBuffSize];

	strncpy(Buff, nmeaBuff, nmeaBuffSize-1);
	Buff[nmeaBuffSize-1] = '\0';

	char *token;
	char *save;

	int field = 0;
	token = strtok_r(Buff,",", &save);

	while(token != NULL)
	{
		field++;

		switch(field)
		{
		   case 4:   //lat
			   strncpy(logg->latitude, token, sizeof(logg->latitude) - 1);
			   logg->latitude[sizeof(logg->latitude) - 1] = '\0';
			   break;

		   case 5:  //ns
			   strncpy(logg->ns, token, sizeof(logg->ns) - 1);
			   logg->ns[sizeof(logg->ns) - 1] = '\0';
			   break;

		   case 6:   //lon
			   strncpy(logg->longitute, token, sizeof(logg->longitute) - 1);
			   logg->longitute[sizeof(logg->longitute) - 1] = '\0';
			   break;

		   case 7:  //ew
			   strncpy(logg->ew, token, sizeof(logg->ew) - 1);
			   logg->ew[sizeof(logg->ew) - 1] = '\0';
			   break;

		}
		 token = strtok_r(NULL, ",", &save);
	}
}


void GPS_UART_Init(void)
{
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB2ENR |= (1U << 4U);

	GPIOA->MODER &= ~(3U << (Tx_GPS * 2U));
	GPIOA->MODER &= ~(3U << (Rx_GPS * 2U));

	GPIOA->MODER |= (2U << (Tx_GPS * 2U));
	GPIOA->MODER |= (2U << (Rx_GPS * 2U));

	GPIOA->AFRH &= ~(0xFUL << 4);
	GPIOA->AFRH &= ~(0xFUL << 8);

	GPIOA->AFRH |= (7U << 4);
	GPIOA->AFRH |= (7U << 8);

	UART1->CR1 = 0;
	UART1->CR2 = 0;


	UART1->CR1 &= ~(1U << 15);
	UART1->CR1 &= ~(1U << 12);
	UART1->CR2 &= ~(3U << 12);

	UART1->BRR = (104 << 4)|3;

	UART1->CR1 |= ((1 << 2) | (1 << 13));
}


uint8_t GPS_UART_Receive()
{

    while(!(UART1->SR & (1 << 5))) {}
     return UART1->DR & 0xFFUL;
}

char* ProcessData(uint8_t data)
{
	if(data == '$') nmeaIdx = 0;

	if(nmeaIdx < nmeaBuffSize - 1) nmeaBuff[nmeaIdx++] = data;

	if(data == '\n')
	{
		nmeaBuff[nmeaIdx] = '\0';
		nmeaIdx = 0;
		Get_RequiredData(nmeaBuff, &data_log);

		return nmeaBuff;
	}
	return NULL;
}
