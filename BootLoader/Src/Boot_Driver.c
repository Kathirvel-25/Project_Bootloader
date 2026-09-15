/*
 * Boot_Driver.c
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */


#include "Boot_Driver.h"
#include "UART2_Driver.h"

typedef void(* application_function_t)(void);

int ApplicationisValid(void)
{

	uint32_t stack_addr;
	uint32_t reset_addr;

	stack_addr = *(volatile uint32_t*)APP_ADDR;
	reset_addr = *(volatile uint32_t*)(APP_ADDR + 4U);

    UART_Transmit_string("STACK: ");
    UART_Transmit_u32(stack_addr);
    UART_Transmit_string("\r\n");

    UART_Transmit_string("RESET: ");
    UART_Transmit_u32(reset_addr);
    UART_Transmit_string("\r\n");

	if(stack_addr < 0x20000000UL) return 0;
	if(stack_addr > 0x20020000UL) return 0;

	if(reset_addr < APP_ADDR) return 0;
	if(reset_addr >= APP_ENDADDR) return 0;
	if((reset_addr & 1U) == 0) return 0;

	return 1;
}


void JumptoApplication(void)
{

	uint32_t stack_addr = *(volatile uint32_t*)APP_ADDR;
	uint32_t reset_addr = *(volatile uint32_t*)(APP_ADDR + 4U);

	application_function_t application;

	disable_interrupts();
	SCB->VTOR = APP_ADDR;
	data_sync_barrier();
	instruction_sync_barrier();

	set_msp(stack_addr);

	application = (application_function_t)reset_addr;
	application();
	while(1)
	{

	}
}
