/*
 * MPU6050_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef MPU6050_DRIVER_H_
#define MPU6050_DRIVER_H_
#include "logdata.h"
#include "I2C_Driver.h"

#define MPU6050_ADDR   0x68U

void MPU6050_Init(void);
uint8_t MPU6050_ReadByte(uint8_t reg);
void MPU6050_WriteByte(uint8_t reg, uint8_t data);
void MPU6050_Readbytes(uint8_t reg, uint8_t *data, uint8_t len);
uint8_t MPU6050_WhoIAm(void);
void MPU6050_ReadAccel(int16_t *ax, int16_t *ay, int16_t *az, logdata_t *logg);
void MPU6050_ReadGyro(int16_t *gx, int16_t *gy, int16_t *gz, logdata_t *logg);


#endif /* MPU6050_DRIVER_H_ */
