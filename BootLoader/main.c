#include <stdint.h>
#include "UART2_Driver.h"
#include "GPIO_Driver.h"
#include "Flash_Driver.h"
#include "Boot_Driver.h"
#include "CRC32_Driver.h"

#define CMD_START  0x01
#define CMD_DATA   0x02
#define CMD_END    0x03
#define ACK        0x79
#define NACK       0x1F

#define PACKET_SIZE 256U

static uint8_t packet[PACKET_SIZE];


static uint32_t read_u32(const uint8_t *data)
{
	return ((uint32_t)data[0]) |
			((uint32_t)data[1] << 8) |
			((uint32_t)data[2] << 16)|
			((uint32_t)data[3] << 24);
}


static void send_ACK(void)
{
	UART_Transmit_Char(ACK);
}

static void send_NACK(void)
{
	UART_Transmit_Char(NACK);
}

static int receive_exact(uint8_t *buff, uint32_t len)
{
	uint32_t i;
	for(i = 0; i < len; i++)
	   if(!UART_Receive_Timeout(&buff[i], 0xFFFFFFFFUL)) return 0;

	return 1;
}


static int Erase_Application(void)
{
	FLASH_UNLOCK();

	if(FLASH_SECTOR_Erase(4) != FLASH_OK) goto error;
	if(FLASH_SECTOR_Erase(5) != FLASH_OK) goto error;
	if(FLASH_SECTOR_Erase(6) != FLASH_OK) goto error;
	if(FLASH_SECTOR_Erase(7) != FLASH_OK) goto error;

	FLASH_LOCK();
	return 1;
error:
   FLASH_LOCK();
   return 0;
}


static int Receive_Frimware(void)
{
	uint8_t command;

	uint32_t firmware_size;
	uint32_t calculated_crc;
	uint32_t excepted_crc;

	uint32_t received = 0;
	uint32_t addr = APP_ADDR;

	UART_Transmit_string("Waiting for the firmware....\r\n");

	/*  Starting section */

	while(1){
		command = UART_Receive_char();

		if(command == CMD_START)
		{
//			UART_Transmit_string("START RECEIVED\r\n");
			break;
		}
	}

	if(!receive_exact(packet, 8U))
	{
//		UART_Transmit_string("Starting crc and size Failed...\r\n");
		send_NACK();
		return 0;
	}

	firmware_size = read_u32(&packet[0]);
	excepted_crc = read_u32(&packet[4]);

//	UART_Transmit_string("SIZE: ");
//	UART_Transmit_u32(firmware_size);
//	UART_Transmit_string("\r\n");
//
//	UART_Transmit_string("CRC: ");
//	UART_Transmit_u32(excepted_crc);
//	UART_Transmit_string("\r\n");


	if(firmware_size == 0U)
	{
//		UART_Transmit_string("Firmware  size is less than zero...\r\n");
		send_NACK();
		return 0;
	}
	if(firmware_size > (APP_ENDADDR - APP_ADDR))
	{
//		UART_Transmit_string("Firmware  size is greater than excepted...\r\n");
		send_NACK();
		return 0;
	}

	if(!Erase_Application())
	{
		send_NACK();
		return 0;
	}

	send_ACK();

	/*    data section   */

	while(received < firmware_size)
	{
		uint32_t len;
		uint32_t packet_crc;
		uint32_t Calculated_packet_crc;
		uint8_t crc_bytes[4];

		command = UART_Receive_char();

		if(command != CMD_DATA)
		{
			UART_Transmit_string("Data Command Failed..\r\n");
			send_NACK();
			return 0;
		}

		if(!receive_exact(packet, 4U))
		{
			UART_Transmit_string("Packet Size received Error..\r\n");
			send_NACK();
			return 0;
		}

		len = read_u32(packet);

		if(len == 0U || len > PACKET_SIZE)
		{
			UART_Transmit_string("Packet size is Error...\r\n");
			send_NACK();
			return 0;
		}
		if((received + len) > firmware_size)
		{
			send_NACK();
			return 0;
		}
		if(!receive_exact(packet, len))
		{
			UART_Transmit_string("Receving Packet is Problem...\r\n");
			send_NACK();
			return 0;
		}

		if(!(receive_exact(crc_bytes, 4U)))
		{
			UART_Transmit_string("Receving packet crc is Error...\r\n");
			send_NACK();
			return 0;
		}

		packet_crc = read_u32(crc_bytes);
		Calculated_packet_crc = crc32(packet, len);

		if(packet_crc != Calculated_packet_crc)
		{
			UART_Transmit_string("Transmitted and Received packet crc Error");
			send_NACK();
			return 0;
		}

		FLASH_UNLOCK();

		if(FLASH_Write(addr, packet, len) != FLASH_OK)
		{
			UART_Transmit_string("Flash Write Error...\r\n");
			send_NACK();
			return 0;
		}

		FLASH_LOCK();
		addr += len;
		received += len;
		send_ACK();
	}

	/* END Section */

	command = UART_Receive_char();

	if(command != CMD_END)
	{
		UART_Transmit_string("End command Error...\r\n");
		send_NACK();
		return 0;
	}

	calculated_crc = crc32((const uint8_t *)APP_ADDR, firmware_size);

	if(calculated_crc != excepted_crc)
	{
		UART_Transmit_string("Final crc Error...\r\n");
		send_NACK();
		return 0;
	}
	send_ACK();
	return 1;
}


int main(void)
{

	UART_Init();
	GPIO_Init();

    UART_Transmit_string(
        "\r\n"
        "============================\r\n"
        " STM32F401 BARE METAL BL\r\n"
        "============================\r\n"
    );

    UART_Transmit_string("Checking application...\r\n");



    if(Button_pressed()){

    	UART_Transmit_string("Update Mode...\r\n");

    	if(Receive_Frimware())
    	{
    		UART_Transmit_string("Update Finished....\r\n");

    		if(ApplicationisValid())
    		{
    			UART_Transmit_string("Application is valid");

    			for(volatile uint32_t i = 0; i < 5000000U; i++){}

    			JumptoApplication();
    		}

    	}

    }


    if(ApplicationisValid()){

    	UART_Transmit_string("Application Found\r\n");
    	JumptoApplication();
    }

    UART_Transmit_string("No valid Application");

	while(1)
	{
		Toogle_LED();

        for (volatile uint32_t i = 0; i < 500000U; i++){}
	}
}
