/*
 * goal.c
 *
 * Created: 26.10.2022 14:02:38
 *  Author: akilanj
 */ 

#include "ADC.h"
#include "goal.h"
#include <stdio.h>

uint8_t goal ( void ){
	uint32_t ir_value = ADC_read();
	//printf("IR_VAL: %d \n\r", ir_value);
	if (ir_value < GOAL_THRESHOLD){
		return 1;}
	return 0;
}