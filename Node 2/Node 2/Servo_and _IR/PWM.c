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
	 
	 
	//set channel mode
	// Set clk source = 656250 hz
	REG_PWM_CMR5 |= PWM_CMR_CPRE_MCK_DIV_128;
	REG_PWM_CMR6 |= PWM_CMR_CPRE_MCK_DIV_128;
	
	//Set Period = CPRD/21 Mhz
	// CPRD = 0x3345 => T=20 ms
	REG_PWM_CPRD5 |= 0x3345;
	REG_PWM_CPRD6 |= 0x3345;
	
	//Set duty Cycle = 1 - CDTY/CPRD
	//CDTY = 0x30F5 => d =  0.9 ms
	//CDTY = 0x2DE2 => d =  2.1 ms
	
	REG_PWM_CDTY5 |= 0x30F5;
	REG_PWM_CDTY6 |= 0x2DE2;
	
	PWM->PWM_ENA |= PWM_ENA_CHID5;
	PWM->PWM_ENA |= PWM_ENA_CHID6;

	
}

void PWM_update_dutycycle(uint32_t percentage){
	
	REG_PWM_CDTYUPD5 = ((100 - percentage)*13124)/100;

	REG_PWM_CDTYUPD6 = ((100 - percentage)*13124)/100;

	
}


