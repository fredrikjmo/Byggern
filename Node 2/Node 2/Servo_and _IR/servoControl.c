/*
 * servoControl.c
 *
 * Created: 26.10.2022 10:47:45
 *  Author: akilanj
 */ 

#include "servocontrol.h"
#include <stdio.h>


void set_servo_posistion(uint32_t joystick_percentage){
	
	printf("joystick: %d \n\r",joystick_percentage);
	
	
	uint32_t dutyCycle = (100-joystick_percentage)/20 + 5;
	printf("duty    : %d \n\r",dutyCycle);
	
	//printf("dutyculce %d \n\r", dutyCycle);
	
	
	PWM_update_dutycycle(dutyCycle);
	
}
