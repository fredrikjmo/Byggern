/*
 * servoControl.c
 *
 * Created: 26.10.2022 10:47:45
 *  Author: akilanj
 */ 

#include "servocontrol.h"
#include <stdio.h>


void set_servo_posistion(uint32_t joystick_percentage){
		
	uint32_t dutyCycle = (100-joystick_percentage)/20 + 5;
		
	PWM_update_dutycycle(dutyCycle);
	
}
