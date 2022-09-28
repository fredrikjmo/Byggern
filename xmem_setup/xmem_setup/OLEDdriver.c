/*
 * OLEDdriver.c
 *
 * Created: 21.09.2022 17:34:44
 *  Author: akilanj
 */ 

#include "OLEDdriver.h"
#include "fonts.h"
#include <stdio.h>
#include <string.h>

void OLED_init( void )
{
	OLED_write_command(0xAE); // display off
	OLED_write_command(0xA1); //segment remap
	OLED_write_command(0xDA); //common pads hardware: alternative
	OLED_write_command(0x12);
	OLED_write_command(0xC8); //common output scan direction:com63~com0
	OLED_write_command(0xA8); //multiplex ration mode:63
	OLED_write_command(0x3F);
	OLED_write_command(0xD5); //display divide ratio/osc. freq. mode
	OLED_write_command(0x80);
	OLED_write_command(0x81); //contrast control
	OLED_write_command(0x50);
	OLED_write_command(0xD9); //set pre-charge period
	OLED_write_command(0x21);
	OLED_write_command(0x20); //Set Memory Addressing Mode
	OLED_write_command(0x02);		// Set Page addressing
	OLED_write_command(0xDB); //VCOM deselect level mode
	OLED_write_command(0x30);
	OLED_write_command(0xAD); //master configuration
	OLED_write_command(0x00);
	OLED_write_command(0xA4); //out follows RAM content
	OLED_write_command(0xA6); //set normal display
	OLED_write_command(0xAF); // display on
	
	fdevopen(OLED_write_char, NULL);
}

void OLED_write_command( uint8_t command ){
	volatile char * ext_mem = ( char *) OLED_COMMAND_BASE;
	ext_mem [ 0 ]= command ;

}

void OLED_write_data ( uint8_t data ){
	volatile char * ext_mem = ( char *) OLED_DATA_BASE ;
	ext_mem [ 0 ]= data ;
}

void OLED_reset( void ){
	
}

void OLED_home( void ){
	
}

void OLED_goto_page( uint8_t page ){
	OLED_write_command( 0xB0 + page ); // Set page
	
}

void OLED_clear_page( uint8_t page ){
	OLED_goto_page( page );
	for ( uint8_t i = 0; i < 128; i++){
		OLED_write_data(0);
	}
}

void OLED_clear_area( uint8_t page, uint8_t from_col, uint8_t to_col ){
	OLED_goto_pos( page, from_col );
	for ( uint8_t i = from_col; i < to_col; i++){
		OLED_write_data(0);
	}
}

void OLED_clear_screen( void ){
	for ( uint8_t i = 0; i < 8; i++){
		OLED_clear_page( i );
	}
}

void OLED_goto_column ( uint8_t column ){
	OLED_write_command(0x10 + column / 16); // Set column high address
	OLED_write_command(0x00 + column % 16); // Set column low address
}

void OLED_goto_pos( uint8_t page, uint8_t column ){
	OLED_goto_page( page );
	OLED_goto_column( column );
}


void OLED_write_char( char c ){
	
	for (uint8_t i = 0; i < 8; i++){
		OLED_write_data(pgm_read_byte(&(font8[c-32][i])));
	}
	
}
	
void OLED_print( char* string ){
	for ( int i = 0 ; i < strlen(string) ; i++ ){
		OLED_write_char(string[i]);
	}
	
}

void OLED_set_brightness(uint8_t lvl ){
	
}

void OLED_print_arrow( uint8_t page, uint8_t column ){
	OLED_goto_pos( page , column );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b01111110 );
	OLED_write_data ( 0b00111100 );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b00000000 );
}


void OLED_print_penis( uint8_t page, uint8_t column ){
	OLED_goto_pos( page , column );
	OLED_write_data ( 0b01100110 );
	OLED_write_data ( 0b11111111 );
	OLED_write_data ( 0b11111111 );
	OLED_write_data ( 0b01111110 );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b00011000 );
	OLED_write_data ( 0b00111100 );
	OLED_write_data ( 0b00111100 );
	OLED_write_data ( 0b00011000 );
}

