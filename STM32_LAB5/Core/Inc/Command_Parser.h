/*
 * Command_Parser.h
 *
 *  Created on: Dec 9, 2023
 *      Author: DELL
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_
#include "main.h"

extern uint8_t command_OK;
extern uint8_t command_RST;
extern uint8_t buffer_flag;
extern uint8_t temp;

enum CommandState {
	INIT, READ_EXCLAM, READ_R, READ_S, READ_T, READ_HASTAG,
	READ_O, READ_K, INVALID_COMMAND, READ_NEWLINE
};

void Command_Parser_FSM();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *);

#endif /* INC_COMMAND_PARSER_H_ */
