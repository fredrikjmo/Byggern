/*
 * motor_controller.c
 *
 * Created: 26.10.2022 16:46:48
 *  Author: akilanj
 */ 
#include "motor_controller.h"

void motor_init(void){
	
	PIOD->PIO_OER = PIO_OER_P2 | PIO_OER_P9 | PIO_OER_P10 ; // Output enable on MJ1_EN, MJ1_SEL and MJ1_DIR
}

void motor_disable_break(uint8_t bool){
	if(bool){
		PIOD->PIO_SODR |= PIO_SODR_P2; // Set MJ1_EN high
		return;
	}
	PIOD->PIO_SODR &= ~PIO_SODR_P2; // Set MJ1_EN low

}

//void motor_set_speed(uint8_t speed){
	//if(speed){
		//PIOD->PIO_SODR |= PIO_SODR_P2; // Set MJ1_EN high
		//return;
	//}
	//PIOD->PIO_SODR &= ~PIO_SODR_P2; // Set MJ1_EN low
	//return;
//}

void motor_set_direction(uint8_t dir){
	if(dir){
		PIOD->PIO_SODR |= PIO_SODR_P9; // Set MJ1_SEL high
		return;
	}
	PIOD->PIO_SODR &= ~PIO_SODR_P9; // Set MJ1_SEL low
	return;
}

void DAC_init(void){
	
	//set perifiral clk on PMC
	
	// Enable peripheral clock on PID38 (DACC)
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	
	// Disable IO for PB16, which enables Peripheral control of the pin
	PIOB->PIO_PDR |= PIO_PDR_P16;
	
	
	//set DAC Mode
	
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_MR |= DACC_MR_WORD_HALF;
	
	//Enable channel 1
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
	
	
}


void motor_set_speed(uint32_t percentage){
	
	DAC_init();
	
	uint32_t digitalspeed = ((percentage)/100) ;
	
	//digitalspeed = percentage;
	
	//set conversion reg in DAC
	DACC->DACC_CDR = digitalspeed;
	printf("digital speed: %d \n\r",digitalspeed);
	
}




void joystick_horizontal_to_speed(uint32_t joystick_output){
	
	//if((joystick_output > 45) && (joystick_output < 55)){
		//motor_set_speed(0);
	//};

	if(joystick_output > 55){
		motor_set_speed(0);
		motor_set_speed(joystick_output);
	};
	
	if(joystick_output < 55){
		motor_set_direction(0);
		motor_set_speed(joystick_output);
	};
}
