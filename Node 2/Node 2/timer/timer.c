
/*
 * timer.c
 *
 * Created: 28.10.2022 14:45:41
 *  Author: fjmo
 */ 

#include "timer.h"
#include "sam.h"
#include <stdio.h>

void timer_init( void ){	
	// Enable clock for TC0 in MPC

	
	PMC->PMC_PCR |= PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_EN;
	PMC->PMC_PCER0 |= PMC_PCER0_PID27;
	
	REG_TC0_CMR0 |= TC_CMR_WAVE;
	REG_TC0_CMR0 |= TC_CMR_CPCSTOP;
	REG_TC0_CCR0 |= TC_CCR_CLKEN;


}

void delay_ms( int delay ){

	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK3;
	REG_TC0_RC0 = 2625;

	for (int i = 0; i < delay; i++){
		// Start the clock
		REG_TC0_CCR0 |= TC_CCR_SWTRG;
		while (!(REG_TC0_SR0 & TC_SR_CPCS));
	}
}

void delay_us( int delay ){
	
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK1;
	REG_TC0_RC0 = 41;

	for (int i = 0; i < delay; i++){
		// Start the clock
		REG_TC0_CCR0 |= TC_CCR_SWTRG;
		while (!(REG_TC0_SR0 & TC_SR_CPCS));
	}
}