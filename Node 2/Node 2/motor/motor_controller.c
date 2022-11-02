/*
 * motor_controller.c
 *
 * Created: 26.10.2022 16:46:48
 *  Author: akilanj
 */ 
#include "motor_controller.h"
#include "../timer/timer.h"

uint8_t joystick_horizontal_val = 0;
uint8_t right_slider_val = 0;
uint8_t right_button_val = 0;

#define ENCODER_DATA_MASK   (0xFF << DO0_IDX)
#define MIN_ENCODER_VALUE   0
#define MAX_ENCODER_VALUE   8800

void set_joystick_horizontal_val(uint8_t val) {joystick_horizontal_val = val;}
void set_right_slider_val(uint8_t val) {right_slider_val = val;}
void set_right_button_val(uint8_t val) {right_button_val = val;}

void print_joy_h ( void ){ printf("Joystick Global Value: %d \r\n", joystick_horizontal_val); }

void motor_init(void){
	DAC_init(); 

    // enable PIOC clock so that input can be read on C
	PMC->PMC_PCER0 |= PMC_PCER0_PID13 ;
	PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_PID(13) ;
	
	// Set D to output and C to input
	PIOD->PIO_OER = DIR | EN | SEL | NOT_RST | NOT_IOE ;
	PIOC->PIO_ODR = (DO0 | DO1 | DO2 | DO3 | DO4 | DO5 | DO6 | DO7);
}

void motor_disable_break(uint8_t bool){
	if(bool){
		PIOD->PIO_SODR = PIO_SODR_P9; // Set MJ1_EN high
		return;
	}
	PIOD->PIO_CODR = PIO_CODR_P9; // Set MJ1_EN low

}

void motor_set_direction(uint8_t dir){
	if(dir){
		PIOD->PIO_SODR = PIO_SODR_P10; // Set MJ1_SEL high
		return;
	}
	PIOD->PIO_CODR = PIO_CODR_P10; // Set MJ1_SEL low
	return;
}

void motor_encoder_reset(void){
	PIOD->PIO_CODR = NOT_RST;
	PIOD->PIO_SODR = NOT_RST;
}
	
uint16_t motor_encoder_read(void){

	// Encoder output enable
	PIOD->PIO_CODR = NOT_IOE;
	
	PIOD->PIO_SODR = SEL;// Set SEL = 1
	_delay_us(20);
	uint8_t low_byte = ((PIOC->PIO_PDSR) & (DO0 | DO1 | DO2 | DO3 | DO4 | DO5 | DO6 | DO7)) >> 1;
	
	
	
	PIOD->PIO_CODR = SEL; // Set SEL = 0
	_delay_us(20);
	uint8_t high_byte = ((PIOC->PIO_PDSR) & (DO0 | DO1 | DO2 | DO3 | DO4 | DO5 | DO6 | DO7)) >> 1;
		
	motor_encoder_reset();
	
	uint16_t data = low_byte | (high_byte << 8);
	
	// Encoder output disable
	PIOD->PIO_SODR = NOT_IOE;
	printf("Data: %d \r\n",data);
	return data;
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

	uint32_t digitalspeed = ((percentage))*0x1C ;

	//set conversion reg in DAC
	DACC->DACC_CDR = digitalspeed;	
}


void joystick_horizontal_to_speed(uint32_t joystick_output){
	
	//if((joystick_output > 45) && (joystick_output < 55)){
		//motor_set_speed(0);
	//};

	if(joystick_output > 55){
		motor_set_direction(1);
		motor_set_speed(joystick_output);
	};
	
	if(joystick_output < 55){
		motor_set_direction(0);
		motor_set_speed(joystick_output);
	};
}


void motor_raw_dog(void){
	if (right_slider_val >= 50){
		motor_set_direction(1);
		motor_set_speed((right_slider_val - 50)*2);
		return;
	}
	motor_set_direction(0);
	motor_set_speed((50 - right_slider_val)*2);
	return;
	
}