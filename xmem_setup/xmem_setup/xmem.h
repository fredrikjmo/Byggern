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

void xmem_init ( void );

void adc_init ( void );

void adc_sample( void );

void adc_calibrate( void );

uint8_t adc_read ( uint8_t channel );

void xmem_write ( uint8_t data , uint16_t addr );
uint8_t xmem_read ( uint16_t addr );void SRAM_test(void);


#endif /* XRAM_H_ */