/*
 * UART_Communication.h
 *
 *  Created on: Dec 9, 2023
 *      Author: DELL
 */

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_
#include "main.h"
#include "Command_Parser.h"
#include "Sensor.h"
#include <string.h>
#include <stdio.h>

enum UARTStatus{
	UINIT, RST, WAIT_3s, OK
};

void UART_Communication_FSM();

#endif /* INC_UART_COMMUNICATION_H_ */
