/*
 * button.c
 *
 * Created: 28.09.2022 11:11:48
 *  Author: akilanj
 */ 
#include "button.h"
#include <avr/io.h>

void button_init ( void ){
	DDRB |= (0<<DDB0); // Set Data Direction PB2 to Read (input). Used for button on joystick
}

uint8_t button_joystick_read ( void ) {
	return (PINB & 1<<PINB0); // Return value of PIN B2
}