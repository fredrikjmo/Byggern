/*
 * OLEDdriver.h
 *
 * Created: 21.09.2022 17:34:33
 *  Author: akilanj
 */ 

#ifndef OLEDDRIVER_H_
#define OLEDDRIVER_H_

#include "../XMEM/XMEMdriver.h"

#define OLED_COMMAND_BASE 0x1000
#define OLED_DATA_BASE 0x1200

void OLED_init ( void );

void OLED_write_command ( uint8_t command );

void OLED_write_data ( uint8_t data );

// Recomended by lecturer

void OLED_goto_column ( uint8_t column );

void OLED_goto_page ( uint8_t page );

void OLED_clear_page( uint8_t page );

void OLED_clear_area( uint8_t page, uint8_t from_col, uint8_t to_col );

void OLED_clear_screen( void );

void OLED_goto_pos( uint8_t page, uint8_t column );

void OLED_write_char( char c );

void OLED_print( char* string );

// Drawing functions
void OLED_print_arrow ( uint8_t page, uint8_t column );

void OLED_print_rounded_arrow ( uint8_t page, uint8_t column );


#endif /* OLEDDRIVER_H_ */