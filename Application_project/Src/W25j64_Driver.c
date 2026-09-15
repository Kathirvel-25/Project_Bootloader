/*
 * W25j64_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */
#include "W25j64_Driver.h"

static uint8_t W25_ReadStatus(void)
{
	uint8_t cmd = 0x05;
	uint8_t status;

	CS_LOW();

	SPI_Transmit(&cmd, 1);
	SPI_receive(&status, 1);

	CS_HIGH();

	return status;
}

static void W25_WriteEnable(void)
{
	 uint8_t cmd = 0x06;

     CS_LOW();
     SPI_Transmit(&cmd, 1);
     CS_HIGH();
}


void IS_Bussy()
{
    while(W25_ReadStatus() & 0x01);
}


void W25_ChipErase(void)
{

	uint8_t cmd = 0xC7;

	W25_WriteEnable();

	CS_LOW();

	SPI_Transmit(&cmd, 1);

	CS_HIGH();

	IS_Bussy();

}

void W25_Read(uint32_t addr, uint8_t *data, uint8_t len)
{
	uint8_t cmd = 0x03;
	uint8_t address[3];

	address[0] = (addr >> 16);
	address[1] = (addr >> 8);
	address[2] = addr;

	CS_LOW();

	SPI_Transmit(&cmd, 1);
	SPI_Transmit(address, 3);
	SPI_receive(data, len);

	CS_HIGH();
}

void W25_PageProgram(uint32_t addr, const uint8_t *data, uint8_t len)
{
     uint8_t cmd = 0x02;
     uint8_t address[3];

 	address[0] = (addr >> 16);
 	address[1] = (addr >> 8);
 	address[2] = addr;

 	W25_WriteEnable();

 	CS_LOW();

 	SPI_Transmit(&cmd, 1);
 	SPI_Transmit(address, 3);

 	SPI_Transmit(data, len);

 	CS_HIGH();

 	IS_Bussy();
}

void W25_SectorErase(uint32_t addr)
{

	uint8_t cmd = 0x20;
	uint8_t address[3];

	address[0] = (addr >> 16);
	address[1] = (addr >> 8);
	address[2] = addr;

	W25_WriteEnable();

	CS_LOW();

	SPI_Transmit(&cmd, 1);
	SPI_Transmit(address, 3);

	CS_HIGH();

	IS_Bussy();
}

void Read_Id(uint8_t *id)
{
      uint8_t cmd = 0x9F;

      CS_LOW();

      SPI_Transmit(&cmd, 1);

      SPI_receive(id, 3);

      CS_HIGH();
}
