/*
 * Command_Parser.c
 *
 *  Created on: Dec 9, 2023
 *      Author: DELL
 */


#include "Command_Parser.h"
#include <string.h>
#define MAX_BUFFER_SIZE 30

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t buffer_index = 0;
uint8_t character = 0;
uint8_t invalid = 0;
uint8_t enterkey = 13;
uint8_t buffer_flag = 0;

uint8_t rst = 0;
uint8_t ok = 0;
uint8_t command_OK = 0;
uint8_t command_RST = 0;

enum CommandState command = INIT;

// add new character to buffer if terminal was typed
// send back this character to terminal
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart -> Instance == USART2){
		buffer[buffer_index++] = temp;
		if(buffer_index == MAX_BUFFER_SIZE) buffer_index = 0;
		buffer_flag = 1;
		HAL_UART_Transmit(&huart2, &temp, 1, 50);
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

void Readnewline(){
	command_OK = ok;
	command_RST = rst;
	if(invalid == 1){
		// print error
		char str[30] = "INVALID COMMAND\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t *)str, sizeof(str), 1000);
		invalid = 0;
	}
	command = INIT;
}

void Command_Parser_FSM(){
	uint8_t i = buffer_index - 1;
	if(i < 0) i = MAX_BUFFER_SIZE - 1;
	character = buffer[i];
	switch(command){
		case INIT:
			rst = ok = 0;
			if(character == '!'){
				command = READ_EXCLAM;
			}
			break;
		case READ_EXCLAM:
			if(character == 'R'){
				command = READ_R;
			}
			else if(character == 'O'){
				command = READ_O;
			}
			else if(character == enterkey){
				invalid = 1;
				Readnewline();
			}
			else command = INVALID_COMMAND;
			break;
		case READ_R:
			if(character == 'S'){
				command = READ_S;
			}
			else if(character == enterkey){
				invalid = 1;
				Readnewline();
			}
			else command = INVALID_COMMAND;
			break;
		case READ_S:
			if(character == 'T'){
				command = READ_T;
			}
			else if(character == enterkey){
				invalid = 1;
				Readnewline();
			}
			else command = INVALID_COMMAND;
			break;
		case READ_T:
			if(character == '#'){
				command = READ_HASTAG;
				// set the RST flag to 1
				rst = 1;
			}
			else if(character == enterkey){
				invalid = 1;
				Readnewline();
			}
			else command = INVALID_COMMAND;
			break;
		case READ_HASTAG:
			if(character == enterkey){
				Readnewline();
			}
			break;
		case READ_O:
			if(character == 'K'){
				command = READ_K;
			}
			else if(character == enterkey){
				invalid = 1;
				Readnewline();
			}
			else command = INVALID_COMMAND;
			break;
		case READ_K:
			if(character == '#'){
				command = READ_HASTAG;
				// set command flag OK to 1
				ok = 1;
			}
			else if(character == enterkey){
				invalid = 1;
				Readnewline();
			}
			else command = INVALID_COMMAND;
			break;
		case INVALID_COMMAND:
			invalid = 1;
			if(character == enterkey){
				Readnewline();
			}
			break;
		default:
			break;
	}
}



