/*
 * TestUartInterface.c
 *
 * Created: 31.08.2022 17:50:45
 * Author : fjmo
 */ 
#include "USARTdriver.h"
#include <avr/io.h>
#include <stdio.h>

#define F_CPU 4.9152E6
#include <util/delay.h>


int main(void)
{
	USART_Init ( MYUBRR );
	while (1)
	{
		printf("Hei Luan!!\n");
		
		_delay_ms(100);
	}
	

	return 0;
}

