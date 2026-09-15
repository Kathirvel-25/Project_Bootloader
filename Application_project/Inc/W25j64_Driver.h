/*
 * W25j64_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef W25J64_DRIVER_H_
#define W25J64_DRIVER_H_
#include "SPI_Driver.h"
#include "stdint.h"


void W25_ChipErase(void);
void W25_Read(uint32_t addr, uint8_t *data, uint8_t len);
void W25_PageProgram(uint32_t addr, const uint8_t *data, uint8_t len);
void W25_SectorErase(uint32_t addr);
void IS_Bussy();
void Read_Id(uint8_t *id);



#endif /* W25J64_DRIVER_H_ */
