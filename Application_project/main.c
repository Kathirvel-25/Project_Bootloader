
#include <stdint.h>
#include "GPS_Driver.h"
#include "UART_Driver.h"
#include "W25j64_Driver.h"
#include "MPU6050_Driver.h"
#include "I2C_Driver.h"
#include "SPI_Driver.h"






logdata_t read;


int main(void)
{

	UART_Init();
	GPS_UART_Init();
	SPI_Init();
	I2C_Init();

	MPU6050_Init();

	int16_t gx, gy, gz;
	int16_t ax, ay, az;

	*(volatile uint32_t *)0xE000ED88 |= (0xFUL << 20);

	uint8_t data;

	uint32_t flash_addr = 0x00000000UL;

	W25_ChipErase();

	while(1)
	{
		data = GPS_UART_Receive();
		if(ProcessData(data))
		{

		    MPU6050_ReadGyro(&gx,&gy,&gz, &data_log);
		    MPU6050_ReadAccel(&ax,&ay,&az, &data_log);

			if((flash_addr % 256) + (sizeof(logdata_t)) > 256) flash_addr = (flash_addr/ 256 + 1)*256;

			W25_PageProgram(flash_addr,(uint8_t*)&data_log, sizeof(logdata_t));

			W25_Read(flash_addr, (uint8_t*)&read, sizeof(logdata_t));

			flash_addr += sizeof(data_log);

			UART_Transmit_String(
		        "\r\n"
		        "============================\r\n"
		        "            Writing         \r\n"
		        "============================\r\n"
		    );

			UART_Transmit_String("Latitude: ");
			UART_Transmit_String(data_log.latitude);
			UART_Transmit_String("\r\n");
			UART_Transmit_String("NS: ");
			UART_Transmit_String(data_log.ns);
			UART_Transmit_String("\r\n");
			UART_Transmit_String("Longitude: ");
			UART_Transmit_String(data_log.longitute);
			UART_Transmit_String("\r\n");
			UART_Transmit_String("ew: ");
			UART_Transmit_String(data_log.ew);
			UART_Transmit_String("\r\n");

		    UART_Transmit_String("ACCEL X: ");
		    UART_Transmit_Float(data_log.accel_x);
		    UART_Transmit_String(" g\r\n");

		    UART_Transmit_String("ACCEL Y: ");
		    UART_Transmit_Float(data_log.accel_y);
		    UART_Transmit_String(" g\r\n");

		    UART_Transmit_String("ACCEL Z: ");
		    UART_Transmit_Float(data_log.accel_z);
		    UART_Transmit_String(" g\r\n");


		    UART_Transmit_String("GYRO X: ");
		    UART_Transmit_Float(data_log.gyro_x);
		    UART_Transmit_String(" deg/s\r\n");

		    UART_Transmit_String("GYRO Y: ");
		    UART_Transmit_Float(data_log.gyro_y);
		    UART_Transmit_String(" deg/s\r\n");

		    UART_Transmit_String("GYRO Z: ");
		    UART_Transmit_Float(data_log.gyro_z);
		    UART_Transmit_String(" deg/s\r\n");

			UART_Transmit_String(
		        "\r\n"
		        "============================\r\n"
		        "            Reading         \r\n"
		        "============================\r\n"
		    );


			UART_Transmit_String("Latitude: ");
			UART_Transmit_String(read.latitude);
			UART_Transmit_String("\r\n");
			UART_Transmit_String("NS: ");
			UART_Transmit_String(read.ns);
			UART_Transmit_String("\r\n");
			UART_Transmit_String("Longitude: ");
			UART_Transmit_String(read.longitute);
			UART_Transmit_String("\r\n");
			UART_Transmit_String("ew: ");
			UART_Transmit_String(read.ew);
			UART_Transmit_String("\r\n");

		    UART_Transmit_String("ACCEL X: ");
		    UART_Transmit_Float(read.accel_x);
		    UART_Transmit_String(" g\r\n");

		    UART_Transmit_String("ACCEL Y: ");
		    UART_Transmit_Float(read.accel_y);
		    UART_Transmit_String(" g\r\n");

		    UART_Transmit_String("ACCEL Z: ");
		    UART_Transmit_Float(read.accel_z);
		    UART_Transmit_String(" g\r\n");


		    UART_Transmit_String("GYRO X: ");
		    UART_Transmit_Float(read.gyro_x);
		    UART_Transmit_String(" deg/s\r\n");

		    UART_Transmit_String("GYRO Y: ");
		    UART_Transmit_Float(read.gyro_y);
		    UART_Transmit_String(" deg/s\r\n");

		    UART_Transmit_String("GYRO Z: ");
		    UART_Transmit_Float(read.gyro_z);
		    UART_Transmit_String(" deg/s\r\n");
		}
	}
}
