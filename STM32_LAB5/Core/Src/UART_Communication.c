/*
 * UART_Communication.c
 *
 *  Created on: Dec 9, 2023
 *      Author: DELL
 */

#include "UART_Communication.h"

enum UARTStatus uart = UINIT;
int counter = 300;
uint32_t Data = 0;
uint8_t sendback = 0;
char arr[30];

void UART_Communication_FSM(){
	switch(uart){
		case UINIT:
			if(command_RST){
				uart = RST;
				command_RST = 0;
			}
			break;
		case RST:
			if(sendback){
				HAL_UART_Transmit(&huart2, (uint8_t*)arr,
						strlen(arr), 1000);
			}
			else{
				Data = Sensor_reading();
				HAL_UART_Transmit(&huart2, (uint8_t*)arr,
				sprintf(arr, "!ADC=%d#\r\n", (int)Data), 1000);
			}
			uart = WAIT_3s;
			break;
		case WAIT_3s:
			// finish communication
			if(command_OK){
				uart = UINIT;
				sendback = 0;
				command_OK = 0;
			}
			else{
				counter--;
				if(counter <= 0){
					uart = RST;
					sendback = 1;
					counter = 300;
				}
			}
			break;
		default:
			break;
	}

}
