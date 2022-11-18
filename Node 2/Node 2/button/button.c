/*
 * button.c
 *
 * Created: 02.11.2022 13:23:27
 *  Author: akilanj
 */ 
#include "button.h"
#include "sam.h"


void button_init(void){
	PIOC->PIO_OER = PIO_OER_P12; // Output enable on PC19 and PA20

}
void set_button (uint8_t val){
	if(val){
		PIOC->PIO_CODR = PIO_SODR_P12; // set btn value 
		
	} else {
		PIOC->PIO_SODR = PIO_SODR_P12; // clear btn value 
	}
}