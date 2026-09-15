/*
 * MPU6050_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */


#include "MPU6050_Driver.h"


void MPU6050_WriteByte(uint8_t reg, uint8_t data)
{

	uint8_t buff[2];

	buff[0] = reg;
	buff[1] = data;

	I2C_Transmit(MPU6050_ADDR, buff, 2);
}


void MPU6050_Init(void)
{
      MPU6050_WriteByte(0x6BU, 0x00);
      MPU6050_WriteByte(0x19U, 0x00);
      MPU6050_WriteByte(0x1AU, 0x00);
      MPU6050_WriteByte(0x1BU, 0x00);
      MPU6050_WriteByte(0x1CU, 0x00);

}

uint8_t MPU6050_ReadByte(uint8_t reg)
{

	uint8_t data;

	I2C_Transmit(MPU6050_ADDR, &reg, 1);

	I2C_Receive(MPU6050_ADDR, &data, 1);

	return data;
}

void MPU6050_Readbytes(uint8_t reg, uint8_t *data, uint8_t len)
{
   I2C_Transmit(MPU6050_ADDR, &reg, 1);

   I2C_Receive(MPU6050_ADDR, data, len);
}

uint8_t MPU6050_WhoIAm(void)
{

	return MPU6050_ReadByte(0x75U);
}

void MPU6050_ReadAccel(int16_t *ax, int16_t *ay, int16_t *az, logdata_t *logg)
{
	uint8_t data[6];

    MPU6050_Readbytes(0x3BU, data, 6);

    *ax = (int16_t)(((uint16_t)data[0] << 8) | data[1]);
    *ay = (int16_t)(((uint16_t)data[2] << 8) | data[3]);
    *az = (int16_t)(((uint16_t)data[4] << 8) | data[5]);


    logg->accel_x = (float)(*ax) / 16384.0f;
    logg->accel_y = (float)(*ay) / 16384.0f;
    logg->accel_z = (float)(*az) / 16384.0f;
}


void MPU6050_ReadGyro(int16_t *gx, int16_t *gy, int16_t *gz, logdata_t *logg)
{
	uint8_t data[6];

    MPU6050_Readbytes(0x43U, data, 6);

    *gx = (int16_t)(((uint16_t)data[0] << 8) | data[1]);
    *gy = (int16_t)(((uint16_t)data[2] << 8) | data[3]);
    *gz = (int16_t)(((uint16_t)data[4] << 8) | data[5]);

    logg->gyro_x = (float)(*gx) / 131.0f;
    logg->gyro_y = (float)(*gy) / 131.0f;
    logg->gyro_z = (float)(*gz) / 131.0f;
}
