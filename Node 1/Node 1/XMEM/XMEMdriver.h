/*
 * xram.h
 *
 * Created: 07.09.2022 09:21:44
 *  Author: akilanj
 */ 


#ifndef XMEMDRIVER_H_
#define XMEMDRIVER_H_

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>

#define F_CPU 4.9152E6

#include <util/delay.h>

#define BASE_ADDRESS 0x1000

void xmem_init ( void );

void xmem_write ( uint8_t data , uint16_t addr );

uint8_t xmem_read ( uint16_t addr );

void SRAM_test(void);

#endif /* XMEMDRIVER_H_ */