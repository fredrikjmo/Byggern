/*
 * timer.c
 *
 * Created: 27.10.2022 13:10:09
 *  Author: fjmo
 */ 
#include "timer.h"
#include "sam.h"
#include <stdio.h>

#define MCK					84000000
#define MCK_CLOCK_DIVISOR	128


void timer_init(void){
	
	// Use TC0 for delay (Peripheral ID27)
	// Use TC1 for interrupt (Peripheral ID28)
	
	// Configure PMC
	// Enable peripheral clock for TC0 (ID27)
	PMC->PMC_PCER0 |= PMC_PCER0_PID27;
	PMC->PMC_PCR |= PMC_PCR_EN;

	REG_TC0_CCR0 = TC_CCR_CLKEN;
	REG_TC0_CMR0 = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ETRGEDG_RISING | TC_CMR_CPCDIS | TC_CMR_WAVE;
	
}

void delay_ms(int delay){
	
	uint32_t count_val = (MCK/MCK_CLOCK_DIVISOR)/1000;
	REG_TC0_RC0 = count_val;
	for (int i = 0; i < delay; i++)
	{
		REG_TC0_CCR0 = TC_CCR_SWTRG;
		while(!(REG_TC0_SR0 & TC_SR_CPCS));
	}
}





//TIOA0 must be set to peripheral B, PB25 (TC0) Maybe unnessecary
//TIOA3 must be set to peripheral B, PB0 (TC1) Maybe unnessecary


// Program TC interrupt before configuring TC

