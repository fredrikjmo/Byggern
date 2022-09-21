/*
 * xram.h
 *
 * Created: 07.09.2022 09:21:44
 *  Author: akilanj
 */ 


#ifndef XMEM_H_
#define XMEM_H_

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>

#define F_CPU 4.9152E6

#include <util/delay.h>

#define BASE_ADDRESS 0x1000

extern uint8_t m_max_x_value;
extern uint8_t m_min_x_value;
extern uint8_t m_middle_x_value;

extern uint8_t m_max_y_value;
extern uint8_t m_min_y_value;
extern uint8_t m_middle_y_value;

typedef enum direction
	{right, 
	left,
	up, 
	down,
	neutral}direction;

typedef struct pos_p{
	int8_t x_axis;
	int8_t y_axis;
}pos_p ;


void xmem_init ( void );

void adc_init ( void );

void adc_sample( void );

void adc_calibrate( void );

uint8_t adc_read ( uint8_t channel );

void xmem_write ( uint8_t data , uint16_t addr );
uint8_t xmem_read ( uint16_t addr );void SRAM_test(void);pos_p pos_read(void);uint8_t pos_left_slider(void);uint8_t pos_right_slider(void);direction direction_read (void); 


#endif /* XRAM_H_ */