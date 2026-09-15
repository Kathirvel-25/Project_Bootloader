/*
 * SPI_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
#include "Nucleo_Driver.h"

#define CS    12U
#define SCK   13U
#define MISO  14U
#define MOSI  15U


void SPI_Init(void);
uint8_t SPI_Transfer(uint8_t data);
void SPI_Transmit(const uint8_t *data, uint8_t size);
void SPI_receive(uint8_t *data, uint8_t size);
void CS_LOW(void);
void CS_HIGH(void);



#endif /* SPI_DRIVER_H_ */
