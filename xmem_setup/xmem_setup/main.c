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
	adc_init();
	
	while(1){
		uint8_t x_dir = adc_read(2);
		uint8_t y_dir = adc_read(3);
		printf("X: %u, Y: %u \n\r", x_dir, y_dir);
	}
}
 