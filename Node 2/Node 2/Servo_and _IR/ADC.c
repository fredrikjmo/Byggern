/*
 * ADC.c
 *
 * Created: 26.10.2022 11:31:07
 *  Author: fjmo
 */ 
#include "sam.h"

void ADC_init( void ) {

	// Enable periferal clock on PID37 (The ADC)
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;
	
	// Disable IO for P2, which enables Peripheral control of the pin
	 PIOA->PIO_PDR |= PIO_PDR_P2;
	
	// Enable ADC chanel 0
	ADC->ADC_CHER |= ADC_CHER_CH0;
	
	// Enable freerun, sample all the time
	ADC->ADC_MR |= ADC_MR_FREERUN_ON;

	
	// Start ADC-Conversion
	ADC->ADC_CR |= ADC_CR_START;
}

uint32_t ADC_read( void ){
	return ADC->ADC_CDR[0];
}
