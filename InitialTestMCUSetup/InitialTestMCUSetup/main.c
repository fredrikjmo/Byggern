/*
 * InitialTestMCUSetup.c
 *
 * Created: 31.08.2022 17:41:45
 * Author : fjmo
 */ 

#define F_CPU 4.9152E6
#include <util/delay.h>

#include <avr/io.h>
#include <stdint.h>


int main(void)
{
    /* Replace with your application code */
    DDRA |= (1<< DDA0 );
	while (1) 
    {
		PORTA ^= (1 << PA0);
		_delay_ms(2000);
    }
}


 
