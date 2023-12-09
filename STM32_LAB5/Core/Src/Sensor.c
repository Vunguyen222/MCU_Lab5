/*
 * Sensor.c
 *
 *  Created on: Dec 9, 2023
 *      Author: DELL
 */

#ifndef SRC_SENSOR_C_
#define SRC_SENSOR_C_
#include "Sensor.h"

uint32_t Sensor_reading(){
	HAL_GPIO_TogglePin(led_yellow_GPIO_Port, led_yellow_Pin);
	HAL_ADC_Start(&hadc1);
	uint32_t ADC_value = HAL_ADC_GetValue(&hadc1);
	return ADC_value;
}


#endif /* SRC_SENSOR_C_ */
