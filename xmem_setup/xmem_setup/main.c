/*
 * xmem_setup.c
 *
 * Created: 07.09.2022 09:02:38
 * Author : akilanj
 */ 
#include <avr/io.h>
#define F_CPU 4.9152E6

#include <util/delay.h>
#include "XMEMdriver.h"
#include "ADCdriver.h"
#include "USARTdriver.h"

int main(void)
{
	USART_Init( MYUBRR );
	
	xmem_init();
	adc_init();
	
	
	while(1){
		adc_calibrate();
		pos_p p = pos_read();

		//uint8_t adc_l = pos_left_slider();
		//uint8_t adc_r = pos_right_slider();
		
		enum direction dirt = direction_read ();	

		//printf("X: %d, Y: %d  \n\r", p.x_axis, p.y_axis);
		//
		printf("%d \n\r",dirt);


		//printf("L: %u, R: %u \n\r", adc_l, adc_r);
		_delay_ms(10);

		
	}
}
 