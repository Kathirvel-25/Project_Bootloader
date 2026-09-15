/*
 * Flash_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#include "Flash_Driver.h"


static int FLASH_WAIT(void)
{
	uint32_t timeout = FLASH_TIMEOUT_COUNT;

	while(FLASH->SR & (1 << 16))
	{
		if(--timeout == 0) return FLASH_TIMEOUT;
	}

	if(FLASH->SR & ((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8))) return FLASH_ERROR;

	return FLASH_OK;

}

void FLASH_LOCK(void)
{
	FLASH->CR |= (1 << 31);

}


void FLASH_UNLOCK(void)
{
	if(FLASH->CR & (1 << 31))
	{
		FLASH->KEYR = 0x45670123;
		FLASH->KEYR = 0xCDEF89AB;
	}
}


int FLASH_Program_Word(uint32_t addr, uint32_t data)
{
	int result;

	if(addr & 3U) return FLASH_INVALID;

	result = FLASH_WAIT();

	if(result != FLASH_OK) return result;

	FLASH->CR &= ~(3U << 8);
	FLASH->CR |= (2U << 8);

	FLASH->CR |= (1 << 0);

	*(volatile uint32_t *)addr = data;

	result = FLASH_WAIT();

	FLASH->CR &= ~(1U << 0);

	if(result != FLASH_OK) return result;

	if(*(volatile uint32_t *)addr != data) return FLASH_ERROR;

	return FLASH_OK;
}


int FLASH_Write(uint32_t addr, uint8_t *data, uint32_t len)
{

	uint32_t word;
	uint32_t i;

	while(len >= 4U)
	{
		word = ((uint32_t)data[0]) |
				((uint32_t)data[1] << 8)  |
				((uint32_t)data[2] << 16) |
				((uint32_t)data[3] << 24);

		if(FLASH_Program_Word(addr, word) != FLASH_OK) return FLASH_ERROR;

		addr += 4U;
		data += 4U;
		len -= 4U;
	}

	if(len > 0U)
	{
		 word = 0xFFFFFFFFUL;

		 for(i = 0; i < len; i++)
		 {
			 word &= ~(0xFFUL << (i * 8U));
			 word |= ((uint32_t)data[i] << (i * 8U));
		 }

		 if(FLASH_Program_Word(addr, word) != FLASH_OK) return FLASH_ERROR;
	}

	return FLASH_OK;
}


int FLASH_SECTOR_Erase(uint32_t sector)
{

	int result;

	if(sector > 7U) return FLASH_INVALID;

	result = FLASH_WAIT();

	if(result != FLASH_OK) return result;

	FLASH->CR &= ~(0xFUL << 3);

	FLASH->CR &= ~(3U << 8);
	FLASH->CR |= (2U << 8);

	FLASH->CR |= (1 << 1);

	FLASH->CR |= ((sector & 0xFUL) << 3);

	FLASH->CR |= (1 << 16);

	result = FLASH_WAIT();

	FLASH->CR &= ~(1 << 1);
	FLASH->CR &= ~(0xFUL << 3);

	return result;
}


