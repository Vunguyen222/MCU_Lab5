/*
 * Software_timer.c
 *
 *  Created on: 11 thg 12, 2023
 *      Author: DELL
 */

#include "Software_timer.h"

#define DURATION 10

int timer_flag = 0;
int timer_counter = 0;

void setTimer(int time){
	timer_counter = time / DURATION;
	timer_flag = 0;
}

void timer_run(){
	if(timer_counter > 0){
		timer_counter--;
		if(timer_counter <= 0){
			timer_flag = 1;
		}
	}
}






