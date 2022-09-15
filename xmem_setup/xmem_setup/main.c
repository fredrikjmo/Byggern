/*
 * xmem_setup.c
 *
 * Created: 07.09.2022 09:02:38
 * Author : akilanj
 */ 
#include <avr/io.h>
#define F_CPU 4.9152E6

#include <util/delay.h>
#include "xmem.h"
#include "USARTdriver.h"

int main(void)
{
	USART_Init( MYUBRR );
	
	xmem_init();
	SRAM_test();

    while (1) 
    { 
		SRAM_test();
		_delay_ms(1000);

    }
}
 