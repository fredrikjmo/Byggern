/*
 * servoControl.c
 *
 * Created: 26.10.2022 10:47:45
 *  Author: akilanj
 */ 

#include "servocontrol.h"


void set_servo_posistion(uint32_t joystick_percentage){
	
	uint32_t dutyCycle = joystick_percentage/20 + 5;
	
	printf("dutyculce %d \n\r", dutyCycle);
	
	
	PWM_update_dutycycle(dutyCycle);
	
}
