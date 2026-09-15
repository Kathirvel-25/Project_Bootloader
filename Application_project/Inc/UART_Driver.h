/*
 * UART_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_
#include "Nucleo_Driver.h"



#define Tx  2U
#define Rx  3U

void UART_Init(void);
void UART_Tarnsmit_Char(char c);
void UART_Transmit_String(char *str);
void UART_Transmit_Int(int32_t value);
void UART_Transmit_Hex(uint8_t data);
void UART_Transmit_Float(float value);


#endif /* UART_DRIVER_H_ */
