/*
 * Flash_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_
#include "Nucleo_Driver.h"


#define FLASH_OK       0
#define FLASH_ERROR   -1
#define FLASH_TIMEOUT -2
#define FLASH_INVALID -3
#define FLASH_TIMEOUT_COUNT  10000000UL


void FLASH_LOCK(void);
void FLASH_UNLOCK(void);
int FLASH_Program_Word(uint32_t addr, uint32_t data);
int FLASH_Write(uint32_t addr, uint8_t *data, uint32_t len);
int FLASH_SECTOR_Erase(uint32_t sector);


#endif /* FLASH_DRIVER_H_ */
