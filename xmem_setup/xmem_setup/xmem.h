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

#define BASE_ADDRESS 0x1000

void xmem_init ( void );

void xmem_write ( uint8_t data , uint16_t addr );
uint8_t xmem_read ( uint16_t addr );void SRAM_test(void);


#endif /* XRAM_H_ */