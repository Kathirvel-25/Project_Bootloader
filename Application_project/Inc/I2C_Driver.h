/*
 * I2C_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_
#include "Nucleo_Driver.h"

#define SCL 6U
#define SDA 7U


void I2C_Init(void);
void I2C_Transmit(uint8_t addr, uint8_t *data, uint8_t len);
void I2C_Receive(uint8_t addr, uint8_t *data, uint8_t len);

#endif /* I2C_DRIVER_H_ */
