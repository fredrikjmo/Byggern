/*
 * PWM.c
 *
 * Created: 19.10.2022 09:02:54
 *  Author: akilanj
 */ 

#include "PWM.h"

void PWM_init(void){
	
	//enable PWM in PMC
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	
	//Select functionality of PIO-pis, on PC19 - (pin 44) and PC18 - (pin 45)
	//choosing PWM channel H5 and H6
	
	//PIO disable  
	PIOC->PIO_PDR |= PIO_PDR_P19;
	PIOC->PIO_PDR |= PIO_PDR_P18;	
	
	//PWM peripheral select
	PIOC->PIO_ABSR |= PIO_ABSR_P19;
	PIOC->PIO_ABSR |= PIO_ABSR_P18;
	

	
	//Set PWM Clk = MCK = 84 Mhz
	 
	 
	//set channel mode
	// Set clk source = 21 Mhz
	REG_PWM_CMR5 |= PWM_CMR_CPRE_MCK_DIV_4;
	REG_PWM_CMR6 |= PWM_CMR_CPRE_MCK_DIV_4;
	
	//Set Dualslope PWM mode?	
	

	//Set Period = CPRD/21 Mhz
	REG_PWM_CPRD5 |= 0x5;
	REG_PWM_CPRD6 |= 0x5;
	
	//Set duty Cycle = (period - 1/srcclk * CDTY)/period
	
	REG_PWM_CDTY5 |= 0x2;
	REG_PWM_CDTY6 |= 0x2;
	
	PWM->PWM_ENA |= PWM_ENA_CHID5;
	PWM->PWM_ENA |= PWM_ENA_CHID6;

	
	
	
	
	
	
	
	
	 
	
	//MCK 84
	
	
	
	//dual slope peroide mode
	
	
	
	
	
	//enable PWM in PMC
	
	//set waveform polartity
	
}