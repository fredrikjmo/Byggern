/*
 * OLEDdriver.c
 *
 * Created: 21.09.2022 17:34:44
 *  Author: akilanj
 */ 

#include "OLEDdriver.h"

void write_c( uint8_t data ){
	xmem_write ( data , OLED_COMMAND_BASE_ADDRESS );
}

void oled_init( void )
{
	write_c(0xAE); // display off
	write_c(0xA1); //segment remap
	write_c(0xDA); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xC8); //common output scan direction:com63~com0
	write_c(0xA8); //multiplex ration mode:63
	write_c(0x3F);
	write_c(0xD5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xD9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	write_c(0xDB); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xAD); //master configuration
	write_c(0x00);
	write_c(0xA4); //out follows RAM content
	write_c(0xA6); //set normal display
	write_c(0xAF); // display on
	write_c(0xA7); //inverse dipslay 
}