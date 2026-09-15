/*
 * GPS_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef GPS_DRIVER_H_
#define GPS_DRIVER_H_
#include "Nucleo_Driver.h"
#include "UART_Driver.h"
#include "logdata.h"
#include "string.h"


#define Tx_GPS  9U
#define Rx_GPS  10U


void GPS_UART_Init(void);
uint8_t GPS_UART_Receive(void);
char* ProcessData(uint8_t data);

#endif /* GPS_DRIVER_H_ */
