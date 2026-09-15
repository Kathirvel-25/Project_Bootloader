/*
 * CRC32_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#include "CRC32_Driver.h"


uint32_t crc32(const uint8_t *data, uint32_t len)
{
	uint32_t crc = 0xFFFFFFFFUL;

	while(len--)
	{
		crc ^= *data++;
		for(int i = 0; i < 8; i++)
		{
			if(crc & 1U) crc = (crc >> 1U)^0xEDB88320UL;
			else crc >>= 1U;
		}
	}

	return ~crc;
}
