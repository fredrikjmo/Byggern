/*
 * pid.c
 *
 * Created: 02.11.2022 09:09:14
 *  Author: akilanj
 */ 

#include "pid.h"
#include "../timer/timer.h"
#include "sam.h"
#include "../motor/motor_controller.h"

static volatile int e = 0;
static volatile int e_pri = 0;
static volatile int e_i = 0;
static volatile int u = 0;

TC1_Handler(){
	REG_TC0_SR1;
	pid_update_e();
}

void pid_update_e (void){
	e_pri = e;
	e_i += e;
	uint16_t encoder_val = motor_encoder_read();
	if(encoder_val > 10000) encoder_val = 0;
	e = get_joystick_horizontal_val()-(100-(encoder_val*100)/9010);
}

void pid_update_u (void){
	u = K_p*e + (e_i*K_i*T_ms)/1000;

}

int pid_get_u (void){
	pid_update_u();
	return u;
}