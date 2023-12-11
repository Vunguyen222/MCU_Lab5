/*
 * Software_timer.h
 *
 *  Created on: 11 thg 12, 2023
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#include "main.h"

extern int timer_flag;
extern int timer_counter;

void setTimer(int);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
