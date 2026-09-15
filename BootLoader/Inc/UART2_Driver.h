/*
 * UART2_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef UART2_DRIVER_H_
#define UART2_DRIVER_H_
#include "Nucleo_Driver.h"



void UART_Init(void);
void UART_Transmit_Char(char c);
void UART_Transmit_u32(uint32_t val);
void UART_Transmit_string(char *str);
char UART_Receive_char(void);
int  UART_Receive_Timeout(uint8_t *data, uint32_t timeout);

#endif /* UART2_DRIVER_H_ */
