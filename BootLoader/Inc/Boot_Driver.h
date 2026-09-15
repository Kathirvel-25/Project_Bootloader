/*
 * Boot_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef BOOT_DRIVER_H_
#define BOOT_DRIVER_H_
#include "Nucleo_Driver.h"

#define APP_ADDR     0x08010000UL
#define APP_ENDADDR  0x08080000UL


int ApplicationisValid(void);
void JumptoApplication(void);


#endif /* BOOT_DRIVER_H_ */
